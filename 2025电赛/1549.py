'''
    2025电赛E题找A4 UV纸圆心，可以找到圆心和第三个圆圈，帧率 > 25fps。
    控制云台可以基于中心点误差 err_center 进行 PID 控制
    重构版本：职责分离，易维护
    @author…
    @license MIT
    @date 2025.7.30
'''

import os
import cv2
import numpy as np

from maix import camera, display, image, nn, app, time, uart, gpio, pinmap
from maix.ext_dev import pmu

# ─────────────────── CONFIG ───────────────────
crop_padding        = 12
rect_min_limit      = 12
std_from_white_rect = True
circle_num_points   = 50
std_res             = [int(29.7/21*80), 80]
high_res            = 448
model_path          = "/root/models/model_3356.mud"
find_circle         = False
find_laser          = True
cam_buff_num        = 1
device              = "/dev/ttyS0"
laser_state         = 0
show_ai_rect=True   # 是否显示 AI 检测的矩形框
# ─────────────────── 全局 display ───────────────────
disp = display.Display()

def init_system():
    # 模型与相机
    detector = nn.YOLOv5(model=model_path, dual_buff=True)
    cam = camera.Camera(high_res, high_res,
                        detector.input_format(),
                        buff_num=cam_buff_num)
    # 串口
    serial = uart.UART(device, 115200)
    serial.write_str("hello world\n")
    # 电量监控
    pwr = pmu.PMU("axp2101")
    # 激光控制引脚
    pinmap.set_pin_function("A15", "GPIOA15")
    laser_sw = gpio.GPIO("GPIOA15", gpio.Mode.OUT)
    return detector, cam, serial, pwr, laser_sw

def get_blob_score(blob):
    x, y, w, h = blob[0], blob[1], blob[2], blob[3]
    pixels = blob[4]
    if w == 0 or h == 0:
        return 0

    aspect_ratio = w / h
    bounding_area = w * h
    fill_ratio = pixels / bounding_area if bounding_area != 0 else 0
    aspect_ratio_diff = abs(aspect_ratio - 1) + 1e-5
    return fill_ratio / aspect_ratio_diff
def find_laser_point(img, img_ori):
    threshold = [[81, 100, -69, 34, -76, 27]]
    # binary_img = img.binary(threshold, copy=True)
    # binary_img=No
    blobs = img.find_blobs(threshold, x_stride=2, y_stride=2)

    if not blobs:
        return None
    best_blob = max(blobs, key=get_blob_score)
    return best_blob


def process_frame(frame, detector):
    # AI 检测黑框
    ai = frame.resize(detector.input_width(),
                      detector.input_height())
    objs = detector.detect(ai, conf_th=0.5, iou_th=0.45)
    if not objs:
        return frame, None, None, None, None, None

    # 取最大目标裁切
    obj = max(objs, key=lambda o: o.w*o.h)
    w,h = obj.w+2*crop_padding, obj.h+2*crop_padding
    w += w%2; h += h%2
    x = max(0, obj.x-crop_padding)
    y = max(0, obj.y-crop_padding)
    w = min(w, ai.width()-x)
    h = min(h, ai.height()-y)
    crop = ai.crop(x,y,w,h)

    # 透视变换到标准图
    scale = [frame.width()/ai.width(),
             frame.height()/ai.height()]
    img_cv = image.image2cv(frame, False, False)
    # 计算 AI 检测矩形框位置，用于后续统一绘制
    x0 = int(x * scale[0]); y0 = int(y * scale[1])
    w0 = int(w * scale[0]); h0 = int(h * scale[1])
    ai_rect = (x0, y0, w0, h0) if show_ai_rect else None
    # 使用 cv2.approxPolyDP 进行多边形近似，无需 alias
    # 找最外轮廓四点
    gray = crop.to_format(image.Format.FMT_GRAYSCALE)
    bw = cv2.adaptiveThreshold(
        image.image2cv(gray,False,False),
        255, cv2.ADAPTIVE_THRESH_MEAN_C,
        cv2.THRESH_BINARY_INV,27,31)
    if std_from_white_rect:
        h0,w0 = bw.shape[:2]
        m = np.zeros((h0+2,w0+2),np.uint8)
        cv2.floodFill(bw, m, (2,2),255,loDiff=5,upDiff=5)
        cv2.floodFill(bw, m, (w0-2,h0-2),255,loDiff=5,upDiff=5)
        bw = cv2.bitwise_not(bw)
    cnts,_ = cv2.findContours(bw,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    if not cnts:
        return frame, None, None, None, None, None
    lc = max(cnts, key=cv2.contourArea)
    eps = 0.02*cv2.arcLength(lc,True)
    approx = cv2.approxPolyDP(lc, eps, True)
    if len(approx)!=4:
        return frame, None, None, None, None, None

    # 排序 & 计算透视矩阵
    corners = approx.reshape(-1,2).astype(np.float32)
    s = corners.sum(axis=1)
    diff = np.diff(corners,axis=1).reshape(-1)
    rect = np.zeros((4,2),np.float32)
    rect[0]=corners[np.argmin(s)]  # tl
    rect[2]=corners[np.argmax(s)]  # br
    rect[3]=corners[np.argmax(diff)] # bl
    rect[1]=corners[np.argmin(diff)] # tr
    rect[:,0] = rect[:,0]*scale[0] + x*scale[0]
    rect[:,1] = rect[:,1]*scale[1] + y*scale[1]
    # 边界尺寸检查，避免透视变换奇异矩阵
    minW = min(rect[1][0] - rect[0][0], rect[2][0] - rect[3][0])
    minH = min(rect[3][1] - rect[0][1], rect[2][1] - rect[1][1])
    if minW <= rect_min_limit or minH <= rect_min_limit:
        return frame, None, None, None, None, ai_rect
    dst = np.array([[0,0],
                    [std_res[0]-1,0],
                    [std_res[0]-1,std_res[1]-1],
                    [0,std_res[1]-1]],np.float32)
    M = cv2.getPerspectiveTransform(rect, dst)
    M_inv = np.linalg.inv(M)
    std_cv = cv2.warpPerspective(img_cv, M,
                                 tuple(std_res))

    # 圆心计算 (标准图中心)
    circle_dist = int(std_res[1] * (0.114942 if std_from_white_rect else 0.095238))
    center = (std_res[0] // 2, std_res[1] // 2)
    # 可选圆检测
    if find_circle and circle_dist > 0:
        gray_std = cv2.cvtColor(std_cv, cv2.COLOR_RGB2GRAY)
        rsize = int(circle_dist * 3)
        x0, y0 = center[0] - rsize // 2, center[1] - rsize // 2
        roi = gray_std[y0:y0 + rsize, x0:x0 + rsize]
        # 在标准图像上绘制 ROI 矩形用于调试
        img_std_maix = image.cv2image(std_cv, False, False)
        img_std_maix.draw_rectangle(x0, y0, rsize, rsize, image.COLOR_ORANGE, 1)
        disp.show(img_std_maix)
        circles = cv2.HoughCircles(roi, cv2.HOUGH_GRADIENT, dp=1.2,
                                   minDist=rsize // 2, param1=100, param2=20,
                                   minRadius=rsize // 4, maxRadius=rsize // 2)
        if circles is not None:
            c0 = np.uint16(np.around(circles))[0, 0]
            center = (c0[0] + x0, c0[1] + y0)
            circle_dist = c0[2]

    # 映射回原图
    std_pt = np.array([[[center[0],center[1]]]],np.float32)
    orig_center = cv2.perspectiveTransform(std_pt, M_inv)[0][0].astype(int)
    err = [orig_center[0]-frame.width()//2,
           orig_center[1]-frame.height()//2]

    # 激光点检测
    orig_laser = None
    if find_laser:
        # 用 Maix image.find_blobs
        img_std = image.cv2image(std_cv, False, False)
        blob = find_laser_point(img_std, frame)
        if blob:
            p = np.array([[[blob.cx(),blob.cy()]]],np.float32)
            orig_laser = cv2.perspectiveTransform(p, M_inv)[0][0].astype(int)

    # 计算并返回圆多边形坐标
    orig_circle_pts = None
    if circle_dist and circle_dist > 0:
        angles = np.linspace(0, 2 * np.pi, circle_num_points, endpoint=False)
        pts = np.stack((center[0] + circle_dist * 3 * np.cos(angles),
                        center[1] + circle_dist * 3 * np.sin(angles)), axis=1).astype(np.float32)
        orig_circle_pts = cv2.perspectiveTransform(pts[np.newaxis], M_inv)[0].astype(np.int32)
    return frame, tuple(orig_center), orig_laser, tuple(err), orig_circle_pts, ai_rect
def circle_pos(cen,len,angle):
    x = cen[0] + len * np.cos(angle)
    y = cen[1] + len * np.sin(angle)
    return (int(x), int(y))
def img_show_and_send(frame, serial, pwr, center, laser_pt, err, circle_pts=None, ai_rect=None):
    # 电量 + FPS
    bat = pwr.get_bat_percent()
    frame.draw_string(10,10,f"Bat:{bat}%",color=image.COLOR_RED)
    fps = time.fps()
    frame.draw_string(10,frame.height()-20,f"FPS:{fps:.1f}",color=image.COLOR_GREEN)
    # 圆心 & 激光点
    if center is not None:
        frame.draw_circle(center[0],center[1],4,image.COLOR_RED,thickness=-1)
    if laser_pt is not None:
        frame.draw_circle(laser_pt[0],laser_pt[1],4,image.COLOR_RED,thickness=2)
    # 圆圈多边形绘制：使用 OpenCV 画多边形
    if circle_pts is not None:
        # 转为 OpenCV 图像
        img_cv = image.image2cv(frame, False, False)
        pts_np = np.round(circle_pts).astype(np.int32)
        cv2.polylines(img_cv, [pts_np], True, (0, 0, 255), 1)
        # 转回 Maix 图像
        frame = image.cv2image(img_cv, False, False)
    # AI 检测矩形框
    if ai_rect is not None:
        x0, y0, w0, h0 = ai_rect
        frame.draw_rect(x0, y0, w0, h0, image.COLOR_GREEN, 1)
    # 发送串口
    if center is not None and laser_pt is not None:
        # data = (*laser_pt, *center, laser_state)
        data=(center[0]-laser_pt[0],center[1]-laser_pt[1],laser_state)
        serial.write_str(",".join(map(str,data))+"\n")
    disp.show(frame)

def main():
    detector, cam, serial, pwr, laser_sw = init_system()
    # 激光点平滑参数
    prev_laser = None
    alpha = 0.3  # EMA权重，越小更新越慢

    while not app.need_exit():
        frame = cam.read()
        out, c, l, e, circle_pts, ai_rect = process_frame(frame, detector)

        # 平滑激光中心坐标
        if l is not None:
            cur = (l[0], l[1])
            if prev_laser is None:
                smooth = cur
            else:
                smooth = (int(prev_laser[0]*alpha + cur[0]*(1-alpha)),
                          int(prev_laser[1]*alpha + cur[1]*(1-alpha)))
            prev_laser = smooth
        else:
            smooth = None

        img_show_and_send(out, serial, pwr, c, smooth, e, circle_pts, ai_rect)

if __name__ == "__main__":
    main()
'''
    2025电赛E题找A4 UV纸圆心，可以找到圆心和第三个圆圈，帧率 > 25fps。
    控制云台可以基于中心点误差 err_center 进行 PID 控制
    @author Neucrack@sipeed & lxo@sieed 协助
    @license MIT
    @date 2025.7.30
'''

from maix import camera, display, image, nn, app, time,uart
from maix import gpio, pinmap, time
disp = display.Display()
img = image.Image(disp.width(), disp.height())
msg = "Loading ..."
size = image.string_size(msg, scale=1.5, thickness=2)
img.draw_string((img.width() - size.width()) // 2, (img.height() - size.height()) // 2, msg, scale=1.5, thickness=2)
disp.show(img)

import cv2
import numpy as np
import os

################################ config #########################################
crop_padding = 12            # 裁切图时的外扩距离
rect_min_limit = 12          # 边框最小距离限制
std_from_white_rect = True   # 从白色区域裁切标准图
circle_num_points = 50       # 圆圈点数量
std_res = [int(29.7 / 21 * 80), 80]  # 标准图分辨率
high_res = 448               # 高分辨率
model_path = "/root/models/model_3356.mud" # 模型路径

find_circle = False          # 是否找圆
cam_buff_num = 1             # 摄像头缓冲
find_laser = True            # 是否找激光点
contrast = 80                # 对比度
###################################################################################
# 初始化模型和摄像头
detector = nn.YOLOv5(model=model_path, dual_buff=True)
cam = camera.Camera(high_res, high_res, detector.input_format(), buff_num=cam_buff_num)
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

def find_laser_point(img, ori):
    threshold = [[81, 100, -69, 34, -76, 27]]
    blobs = img.find_blobs(threshold, x_stride=2, y_stride=2)
    return max(blobs, key=get_blob_score) if blobs else None

#err_center = [0, 0]  # 中心误差
center_pos = [cam.width() // 2, cam.height() // 2]  # 画面中心
def cal_dir(laser,target,state):
    return (target[0]-laser[0],target[1]-laser[1],state)
device = "/dev/ttyS0"
# ports = uart.list_devices() # 列出当前可用的串口

serial = uart.UART(device, 115200)
serial.write_str("hello world")
def uart_send(data):
    content = ",".join(str(x) for x in data) + "\n"
    serial.write_str(content)
def circle_pos(cen,len,angle):
    x = cen[0] + len * np.cos(angle)
    y = cen[1] + len * np.sin(angle)
    return (int(x), int(y))
def oper_laser(state, laser):
    laser.value(state)
while not app.need_exit():
    img = cam.read()
    img_ai = img.resize(detector.input_width(), detector.input_height())
    
    # 检测目标
    objs = detector.detect(img_ai, conf_th=0.5, iou_th=0.45)
    if not objs:
        disp.show(img)
        continue
        
    obj = max(objs, key=lambda o: o.w * o.h)
    w, h = obj.w + crop_padding * 2, obj.h + crop_padding * 2
    w += 1 if w % 2 else 0
    h += 1 if h % 2 else 0
    x, y = max(0, obj.x - crop_padding), max(0, obj.y - crop_padding)
    w = min(w, img_ai.width() - x)
    h = min(h, img_ai.height() - y)
    
    crop_ai = img_ai.crop(x, y, w, h)
    img_ai_scale = [img.width() / img_ai.width(), img.height() / img_ai.height()]
    img_cv = image.image2cv(img, False, False)
    crop_ai_cv = image.image2cv(crop_ai, False, False)

    # 图像处理
    gray = crop_ai.to_format(image.Format.FMT_GRAYSCALE)
    gray_cv = image.image2cv(gray, False, False)
    binary = cv2.adaptiveThreshold(gray_cv, 255, cv2.ADAPTIVE_THRESH_MEAN_C, 
                                 cv2.THRESH_BINARY_INV, 27, 31)

    if std_from_white_rect:
        h, w = binary.shape[:2]
        mask = np.zeros((h + 2, w + 2), np.uint8)
        cv2.floodFill(binary, mask, (2, 2), 255, loDiff=5, upDiff=5, flags=4)
        cv2.floodFill(binary, mask, (w - 2, h - 2), 255, loDiff=5, upDiff=5, flags=4)
        binary = cv2.bitwise_not(binary)

    # 查找轮廓
    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if not contours:
        disp.show(img)
        continue
        
    largest_contour = max(contours, key=cv2.contourArea)
    epsilon = 0.02 * cv2.arcLength(largest_contour, True)
    approx = cv2.approxPolyDP(largest_contour, epsilon, True)
    
    if len(approx) == 4:
        corners = approx.reshape((4, 2))
        rect = np.zeros((4, 2), dtype="float32")
        s = corners.sum(axis=1)
        rect[0] = corners[np.argmin(s)]  # 左上
        rect[2] = corners[np.argmax(s)]  # 右下
        diff = np.diff(corners, axis=1)
        rect[3] = corners[np.argmax(diff)]  # 左下
        rect[1] = corners[np.argmin(diff)]  # 右上
        
        minW = min(rect[1][0] - rect[0][0], rect[2][0] - rect[3][0])
        minH = min(rect[3][1] - rect[0][1], rect[2][1] - rect[1][1])
        
        if minH > rect_min_limit and minW > rect_min_limit:
            # 透视变换
            rect[:, 0] += x
            rect[:, 1] += y
            rect[:, 0] *= img_ai_scale[0]
            rect[:, 1] *= img_ai_scale[1]
            
            dst = np.array([[0, 0], [std_res[0] - 1, 0], 
                          [std_res[0] - 1, std_res[1] - 1], [0, std_res[1] - 1]], dtype="float32")
            M = cv2.getPerspectiveTransform(rect, dst)
            M_inv = np.linalg.inv(M)
            img_std_cv = cv2.warpPerspective(img_cv, M, (std_res[0], std_res[1]))
            
            # 计算圆心和圆圈
            circle_dist = int(img_std_cv.shape[0] * (0.114942 if std_from_white_rect else 0.095238))
            if circle_dist > 0:
                center = [img_std_cv.shape[1] // 2, img_std_cv.shape[0] // 2]
                
                if find_circle:
                    img_std_gray = cv2.cvtColor(img_std_cv, cv2.COLOR_RGB2GRAY)
                    roi_size = int(circle_dist * 3)
                    roi = [center[0] - roi_size//2, center[1] - roi_size//2, roi_size, roi_size]
                    roi_img = img_std_gray[roi[1]:roi[1]+roi[3], roi[0]:roi[0]+roi[2]]
                    
                    circles = cv2.HoughCircles(roi_img, cv2.HOUGH_GRADIENT, dp=1.2,
                                            minDist=roi_size//2, param1=100, param2=20,
                                            minRadius=roi_size//4, maxRadius=roi_size//2)
                    if circles is not None:
                        c = np.uint16(np.around(circles))[0, 0]
                        center = (c[0] + roi[0], c[1] + roi[1])
                        circle_dist = c[2]

                # 计算中心点误差
                std_center = np.array([[center]], dtype=np.float32)
                original_center = cv2.perspectiveTransform(std_center, M_inv)[0][0].astype(np.int32)
                err_center = [original_center[0] - center_pos[0], original_center[1] - center_pos[1]]
                
                # 绘制圆心和圆圈
                radius = circle_dist * 3
                angles = np.linspace(0, 2*np.pi, circle_num_points, endpoint=False)
                circle_pts = np.stack((center[0] + radius*np.cos(angles), 
                                     center[1] + radius*np.sin(angles)), axis=1).astype(np.float32)
                orig_circle_pts = cv2.perspectiveTransform(circle_pts[np.newaxis], M_inv)[0]

                img.draw_circle(original_center[0], original_center[1], 4, image.COLOR_RED, -1)
                cv2.polylines(img_cv, [np.round(orig_circle_pts).astype(np.int32)], 
                             True, (0, 0, 255), 1)

                # 检测激光点并绘制
                if find_laser:
                    laser_blob = find_laser_point(image.cv2image(img_std_cv, False, False), img)
                    if laser_blob:
                        laser_center = np.array([[[laser_blob.cx(), laser_blob.cy()]]], dtype=np.float32)
                        original_laser_point = cv2.perspectiveTransform(laser_center, M_inv)[0][0].astype(int)
                        img.draw_circle(original_laser_point[0], original_laser_point[1], 4, image.COLOR_GREEN, 2)

    disp.show(img)
    fps = time.fps()
    print(f"time: {1000/fps:.2f}ms, fps: {fps:.2f}")
import time
from media.sensor import *
from media.display import *
from media.media import *

from libs.YbProtocol import YbProtocol
from ybUtils.YbUart import YbUart

# 初始化串口与协议
uart = YbUart(baudrate=115200)
pto = YbProtocol()

# 显示分辨率
DISPLAY_WIDTH = 640
DISPLAY_HEIGHT = 480

# 紫蓝色激光点的 LAB 阈值
LASER_THRESHOLD = (85, 100, -18, 71, -45, 19)

def init_sensor():
    sensor = Sensor()
    sensor.reset()
    sensor.set_framesize(width=DISPLAY_WIDTH, height=DISPLAY_HEIGHT)
    sensor.set_pixformat(Sensor.RGB565)
    return sensor

def init_display():
    Display.init(Display.ST7701, width=DISPLAY_WIDTH, height=DISPLAY_HEIGHT, to_ide=True)
    MediaManager.init()

def get_blob_score(blob):
    x, y, w, h = blob[0], blob[1], blob[2], blob[3]
    pixels = blob[4]

    if h == 0 or w == 0:
        return 0  # 无效 blob

    aspect_ratio = w / h
    bounding_area = w * h
    fill_ratio = pixels / bounding_area if bounding_area != 0 else 0
    aspect_ratio_diff = abs(aspect_ratio - 1) + 1e-5  # 越接近1越像正方形/圆

    return fill_ratio / aspect_ratio_diff  # 圆形评分：越高越接近理想圆

def main():
    try:
        sensor = init_sensor()
        init_display()
        sensor.run()

        detect_color = (255, 0, 0)  # 红色框
        clock = time.clock()

        while True:
            clock.tick()
            img = sensor.snapshot()
            
            blobs = img.find_blobs([LASER_THRESHOLD], merge=True, area_threshold=10, pixels_threshold=10)
            
            if blobs:
                # 找到圆形评分最高的那个 blob
                best_blob = max(blobs, key=get_blob_score)
            
                x, y, w, h = best_blob[0], best_blob[1], best_blob[2], best_blob[3]
                cx, cy = best_blob[5], best_blob[6]
            
                img.draw_rectangle((x, y, w, h), thickness=2, color=detect_color)
                img.draw_cross(cx, cy, color=detect_color, thickness=2)
            
                pto_data = pto.get_color_data(x, y, w, h)
                uart.send(pto_data)
                print("发送数据:", pto_data)
            else:
                uart.send(pto.get_color_data(0, 0, 0, 0))
                print("未识别")


            img.draw_string_advanced(0, 0, 30, f'FPS: {clock.fps():.2f}', color=(255, 255, 255))
            Display.show_image(img)

    except Exception as e:
        print("发生错误:", e)
    finally:
        sensor.stop()
        Display.deinit()
        MediaManager.deinit()

if __name__ == "__main__":
    main()

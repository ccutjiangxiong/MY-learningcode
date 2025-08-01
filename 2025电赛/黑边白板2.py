from maix import image, camera, display, time
import numpy as np

cam = camera.Camera(320, 240)
disp = display.Display()

white_thresh = [56, 100, -4, 127, -53, 37]
black_thresh = [7, 29, -50, 12, -64, -4]
frame_count = 0

def polygon_area(corners):
    x = [pt[0] for pt in corners]
    y = [pt[1] for pt in corners]
    return 0.5 * abs(
        x[0]*y[1] + x[1]*y[2] + x[2]*y[3] + x[3]*y[0]
      - y[0]*x[1] - y[1]*x[2] - y[2]*x[3] - y[3]*x[0]
    )

while True:
    img = cam.read()
    binary_img = img.binary([black_thresh], copy=True)
    # binary_img.close(size=1)
    binary_img.erode(size=2)
    binary_img.dilate(size=2)


    rects = binary_img.find_rects(threshold=5000)

    max_area = 0
    target_rect = None

    img_w, img_h = img.width(), img.height()
    margin = 10

    def is_inside_image(corners, margin=10):
        for x, y in corners:
            if x < margin or x > img_w - margin or y < margin or y > img_h - margin:
                return False
        return True

    for rect in rects:
        corners = rect.corners()
        area = polygon_area(corners)

        if area > max_area and is_inside_image(corners):
            max_area = area
            target_rect = rect

    if target_rect:
        corners = target_rect.corners()
        for i in range(4):
            x0, y0 = corners[i]
            x1, y1 = corners[(i + 1) % 4]
            img.draw_line(x0, y0, x1, y1, color=image.COLOR_BLUE, thickness=3)
            binary_img.draw_line(x0, y0, x1, y1, color=image.COLOR_BLUE, thickness=3)

    disp.show(binary_img)

    fps = time.fps()
    print(f"time: {1000/fps:.02f}ms, fps: {fps:.02f}")

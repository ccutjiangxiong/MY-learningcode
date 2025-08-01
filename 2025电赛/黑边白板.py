from PIL.Image import merge
from maix import image, camera, display
cam = camera.Camera(320, 240)
disp = display.Display()

black_thresh = [7, 29, -50, 12, -64, -4]
white_thresh = [36, 73, -9, 54, -51, -8]

while True:
    img = cam.read()
    # 对黑色阈值做二值化，得到区域（白色表示黑色区域）
    binary_img = img.binary([black_thresh], copy=True)

    binary_img.dilate(size=2)
    binary_img.erode(size=2)


    blobs = binary_img.find_blobs([[1, 16777215]], pixels_threshold=5,merge=True,margin=1)


    max_white_count = 0
    target_blob = None

    for blob in blobs:
        x, y, w, h = blob.rect()
        white_count = 0
        black_count = blob.pixels()  # 白色面积（即原图中黑色的面积）
        image_tmp = img.crop(x, y, w, h)

        blk=image_tmp.find_blobs([white_thresh],pixels_threshold=5)
        for b in blk:
            white_count+=b.pixels()
        # 判断白色是否是黑色的 5 倍以上
        if white_count >= 3 * black_count and white_count > max_white_count:
                max_white_count = white_count
                target_blob = blob
        # print(white_count,black_count,white_count/black_count)

    if target_blob:
        x, y, w, h = target_blob.rect()
        img.draw_rect(x, y, w, h, image.COLOR_BLUE, thickness=2)

    fps = time.fps()            # Calculate FPS between last time fps() call and this time call.
                                # | 计算两次 fps 函数调用之间的帧率
    print(f"time: {1000/fps:.02f}ms, fps: {fps:.02f}") # print FPS in console
                                                       # | 在终端打印帧率（FPS）
    # 用原图显示框更直观（也可切回 binary_img）
    disp.show(img)

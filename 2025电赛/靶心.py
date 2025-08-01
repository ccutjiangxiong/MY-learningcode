from maix import camera, display, image, app, time

cam = camera.Camera(320, 240)  # 降低分辨率提高帧率
disp = display.Display()

# 优化后的LAB阈值（红色靶心）
RED_LAB = (49, 61, 9, 48, -29, 7)

while not app.need_exit():
    img = cam.read()
    
    # 颜色分割+圆形度验证
    blobs = img.find_blobs([RED_LAB], area_threshold=100, merge=True)
    valid_rings = [b for b in blobs if 0.7 < (4*3.14*b.area()/(b.perimeter()**2)) < 1.3]
    
    # 生成二值化图像
    binary_img = img.binary([RED_LAB], invert=False)
    
    if valid_rings:
        target = max(valid_rings, key=lambda b: b.area())
        
        # 更精确的圆心计算方法
        cx = target.x() + target.w() // 2  # 使用x坐标+宽度的一半
        cy = target.y() + target.h() // 2  # 使用y坐标+高度的一半
        radius = (target.w() + target.h()) // 4  # 平均半径
        
        # 在图像上绘制靶心标记
        img.draw_circle(cx, cy, radius, color=image.COLOR_RED, thickness=2)
        img.draw_cross(cx, cy, size=15, color=image.COLOR_YELLOW)
        img.draw_string(cx-20, cy-radius-20, "TARGET", color=image.COLOR_GREEN)
        
        # 在二值化图像上也绘制标记（可选）
        binary_img.draw_circle(cx, cy, radius, color=image.COLOR_WHITE, thickness=2)
        binary_img.draw_cross(cx, cy, size=15, color=image.COLOR_WHITE)
    
    # 显示图像（原图或二值图，根据需要选择）
    # disp.show(img)  # 显示原图
    disp.show(binary_img)  # 显示二值图
from maix import camera, display, app, time, image

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

def find_laser_point(img):
    threshold = [[81, 100, -69, 34, -76, 27]]
    # binary_img = img.binary(threshold, copy=True)
    # binary_img=No
    blobs = img.find_blobs(threshold, x_stride=2, y_stride=2)

    if not blobs:
        return None
    best_blob = max(blobs, key=get_blob_score)
    return best_blob

def main():
    cam = camera.Camera(512, 320)
    disp = display.Display()

    while not app.need_exit():
        img = cam.read()
        blob = find_laser_point(img)

        if blob:
            img.draw_rect(blob.x(), blob.y(), blob.w(), blob.h(), color=image.COLOR_GREEN, thickness=1)
            img.draw_circle(blob.cx(), blob.cy(), 5, image.COLOR_RED, thickness=1)
        disp.show(img)

        fps = time.fps()
        print(f"time: {1000/fps:.2f}ms, fps: {fps:.2f}")

if __name__ == "__main__":
    main()

import sys
from itertools import product

# Function to calculate the area of a triangle given three points
def triangle_area(x1, y1, x2, y2, x3, y3):
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0)

def main():
    input = sys.stdin.read
    data = input().split()
    
    # Read the number of points for each puppet
    n1, n2, n3 = map(int, data[:3])
    
    # Read the points for each puppet
    index = 3
    path1 = []
    for _ in range(n1):
        x, y = map(int, data[index:index+2])
        path1.append((x, y))
        index += 2
    
    path2 = []
    for _ in range(n2):
        x, y = map(int, data[index:index+2])
        path2.append((x, y))
        index += 2
    
    path3 = []
    for _ in range(n3):
        x, y = map(int, data[index:index+2])
        path3.append((x, y))
        index += 2
    
    # Calculate the maximum area
    max_area = 0
    for (x1, y1), (x2, y2), (x3, y3) in product(path1, path2, path3):
        max_area = max(max_area, triangle_area(x1, y1, x2, y2, x3, y3))
    
    # Print the result with 10 decimal places
    print(f"{max_area:.10f}")

if __name__ == "__main__":
    main()
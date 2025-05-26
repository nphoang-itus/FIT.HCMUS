import numpy as np

# 01: Nội suy hàm số bằng Spline
x = np.array([2, 4, 7, 8])
y = np.array([2.2, 1.8, 2.7, 3.1])

n = len(x) - 1
h = np.diff(x) # Tính số khoảng h giữa các điểm

A = np.zeros((n - 1, n - 1))
b = np.zeros(n - 1)

for i in range(1, n):
    A[i - 1, i - 1] = 2 * (h[i - 1] + h[i]) # Phần tử đường chéo
    if i - 1 > 0:
        A[i - 1, i - 2] = h[i - 1] # Phần tử dưới đường chéo
    if i < n - 1:
        A[i - 1, i] = h[i] # Phần tử trên đường chéo

    b[i - 1] = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]) # Vế phải của phương trình
    
c = np.zeros(n + 1)
c[1:n] = np.linalg.solve(A, b) # Giải HPTTT Tìm c

b = np.zeros(n)
d = np.zeros(n)

for i in range(n):
    b[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (2 * c[i] + c[i + 1]) / 3
    d[i] = (c[i + 1] - c[i]) / (3 * h[i])

def spline_interpolate(x_query):
    for i in range(n):
        if (x[i] <= x_query <= x[i + 1]):
            dx = x_query - x[i]
            return y[i] + b[i] * dx + c[i] * dx**2 + d[i] * dx**3
    
    return None

x_values = [3, 7.5]
y_values = [spline_interpolate(xq) for xq in x_values]

# for xi, yi in zip(x_values, y_values):
#     print(f"f({xi}) = {yi:.4f}")

# 02: Bình phương nhỏ nhất
x = np.array([2, 4, 7, 8.5, 9.5, 11])
y = np.array([2.2, 4.2, 6.8, 8.1, 9.7, 10.5])

n = len(x)

X = np.vstack((x, np.ones(n))).T # Ma trận thiết kế [[x, 1]]
a, b = np.linalg.lstsq(X, y, rcond=None)[0] # Giải phương trình X * [a, b] = y

x_query = 6
y_query = a * x_query + b

print(f"Hàm nội suy: R(x) = {a:.4f}x + {b:.4f}")
print(f"Giá trị nội suy tại x = {x_query}: f({x_query}) = {y_query:.4f}")
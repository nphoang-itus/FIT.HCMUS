import numpy as np

# 01: Nội suy hàm số bằng Spline
def spline_interpolation(x_data, y_data, x_query):
    """Nội suy hàm số bằng Spline tự nhiên"""
    n = len(x_data) - 1
    h = np.diff(x_data)  # Tính số khoảng h giữa các điểm

    A = np.zeros((n - 1, n - 1))
    b_vec = np.zeros(n - 1)
        
    for i in range(1, n):
        A[i - 1, i - 1] = 2 * (h[i - 1] + h[i])  # Phần tử đường chéo
        if i - 1 > 0:
            A[i - 1, i - 2] = h[i - 1]  # Phần tử dưới đường chéo
        if i < n - 1:
            A[i - 1, i] = h[i]  # Phần tử trên đường chéo

        b_vec[i - 1] = 3 * ((y_data[i + 1] - y_data[i]) / h[i] - (y_data[i] - y_data[i - 1]) / h[i - 1])  # Vế phải của phương trình
        
    c = np.zeros(n + 1)
    c[1:n] = np.linalg.solve(A, b_vec)  # Giải HPTTT Tìm c

    b_coeff = np.zeros(n)
    d = np.zeros(n)

    for i in range(n):
        b_coeff[i] = (y_data[i + 1] - y_data[i]) / h[i] - h[i] * (2 * c[i] + c[i + 1]) / 3
        d[i] = (c[i + 1] - c[i]) / (3 * h[i])

    # Tìm khoảng chứa x_query và tính giá trị nội suy
    for i in range(n):
        if (x_data[i] <= x_query <= x_data[i + 1]):
            dx = x_query - x_data[i]
            return y_data[i] + b_coeff[i] * dx + c[i] * dx**2 + d[i] * dx**3
    
    return None

# 02: Bình phương nhỏ nhất
def least_squares_approximation(x_data, y_data, x_query):
    """Xấp xỉ bằng phương pháp bình phương nhỏ nhất (đường thẳng)"""
    n = len(x_data)

    X = np.vstack((x_data, np.ones(n))).T  # Ma trận thiết kế [[x, 1]]
    a, b = np.linalg.lstsq(X, y_data, rcond=None)[0]  # Giải phương trình X * [a, b] = y

    y_query = a * x_query + b
    
    return y_query, a, b

# Sử dụng hàm Spline
x_spline = np.array([2, 4, 7, 8])
y_spline = np.array([2.2, 1.8, 2.7, 3.1])

x_values = [3, 7.5]
y_values = [spline_interpolation(x_spline, y_spline, xq) for xq in x_values]

for xi, yi in zip(x_values, y_values):
    print(f"Spline - f({xi}) = {yi:.4f}")

# Sử dụng hàm Least Squares
x_ls = np.array([2, 4, 7, 8.5, 9.5, 11])
y_ls = np.array([2.2, 4.2, 6.8, 8.1, 9.7, 10.5])

x_query = 6
y_query, a, b = least_squares_approximation(x_ls, y_ls, x_query)

print(f"Hàm nội suy: R(x) = {a:.4f}x + {b:.4f}")
print(f"Giá trị nội suy tại x = {x_query}: f({x_query}) = {y_query:.4f}")
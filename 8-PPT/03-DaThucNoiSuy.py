import numpy as np

# 01: Xấp xỉ bằng đa thức tổng quát
def polynomial_approximation(x_data, y_data, x_interp):
    """Xấp xỉ bằng đa thức tổng quát sử dụng np.polyfit"""
    coefficients = np.polyfit(x_data, y_data, len(x_data) - 1)
    poly = np.poly1d(coefficients)
    y_interp = poly(x_interp)
    return y_interp

# 02: Nội suy hàm số bằng đa thức Lagrange
def lagrange_interpolation(x_data, y_data, x_interp):
    """Nội suy hàm số bằng đa thức Lagrange"""
    poly = np.polynomial.polynomial.Polynomial.fit(x_data, y_data, deg=len(x_data) - 1)
    y_interp = poly(x_interp)
    return y_interp

# 03: Nội suy hàm số bằng đa thức Newton
def newton_interpolation(x_data, y_data, x_interp):
    """Nội suy hàm số bằng đa thức Newton"""
    coefficients = np.polynomial.polynomial.polyfit(x_data, y_data, len(x_data) - 1)
    poly = np.polynomial.Polynomial(coefficients)
    y_interp = poly(x_interp)
    return y_interp

# Dữ liệu đầu vào
x = np.array([1, 2.2, 3.1, 4])
y = np.array([1.678, 3.267, 2.198, 3.787])
x_interp = 2.5

# Sử dụng các hàm
y1 = polynomial_approximation(x, y, x_interp)
y2 = lagrange_interpolation(x, y, x_interp)
y3 = newton_interpolation(x, y, x_interp)

print(f"Cách 1 - Giá trị tại x = {x_interp} là: {y1}")
print(f"Cách 2 - Giá trị tại x = {x_interp} là: {y2}")
print(f"Cách 3 - Giá trị tại x = {x_interp} là: {y3}")
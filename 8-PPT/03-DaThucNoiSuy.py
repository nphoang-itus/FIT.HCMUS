import numpy as np

# 01: Xấp xỉ bằng đa thức tổng quát
x = np.array([1, 2.2, 3.1, 4])
y = np.array([1.678, 3.267, 2.198, 3.787])

coefficients = np.polyfit(x, y, 3)
poly = np.poly1d(coefficients)

x_interp = 2.5
y_interp = poly(x_interp)

print(f"Giá trị tại x = {x_interp} là: {y_interp}")

# # 02: Nội suy hàm số bằng đa thức Lagrange
poly = np.polynomial.polynomial.Polynomial.fit(x, y, deg=len(x) - 1)
print(f"Giá trị tại x = {x_interp} là: {y_interp}")

# 03: Nội suy hàm số bằng đa thức Newton
coefficients = np.polynomial.polynomial.polyfit(x, y, len(x) - 1)
poly = np.polynomial.Polynomial(coefficients)
print(f"Giá trị tại x = {x_interp} là: {y_interp}")
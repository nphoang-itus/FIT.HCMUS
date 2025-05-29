# 23120264 - Nguyễn Phúc Hoàng - Ca 2
# file đáp án/ file code/ file hình
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

m = 4

def bisection_method(func, a, b, tol, m, max_iter=1000):
    if func(a, m) * func(b, m) > 0:
        print("Loi")
        return None
    
    for i in range(max_iter):
        c = (a + b) / 2
        if abs(func(c, m)) < tol or abs(b - a) < tol:
            return c
        
        if func(a, m) * func(c, m) < 0:
            b = c
        else:
            a = c
    
    return c

def f(x, m):
    return np.exp(m/10 * x) - (m * x**2 + x * np.sin(m/10 * x))

def find_exact_solution(m):
    return bisection_method(f, -1, 0, 1e-12, m)

a, b = -1, 0
tolerance = 1e-3

# (b) Find approximate solution
approx_solution = bisection_method(f, a, b, tolerance, m)

if approx_solution is not None:
    print(f"Nghiệm xấp xỉ là: {approx_solution:.6f}")
    print(f"Kiểm tra f({approx_solution:.6f}) = {f(approx_solution, m):.6e}")
else:
    print("Không tìm được nghiệm trong khoảng đã cho")

print("-" * 60)

# (c) Find exact solution and calculate errors
exact_solution = find_exact_solution(m)

if exact_solution is not None:
    print(f"Nghiệm chính xác là: {exact_solution:.12f}")
    
    # Calculate absolute error
    absolute_error = abs(exact_solution - approx_solution)
    print(f"Sai số tuyệt đối là: {absolute_error:.6e}")
    
    # Calculate relative error
    if exact_solution != 0:
        relative_error = abs((exact_solution - approx_solution) / exact_solution)
        print(f"Sai số tương đối là: {relative_error:.6e}")
    else:
        print("Sai số tương đối: Không xác định (nghiệm chính xác = 0)")
    
    print(f"Kiểm tra f({exact_solution:.12f}) = {f(exact_solution, m):.6e}")

'''
với m = 4
Câu 4 (3.0 điểm). Người ta khảo sát nhiệt độ (◦F) tại một khu vực X tại sao Hỏa sau t giờ kể
từ lúc m AM được mô hình hóa theo công thức
T(t) = 10 + 6 * np.sin((np.pi * t)/18)
(a) Tính xấp xỉ nhiệt độ (◦F) trung bình trong khoảng từ m AM đến m PM sử dụng công thức
tích phân Simpson 3/8 với đoạn chia là ∆t = 0,2.
Nhiệt độ trung bình ≈. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
(b) Thời gian nào (time: 24h) thì nhiệt độ tại khu vực X bằng với nhiệt độ trung bình ở câu (a)?
(Sử dụng phương pháp chia đôi ở câu 1a)
Thời gian là . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
(c) Tìm nghiệm chính xác của câu (a) và nghiệm chính xác của câu (b) dựa trên nghiệm chính xác của câu (a).
Nghiệm chính xác câu (a) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
Nghiệm chính xác câu (b) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
'''
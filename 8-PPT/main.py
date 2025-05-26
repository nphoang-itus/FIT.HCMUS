import numpy as np
import matplotlib.pyplot as plt

# GIẢI PHƯƠNG TRÌNH SIÊU VIỆT

## 01: Hàm triển khai phương pháp chia đôi (bisection method)
def bisection_method(f, a, b, tol = 1e-3, max_iter = 100):
    if f(a) * f(b) >= 0:
        print("Phương pháp chia đôi không được áp dụng vì f(a) và f(b) không cùng dấu.")
        return None

    iter_count = 0
    while (b - a) / 2.0 > tol and iter_count < max_iter:
        iter_count += 1
        mid_point = (a + b) / 2.0
        
        if f(mid_point) == 0:
            return mid_point
        elif f(a) * f(mid_point) > 0:
            a = mid_point
        else:
            b = mid_point
    
    return (a + b) / 2.0

def f(x):
    return x + np.sin(x) - 2

a = 1
b = 1.4
tolerance = 1e-3

root = bisection_method(f, a, b)

# if root is not None:
#     print(f"Nghiệm của phương trình là: {root}")
# else:
    # print(f"Không tìm thấy nghiệm trong khoảng ({a}, {b})")

### Phương pháp chia đôi có in thông tin và vẽ biểu đồ:
def bisection_method_info(f, a, b, Df):
    k = 1
    c_values = []
    fc_values = []
    while True:
        c = (a + b) / 2.0
        fc = f(c)
        c_values.append(c)
        fc_values.append(fc)
        print(f"Iterator {k}: c = {c}, f(c) = {fc}")

        if abs(fc) < Df:
            break
        
        if f(a) * f(c) > 0:
            a = c
        else:
            b = c
        
        k += 1
    
    plt.plot(range(1, k + 1), fc_values, 'ro-')
    plt.xlabel('Iterator (k)')
    plt.ylabel('f(c)')
    plt.title('Bisection Method')
    plt.grid()
    plt.show()
    return c, fc

# root, result = bisection_method_info(f, a, b, Df=1e-3)
# print(f"Nghiệm của phương trình là {root}")


## 02: Phương pháp lặp

def fixed_point_iteration(phi, x0, tol = 1e-3, max_iter = 100):
    x = x0

    for i in range(max_iter):
        x_new = phi(x)
        if abs(x_new - x) < tol:
            return x_new
        x = x_new

    return x

def phi(x):
    return 2 - np.sin(x)

x0 = 1.05
tolerance = 1e-3

root = fixed_point_iteration(phi, x0)
# print(f"Nghiệm của Phương trình là {root}")

## 03 - Phương pháp tiếp tuyến
def tangent_method(f, df, x, Delta_f = 1e-3, max_iter = 100):
    print("=" * 80)
    print(f"{'STT':<5}{'x_0':<12}{'x_n':<12}{'f(x_n)':<15}{'|f(x_n)| <= Δf':<18}{'δx_n':<12}")
    print("=" * 80)
    
    iter_count = 0
    x_prev = x
    
    while np.abs(f(x)) > Delta_f and iter_count < max_iter:
        fx = f(x)
        dfx = df(x)
        x_new = x - fx / dfx
        delta_x = abs(x_new - x)
        check = "✓" if abs(fx) <= Delta_f else "✗"
        
        print(f"{iter_count+1:<5}{x_prev:<12.6f}{x:<12.6f}{fx:<15.6f}{check:<18}{delta_x:<12.6f}")
        
        x_prev = x
        x = x_new
        iter_count += 1
    
    print("=" * 80)
    return x
    
def f(x):
    return x**2 - np.sin(x) - 50

def df(x):
    return 2*x - np.cos(x)

x0 = 2
Df = 1e-3

# root = tangent_method(f, df, x0, Df)

## 04 - Phương pháp dây cung
def chord_method(f, a, b, delta_f = 1e-3, iter_max = 100):
    if f(a) * f(b) > 0:
        print(f"Thuật toán không thể thực hiện được với f({a}) và f({b}) cùng dấu")
        return None

    print("=" * 80)
    print(f"{'STT':<5}{'a':<12}{'b':<12}{'c':<12}{'f(c)':<12}{'f(c) < delta_f':<7}{'sigma_c':<5}")
    print("=" * 80)

    iter_count = 1
    
    c = a - f(a) * (b - a)/(f(b) - f(a))
    fc = f(c)

    while np.abs(f(c)) >= delta_f and iter_count < iter_max:
        c_new = a - f(a) * (b - a) / (f(b) - f(a))
        fc = f(c)

        check = "true" if np.abs(fc) <= delta_f else "false"

        print(f"{iter_count:<5}{a:<12.4f}{b:<12.4f}{c:<12.4f}{fc:<12.4f}{check:<12}{np.abs(c_new - c):<5.4f}")

        if f(a) * f(c) < 0:
            b = c
        else:
            a = c

        c = c_new
        iter_count += 1

    print("=" * 80)
    return c

def f(x):
    return x**2 - np.sin(x) - 50

a, b, delta_f = 0, 8, 3e-3

root = chord_method(f, a, b, delta_f)

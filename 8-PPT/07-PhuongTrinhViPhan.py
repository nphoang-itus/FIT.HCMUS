import numpy as np

def f(x, y):
    return x + y

# 01: Phương pháp lặp với bước thích ứng
def adaptive_step_method(func, x0, y0, x_end, delta_y=0.001, h_initial=0.1):
    """Phương pháp lặp với bước thích ứng"""
    h = h_initial
    x_values = [x0]
    y_values = [y0]

    while x_values[-1] < x_end:
        x_n = x_values[-1]
        y_n = y_values[-1]

        y_start = y_n + h * func(x_n, y_n)
        y_next = y_n + (h/2) * (func(x_n, y_n) + func(x_n + h, y_start))
        error = abs((y_next - y_n) / y_next) if y_next != 0 else abs(y_next - y_n)
        
        if error > delta_y:
            h /= 2
            continue

        x_values.append(x_n + h)
        y_values.append(y_next)

        if error < delta_y / 10:
            h *= 2

    return np.array(x_values), np.array(y_values)

# 02: Phương pháp Euler
def euler_method(func, x0, y0, x_end, h):
    """Phương pháp Euler"""
    x_values = np.arange(x0, x_end + h, h)
    y_values = np.zeros_like(x_values)
    y_values[0] = y0

    for i in range(len(x_values) - 1):
        y_values[i + 1] = y_values[i] + h * func(x_values[i], y_values[i])

    return x_values, y_values

# 03: Phương pháp Runge-Kutta với bậc tùy chọn
def runge_kutta(func, x0, y0, x_end, h, order=4):
    """Phương pháp Runge-Kutta với bậc tùy chọn (2, 3, hoặc 4)"""
    x_values = np.arange(x0, x_end + h, h)
    y_values = np.zeros_like(x_values)
    y_values[0] = y0

    for i in range(len(x_values) - 1):
        x_i, y_i = x_values[i], y_values[i]

        if order == 2:
            # RK2 (Phương pháp Heun hoặc RK2 cải tiến)
            k1 = h * func(x_i, y_i)
            k2 = h * func(x_i + h, y_i + k1)
            y_values[i + 1] = y_i + (k1 + k2) / 2
            
        elif order == 3:
            # RK3
            k1 = h * func(x_i, y_i)
            k2 = h * func(x_i + h/2, y_i + k1/2)
            k3 = h * func(x_i + h, y_i - k1 + 2*k2)
            y_values[i + 1] = y_i + (k1 + 4*k2 + k3) / 6
            
        elif order == 4:
            # RK4 (Phương pháp Runge-Kutta bậc 4 cổ điển)
            k1 = h * func(x_i, y_i)
            k2 = h * func(x_i + h/2, y_i + k1/2)
            k3 = h * func(x_i + h/2, y_i + k2/2) 
            k4 = h * func(x_i + h, y_i + k3)
            y_values[i + 1] = y_i + (k1 + 2*k2 + 2*k3 + k4) / 6
            
        else:
            raise ValueError("Bậc Runge-Kutta chỉ hỗ trợ 2, 3, hoặc 4")

    return x_values, y_values

# Sử dụng các hàm
x0, y0 = 0, 1
x_end = 0.4
h = 0.1

# Phương pháp lặp
x_adaptive, y_adaptive = adaptive_step_method(f, x0, y0, x_end)
print("Phương pháp lặp với bước thích ứng:")
for x_i, y_i in zip(x_adaptive, y_adaptive):
    print(f"x = {x_i:.4f}, y = {y_i:.6f}")

# Phương pháp Euler
x_euler, y_euler = euler_method(f, x0, y0, x_end, h)
print("\nPhương pháp Euler:")
for x_i, y_i in zip(x_euler, y_euler):
    print(f"x = {x_i:.4f}, y = {y_i:.6f}")

# Phương pháp Runge-Kutta với các bậc khác nhau
for order in [2, 3, 4]:
    x_rk, y_rk = runge_kutta(f, x0, y0, x_end, h, order=order)
    print(f"\nBảng giá trị x và y tính theo phương pháp Runge-Kutta bậc {order}:")
    print("x:", x_rk)
    print("y:", y_rk)
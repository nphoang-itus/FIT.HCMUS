import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

# ============================================================================
# PHẦN 1: GIẢI PHƯƠNG TRÌNH SIÊU VIỆT
# ============================================================================

def bisection_method(f, a, b, tol=1e-3, max_iter=100, plot=False):
    """
    Phương pháp chia đôi để tìm nghiệm phương trình f(x) = 0
    
    Parameters:
    - f: hàm số
    - a, b: khoảng chứa nghiệm
    - tol: sai số cho phép
    - max_iter: số lần lặp tối đa
    - plot: có vẽ biểu đồ hay không
    """
    if f(a) * f(b) >= 0:
        print("Phương pháp chia đôi không được áp dụng vì f(a) và f(b) không cùng dấu.")
        return None

    iter_count = 0
    c_values = []
    fc_values = []
    
    while (b - a) / 2.0 > tol and iter_count < max_iter:
        iter_count += 1
        mid_point = (a + b) / 2.0
        fc = f(mid_point)
        
        c_values.append(mid_point)
        fc_values.append(fc)
        
        print(f"Lần lặp {iter_count}: c = {mid_point:.6f}, f(c) = {fc:.6f}")
        
        if f(mid_point) == 0:
            break
        elif f(a) * f(mid_point) > 0:
            a = mid_point
        else:
            b = mid_point
    
    result = (a + b) / 2.0
    
    if plot:
        plt.figure(figsize=(10, 6))
        plt.plot(range(1, len(fc_values) + 1), fc_values, 'ro-')
        plt.xlabel('Số lần lặp')
        plt.ylabel('f(c)')
        plt.title('Phương pháp chia đôi - Hội tụ về nghiệm')
        plt.grid(True)
        plt.axhline(y=0, color='k', linestyle='--', alpha=0.5)
        plt.show()
    
    return result

def fixed_point_iteration(phi, x0, tol=1e-3, max_iter=100, plot=False):
    """
    Phương pháp lặp điểm bất động
    
    Parameters:
    - phi: hàm lặp phi(x)
    - x0: giá trị khởi tạo
    - tol: sai số cho phép
    - max_iter: số lần lặp tối đa
    - plot: có vẽ biểu đồ hay không
    """
    x = x0
    x_values = [x0]
    
    for i in range(max_iter):
        x_new = phi(x)
        x_values.append(x_new)
        
        print(f"Lần lặp {i+1}: x = {x_new:.6f}")
        
        if abs(x_new - x) < tol:
            if plot:
                plt.figure(figsize=(10, 6))
                plt.plot(range(len(x_values)), x_values, 'bo-')
                plt.xlabel('Số lần lặp')
                plt.ylabel('x')
                plt.title('Phương pháp lặp điểm bất động')
                plt.grid(True)
                plt.show()
            return x_new
        x = x_new
    
    return x

def newton_method(f, df, x0, tol=1e-3, max_iter=100, plot=False):
    """
    Phương pháp Newton-Raphson (tiếp tuyến)
    
    Parameters:
    - f: hàm số
    - df: đạo hàm của hàm số
    - x0: giá trị khởi tạo
    - tol: sai số cho phép
    - max_iter: số lần lặp tối đa
    - plot: có vẽ biểu đồ hay không
    """
    print("=" * 80)
    print(f"{'STT':<5}{'x_0':<12}{'x_n':<12}{'f(x_n)':<15}{'|f(x_n)| <= Δf':<18}{'δx_n':<12}")
    print("=" * 80)
    
    x = x0
    x_values = [x0]
    fx_values = [f(x0)]
    
    for i in range(max_iter):
        fx = f(x)
        dfx = df(x)
        x_new = x - fx / dfx
        delta_x = abs(x_new - x)
        check = "✓" if abs(fx) <= tol else "✗"
        
        print(f"{i+1:<5}{x:<12.6f}{x_new:<12.6f}{fx:<15.6f}{check:<18}{delta_x:<12.6f}")
        
        x_values.append(x_new)
        fx_values.append(f(x_new))
        
        if abs(fx) <= tol:
            break
            
        x = x_new
    
    print("=" * 80)
    
    if plot:
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
        
        # Biểu đồ hội tụ của x
        ax1.plot(range(len(x_values)), x_values, 'ro-')
        ax1.set_xlabel('Số lần lặp')
        ax1.set_ylabel('x')
        ax1.set_title('Hội tụ giá trị x')
        ax1.grid(True)
        
        # Biểu đồ hội tụ của f(x)
        ax2.plot(range(len(fx_values)), np.abs(fx_values), 'bo-')
        ax2.set_xlabel('Số lần lặp')
        ax2.set_ylabel('|f(x)|')
        ax2.set_title('Hội tụ |f(x)| về 0')
        ax2.set_yscale('log')
        ax2.grid(True)
        
        plt.tight_layout()
        plt.show()
    
    return x

def secant_method(f, a, b, tol=1e-3, max_iter=100, plot=False):
    """
    Phương pháp dây cung (secant method)
    
    Parameters:
    - f: hàm số
    - a, b: hai điểm khởi tạo
    - tol: sai số cho phép
    - max_iter: số lần lặp tối đa
    - plot: có vẽ biểu đồ hay không
    """
    if f(a) * f(b) > 0:
        print(f"Thuật toán không thể thực hiện được với f({a}) và f({b}) cùng dấu")
        return None

    print("=" * 80)
    print(f"{'STT':<5}{'a':<12}{'b':<12}{'c':<12}{'f(c)':<12}{'f(c) < δf':<12}{'σc':<12}")
    print("=" * 80)

    c_values = []
    fc_values = []
    
    for i in range(max_iter):
        c = a - f(a) * (b - a) / (f(b) - f(a))
        fc = f(c)
        
        c_values.append(c)
        fc_values.append(fc)
        
        check = "true" if abs(fc) <= tol else "false"
        sigma_c = abs(c - a) if i == 0 else abs(c - c_values[-2])
        
        print(f"{i+1:<5}{a:<12.4f}{b:<12.4f}{c:<12.4f}{fc:<12.4f}{check:<12}{sigma_c:<12.4f}")

        if abs(fc) < tol:
            break

        if f(a) * fc < 0:
            b = c
        else:
            a = c

    print("=" * 80)
    
    if plot:
        plt.figure(figsize=(10, 6))
        plt.plot(range(1, len(fc_values) + 1), np.abs(fc_values), 'go-')
        plt.xlabel('Số lần lặp')
        plt.ylabel('|f(c)|')
        plt.title('Phương pháp dây cung - Hội tụ về nghiệm')
        plt.yscale('log')
        plt.grid(True)
        plt.show()
    
    return c

# Ví dụ sử dụng phương trình siêu việt
def example_transcendental_equations():
    """Ví dụ giải phương trình siêu việt"""
    print("=== VÍ DỤ GIẢI PHƯƠNG TRÌNH SIÊU VIỆT ===\n")
    
    # Phương trình: x + sin(x) - 2 = 0
    def f1(x):
        return x + np.sin(x) - 2
    
    def df1(x):
        return 1 + np.cos(x)
    
    def phi1(x):
        return 2 - np.sin(x)
    
    print("1. Phương pháp chia đôi:")
    root1 = bisection_method(f1, 1, 1.4, plot=True)
    print(f"Nghiệm: {root1:.6f}\n")
    
    print("2. Phương pháp lặp:")
    root2 = fixed_point_iteration(phi1, 1.05, plot=True)
    print(f"Nghiệm: {root2:.6f}\n")
    
    print("3. Phương pháp Newton:")
    root3 = newton_method(f1, df1, 1.2, plot=True)
    print(f"Nghiệm: {root3:.6f}\n")

# ============================================================================
# PHẦN 2: GIẢI HỆ PHƯƠNG TRÌNH TUYẾN TÍNH
# ============================================================================

def jacobi_method(A, B, tol=1e-3, max_iter=100, plot=False):
    """
    Phương pháp lặp Jacobi
    
    Parameters:
    - A: ma trận hệ số
    - B: vector vế phải
    - tol: sai số cho phép
    - max_iter: số lần lặp tối đa
    - plot: có vẽ biểu đồ hay không
    """
    X = np.zeros_like(B, dtype=float)
    X_history = [X.copy()]
    errors = []

    for iter_count in range(max_iter):
        X_new = np.zeros_like(X)
        
        for i in range(len(A)):
            sum1 = sum(A[i][j] * X[j] for j in range(len(A)) if j != i)
            X_new[i] = (B[i] - sum1) / A[i][i]

        error = np.linalg.norm(X_new - X, ord=np.inf)
        errors.append(error)
        X_history.append(X_new.copy())
        
        print(f"Lần lặp {iter_count+1}: X = {X_new}, Error = {error:.6f}")

        if error < tol:
            break

        X = X_new

    if plot:
        plt.figure(figsize=(12, 5))
        
        # Biểu đồ hội tụ sai số
        plt.subplot(1, 2, 1)
        plt.plot(range(1, len(errors) + 1), errors, 'ro-')
        plt.xlabel('Số lần lặp')
        plt.ylabel('Sai số')
        plt.title('Hội tụ sai số - Phương pháp Jacobi')
        plt.yscale('log')
        plt.grid(True)
        
        # Biểu đồ hội tụ các nghiệm
        plt.subplot(1, 2, 2)
        X_history = np.array(X_history)
        for i in range(len(B)):
            plt.plot(range(len(X_history)), X_history[:, i], 'o-', label=f'x{i+1}')
        plt.xlabel('Số lần lặp')
        plt.ylabel('Giá trị nghiệm')
        plt.title('Hội tụ các nghiệm')
        plt.legend()
        plt.grid(True)
        
        plt.tight_layout()
        plt.show()

    return X

def gauss_seidel_method(A, B, tol=1e-3, max_iter=100, plot=False):
    """
    Phương pháp Gauss-Seidel
    
    Parameters:
    - A: ma trận hệ số
    - B: vector vế phải
    - tol: sai số cho phép
    - max_iter: số lần lặp tối đa
    - plot: có vẽ biểu đồ hay không
    """
    X = np.zeros_like(B, dtype=float)
    X_history = [X.copy()]
    errors = []

    for iter_count in range(max_iter):
        X_old = X.copy()

        for i in range(len(A)):
            sum1 = sum(A[i][j] * X[j] for j in range(len(A)) if j != i)
            X[i] = (B[i] - sum1) / A[i][i]

        error = np.linalg.norm(X - X_old, ord=np.inf)
        errors.append(error)
        X_history.append(X.copy())
        
        print(f"Lần lặp {iter_count+1}: X = {X}, Error = {error:.6f}")

        if error < tol:
            break

    if plot:
        plt.figure(figsize=(12, 5))
        
        # Biểu đồ hội tụ sai số
        plt.subplot(1, 2, 1)
        plt.plot(range(1, len(errors) + 1), errors, 'bo-')
        plt.xlabel('Số lần lặp')
        plt.ylabel('Sai số')
        plt.title('Hội tụ sai số - Phương pháp Gauss-Seidel')
        plt.yscale('log')
        plt.grid(True)
        
        # Biểu đồ hội tụ các nghiệm
        plt.subplot(1, 2, 2)
        X_history = np.array(X_history)
        for i in range(len(B)):
            plt.plot(range(len(X_history)), X_history[:, i], 'o-', label=f'x{i+1}')
        plt.xlabel('Số lần lặp')
        plt.ylabel('Giá trị nghiệm')
        plt.title('Hội tụ các nghiệm')
        plt.legend()
        plt.grid(True)
        
        plt.tight_layout()
        plt.show()
    
    return X

# Ví dụ sử dụng hệ phương trình tuyến tính
def example_linear_systems():
    """Ví dụ giải hệ phương trình tuyến tính"""
    print("=== VÍ DỤ GIẢI HỆ PHƯƠNG TRÌNH TUYẾN TÍNH ===\n")
    
    A = np.array([
        [5, 1, 1],
        [1, 10, 1],
        [1, 1, 10]
    ], dtype=float)

    B = np.array([7, 12, 22], dtype=float)
    
    print("Ma trận A:")
    print(A)
    print("\nVector B:")
    print(B)
    
    print("\n1. Phương pháp Jacobi:")
    root1 = jacobi_method(A, B, plot=True)
    print(f"Nghiệm: {root1}\n")
    
    print("2. Phương pháp Gauss-Seidel:")
    root2 = gauss_seidel_method(A, B, plot=True)
    print(f"Nghiệm: {root2}\n")

# ============================================================================
# PHẦN 3: NỘI SUY VÀ XẤP XỈ HÀM SỐ
# ============================================================================

def lagrange_interpolation(x_data, y_data, x_interp, plot=False):
    """
    Nội suy Lagrange
    
    Parameters:
    - x_data, y_data: các điểm dữ liệu
    - x_interp: điểm cần nội suy
    - plot: có vẽ biểu đồ hay không
    """
    n = len(x_data)
    result = 0
    
    for i in range(n):
        L = 1
        for j in range(n):
            if i != j:
                L *= (x_interp - x_data[j]) / (x_data[i] - x_data[j])
        result += y_data[i] * L
    
    if plot:
        x_plot = np.linspace(min(x_data), max(x_data), 100)
        y_plot = []
        
        for x in x_plot:
            y = 0
            for i in range(n):
                L = 1
                for j in range(n):
                    if i != j:
                        L *= (x - x_data[j]) / (x_data[i] - x_data[j])
                y += y_data[i] * L
            y_plot.append(y)
        
        plt.figure(figsize=(10, 6))
        plt.plot(x_data, y_data, 'ro', markersize=8, label='Điểm dữ liệu')
        plt.plot(x_plot, y_plot, 'b-', label='Đa thức Lagrange')
        plt.plot(x_interp, result, 'gs', markersize=10, label=f'Nội suy tại x={x_interp}')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Nội suy Lagrange')
        plt.legend()
        plt.grid(True)
        plt.show()
    
    return result

def spline_interpolation(x_data, y_data, x_query, plot=False):
    """
    Nội suy Spline bậc 3
    
    Parameters:
    - x_data, y_data: các điểm dữ liệu
    - x_query: điểm cần nội suy
    - plot: có vẽ biểu đồ hay không
    """
    n = len(x_data) - 1
    h = np.diff(x_data)

    A = np.zeros((n - 1, n - 1))
    b_vec = np.zeros(n - 1)
        
    for i in range(1, n):
        A[i - 1, i - 1] = 2 * (h[i - 1] + h[i])
        if i - 1 > 0:
            A[i - 1, i - 2] = h[i - 1]
        if i < n - 1:
            A[i - 1, i] = h[i]

        b_vec[i - 1] = 3 * ((y_data[i + 1] - y_data[i]) / h[i] - (y_data[i] - y_data[i - 1]) / h[i - 1])
        
    c = np.zeros(n + 1)
    c[1:n] = np.linalg.solve(A, b_vec)

    b_coeff = np.zeros(n)
    d = np.zeros(n)

    for i in range(n):
        b_coeff[i] = (y_data[i + 1] - y_data[i]) / h[i] - h[i] * (2 * c[i] + c[i + 1]) / 3
        d[i] = (c[i + 1] - c[i]) / (3 * h[i])

    # Tìm khoảng chứa x_query và tính giá trị nội suy
    result = None
    for i in range(n):
        if x_data[i] <= x_query <= x_data[i + 1]:
            dx = x_query - x_data[i]
            result = y_data[i] + b_coeff[i] * dx + c[i] * dx**2 + d[i] * dx**3
            break
    
    if plot:
        x_plot = np.linspace(min(x_data), max(x_data), 200)
        y_plot = []
        
        for x in x_plot:
            for i in range(n):
                if x_data[i] <= x <= x_data[i + 1]:
                    dx = x - x_data[i]
                    y = y_data[i] + b_coeff[i] * dx + c[i] * dx**2 + d[i] * dx**3
                    y_plot.append(y)
                    break
        
        plt.figure(figsize=(10, 6))
        plt.plot(x_data, y_data, 'ro', markersize=8, label='Điểm dữ liệu')
        plt.plot(x_plot, y_plot, 'b-', label='Spline bậc 3')
        if result is not None:
            plt.plot(x_query, result, 'gs', markersize=10, label=f'Nội suy tại x={x_query}')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Nội suy Spline bậc 3')
        plt.legend()
        plt.grid(True)
        plt.show()
    
    return result

def least_squares_approximation(x_data, y_data, x_query, plot=False):
    """
    Xấp xỉ bình phương nhỏ nhất (đường thẳng)
    
    Parameters:
    - x_data, y_data: các điểm dữ liệu
    - x_query: điểm cần xấp xỉ
    - plot: có vẽ biểu đồ hay không
    """
    n = len(x_data)
    X = np.vstack((x_data, np.ones(n))).T
    a, b = np.linalg.lstsq(X, y_data, rcond=None)[0]
    
    y_query = a * x_query + b
    
    if plot:
        x_plot = np.linspace(min(x_data), max(x_data), 100)
        y_plot = a * x_plot + b
        
        plt.figure(figsize=(10, 6))
        plt.plot(x_data, y_data, 'ro', markersize=8, label='Điểm dữ liệu')
        plt.plot(x_plot, y_plot, 'b-', label=f'y = {a:.4f}x + {b:.4f}')
        plt.plot(x_query, y_query, 'gs', markersize=10, label=f'Xấp xỉ tại x={x_query}')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Xấp xỉ bình phương nhỏ nhất')
        plt.legend()
        plt.grid(True)
        plt.show()
    
    return y_query, a, b

# Ví dụ sử dụng nội suy và xấp xỉ
def example_interpolation():
    """Ví dụ nội suy và xấp xỉ hàm số"""
    print("=== VÍ DỤ NỘI SUY VÀ XẤP XỈ HÀM SỐ ===\n")
    
    # Dữ liệu cho nội suy
    x = np.array([1, 2.2, 3.1, 4])
    y = np.array([1.678, 3.267, 2.198, 3.787])
    x_interp = 2.5
    
    print("1. Nội suy Lagrange:")
    result1 = lagrange_interpolation(x, y, x_interp, plot=True)
    print(f"Giá trị tại x = {x_interp}: {result1:.6f}\n")
    
    # Dữ liệu cho Spline
    x_spline = np.array([2, 4, 7, 8])
    y_spline = np.array([2.2, 1.8, 2.7, 3.1])
    
    print("2. Nội suy Spline:")
    result2 = spline_interpolation(x_spline, y_spline, 3, plot=True)
    print(f"Giá trị tại x = 3: {result2:.6f}\n")
    
    # Dữ liệu cho bình phương nhỏ nhất
    x_ls = np.array([2, 4, 7, 8.5, 9.5, 11])
    y_ls = np.array([2.2, 4.2, 6.8, 8.1, 9.7, 10.5])
    
    print("3. Xấp xỉ bình phương nhỏ nhất:")
    result3, a, b = least_squares_approximation(x_ls, y_ls, 6, plot=True)
    print(f"Hàm xấp xỉ: y = {a:.4f}x + {b:.4f}")
    print(f"Giá trị tại x = 6: {result3:.6f}\n")

# ============================================================================
# PHẦN 4: ĐẠO HÀM SỐ
# ============================================================================

def forward_difference(x_data, y_data, index):
    """Tính đạo hàm bằng sai phân tiến"""
    return (y_data[index + 1] - y_data[index]) / (x_data[index + 1] - x_data[index])

def backward_difference(x_data, y_data, index):
    """Tính đạo hàm bằng sai phân lùi"""
    return (y_data[index] - y_data[index - 1]) / (x_data[index] - x_data[index - 1])

def three_point_endpoint(x_data, y_data, index):
    """Tính đạo hàm bằng công thức 3 điểm cuối"""
    h = x_data[index + 1] - x_data[index]
    return (-3 * y_data[index] + 4 * y_data[index + 1] - y_data[index + 2]) / (2 * h)

def three_point_midpoint(x_data, y_data, index):
    """Tính đạo hàm bằng công thức 3 điểm giữa"""
    h = x_data[index + 1] - x_data[index]
    return (y_data[index + 1] - y_data[index - 1]) / (2 * h)

def five_point_midpoint(x_data, y_data, index):
    """Tính đạo hàm bằng công thức 5 điểm giữa"""
    h = x_data[index + 1] - x_data[index]
    return (-y_data[index + 2] + 8*y_data[index + 1] - 8*y_data[index - 1] + y_data[index - 2]) / (12 * h)

def relative_error(exact_value, approximate_value):
    """Tính sai số tương đối"""
    return np.abs((exact_value - approximate_value) / exact_value)

# Ví dụ sử dụng đạo hàm số
def example_numerical_derivatives():
    """Ví dụ tính đạo hàm số"""
    print("=== VÍ DỤ TÍNH ĐẠO HÀM SỐ ===\n")
    
    xx = np.array([0.9, 1, 1.1, 1.2])
    yy = np.array([0.7833, 0.8415, 0.8912, 0.932])
    df_exact = 0.5403  # Giá trị đạo hàm chính xác tại x = 1
    
    methods = [
        ("Sai phân tiến", forward_difference(xx, yy, 1)),
        ("Sai phân lùi", backward_difference(xx, yy, 1)),
        ("3 điểm cuối", three_point_endpoint(xx, yy, 1)),
        ("3 điểm giữa", three_point_midpoint(xx, yy, 1))
    ]
    
    # Thêm dữ liệu cho 5 điểm giữa
    xx_extended = np.array([0.8, 0.9, 1, 1.1, 1.2])
    yy_extended = np.array([0.7174, 0.7833, 0.8415, 0.8912, 0.932])
    methods.append(("5 điểm giữa", five_point_midpoint(xx_extended, yy_extended, 2)))
    
    print(f"{'Phương pháp':<15}{'Giá trị':<12}{'Sai số tương đối':<18}")
    print("-" * 45)
    
    for method_name, df_approx in methods:
        error = relative_error(df_exact, df_approx)
        print(f"{method_name:<15}{df_approx:<12.6f}{error:<18.6f}")

# ============================================================================
# PHẦN 5: TÍCH PHÂN SỐ
# ============================================================================

def simpson_1_3_rule(x_data, y_data):
    """Công thức Simpson 1/3 (Newton-Cotes 3 điểm)"""
    return (x_data[2] - x_data[0]) * (y_data[0] + 4*y_data[1] + y_data[2]) / 6

def simpson_3_8_rule(x_data, y_data):
    """Công thức Simpson 3/8 (Newton-Cotes 4 điểm)"""
    return (x_data[3] - x_data[0]) * (y_data[0] + 3*y_data[1] + 3*y_data[2] + y_data[3]) / 8

def boole_rule(x_data, y_data):
    """Công thức Boole (Newton-Cotes 5 điểm)"""
    return (x_data[4] - x_data[0]) * (7*y_data[0] + 32*y_data[1] + 12*y_data[2] + 32*y_data[3] + 7*y_data[4]) / 90

def gaussian_quadrature(func, a, b, n_points=2):
    """Tích phân bằng phương pháp Gauss"""
    result, _ = quad(func, a, b)
    return result

def composite_simpson(func, a, b, n, plot=False):
    """
    Tích phân Simpson tổng hợp
    
    Parameters:
    - func: hàm số cần tích phân
    - a, b: cận tích phân
    - n: số khoảng chia (phải là số chẵn)
    - plot: có vẽ biểu đồ hay không
    """
    if n % 2 != 0:
        raise ValueError("Số khoảng chia phải là số chẵn")
    
    h = (b - a) / n
    x = np.linspace(a, b, n + 1)
    y = func(x)
    
    result = y[0] + y[-1]
    for i in range(1, n):
        if i % 2 == 1:
            result += 4 * y[i]
        else:
            result += 2 * y[i]
    
    result *= h / 3
    
    if plot:
        x_plot = np.linspace(a, b, 1000)
        y_plot = func(x_plot)
        
        plt.figure(figsize=(12, 8))
        
        # Biểu đồ hàm số và phân chia
        plt.subplot(2, 1, 1)
        plt.plot(x_plot, y_plot, 'b-', linewidth=2, label='f(x)')
        plt.fill_between(x_plot, 0, y_plot, alpha=0.3, color='lightblue')
        
        # Vẽ các điểm chia
        plt.plot(x, y, 'ro', markersize=6)
        for i in range(len(x)):
            plt.axvline(x[i], color='gray', linestyle='--', alpha=0.5)
        
        plt.xlabel('x')
        plt.ylabel('f(x)')
        plt.title(f'Tích phân Simpson tổng hợp với {n} khoảng')
        plt.legend()
        plt.grid(True)
        
        # Biểu đồ hội tụ với số khoảng chia khác nhau
        plt.subplot(2, 1, 2)
        n_values = np.arange(2, 21, 2)
        results = []
        for ni in n_values:
            hi = (b - a) / ni
            xi = np.linspace(a, b, ni + 1)
            yi = func(xi)
            ri = yi[0] + yi[-1]
            for j in range(1, ni):
                if j % 2 == 1:
                    ri += 4 * yi[j]
                else:
                    ri += 2 * yi[j]
            ri *= hi / 3
            results.append(ri)
        
        plt.plot(n_values, results, 'ro-')
        plt.axhline(y=result, color='b', linestyle='--', label=f'Giá trị cuối = {result:.6f}')
        plt.xlabel('Số khoảng chia')
        plt.ylabel('Giá trị tích phân')
        plt.title('Hội tụ theo số khoảng chia')
        plt.legend()
        plt.grid(True)
        
        plt.tight_layout()
        plt.show()
    
    return result

# Ví dụ sử dụng tích phân số
def example_numerical_integration():
    """Ví dụ tính tích phân số"""
    print("=== VÍ DỤ TÍCH PHÂN SỐ ===\n")
    
    # Dữ liệu cho Newton-Cotes
    x = np.array([1, 2, 3, 4, 5, 6, 7])
    y = np.array([4, -6, -14, -14, 0, 34, 94])
    I_exact = 42
    
    print("1. Các công thức Newton-Cotes:")
    I1 = simpson_1_3_rule(x[:3], y[:3])
    I2 = simpson_3_8_rule(x[:4], y[:4])
    I3 = boole_rule(x[:5], y[:5])
    
    print(f"Simpson 1/3: {I1:.6f}, Sai số: {relative_error(I_exact, I1):.6f}")
    print(f"Simpson 3/8: {I2:.6f}, Sai số: {relative_error(I_exact, I2):.6f}")
    print(f"Boole: {I3:.6f}, Sai số: {relative_error(I_exact, I3):.6f}\n")
    
    # Tích phân hàm e^x
    def f_exp(x):
        return np.exp(x)
    
    print("2. Tích phân hàm e^x từ 2 đến 4:")
    I_exact_exp = gaussian_quadrature(f_exp, 2, 4)
    I_simpson = composite_simpson(f_exp, 2, 4, 10, plot=True)
    
    print(f"Giá trị chính xác: {I_exact_exp:.6f}")
    print(f"Simpson tổng hợp: {I_simpson:.6f}")
    print(f"Sai số: {relative_error(I_exact_exp, I_simpson):.6f}\n")

# ============================================================================
# PHẦN 6: GIẢI PHƯƠNG TRÌNH VI PHÂN
# ============================================================================

def euler_method(f, x0, y0, x_end, h, plot=False):
    """
    Phương pháp Euler
    
    Parameters:
    - f: hàm f(x, y) trong phương trình y' = f(x, y)
    - x0, y0: điều kiện ban đầu
    - x_end: điểm cuối
    - h: bước tích phân
    - plot: có vẽ biểu đồ hay không
    """
    x_values = np.arange(x0, x_end + h, h)
    y_values = np.zeros_like(x_values)
    y_values[0] = y0

    for i in range(len(x_values) - 1):
        y_values[i + 1] = y_values[i] + h * f(x_values[i], y_values[i])
        print(f"x = {x_values[i+1]:.4f}, y = {y_values[i+1]:.6f}")

    if plot:
        plt.figure(figsize=(10, 6))
        plt.plot(x_values, y_values, 'ro-', linewidth=2, markersize=6, label='Euler')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Phương pháp Euler')
        plt.legend()
        plt.grid(True)
        plt.show()

    return x_values, y_values

def runge_kutta_4(f, x0, y0, x_end, h, plot=False):
    """
    Phương pháp Runge-Kutta bậc 4
    
    Parameters:
    - f: hàm f(x, y) trong phương trình y' = f(x, y)
    - x0, y0: điều kiện ban đầu
    - x_end: điểm cuối
    - h: bước tích phân
    - plot: có vẽ biểu đồ hay không
    """
    x_values = np.arange(x0, x_end + h, h)
    y_values = np.zeros_like(x_values)
    y_values[0] = y0

    for i in range(len(x_values) - 1):
        x_i, y_i = x_values[i], y_values[i]
        
        k1 = h * f(x_i, y_i)
        k2 = h * f(x_i + h/2, y_i + k1/2)
        k3 = h * f(x_i + h/2, y_i + k2/2) 
        k4 = h * f(x_i + h, y_i + k3)
        
        y_values[i + 1] = y_i + (k1 + 2*k2 + 2*k3 + k4) / 6
        print(f"x = {x_values[i+1]:.4f}, y = {y_values[i+1]:.6f}")

    if plot:
        plt.figure(figsize=(10, 6))
        plt.plot(x_values, y_values, 'bo-', linewidth=2, markersize=6, label='RK4')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Phương pháp Runge-Kutta bậc 4')
        plt.legend()
        plt.grid(True)
        plt.show()

    return x_values, y_values

def adaptive_runge_kutta(f, x0, y0, x_end, tol=1e-6, h_initial=0.1, plot=False):
    """
    Phương pháp Runge-Kutta với bước thích ứng
    
    Parameters:
    - f: hàm f(x, y) trong phương trình y' = f(x, y)
    - x0, y0: điều kiện ban đầu
    - x_end: điểm cuối
    - tol: sai số cho phép
    - h_initial: bước ban đầu
    - plot: có vẽ biểu đồ hay không
    """
    h = h_initial
    x_values = [x0]
    y_values = [y0]
    h_values = []

    while x_values[-1] < x_end:
        x_n = x_values[-1]
        y_n = y_values[-1]

        # RK4 với bước h
        k1 = h * f(x_n, y_n)
        k2 = h * f(x_n + h/2, y_n + k1/2)
        k3 = h * f(x_n + h/2, y_n + k2/2)
        k4 = h * f(x_n + h, y_n + k3)
        y_full = y_n + (k1 + 2*k2 + 2*k3 + k4) / 6

        # RK4 với hai bước h/2
        h_half = h / 2
        
        # Bước 1
        k1_1 = h_half * f(x_n, y_n)
        k2_1 = h_half * f(x_n + h_half/2, y_n + k1_1/2)
        k3_1 = h_half * f(x_n + h_half/2, y_n + k2_1/2)
        k4_1 = h_half * f(x_n + h_half, y_n + k3_1)
        y_mid = y_n + (k1_1 + 2*k2_1 + 2*k3_1 + k4_1) / 6
        
        # Bước 2
        k1_2 = h_half * f(x_n + h_half, y_mid)
        k2_2 = h_half * f(x_n + h_half + h_half/2, y_mid + k1_2/2)
        k3_2 = h_half * f(x_n + h_half + h_half/2, y_mid + k2_2/2)
        k4_2 = h_half * f(x_n + h, y_mid + k3_2)
        y_double = y_mid + (k1_2 + 2*k2_2 + 2*k3_2 + k4_2) / 6

        # Ước lượng sai số
        error = abs(y_double - y_full) / 15  # Sai số Richardson

        if error < tol:
            x_values.append(x_n + h)
            y_values.append(y_double)
            h_values.append(h)
            print(f"x = {x_values[-1]:.4f}, y = {y_values[-1]:.6f}, h = {h:.6f}")
            
            # Tăng bước nếu sai số quá nhỏ
            if error < tol / 10:
                h = min(h * 2, 0.5)
        else:
            # Giảm bước nếu sai số quá lớn
            h = h / 2

    if plot and len(h_values) > 0:
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))
        
        # Biểu đồ nghiệm
        ax1.plot(x_values, y_values, 'ro-', markersize=4, label='Adaptive RK4')
        ax1.set_xlabel('x')
        ax1.set_ylabel('y')
        ax1.set_title('Phương pháp Runge-Kutta thích ứng')
        ax1.legend()
        ax1.grid(True)
        
        # Biểu đồ bước tích phân - sửa lỗi kích thước mảng
        ax2.plot(x_values[1:len(h_values)+1], h_values, 'bo-', markersize=4)
        ax2.set_xlabel('x')
        ax2.set_ylabel('Bước h')
        ax2.set_title('Thay đổi bước tích phân')
        ax2.grid(True)
        
        plt.tight_layout()
        plt.show()

    return np.array(x_values), np.array(y_values)

def compare_ode_methods(f, x0, y0, x_end, h, exact_solution=None):
    """
    So sánh các phương pháp giải phương trình vi phân
    
    Parameters:
    - f: hàm f(x, y) trong phương trình y' = f(x, y)
    - x0, y0: điều kiện ban đầu
    - x_end: điểm cuối
    - h: bước tích phân
    - exact_solution: nghiệm chính xác (nếu có)
    """
    # Euler
    x_euler, y_euler = euler_method(f, x0, y0, x_end, h)
    
    # RK4
    x_rk4, y_rk4 = runge_kutta_4(f, x0, y0, x_end, h)
    
    # Adaptive RK
    x_adaptive, y_adaptive = adaptive_runge_kutta(f, x0, y0, x_end, h_initial=h)
    
    # Vẽ biểu đồ so sánh
    plt.figure(figsize=(12, 8))
    
    plt.plot(x_euler, y_euler, 'ro-', markersize=4, label='Euler', alpha=0.7)
    plt.plot(x_rk4, y_rk4, 'bo-', markersize=4, label='RK4', alpha=0.7)
    plt.plot(x_adaptive, y_adaptive, 'go-', markersize=3, label='Adaptive RK4', alpha=0.7)
    
    if exact_solution is not None:
        x_exact = np.linspace(x0, x_end, 1000)
        y_exact = exact_solution(x_exact)
        plt.plot(x_exact, y_exact, 'k-', linewidth=2, label='Nghiệm chính xác')
    
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('So sánh các phương pháp giải phương trình vi phân')
    plt.legend()
    plt.grid(True)
    plt.show()

# Ví dụ sử dụng phương trình vi phân
def example_ode():
    """Ví dụ giải phương trình vi phân"""
    print("=== VÍ DỤ GIẢI PHƯƠNG TRÌNH VI PHÂN ===\n")
    
    def f(x, y):
        return x + y
    
    def exact_solution(x):
        return 2 * np.exp(x) - x - 1  # Nghiệm chính xác của y' = x + y, y(0) = 1
    
    x0, y0 = 0, 1
    x_end = 0.4
    h = 0.1
    
    print("Phương trình: y' = x + y, y(0) = 1\n")
    
    print("1. Phương pháp Euler:")
    euler_method(f, x0, y0, x_end, h, plot=True)
    
    print("\n2. Phương pháp Runge-Kutta bậc 4:")
    runge_kutta_4(f, x0, y0, x_end, h, plot=True)
    
    print("\n3. Phương pháp thích ứng:")
    adaptive_runge_kutta(f, x0, y0, x_end, plot=True)
    
    print("\n4. So sánh các phương pháp:")
    compare_ode_methods(f, x0, y0, x_end, h, exact_solution)

# ============================================================================
# CHẠY TẤT CẢ VÍ DỤ
# ============================================================================

def run_all_examples():
    """Chạy tất cả các ví dụ"""
    print("CHƯƠNG TRÌNH DEMO CÁC PHƯƠNG PHÁP TÍNH SỐ")
    print("=" * 80)
    
    example_transcendental_equations()
    example_linear_systems()
    example_interpolation()
    example_numerical_derivatives()
    example_numerical_integration()
    example_ode()

if __name__ == "__main__":
    # Có thể chạy từng phần riêng lẻ hoặc tất cả
    run_all_examples()
    
    # Hoặc chạy từng phần:
    # example_transcendental_equations()
    # example_linear_systems()
    # example_interpolation()
    # example_numerical_derivatives()
    # example_numerical_integration()
    # example_ode()
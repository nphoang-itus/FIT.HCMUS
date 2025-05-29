# 23120264 - Nguyễn Phúc Hoàng - Ca 2
# file đáp án/ file code/ file hình
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

m = 4

# câu 1

def f(x):
    return np.exp(m/10 * x) - (m * x**2 + x * np.sin(m/10 * x))

# Phương pháp chia đôi
def bisection(a, b, tol):
    if f(a) * f(b) >= 0:
        raise ValueError("Không đảm bảo có nghiệm trong khoảng [a, b]")
    
    mid = a
    while (b - a) / 2 > tol:
        mid = (a + b) / 2
        if f(mid) == 0:
            break
        elif f(a) * f(mid) < 0:
            b = mid
        else:
            a = mid
    return mid

# Tìm nghiệm gần đúng
a, b = -1, 0
delta_f = 1e-3

approx_root = bisection(a, b, delta_f)
print("="*70)
print("CÂU 1:")
print("-"*70)
print("(b)")
print(f"Nghiệm xấp xỉ là: {approx_root:.6f}")

def find_exact_solution(m):
    return bisection(-1, 0, 1e-12)

print("-"*70)
print("(c)")
exact_root = find_exact_solution(m)
print(f"Nghiệm chính xác là: {exact_root:.12f}")

# Tính sai số
absolute_error = abs(exact_root - approx_root)
relative_error = abs(absolute_error / exact_root)
print(f"Sai số tương đối là: {relative_error:.6e}")
print(f"Sai số tuyệt đối là: {absolute_error:.6e}")

# câu 2
print("\n" + "="*70)
print("CÂU 2:")
print("="*70)

# Khởi tạo tham số
delta_f = 1e-3
n = 5  # Số ẩn

# Ma trận A và vector b từ hệ phương trình
A = np.array([
    [m + 4, -2, 1, -1, 2],
    [3, -2*(m + 5), -1, -2, 0],
    [2, 0, 2*(m + 3), -2, 1],
    [-1, 4, 0, -(2*m + 5), 3],
    [0, 1, 0, -3, m + 5]
], dtype=float)

b = np.array([3, 1, -1, -3, 0], dtype=float)

# Gauss-Seidel
def gauss_seidel(A, b, tol=1e-3, max_iter=1000):
    n = len(b)
    x = np.zeros(n)
    for itr in range(max_iter):
        x_new = np.copy(x)
        for i in range(n):
            s1 = sum(A[i][j] * x_new[j] for j in range(i))
            s2 = sum(A[i][j] * x[j] for j in range(i + 1, n))
            x_new[i] = (b[i] - s1 - s2) / A[i][i]
        if np.linalg.norm(x_new - x, ord=np.inf) < tol:
            return x_new
        x = x_new
    return x

# Tính nghiệm gần đúng
approx_sol = gauss_seidel(A, b, tol=delta_f)
print("NGHIỆM XẤP XỈ (Gauss-Seidel):")
for i, val in enumerate(approx_sol, 1):
    print(f"x{i} = {val:.6f}")

# Tính nghiệm chính xác bằng NumPy
exact_sol = np.linalg.solve(A, b)

print("\nNGHIỆM CHÍNH XÁC:")
for i in range(n):
    print(f"x{i+1} = {exact_sol[i]:.12f}")

# Câu 3:
def newton_divided_differences(x, y):
    n = len(x)
    # Tạo bảng sai phân chia
    table = np.zeros((n, n))
    table[:, 0] = y  # Cột đầu tiên là các giá trị y
    
    # Tính các sai phân chia
    for j in range(1, n):
        for i in range(n - j):
            table[i, j] = (table[i + 1, j - 1] - table[i, j - 1]) / (x[i + j] - x[i])
    
    return table

def newton_interpolation(x_data, y_data, x_eval):
    table = newton_divided_differences(x_data, y_data)
    n = len(x_data)
    result = table[0, 0]  # f[x0]
    
    for i in range(1, n):
        term = table[0, i]  # Hệ số sai phân chia
        for j in range(i):
            term *= (x_eval - x_data[j])
        result += term
    
    return result

def get_newton_polynomial_string(x_data, y_data):
    table = newton_divided_differences(x_data, y_data)
    n = len(x_data)
    
    polynomial = f"P(x) = {table[0, 0]:.4f}"
    
    for i in range(1, n):
        coeff = table[0, i]
        if coeff >= 0:
            polynomial += f" + {coeff:.4f}"
        else:
            polynomial += f" - {abs(coeff):.4f}"
        
        for j in range(i):
            polynomial += f"(x - {x_data[j]})"
    
    return polynomial

def plot_vn_index(x_data, y_data):
    # Tạo dãy điểm để vẽ đường cong mượt
    x_smooth = np.linspace(min(x_data), max(x_data), 1000)
    y_smooth = [newton_interpolation(x_data, y_data, x) for x in x_smooth]
    
    plt.figure(figsize=(12, 8))
    
    # Vẽ dữ liệu gốc
    plt.plot(x_data, y_data, 'ro', markersize=8, label='Dữ liệu gốc', zorder=5)
    
    # Vẽ đường cong nội suy
    plt.plot(x_smooth, y_smooth, 'b-', linewidth=2, label='Hàm nội suy Newton')
    
    # Thêm nhãn cho các điểm dữ liệu
    for i, (x, y) in enumerate(zip(x_data, y_data)):
        plt.annotate(f'({x}, {y:.2f})', (x, y), xytext=(5, 5), 
                    textcoords='offset points', fontsize=9)
    
    plt.xlabel('Ngày')
    plt.ylabel('VN-INDEX')
    plt.title('Chỉ số VN-INDEX - Nội suy Newton')
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.show()

print("\n" + "="*70)
print("CÂU 3:")
print("="*70)

# Dữ liệu đề bài
days = np.array([4, 6, 10, 13, 17, 19, 23])
index = np.array([1348.68, 1329.26, 1293.56, 1182.77, 1228.37, 1241.64, 1218.81])

# (a) Tạo hàm xấp xỉ Newton
print("(a)")
polynomial_str = get_newton_polynomial_string(days, index)
print(f"Hàm xấp xỉ là: {polynomial_str}")
print()

# (b) Tính giá trị tại các ngày 5, 8, 15, 22
eval_days = [5, 8, 15, 22]
print("(b)")
print("-"*50)

for day in eval_days:
    value = newton_interpolation(days, index, day)
    print(f"Index tại ngày {day:>2}: {value:>10.4f}")

# Vẽ đồ thị
plot_vn_index(days, index)

# Câu 4:
print("\n" + "="*70)
print("CÂU 4:")
print("="*70)

def T(t):
    return 10 + 6 * np.sin((np.pi * t) / 18)

def simpson_3_8_rule(x_data, y_data):
    if len(x_data) != 4 or len(y_data) != 4:
        raise ValueError("Simpson 3/8 cần chính xác 4 điểm")
    return (x_data[3] - x_data[0]) * (y_data[0] + 3*y_data[1] + 3*y_data[2] + y_data[3]) / 8

def simpson_3_8_composite(func, a, b, delta_t):
    # Số khoảng phải chia hết cho 3 cho Simpson 3/8
    n = int((b - a) / delta_t)
    if n % 3 != 0:
        n = ((n // 3) + 1) * 3  # Làm tròn lên để chia hết cho 3
        delta_t = (b - a) / n
    
    x = np.linspace(a, b, n + 1)
    y = [func(xi) for xi in x]
    
    total = 0
    # Áp dụng Simpson 3/8 cho từng nhóm 4 điểm (3 khoảng)
    for i in range(0, n, 3):
        x_segment = x[i:i+4]
        y_segment = y[i:i+4]
        total += simpson_3_8_rule(x_segment, y_segment)
    
    return total

print("(a)")

a, b = m, m + 12
delta_t = 0.2

integral_T = simpson_3_8_composite(T, a, b, delta_t)

avg_temp_approx = integral_T / (b - a)

print(f"Nhiệt độ trung bình từ {a}h đến {b}h ~ {avg_temp_approx:.6f} F")

print("-"*70)
print("(b)")

# Định nghĩa hàm để tìm nghiệm: T(t) - avg_temp = 0
def temp_diff(t):
    return T(t) - avg_temp_approx

# Phương pháp chia đôi để tìm nghiệm
def bisection_temp(func, a, b, tol=1e-3, max_iter=100):
    if func(a) * func(b) >= 0:
        return None
    
    mid = a
    iter_count = 0
    while (b - a) / 2 > tol and iter_count < max_iter:
        mid = (a + b) / 2
        if func(mid) == 0:
            break
        elif func(a) * func(mid) < 0:
            b = mid
        else:
            a = mid
        iter_count += 1
    return mid

# Tìm nghiệm trong khoảng [0, 24] (một ngày)
# Kiểm tra dấu tại các điểm để tìm khoảng có nghiệm
times_found = []
for start in range(0, 24, 2):
    end = min(start + 2, 24)
    if temp_diff(start) * temp_diff(end) < 0:
        root = bisection_temp(temp_diff, start, end, tol=1e-6)
        if root is not None:
            times_found.append(root)

print("Các thời điểm nhiệt độ bằng nhiệt độ trung bình:")
for i, time in enumerate(times_found):
    hours = int(time)
    minutes = int((time - hours) * 60)
    print(f"  Thời điểm {i+1}: {time:.4f} giờ = {hours:02d}:{minutes:02d}")
    print(f"    Kiểm tra: T({time:.4f}) = {T(time):.6f} F")

if times_found:
    print(f"Thời gian đầu tiên là: {times_found[0]:.6f} giờ")
else:
    print("Không tìm thấy thời điểm nào")

print("-"*70)
print("(c)")

# Nghiệm chính xác câu (a): Tích phân chính xác
def T_exact_integral(t):
    return 10*t - (6*18/np.pi)*np.cos(np.pi*t/18)

integral_exact = T_exact_integral(12) - T_exact_integral(0)
avg_temp_exact = integral_exact / 12

print(f"Nghiệm chính xác câu (a): {avg_temp_exact:.12f} F")

# Nghiệm chính xác câu (b): Giải phương trình T(t) = avg_temp_exact
def temp_diff_exact(t):
    return T(t) - avg_temp_exact

# Tìm nghiệm chính xác với độ chính xác cao hơn bằng phương pháp chia đôi
times_exact = []
for start in range(0, 24, 2):
    end = min(start + 2, 24)
    if temp_diff_exact(start) * temp_diff_exact(end) < 0:
        root = bisection_temp(temp_diff_exact, start, end, tol=1e-12)
        if root is not None:
            times_exact.append(root)

if times_exact:
    print(f"Nghiệm chính xác câu (b): {times_exact[0]:.12f} giờ")

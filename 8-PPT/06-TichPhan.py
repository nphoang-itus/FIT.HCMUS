import numpy as np
from scipy.integrate import quad

def simpson_1_3_rule(x_data, y_data):
    """Công thức Simpson 1/3 (Newton-Cotes 3 điểm)"""
    return (x_data[2] - x_data[0]) * (y_data[0] + 4*y_data[1] + y_data[2]) / 6

def simpson_3_8_rule(x_data, y_data):
    """Công thức Simpson 3/8 (Newton-Cotes 4 điểm)"""
    return (x_data[3] - x_data[0]) * (y_data[0] + 3*y_data[1] + 3*y_data[2] + y_data[3]) / 8

def boole_rule(x_data, y_data):
    """Công thức Boole (Newton-Cotes 5 điểm)"""
    return (x_data[4] - x_data[0]) * (7*y_data[0] + 32*y_data[1] + 12*y_data[2] + 32*y_data[3] + 7*y_data[4]) / 90

def gaussian_quadrature(func, a, b, points=None):
    """Tích phân bằng phương pháp Gauss"""
    result, _ = quad(func, a, b, points=points)
    return result

def relative_error(exact_value, approximate_value):
    """Tính sai số tương đối"""
    return np.abs((exact_value - approximate_value) / exact_value)

# Dữ liệu cho Newton-Cotes
x = np.array([1, 2, 3, 4, 5, 6, 7])
y = np.array([4, -6, -14, -14, 0, 34, 94])
I_exact = 42

# Tính tích phân bằng các công thức Newton-Cotes
I1 = simpson_1_3_rule(x, y)
I2 = simpson_3_8_rule(x, y)
I3 = boole_rule(x, y)

delta_I1 = relative_error(I_exact, I1)
delta_I2 = relative_error(I_exact, I2)
delta_I3 = relative_error(I_exact, I3)

print("I1: ", I1)
print("Relative error for I1: ", delta_I1)
print("I2: ", I2)
print("Relative error for I2: ", delta_I2)
print("I3: ", I3)
print("Relative error for I3: ", delta_I3)

# Phương pháp Gauss
def f(x):
    return np.exp(x)

I_exact_gauss = gaussian_quadrature(f, 2, 4)

I1_gauss = gaussian_quadrature(f, 2, 4, points=[3])
I2_gauss = gaussian_quadrature(f, 2, 4, points=[2, 4/3*2**(1/2)-2/3, 4/3*2**(1/2)+2/3])
I3_gauss = gaussian_quadrature(f, 2, 4, points=[2, 4/3*2**(1/2)-2/3, 4/3*2**(1/2)+2/3, 4])

delta_I1_gauss = relative_error(I_exact_gauss, I1_gauss)
delta_I2_gauss = relative_error(I_exact_gauss, I2_gauss)
delta_I3_gauss = relative_error(I_exact_gauss, I3_gauss)

print("| I1\t\t| δI1\t\t| I2\t\t| δI2\t\t| I3\t\t| δI3\t\t|") 
print("| {:.6f}\t| {:.6f}\t| {:.6f}\t| {:.6f}\t| {:.6f}\t| {:.6f}\t|".format(I1_gauss, 
delta_I1_gauss, I2_gauss, delta_I2_gauss, I3_gauss, delta_I3_gauss))
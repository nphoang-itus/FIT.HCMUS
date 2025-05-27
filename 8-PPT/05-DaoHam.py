import numpy as np

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

# Dữ liệu đầu vào
xx = np.array([0.9, 1, 1.1, 1.2])
yy = np.array([0.7833, 0.8415, 0.8912, 0.932])
df = 0.5403

# Sử dụng tỷ sai phân tiến
df_SPT = forward_difference(xx, yy, 1)
print(f"Giá trị đạo hàm xấp xỉ bằng sai phân tiến là {df_SPT}")
rEdf_SPT = relative_error(df, df_SPT)
print(f"Sai số tương đối {rEdf_SPT}")

# Sử dụng tỷ sai phân lùi
df_SPL = backward_difference(xx, yy, 1)
print(f"Giá trị đạo hàm xấp xỉ bằng sai phân lùi là {df_SPL}")
rEdf_SPL = relative_error(df, df_SPL)
print(f"Sai số tương đối {rEdf_SPL}")

# Sử dụng công thức ba điểm cuối
df_3DC = three_point_endpoint(xx, yy, 1)
print(f"Giá trị đạo hàm xấp xỉ bằng công thức 3 điểm cuối là {df_3DC}")
rEdf_3DC = relative_error(df, df_3DC)
print(f"Sai số tương đối {rEdf_3DC}")

# Sử dụng công thức 3 điểm giữa
df_3DG = three_point_midpoint(xx, yy, 1)
print(f"Giá trị đạo hàm xấp xỉ bằng công thức 3 điểm giữa là {df_3DG}")
rEdf_3DG = relative_error(df, df_3DG)
print(f"Sai số tương đối {rEdf_3DG}")

# Sử dụng công thức 5 điểm giữa (cần thêm điểm dữ liệu)
xx_extended = np.array([0.8, 0.9, 1, 1.1, 1.2])
yy_extended = np.array([0.7174, 0.7833, 0.8415, 0.8912, 0.932])

df_5DG = five_point_midpoint(xx_extended, yy_extended, 2)
print(f"Giá trị đạo hàm xấp xỉ bằng công thức 5 điểm giữa là {df_5DG}")
rEdf_5DG = relative_error(df, df_5DG)
print(f"Sai số tương đối {rEdf_5DG}")
import numpy as np

# 01: Phương pháp lặp

def iterative_method(A, B, tolerance = 1e-3, max_iterations = 100):
    X = np.zeros_like(B)

    iter_count = 0
    while iter_count < max_iterations:
        X_new = np.zeros_like(X)
        
        for i in range(len(A)):
            sum1 = sum(A[i][j] * X[j] for j in range(len(A)) if j != i)
            X_new[i] = (B[i] - sum1) / A[i][i]

        if np.linalg.norm(X_new - X, ord=np.inf) < tolerance:
            break

        X = X_new

    return X

A = np.array([
    [5, 1, 1],
    [1, 10, 1],
    [1, 1, 10],
], dtype=float )

B = np.array(
    [7, 12, 22],
dtype=float )

# root = iterative_method(A, B)
# print(f"Nghiệm của phương trình là: {root}")

# 02: Phương pháp seidel
def seidel_method(A, B, tol = 1e-3, max_iter = 100):
    X = np.zeros_like(B)

    iter_count = 0
    while iter_count < max_iter:
        X_new = np.copy(X)

        for i in range(len(A)):
            sum1 = sum(A[i][j] * X_new[j] for j in range(len(A)) if j != i)
            X_new[i] = (B[i] - sum1) / A[i][i]

        if np.linalg.norm(X_new - X, ord=np.inf) < tol:
            break

        X = X_new
    
    return X

root = seidel_method(A, B)
# print(f"Nghiệm của phương trình là: {root}")
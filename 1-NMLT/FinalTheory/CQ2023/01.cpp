#include <iostream>

/*
A = 
0   1   2   3   4   5   6
5   2   6   3   7   11  20

i = 0, j = 0:
    A[i] is prime:


*/

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
    return true;
}

int reduceArray(int A[], int& N) {
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
        if (isPrime(A[i])) {
            cnt++;
            for (int j = i + 1; j < N; ++j) {
                if (isPrime(A[j])) {
                    A[i] += A[j];
                    A[j] = -1;
                } else {
                    i = j - 1;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (A[i] == -1) {
            for (int j = i; j < N - 1; ++j) {
                A[j] = A[j + 1];
            }
            N--;
            i--;
        }
    }

    return cnt;
}

// Tối ưu:
int reduceArray_byGPT(int A[], int& N) {
    int cnt = 0;         // đếm số chuỗi nguyên tố liên tiếp
    int writeIdx = 0;    // vị trí ghi phần tử vào mảng mới

    for (int i = 0; i < N;) {
        if (isPrime(A[i])) {
            int sum = 0;
            while (i < N && isPrime(A[i])) {
                sum += A[i];
                ++i;
            }
            A[writeIdx++] = sum;
            ++cnt;
        } else {
            A[writeIdx++] = A[i++];
        }
    }

    N = writeIdx;
    return cnt;
}

int main() {
    // // testcase 1:
    // int N = 7;
    // int A[] = {5, 2, 6, 3, 7, 11, 20};

    // testcase 2:
    int N = 10;
    int A[] = {5, 2, 6, 7, 11, 8, 13, 5, 3, 13};

    std::cout << "Result: " << reduceArray(A, N) << "\n";
    std::cout << "New Array: ";
    for (int i = 0; i < N; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
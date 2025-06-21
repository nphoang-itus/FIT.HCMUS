#include <iostream>

#define MAX_COL 100

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
    return true;
}

void findSpecialPoints(int mat[][MAX_COL], int nRow, int nCol, int& xA, int& yA, int& xB, int& yB) {
    int max_1th = INT_MIN;
    int max_2th = INT_MIN;

    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
            if (isPrime(mat[i][j])) {
                // update max_1th = new max
                if (mat[i][j] >= max_1th) {
                    max_2th = max_1th;
                    xB = xA, yB = yA;

                    max_1th = mat[i][j];
                    xA = i; yA = j;
                } else if (mat[i][j] >= max_2th) {
                    max_2th = mat[i][j];
                    xB = i, yB = j;
                }
            }
        }
    }
}

void findSpecialPoints_byGPT(int mat[][MAX_COL], int nRow, int nCol, int& xA, int& yA, int& xB, int& yB) {
    int max_1th = INT_MIN, max_2th = INT_MIN;
    bool foundMax = false, foundSecond = false;

    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
            int val = mat[i][j];
            if (isPrime(val)) {
                if (!foundMax || val > max_1th) {
                    max_2th = max_1th; xB = xA; yB = yA; foundSecond = foundMax;
                    max_1th = val; xA = i; yA = j; foundMax = true;
                } else if ((!foundSecond || val > max_2th) && val < max_1th) {
                    max_2th = val; xB = i; yB = j; foundSecond = true;
                }
            }
        }
    }

    if (!foundSecond) {
        xB = yB = -1; // hoặc thông báo "Không tìm thấy số nguyên tố lớn nhì"
    }
}

int countPrimeFromTwoPoints(int mat[][MAX_COL], int nRow, int nCol, int xA, int yA, int xB, int yB) {
    int up = 0, down = nRow - 1, left = 0, right = nCol - 1;
    int cnt = 0;
    bool flag = false;
    
    while (up <= down && left <= right) {
        // duyệt cạnh trên
        for (int i = left; i <= right; ++i) { // 0 -> 3
            if (mat[up][i] == mat[xA][yA] || mat[up][i] == mat[xB][yB]) {
                flag = !flag;
                continue;
            }
            
            if (flag == true && isPrime(mat[up][i])) {
                cnt++;
                std::cout << mat[up][i] << " ";
            }
        }
        up++;

        // duyệt cạnh bên phải
        for (int i = up; i <= down; ++i) { // 1 -> 3
            if (mat[i][right] == mat[xA][yA] || mat[i][right] == mat[xB][yB]) {
                flag = !flag;
                continue;
            }
            
            if (flag == true && isPrime(mat[i][right])) {
                std::cout << mat[i][right] << ' ';
                cnt++;
            }
        }
        right--;

        // duyệt cạnh dưới
        for (int i = right; i >= left; --i) { // 2 -> 0
            if (mat[down][i] == mat[xA][yA] || mat[down][i] == mat[xB][yB]) {
                flag = !flag;
                continue;
            }
            
            if (flag == true && isPrime(mat[down][i])) {
                std::cout << mat[down][i] << " ";
                cnt++;
            }
        }
        down--;

        // duyệt cạnh trái
        for (int i = down; i >= up; --i) {
            if (mat[i][left] == mat[xA][yA] || mat[i][left] == mat[xB][yB]) {
                flag = !flag;
                continue;
            }
            
            if (flag == true && isPrime(mat[i][left])) {
                std::cout << mat[i][left] << " ";
                cnt++;
            }
        }
        left++;
    }

    std::cout << "\n";

    return cnt;
}

// Hàm in ma trận xoắn ốc 
void printMatrix(int mat[][MAX_COL], int nRow, int nCol) {
    int up = 0, down = nRow - 1, left = 0, right = nCol - 1;
    
    while (up <= down && left <= right) {
        // duyệt cạnh trên
        for (int i = left; i <= right; ++i) { // 0 -> 3
            std::cout << mat[up][i] << " ";
        }
        up++;

        // duyệt cạnh bên phải
        for (int i = up; i <= down; ++i) { // 1 -> 3
            std::cout << mat[i][right] << ' ';
        }
        right--;

        // duyệt cạnh dưới
        for (int i = right; i >= left; --i) { // 2 -> 0
            std::cout << mat[down][i] << " ";
        }
        down--;

        // duyệt cạnh trái
        for (int i = down; i >= up; --i) {
            std::cout << mat[i][left] << " ";
        }
        left++;
    }
}

int main() {
    // testcase1
    int mat[MAX_COL][MAX_COL] = {
        {9, 21, 36, 44},
        {7, 5, 14, 52},
        {20, 11, 17, 88},
        {13, 9, 8, 25}
    };

    int nCol, nRow, xA, yA, xB, yB;
    nCol = nRow = 4;
    xA = yA = xB = yB = -1;

    // // testcase2
    // int mat[MAX_COL][MAX_COL];
    // int cnt = 16;
    // for (int i = 0; i < nRow; ++i) {
    //     for (int j = 0; j < nCol; ++j) {
    //         mat[i][j] = cnt--;
    //     }
    // }

    // for (int i = 0; i < nRow; ++i) {
    //     for (int j = 0; j < nCol; ++j) {
    //         std::cout << mat[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }


    findSpecialPoints(mat, nRow, nCol, xA, yA, xB, yB);

    std::cout << "A{" << xA << ", " << yA << "}\n";
    std::cout << "B{" << xB << ", " << yB << "}\n";

    // printMatrix(mat, nRow, nCol);
    std::cout << "Number of prime: " << countPrimeFromTwoPoints(mat, nRow, nCol, xA, yA, xB, yB) << "\n";

    return 0;
}
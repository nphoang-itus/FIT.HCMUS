#include <iostream>

int countByRows(int B[], int nB, int A[], int nA) {
    int count = 0;

    for (int i = 0; i <= nB - nA; ++i) {
        bool match = true;
        for (int k = 0; k < nA; ++k) {
            if (B[i + k] != A[k]) {
                match = false;
                break;
            }
        }
        if (match == true) {
            count++;
            i = i + nA - 1;
        }
    }

    return count;
}

int countNumberOfPassword(int B[][100], int nRow, int nCol, int A[], int nA) {
    int count = 0;
    
    // Đếm theo hàng
    for (int iRow = 0; iRow < nRow; ++iRow) {
        // Từ trái sang phải
        count += countByRows(B[iRow], nCol, A, nA);
        
        // Từ phải qua trái
        int tempArr[nCol];
        for (int i = nCol - 1; i >= 0; --i) {
            tempArr[nCol - i - 1] = B[iRow][i];
        }
        count += countByRows(tempArr, nCol, A, nA);
    }

    // Đếm theo cột
    for (int iCol = 0; iCol < nCol; ++iCol) {
        // Từ trên xuống lên
        int tempArr[nRow];
        for (int i = 0; i < nRow; ++i) {
            tempArr[i] = B[i][iCol];
        }
        count += countByRows(tempArr, nRow, A, nA);

        // Từ dưới lên
        for (int i = nRow - 1; i >= 0; --i) {
            tempArr[nRow - i - 1] = B[i][iCol];
        }
        count += countByRows(tempArr, nRow, A, nA);
    }

    return count;
}

int main() {
    int B[][100] = {
        {3, 2, 1, 2, 3, 1},
        {3, 2, 1, 3, 2, 1},
        {2, 0, 2, 1, 7, 9},
        {1, 2, 3, 2, 1, 6}
    };

    int A[] = {3, 2, 1};
    
    int nCol = 6, nRow = 4, nA = 3;

    std::cout << countNumberOfPassword(B, nRow, nCol, A, nA) << "\n";

    return 0;
}
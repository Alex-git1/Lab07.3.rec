#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo);
void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo);
void InputRow(int** a, const int rowNo, const int colCount, int colNo);
void InputRows(int** a, const int rowCount, const int colCount, int rowNo);
void PrintRow(int** a, const int rowNo, const int colCount, int colNo);
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo);
void ShiftRightRow(int** a, const int colCount, int shift, int rowNo, int colNo);
void ShiftRight(int** a, const int rowCount, const int colCount, int shift, int rowNo);
void ShiftDownColumn(int** a, const int rowCount, int shift, int colNo, int rowNo);
void ShiftDown(int** a, const int rowCount, const int colCount, int shift, int colNo);
int RowWithMostZeroes(int** a, const int rowCount, const int colCount, int rowNo, int maxZeroes, int& maxRowIndex);

int main() {
    srand((unsigned)time(NULL));

    int rowCount, colCount, shift;
    bool shiftRight;

    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    cout << "Enter shift amount (x): "; cin >> shift;
    cout << "Shift right? (1 for yes, 0 for down): "; cin >> shiftRight;

    if (shiftRight) {
        ShiftRight(a, rowCount, colCount, shift, 0);
    }
    else {
        ShiftDown(a, rowCount, colCount, shift, 0);
    }

    PrintRows(a, rowCount, colCount, 0);

    int maxRowIndex = -1;
    RowWithMostZeroes(a, rowCount, colCount, 0, 0, maxRowIndex);

    if (maxRowIndex != -1) {
        cout << "Row with most zeroes: " << maxRowIndex << endl;
    }
    else {
        cout << "No zeroes in the matrix." << endl;
    }

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void ShiftRightRow(int** a, const int colCount, int shift, int rowNo, int colNo) {
    if (shift > 0) {
        int temp = a[rowNo][colCount - 1];  
        for (int j = colCount - 1; j > 0; j--) {
            a[rowNo][j] = a[rowNo][j - 1];
        }
        a[rowNo][0] = temp;
        ShiftRightRow(a, colCount, shift - 1, rowNo, 0);
    }
}

void ShiftRight(int** a, const int rowCount, const int colCount, int shift, int rowNo) {
    if (rowNo < rowCount) {
        ShiftRightRow(a, colCount, shift, rowNo, 0);
        ShiftRight(a, rowCount, colCount, shift, rowNo + 1);
    }
}

void ShiftDownColumn(int** a, const int rowCount, int shift, int colNo, int rowNo) {
    if (shift > 0) {
        int temp = a[rowCount - 1][colNo]; 
        for (int i = rowCount - 1; i > 0; i--) {
            a[i][colNo] = a[i - 1][colNo];
        }
        a[0][colNo] = temp;
        ShiftDownColumn(a, rowCount, shift - 1, colNo, 0);
    }
}

void ShiftDown(int** a, const int rowCount, const int colCount, int shift, int colNo) {
    if (colNo < colCount) {
        ShiftDownColumn(a, rowCount, shift, colNo, 0);
        ShiftDown(a, rowCount, colCount, shift, colNo + 1);
    }
}

int RowWithMostZeroes(int** a, const int rowCount, const int colCount, int rowNo, int maxZeroes, int& maxRowIndex) {
    if (rowNo < rowCount) {
        int zeroCount = 0;
        for (int j = 0; j < colCount; j++) {
            if (a[rowNo][j] == 0)
                zeroCount++;
        }
        if (zeroCount > maxZeroes) {
            maxZeroes = zeroCount;
            maxRowIndex = rowNo;
        }
        return RowWithMostZeroes(a, rowCount, colCount, rowNo + 1, maxZeroes, maxRowIndex);
    }
    return maxRowIndex;
}

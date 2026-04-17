#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

const int V = 20;

void generateMatrix(int a[100][100], int n) {
    srand(time(0));
    int minVal = -10 - V;
    int maxVal = 10 + V;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
}

void printMatrix(int a[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}


int countNegativesSector10(int a[100][100], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = n / 2; j < n; j++) {
            if (a[i][j] < 0) count++;
        }
    }
    return count;
}


void processSector3(int a[100][100], int n) {
    int minDiag = a[0][0];
    for (int i = 0; i < n; i++) {
        if (a[i][i] < minDiag) minDiag = a[i][i];
    }
    for (int i = 0; i < n; i++) {
        a[i][i] = minDiag;
    }
    cout << "Кількість елементів у секторі 3\\ (головна діагональ): " << n << endl;
    cout << "Мінімальний елемент діагоналі: " << minDiag << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    int a[100][100];
    cout << "Введіть розмір матриці n: ";
    cin >> n;

    generateMatrix(a, n);

    cout << "Початкова матриця:\n";
    printMatrix(a, n);

    int negCount = countNegativesSector10(a, n);
    cout << "Кількість від’ємних елементів у секторі 10: " << negCount << endl;

    processSector3(a, n);

    cout << "Матриця після обробки сектору 3\\:\n";
    printMatrix(a, n);

    return 0;
}


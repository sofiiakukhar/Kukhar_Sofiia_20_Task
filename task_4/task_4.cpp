#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int k;

    cout << "Введіть ціле невід'ємне число k (макс. кількість слів): ";
    cin >> k;

    if (k < 0) {
        cout << "Помилка: Число k не може бути від'ємним." << endl;
        return 1;
    }

    cin.ignore();

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "Не вдалося відкрити файл input.txt" << endl;
        return 1;
    }

    if (!fout.is_open()) {
        cout << "Не вдалося відкрити файл output.txt" << endl;
        fin.close();
        return 1;
    }

    string line;
    int linesWritten = 0;

    cout << "\nПочаток обробки..." << endl;

    while (getline(fin, line)) {
        stringstream ss(line);
        string word;
        int count = 0;

        while (ss >> word) {
            count++;
            if (count > k) {
                break;
            }
        }

        if (count <= k) {
            fout << line << endl;
            linesWritten++;
        }
    }

    fin.close();
    fout.close();

    cout << "-----------------------------------" << endl;
    cout << "Обробка завершена успішно." << endl;
    if (linesWritten == 0) {
        cout << "Рядків, що задовольняють умову (count <= " << k << "), не знайдено." << endl;
    }
    else {
        cout << "Записано " << linesWritten << " рядків у файл output.txt" << endl;
    }

    return 0;
}


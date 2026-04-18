#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Footballer {
    string surname;
    string name;
    string position;
    double price;
    string club;

    void print() {
        cout << "Прізвище: " << surname << "\n";
        cout << "Ім'я: " << name << "\n";
        cout << "Позиція: " << position << "\n";
        cout << "Трансферна ціна: " << price << " млн\n";
        cout << "Клуб: " << club << "\n";
        cout << "------------------------\n";
    }
};

const string FILE_NAME = "footballers.txt";

void addFootballer() {
    ofstream fout(FILE_NAME, ios::app);
    Footballer f;
    cout << "Прізвище: ";
    cin >> f.surname;
    cout << "Ім'я: ";
    cin >> f.name;
    cout << "Позиція: ";
    cin >> f.position;
    cout << "Трансферна ціна (млн): ";
    cin >> f.price;
    cout << "Клуб: ";
    cin >> f.club;

    fout << f.surname << " " << f.name << " " << f.position << " "
        << f.price << " " << f.club << endl;
    fout.close();
}


void viewFootballers() {
    ifstream fin(FILE_NAME);
    Footballer f;
    while (fin >> f.surname >> f.name >> f.position >> f.price >> f.club) {
        f.print();
    }
    fin.close();
}


void top5Footballers() {
    ifstream fin(FILE_NAME);
    Footballer arr[100];
    int n = 0;

    while (fin >> arr[n].surname >> arr[n].name >> arr[n].position >> arr[n].price >> arr[n].club) {
        n++;
    }
    fin.close();


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].price < arr[j + 1].price) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "5 найдорожчих футболістів:\n";
    for (int i = 0; i < min(n, 5); i++) {
        arr[i].print();
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    do {
        cout << "Меню:\n";
        cout << "1. Додати футболіста\n";
        cout << "2. Переглянути всіх футболістів\n";
        cout << "3. Вивести 5 найдорожчих футболістів\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1: addFootballer(); break;
        case 2: viewFootballers(); break;
        case 3: top5Footballers(); break;
        case 0: cout << "Вихід з програми.\n"; break;
        default: cout << "Невірний вибір!\n";
        }
    } while (choice != 0);

    return 0;
}

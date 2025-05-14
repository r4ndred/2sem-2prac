#include <iostream>

using namespace std;

// Структура для представления тройки целых чисел (d, a, b)
struct Triple {
    int first, second, third;
    Triple(int d, int a, int b) : first(d), second(a), third(b) {}
};

// Функция расширенного алгоритма Евклида
// Возвращает тройку (d, a, b), где d - НОД(a, b), а также находит коэффициенты x и y такие, что a*x + b*y = d
Triple extendedEuclidean(int a, int b) {
    if (b == 0) {
        return Triple(a, 1, 0); // Базовый случай: если b равно 0, возвращаем (a, 1, 0)
    } else {
        Triple vals = extendedEuclidean(b, a % b); // Рекурсивный случай: вызываем функцию для b и остатка от деления a на b
        int d = vals.first; // НОД(a, b)
        int x = vals.third; // Коэффициент перед a в уравнении a*x + b*y = d
        int y = vals.second - (a / b) * vals.third; // Коэффициент перед b в уравнении a*x + b*y = d
        return Triple(d, x, y);
    }
}

// Функция для вычисления взаимнообратного числа s^-1 mod m
int modInverse(int s, int m) {
    Triple vals = extendedEuclidean(s, m); // Используем расширенный алгоритм Евклида
    int d = vals.first; // НОД(s, m)
    int a = vals.second; // Коэффициент перед s в уравнении s*a + m*b = d
    if (d > 1) {
        return -1; // Если НОД(s, m) больше 1, взаимнообратное число не существует
    }
    return (a % m + m) % m; // Возвращаем коэффициент a, удовлетворяющий условию a*s + b*m = 1
}

int main() {
    setlocale(LC_ALL, "russian");
    int s, m;
    cout << "Введите c: ";
    cin >> s; // Число, для которого нужно найти взаимнообратное
    cout << "Введите m: ";
    cin >> m; // Модуль
    int inverse = modInverse(s, m); // Вызываем функцию modInverse
    if (inverse == -1) {
        cout << "Обратного числа не существует, так как числа не взаимно простые." << endl;
    } else {
        cout << "Обратное число для " << s << " по модулю " << m << " = " << inverse << endl;
    }
    return 0;
}

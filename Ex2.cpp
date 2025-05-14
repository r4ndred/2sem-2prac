#include <iostream>

using namespace std;

// Структура для представления пары целых чисел
struct Pair {
    int first;  // Первый элемент пары (обычно хранит остаток)
    int second; // Второй элемент пары (обычно хранит коэффициент)

    // Конструктор структуры Pair
    Pair(int first, int second) : first(first), second(second) {}
};

// Функция для нахождения модулярного обратного числа с выводом шагов
Pair modInverse(int c, int m, bool verbose = false) {
    if (verbose) {
        cout << "\nНачальные значения:\n";
        cout << "u = (" << m << ", 0)\n";
        cout << "v = (" << c << ", 1)\n";
        cout << "-----------------------------\n";
    }

    Pair u(m, 0); // Инициализация пары u = (m, 0)
    Pair v(c, 1); // Инициализация пары v = (c, 1)
    int iteration = 1; // Счетчик итераций

    while (v.first != 0) { // Пока первый элемент v не равен нулю
        if (verbose) {
            cout << "Итерация " << iteration++ << ":\n";
            cout << "u = (" << u.first << ", " << u.second << ")\n";
            cout << "v = (" << v.first << ", " << v.second << ")\n";
        }

        // Вычисляем частное от деления u.first на v.first
        int q = u.first / v.first;
        if (verbose) cout << "q = u.first / v.first = " << u.first << " / " << v.first << " = " << q << "\n";

        // Вычисляем новую пару t:
        // t.first = остаток от деления u.first на v.first
        // t.second = u.second - q * v.second
        Pair t(u.first % v.first, u.second - q * v.second);
        if (verbose) {
            cout << "t.first = u.first % v.first = " << u.first << " % " << v.first << " = " << t.first << "\n";
            cout << "t.second = u.second - q*v.second = " << u.second << " - " << q << "*" << v.second 
                 << " = " << t.second << "\n";
        }

        // Обновляем значения пар
        u = v;
        v = t;
        if (verbose) {
            cout << "Новые значения:\n";
            cout << "u = v = (" << u.first << ", " << u.second << ")\n";
            cout << "v = t = (" << v.first << ", " << v.second << ")\n";
            cout << "-----------------------------\n";
        }
    }

    // Корректировка, если результат отрицательный
    if (u.second < 0) {
        if (verbose) {
            cout << "Корректировка отрицательного результата:\n";
            cout << "Исходный коэффициент: " << u.second << "\n";
            cout << "Добавляем m = " << m << " к коэффициенту\n";
        }
        u.second += m;
        if (verbose) cout << "Новый коэффициент: " << u.second << "\n";
    }

    if (verbose) {
        cout << "\nФинальные значения:\n";
        cout << "u = (" << u.first << ", " << u.second << ")\n";
        cout << "НОД = " << u.first << "\n";
    }

    return u;
}

int main() {
    setlocale(LC_ALL, "russian"); // Устанавливаем русскую локаль
    
    int c, m;
    cout << "Введите число c: ";
    cin >> c;
    cout << "Введите модуль m: ";
    cin >> m;

    // Вызываем функцию с выводом шагов (true)
    Pair result = modInverse(c, m, true);

    // Проверяем, существует ли обратный элемент
    if (result.first == 1) {
        cout << "\nРезультат:\n";
        cout << "Обратный элемент d = " << result.second << endl;
        cout << "Проверка: (" << c << " * " << result.second << ") mod " << m 
             << " = " << (c * result.second) % m << endl;
    } else {
        cout << "\nРезультат:\n";
        cout << "Обратный элемент не существует, так как НОД(" << c << ", " << m << ") = " 
             << result.first << " ≠ 1" << endl;
    }

    return 0;
}

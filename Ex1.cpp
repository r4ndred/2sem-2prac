#include <iostream>
#include <cmath> // Для использования математических функций

using namespace std;

// Функция для проверки, является ли число простым
bool isPrime(int number) {
    if (number <= 1) return false; // Если число меньше или равно 1, то оно не является простым
    for (int i = 2; i <= sqrt(number); ++i) { // Проверяем делители числа до квадратного корня из числа
        if (number % i == 0) return false; // Если найден делитель, то число не является простым
    }
    return true; // Если не найдено делителей, то число простое
}

// Функция для быстрого возведения в степень по модулю
int modularExponentiation(int base, int exponent, int modulus) {
    int result = 1; // Инициализируем результат
    base = base % modulus; // Уменьшаем base до модуля
    while (exponent > 0) { // Пока степень больше 0
        if (exponent % 2 == 1) { // Если степень нечетная
            result = (result * base) % modulus; // Умножаем результат на base и берем по модулю
        }
        exponent = exponent >> 1; // Уменьшаем степень вдвое
        base = (base * base) % modulus; // Умножаем base на само себя и берем по модулю
    }
    return result; // Возвращаем результат
}

// Функция для проверки выполнения условия теоремы Ферма
bool fermatCondition(int base, int modulus) {
    if (modulus <= 1) return false; // Если modulus меньше или равен 1, то условие теоремы Ферма не выполнено
    return modularExponentiation(base, modulus - 1, modulus) == 1; // Вычисляем a^(p - 1) % p и сравниваем с 1
}

// Функция для вычисления a^x mod p по первому методу
int firstMethod(int base, int exponent, int modulus) {
    if (base % modulus == 0 || !isPrime(modulus) || exponent <= 0) { // Проверяем условия для использования первого метода
        cout << "Ошибка!" << endl; // Выводим сообщение об ошибке
        return -1; // Возвращаем -1
    }

    int result = 1; // Инициализируем результат
    for (int i = 1; i <= exponent; ++i) { // Цикл для возведения числа в степень
        result *= base; // Умножаем результат на число
        result %= modulus; // Берем по модулю
    }

    return result; // Возвращаем результат
}

// Функция для вычисления a^x mod p по второму методу
int secondMethod(int base, int exponent, int modulus) {
    if (!isPrime(modulus)) { // Проверяем модуль на простоту
        cout << "Модуль должен быть простым числом!" << endl; // Выводим сообщение об ошибке
        return -1; // Возвращаем -1
    }

    if (base % modulus == 0 && exponent > 1) { // Проверяем условие теоремы Ферма
        cout << "Условие теоремы не выполнено" << endl; // Выводим сообщение об ошибке
        return -1; // Возвращаем -1
    }

    int t = (int) (log(exponent) / log(2)); // Вычисляем количество степеней
    int binaryExponent[t + 1]; // Создаем массив для хранения двоичного представления степени
    int origExponent = exponent; // Сохраняем оригинальную степень
    for (int i = t; i >= 0; --i) { // Цикл для заполнения массива двоичным представлением степени
        binaryExponent[i] = origExponent % 2; // Заполняем массив остатками от деления степени на 2
        origExponent /= 2; // Делим степень на 2
    }

    int remainders[t + 1]; // Создаем массив для хранения остатков от деления
    remainders[0] = base; // Записываем начальное значение
    int temp = base; // Сохраняем начальное значение
    for (int i = 1; i <= t; ++i) { // Цикл для вычисления остатков
        temp = (temp * temp) % modulus; // Вычисляем квадрат и берем по модулю
        remainders[i] = temp; // Записываем остаток в массив
    }

    int result = 1; // Инициализируем результат
    for (int i = t; i >= 0; --i) { // Обратный проход по массиву двоичного представления степени
        if (binaryExponent[i] == 1) { // Если соответствующий бит равен 1
            result = (result * remainders[t - i]) % modulus; // Умножаем результат на соответствующий остаток и берем по модулю
        }
    }
    return result; // Возвращаем результат
}

int main() { // Главная функция программы

    int base, exponent, modulus; // Переменные для хранения введенных чисел

    cout << "Введите число a: "; // Выводим приглашение для ввода числа
    cin >> base; // Считываем число
    cout << "Введите степень x: "; // Выводим приглашение для ввода степени
    cin >> exponent; // Считываем степень
    cout << "Введите простое число p: "; // Выводим приглашение для ввода простого числа
    cin >> modulus; // Считываем простое число

    int resultFirstMethod = firstMethod(base, exponent, modulus); // Вычисляем результат первого метода
    cout << "Первый метод" << endl; // Выводим сообщение о первом методе
    cout << "Остаток: " << resultFirstMethod << endl; // Выводим результат первого метода

    int resultSecondMethod = secondMethod(base, exponent, modulus); // Вычисляем результат второго метода
    if (resultSecondMethod != -1) { // Если результат не равен -1
        cout << "Второй метод" << endl; // Выводим сообщение о втором методе
        cout << "Остаток: " << resultSecondMethod << endl; // Выводим результат второго метода
    }

    return 0; // Возвращаем 0, указывая на успешное завершение программы
}

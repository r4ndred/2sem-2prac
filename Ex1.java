import java.util.Scanner;

public class Main {

    // Функция для проверки, является ли число простым
    public static boolean isPrime(int number) {
        if (number <= 1) return false; // Если число меньше или равно 1, то оно не является простым
        for (int i = 2; i <= Math.sqrt(number); ++i) { // Проверяем делители числа до квадратного корня из числа
            if (number % i == 0) return false; // Если найден делитель, то число не является простым
        }
        return true; // Если не найдено делителей, то число простое
    }

    // Функция для быстрого возведения в степень по модулю
    public static int modularExponentiation(int base, int exponent, int modulus) {
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
    public static boolean fermatCondition(int base, int modulus) {
        if (modulus <= 1) return false; // Если modulus меньше или равен 1, то условие теоремы Ферма не выполнено
        return modularExponentiation(base, modulus - 1, modulus) == 1; // Вычисляем a^(p - 1) % p и сравниваем с 1
    }

    // Функция для вычисления a^x mod p по первому методу
    public static int firstMethod(int base, int exponent, int modulus) {
        if (base % modulus == 0 || !isPrime(modulus) || exponent <= 0) { // Проверяем условия для использования первого метода
            System.out.println("Ошибка!"); // Выводим сообщение об ошибке
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
    public static int secondMethod(int base, int exponent, int modulus) {
        if (!isPrime(modulus)) { // Проверяем модуль на простоту
            System.out.println("Модуль должен быть простым числом!"); // Выводим сообщение об ошибке
            return -1; // Возвращаем -1
        }

        if (base % modulus == 0 && exponent > 1) { // Проверяем условие теоремы Ферма
            System.out.println("Условие теоремы не выполнено"); // Выводим сообщение об ошибке
            return -1; // Возвращаем -1
        }

        int t = (int) (Math.log(exponent) / Math.log(2)); // Вычисляем количество степеней
        int[] binaryExponent = new int[t + 1]; // Создаем массив для хранения двоичного представления степени
        int origExponent = exponent; // Сохраняем оригинальную степень
        for (int i = t; i >= 0; --i) { // Цикл для заполнения массива двоичным представлением степени
            binaryExponent[i] = origExponent % 2; // Заполняем массив остатками от деления степени на 2
            origExponent /= 2; // Делим степень на 2
        }

        int[] remainders = new int[t + 1]; // Создаем массив для хранения остатков от деления
        remainders[0] = base; // Записываем начальное значение
        int temp = base; // Сохраняем начальное значение
        for (int i = 1; i <= t; ++i) { // Цикл для вычисления остатков
            temp = (temp * temp) % modulus; // Вычисляем квадрат и берем по модулю
            remainders[i] = temp; // Записываем остаток в массив
        }

        int result = 1; // Инициализируем результат
        for (int i = binaryExponent.length - 1; i >= 0; --i) { // Обратный проход по массиву двоичного представления степени
            if (binaryExponent[i] == 1) { // Если соответствующий бит равен 1
                result = (result * remainders[binaryExponent.length - 1 - i]) % modulus; // Умножаем результат на соответствующий остаток и берем по модулю
            }
        }
        return result; // Возвращаем результат
    }

    public static void main(String[] args) { // Главная функция программы

        Scanner scanner = new Scanner(System.in); // Создаем объект Scanner для ввода данных

        System.out.print("Введите число a: "); // Выводим приглашение для ввода числа
        int base = scanner.nextInt(); // Считываем число
        System.out.print("Введите степень x: "); // Выводим приглашение для ввода степени
        int exponent = scanner.nextInt(); // Считываем степень
        System.out.print("Введите простое число p: "); // Выводим приглашение для ввода простого числа
        int modulus = scanner.nextInt(); // Считываем простое число

        int resultFirstMethod = firstMethod(base, exponent, modulus); // Вычисляем результат первого метода
        System.out.println("Первый метод"); // Выводим сообщение о первом методе
        System.out.println("Остаток: " + resultFirstMethod); // Выводим результат первого метода

        int resultSecondMethod = secondMethod(base, exponent, modulus); // Вычисляем результат второго метода
        if (resultSecondMethod != -1) { // Если результат не равен -1
            System.out.println("Второй метод"); // Выводим сообщение о втором методе
            System.out.println("Остаток: " + resultSecondMethod); // Выводим результат второго метода
        }
    }
}

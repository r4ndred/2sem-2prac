import java.util.Scanner;

// Класс для представления тройки целых чисел (d, a, b)
class Triple {
    int first, second, third;

    // Конструктор класса Triple
    Triple(int d, int a, int b) {
        this.first = d;
        this.second = a;
        this.third = b;
    }
}

public class Main {
    // Функция расширенного алгоритма Евклида
    // Возвращает тройку (d, a, b), где d - НОД(a, b),
    // а также находит коэффициенты x и y такие, что a*x + b*y = d
    static Triple extendedEuclidean(int a, int b) {
        if (b == 0) {
            return new Triple(a, 1, 0); // Базовый случай: если b равно 0, возвращаем (a, 1, 0)
        } else {
            // Рекурсивный случай: вызываем функцию для b и остатка от деления a на b,
            // получаем результаты (НОД, x, y) и вычисляем новые коэффициенты
            Triple vals = extendedEuclidean(b, a % b);
            int d = vals.first; // НОД(a, b)
            int x = vals.third; // Коэффициент перед a в уравнении a*x + b*y = d
            int y = vals.second - (a / b) * vals.third; // Коэффициент перед b в уравнении a*x + b*y = d
            return new Triple(d, x, y);
        }
    }

    // Функция для вычисления взаимнообратного числа s^-1 mod m
    static int modInverse(int s, int m) {
        // Используем расширенный алгоритм Евклида для нахождения НОД(s, m) и коэффициентов a и b
        Triple vals = extendedEuclidean(s, m);
        int d = vals.first; // НОД(s, m)
        int a = vals.second; // Коэффициент перед s в уравнении s*a + m*b = d
        if (d > 1) {
            return -1; // Если НОД(s, m) больше 1, взаимнообратное число не существует
        }
        return (a % m + m) % m; // Возвращаем коэффициент a, удовлетворяющий условию a*s + b*m = 1
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите c: ");
        int s = scanner.nextInt(); // Число, для которого нужно найти взаимнообратное
        System.out.print("Введите m: ");
        int m = scanner.nextInt(); // Модуль
        int inverse = modInverse(s, m); // Вызываем функцию modInverse
        if (inverse == -1) {
            System.out.println("Обратного числа не существует, так как числа не взаимно простые.");
        } else {
            System.out.println("Обратное число для " + s + " по модулю " + m + " = " + inverse);
        }
    }
}

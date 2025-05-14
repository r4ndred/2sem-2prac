import java.util.Scanner;

// Класс для представления пары целых чисел
class Pair {
    int first, second; // Поля для первого и второго элементов пары

    // Конструктор класса Pair
    Pair(int first, int second) {
        this.first = first;
        this.second = second;
    }
}

public class Main {
    // Функция для нахождения модулярного обратного числа
    static Pair modInverse(int c, int m) {
        Pair u = new Pair(m, 0); // Инициализируем пару (m, 0)
        Pair v = new Pair(c, 1); // Инициализируем пару (c, 1)
        while (v.first != 0) { // Пока второй элемент пары v не равен нулю
            int q = u.first / v.first; // Находим частное от деления первого элемента пары u на первый элемент пары v
            Pair t = new Pair(u.first % v.first, u.second - q * v.second); // Вычисляем новую пару (u % v, u - q * v)
            u = v; // Обновляем пару u
            v = t; // Обновляем пару v
        }
        if (u.second < 0) // Если второй элемент пары u отрицательный
            u.second += m; // Добавляем m к второму элементу пары u
        return u; // Возвращаем пару u
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите c: "); // Выводим приглашение для ввода пользователем c
        int c = scanner.nextInt(); // Читаем значение c

        System.out.print("Введите m: "); // Выводим приглашение для ввода пользователем m
        int m = scanner.nextInt(); // Читаем значение m

        Pair result = modInverse(c, m); // Вызываем функцию modInverse для нахождения модулярного обратного числа

        if (result.first == 1) // Если первый элемент результата равен 1
            System.out.println("d = " + result.second); // Выводим модулярное обратное число d
        else
            System.out.println("d не существует, так как c и m - не взаимно простые числа"); // Выводим сообщение о том, что модулярное обратное число не существует
    }
}

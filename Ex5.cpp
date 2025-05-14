#include <iostream>

using namespace std;

class LastDigitOfPower {
private:
    int Osnovanie; // переменная для хранения основания степени
    int Stepen; // переменная для хранения показателя степени

public:
    LastDigitOfPower(int Osnovanie, int Stepen) : Osnovanie(Osnovanie), Stepen(Stepen) {} // конструктор класса с инициализацией полей

    int lastDigitOfPower() { // метод для определения последней цифры степени
        if (Osnovanie == 0) { // проверка, если основание равно нулю
            return 0; // возвращаем ноль
        }

        int lastDigit = Osnovanie % 10; // определяем последнюю цифру основания

        int period = getPeriodOfLastDigit(lastDigit); // получаем период последней цифры

        int remainder = Stepen % period; // определяем остаток от деления показателя степени на период
        if (remainder == 0) { // если остаток равен нулю
            remainder = period; // присваиваем остатку значение периода
        }

        int result = 1; // переменная для хранения результата
        for (int i = 0; i < remainder; i++) { // цикл от 0 до остатка
            result = (result * lastDigit) % 10; // вычисляем результат, учитывая только последнюю цифру
        }

        return result; // возвращаем результат
    }

private:
    static int getPeriodOfLastDigit(int lastDigit) { // статический метод для определения периода последней цифры
        if (lastDigit == 1 || lastDigit == 5) { // если последняя цифра равна 1 или 5
            return 1; // период равен 1
        }
        else { // иначе
            return 4; // период равен 4
        }
    }
};

int main() { // главная функция программы
    setlocale(LC_ALL, "russian"); // установка локали для вывода на русском языке
    int Osnovanie, Stepen1, Stepen2; // объявление переменных для основания и показателей степени
    cout << "Введите основание: "; // вывод приглашения на ввод основания
    cin >> Osnovanie; // считываем основание с клавиатуры

    cout << "Введите показатель 1: "; // вывод приглашения на ввод первого показателя степени
    cin >> Stepen1; // считываем первый показатель степени с клавиатуры

    cout << "Введите показатель 2: "; // вывод приглашения на ввод второго показателя степени
    cin >> Stepen2; // считываем второй показатель степени с клавиатуры

    LastDigitOfPower obj(Stepen1, Stepen2); // создаем объект класса с передачей показателей степени
    int lastDigit = obj.lastDigitOfPower(); // вызываем метод для определения последней цифры степени

    LastDigitOfPower obj2(Osnovanie, lastDigit); // создаем второй объект класса с передачей основания и последней цифры предыдущей степени
    int lastDigit2 = obj2.lastDigitOfPower(); // вызываем метод для определения последней цифры степени

    cout << "Последняя цифра данного числа: " << lastDigit2 << endl; // выводим результат

    return 0; // возвращаем ноль, указывая на успешное завершение программы
}

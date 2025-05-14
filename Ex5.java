import java.util.Scanner;

class LastDigitOfPower {
    private int Osnovanie; // переменная для хранения основания степени
    private int Stepen; // переменная для хранения показателя степени

    public LastDigitOfPower(int Osnovanie, int Stepen) {
        this.Osnovanie = Osnovanie;
        this.Stepen = Stepen;
    }

    public int lastDigitOfPower() {
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

    private static int getPeriodOfLastDigit(int lastDigit) { // статический метод для определения периода последней цифры
        if (lastDigit == 1 || lastDigit == 5) { // если последняя цифра равна 1 или 5
            return 1; // период равен 1
        } else { // иначе
            return 4; // период равен 4
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите основание: ");
        int Osnovanie = scanner.nextInt();

        System.out.print("Введите показатель 1: ");
        int Stepen1 = scanner.nextInt();

        System.out.print("Введите показатель 2: ");
        int Stepen2 = scanner.nextInt();

        LastDigitOfPower obj = new LastDigitOfPower(Stepen1, Stepen2);
        int lastDigit = obj.lastDigitOfPower();

        LastDigitOfPower obj2 = new LastDigitOfPower(Osnovanie, lastDigit);
        int lastDigit2 = obj2.lastDigitOfPower();

        System.out.println("Последняя цифра данного числа: " + lastDigit2);
    }
}

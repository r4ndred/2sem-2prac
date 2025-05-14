#include <iostream> 

using namespace std; 

class LastDigitOfPower {
private:
    int Osnovanie; 
    int Stepen;     

public:
    // Конструктор класса, инициализирует поля Osnovanie и Stepen
    LastDigitOfPower(int Osnovanie, int Stepen) : Osnovanie(Osnovanie), Stepen(Stepen) {}

    // Метод для вычисления последней цифры степени с выводом промежуточных шагов
    int lastDigitOfPower(bool verbose = false) {
        // Если основание степени равно 0
        if (Osnovanie == 0) {
            if (verbose) cout << "Основание равно 0, последняя цифра всегда 0" << endl;
            return 0; // Любая степень 0 всегда заканчивается на 0
        }

        // Вычисляем последнюю цифру основания
        int lastDigit = Osnovanie % 10;
        if (verbose) cout << "1. Последняя цифра основания " << Osnovanie 
                          << ": " << lastDigit << endl;

        // Получаем период повторения последней цифры для этой цифры
        int period = getPeriodOfLastDigit(lastDigit);
        if (verbose) cout << "2. Период повторения для цифры " << lastDigit 
                          << ": " << period << endl;

        // Вычисляем остаток от деления степени на период
        int remainder = Stepen % period;
        if (remainder == 0) {
            remainder = period; // Если степень кратна периоду, берем сам период
            if (verbose) cout << "3. Степень " << Stepen 
                              << " кратна периоду, используем период: " << remainder << endl;
        } else {
            if (verbose) cout << "3. Остаток от деления " << Stepen << " на " << period 
                              << ": " << remainder << endl;
        }

        // Вычисляем последнюю цифру степени
        int result = 1;
        if (verbose) cout << "4. Вычисляем " << lastDigit << "^" << remainder << ":" << endl;
        
        // Возводим в степень только остаток, а не всю степень
        for (int i = 0; i < remainder; i++) {
            result = (result * lastDigit) % 10; // Берем только последнюю цифру
            if (verbose) cout << "   Шаг " << i+1 << ": " << lastDigit << "^" << i+1 
                              << " mod 10 = " << result << endl;
        }

        if (verbose) cout << "5. Итоговая последняя цифра: " << result << endl;
        return result;
    }

private:
    // Вспомогательный метод для определения периода последней цифры
    static int getPeriodOfLastDigit(int lastDigit) {
        // Для цифр 1 и 5 период всегда 1 (1^1=1, 5^1=5, 5^2=25 и т.д.)
        if (lastDigit == 1 || lastDigit == 5) {
            return 1;
        }
        // Для остальных цифр период равен 4
        else {
            return 4;
        }
    }
};

int main() {
    setlocale(LC_ALL, "russian"); // Устанавливаем русскую локаль
    
    int Osnovanie, Stepen1, Stepen2;
    cout << "Введите основание: ";
    cin >> Osnovanie; // Читаем основание
    
    cout << "Введите показатель 1: ";
    cin >> Stepen1; // Читаем первый показатель
    
    cout << "Введите показатель 2: ";
    cin >> Stepen2; // Читаем второй показатель

    // Вычисляем показатель1^показатель2 (последнюю цифру)
    cout << "\n=== Вычисление " << Stepen1 << "^" << Stepen2 << " ===" << endl;
    LastDigitOfPower obj1(Stepen1, Stepen2);
    int lastDigit1 = obj1.lastDigitOfPower(true); // true - выводить шаги
    
    // Вычисляем основание^последняя_цифра (последнюю цифру)
    cout << "\n=== Вычисление " << Osnovanie << "^" << lastDigit1 << " ===" << endl;
    LastDigitOfPower obj2(Osnovanie, lastDigit1);
    int finalDigit = obj2.lastDigitOfPower(true); // true - выводить шаги
    
    cout << "\nФинальный результат: " << finalDigit << endl;
    
    return 0;
}

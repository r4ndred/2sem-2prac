#include <iostream>

using namespace std;

// Функция для быстрого возведения в степень по модулю (методом квадратов)
int modPow(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    // 1. Алиса и Боб согласовывают общие параметры
    int p, g;
    cout << "Введите простое число p: ";
    cin >> p;
    cout << "Введите примитивный корень по модулю p (g): ";
    cin >> g;

    // 2. Алиса и Боб генерируют свои секретные ключи
    int a, b;
    cout << "Alice: Введите свой секретный ключ a: ";
    cin >> a;
    cout << "Bob: Введите свой секретный ключ b: ";
    cin >> b;

    // 3. Илья (злоумышленник) генерирует СВОИ секретные ключи для атаки
    int ilya_secret_a = 15;  // Секретный ключ Ильи для общения с Алисой
    int ilya_secret_b = 20;  // Секретный ключ Ильи для общения с Бобом

    // 4. Алиса вычисляет свой открытый ключ A = g^a mod p
    int A = modPow(g, a, p);
    
    // 5. Боб вычисляет свой открытый ключ B = g^b mod p
    int B = modPow(g, b, p);

    // 6. Илья перехватывает открытые ключи Алисы и Боба
    cout << "\n[Илья перехватывает сообщения между Алисой и Бобом]\n";
    
    // 7. Илья подменяет ключи:
    // - Алисе он отправляет СВОЙ ключ (g^ilya_secret_a)
    // - Бобу он отправляет СВОЙ ключ (g^ilya_secret_b)
    int ilya_to_alice = modPow(g, ilya_secret_a, p);
    int ilya_to_bob = modPow(g, ilya_secret_b, p);

    cout << "Илья подменил ключи:\n";
    cout << "Вместо A=" << A << " Алиса получила " << ilya_to_alice << endl;
    cout << "Вместо B=" << B << " Боб получил " << ilya_to_bob << endl;

    // 8. Алиса вычисляет "общий" ключ с Ильей: K_A = (g^ilya_secret_a)^a mod p
    int Alice_secret_with_Ilya = modPow(ilya_to_alice, a, p);
    
    // 9. Боб вычисляет "общий" ключ с Ильей: K_B = (g^ilya_secret_b)^b mod p
    int Bob_secret_with_Ilya = modPow(ilya_to_bob, b, p);
    
    // 10. Илья вычисляет оба ключа:
    // Ключ для общения с Алисой: K_A = (g^a)^ilya_secret_a mod p
    int Ilya_secret_with_Alice = modPow(A, ilya_secret_a, p);
    
    // Ключ для общения с Бобом: K_B = (g^b)^ilya_secret_b mod p
    int Ilya_secret_with_Bob = modPow(B, ilya_secret_b, p);

    // 11. Проверка - ключи должны совпасть
    cout << "\nРезультаты атаки:\n";
    cout << "Алиса думает, что её секретный ключ с Бобом: " << Alice_secret_with_Ilya << endl;
    cout << "На самом деле это её ключ с Ильей: " << Ilya_secret_with_Alice << endl;
    cout << "Боб думает, что его секретный ключ с Алисой: " << Bob_secret_with_Ilya << endl;
    cout << "На самом деле это его ключ с Ильей: " << Ilya_secret_with_Bob << endl;

    // 12. Проверка оригинального протокола (без атаки)
    int real_Alice_secret = modPow(B, a, p);
    int real_Bob_secret = modPow(A, b, p);
    
    cout << "\nБез атаки:\n";
    cout << "Настоящий общий ключ Алисы и Боба: " << real_Alice_secret << endl;
    cout << "Настоящий общий ключ Боба и Алисы: " << real_Bob_secret << endl;

    if (Alice_secret_with_Ilya == Ilya_secret_with_Alice && 
        Bob_secret_with_Ilya == Ilya_secret_with_Bob) {
        cout << "\nАтака успешна! Илья может читать всю переписку между Алисой и Бобом.\n";
        cout << "Илья использует ключ " << Ilya_secret_with_Alice << " для общения с Алисой\n";
        cout << "Илья использует ключ " << Ilya_secret_with_Bob << " для общения с Бобом\n";
    } else {
        cout << "\nАтака не удалась.\n";
    }

    return 0;
}
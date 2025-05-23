#include <iostream>  
#include <vector>  
#include <string>     

using namespace std; 

// Функция для нахождения обратного числа по модулю (c^-1 mod m)
int findModularInverse(int c, int m) {
    cout << "Вычисление " << c << "^-1 mod " << m << ":\n\n";

    // Шаг 1: Находим НОД(c, m) с помощью алгоритма Евклида
    cout << "1. Находим НОД(" << c << "," << m << ") алгоритмом Евклида:\n";
    
    // Инициализируем переменные для алгоритма Евклида
    int a = m; 
    int b = c;  
    vector<pair<int, int>> steps;  // Вектор для хранения шагов (частное, остаток)
    
    // Основной цикл алгоритма Евклида
    while (b != 0) {
        int q = a / b;  // Вычисляем частное от деления
        int r = a % b;  // Вычисляем остаток от деления
        
        steps.push_back({q, r});  // Сохраняем шаг вычисления
        cout << a << " = " << b << "*" << q << " + " << r << endl; // Выводим текущий шаг
        
        // Обновляем значения для следующей итерации
        a = b;
        b = r;
    }
    
    // Последний ненулевой остаток - это НОД
    int gcd = a;
    cout << "НОД = " << gcd << endl << endl;
    
    // Проверяем, существует ли обратный элемент
    if (gcd != 1) {
        cout << "Обратного элемента не существует (НОД != 1)\n";
        return -1;  // Если ошибка
    }

    // Шаг 2: Расширенный алгоритм Евклида для нахождения коэффициентов
    cout << "2. Находим коэффициенты Безу:\n";
    
    // Инициализируем коэффициенты для расширенного алгоритма
    int s_prev = 1, s_curr = 0;  // Коэффициенты для a
    int t_prev = 0, t_curr = 1;  // Коэффициенты для b
    a = m;  // Восстанавливаем исходные значения
    b = c;
    
    vector<string> substitutions;  // Для хранения уравнений подстановки
    
    // Выполняем расширенный алгоритм Евклида
    for (size_t i = 0; i < steps.size(); ++i) {
        int q = steps[i].first;   // Получаем частное из сохраненных шагов
        int r = steps[i].second;  // Получаем остаток из сохраненных шагов
        
        // Вычисляем новые коэффициенты
        int s_next = s_prev - q * s_curr;
        int t_next = t_prev - q * t_curr;
        
        // Сохраняем уравнения для вывода (кроме последнего шага)
        if (i < steps.size() - 1) {
            substitutions.push_back(to_string(r) + " = " + 
                                 to_string(a) + " - " + 
                                 to_string(b) + "*" + 
                                 to_string(q));
        }
        
        // Обновляем коэффициенты для следующей итерации
        s_prev = s_curr;
        s_curr = s_next;
        t_prev = t_curr;
        t_curr = t_next;
        
        // Обновляем значения a и b
        a = b;
        b = r;
    }
    
    // Выводим уравнения подстановки в обратном порядке
if (!substitutions.empty()) {
    for (int i = substitutions.size()-1; i >= 0; --i) {
        if (substitutions[i][0] == '1') {
            cout << "1 = " << substitutions[i].substr(substitutions[i].find("=") + 2) << endl;
            break;
        }
    }
    
    // Выводим остальные уравнения
    for (int i = substitutions.size()-1; i >= 0; --i) {
        if (substitutions[i][0] != '1') {
            cout << substitutions[i] << endl;
        }
    }
} 
    // Получаем обратный элемент
    int d = t_prev;
    // Если коэффициент отрицательный, добавляем модуль
    if (d < 0) {
        cout << "d = " << d << " + " << m << " = " << d + m << endl;
        d += m;
    }
    
    // Проверяем корректность результата
    cout << "\n3. Проверка:\n";
    cout << c << "*" << d << " mod " << m << " = " << (c * d) % m << endl;
    
    return d;  // Возвращаем найденное обратное число
}

int main() {
    int c, m;  // Переменные для хранения входных данных
    
    // Ввод данных
    cout << "Введите c: ";
    cin >> c;
    cout << "Введите m: ";
    cin >> m;
    
    // Вычисление обратного элемента
    int d = findModularInverse(c, m);
    
    // Вывод результата, если он существует
    if (d != -1) {
        cout << "\nРезультат: d = " << 
        d << endl;
    }
    
    return 0;  // Завершение программы
}

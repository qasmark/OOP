#include <iostream>
#include <stack>

using namespace std;

int main() {
    string input = "+(* 2 3)(* 3 4)"; // пример
    stack<int> numbers; // стек для чисел

    for (int i = 0; i < input.length(); i++) {
        char current = input[i];
        if (isdigit(current)) {
            int number = current - '0'; // конвертируем char в int
            numbers.push(number);
        }
        else if (current == '+') {
            int second = numbers.top();
            numbers.pop();
            int first = numbers.top();
            numbers.pop();
            numbers.push(first + second); // добавляем сумму в стек чисел
        }
        else if (current == '*') {
            int second = numbers.top();
            numbers.pop();
            int first = numbers.top();
            numbers.pop();
            numbers.push(first * second); // добавляем произведение в стек чисел
        }
    }

    int result = numbers.top();
    cout << "Результат: " << result << endl; // выводим результат

    return 0;
}
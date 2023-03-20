#include <iostream>
#include <stack>
#include <string>

int main() {
    std::string expr;
    while (std::getline(std::cin, expr)) {
        std::stack<int> stk;
        char op = '+';
        for (int i = 0; i < expr.length(); i++) {
            if (isdigit(expr[i])) {
                int num = 0;
                while (i < expr.length() && isdigit(expr[i])) {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
                i--;
                if (op == '+') {
                    stk.push(num);
                }
                else if (op == '-') {
                    stk.push(-num);
                }
                else if (op == '*') {
                    int arg2 = num;
                    int arg1 = stk.top();
                    stk.pop();
                    stk.push(arg1 * arg2);
                }
            }
            else if (expr[i] == '(') {
                stk.push(0);
                op = '+';
            }
            else if (expr[i] == ')') {
                int sum = 0;
                while (!stk.empty() && stk.top() != 0) {
                    sum += stk.top();
                    stk.pop();
                }
                stk.pop(); // pop 0
                if (op == '+') {
                    stk.push(sum);
                }
                else if (op == '-') {
                    stk.push(-sum);
                }
                else if (op == '*') {
                    int arg2 = sum;
                    int arg1 = stk.top();
                    stk.pop();
                    stk.push(arg1 * arg2);
                }
            }
            else if (expr[i] == '+') {
                op = '+';
            }
            else if (expr[i] == '-') {
                op = '-';
            }
            else if (expr[i] == '*') {
                op = '*';
            }
        }
        int sum = 0;
        while (!stk.empty()) {
            sum += stk.top();
            stk.pop();
        }
        std::cout << sum << std::endl;
    }
    return 0;
}

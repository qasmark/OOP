#include <iostream>
#include <cmath>
#include <stdexcept> 

struct EquationRoot4 {
    double numRoots;
    double roots[4];
};

EquationRoot4 Solve4(double a, double b, double c, double d, double e) {
    if (a == 0) {
        throw std::invalid_argument("Coefficient a cannot be zero.");
    }

    double p = (8 * a * c - 3 * b * b) / (8 * a * a);
    double q = (b * b * b - 4 * a * b * c + 8 * a * a * d) / (8 * a * a * a);
    double r = (-3 * b * b * b * b + 256 * a * a * a * e - 64 * a * b * d + 16 * a * a * c * b) / (256 * a * a * a * a);

    EquationRoot4 result;

    if (r > 0) {
        throw std::domain_error("The equation has no real roots.");
    }
    else if (r == 0) {
        result.numRoots = 2;
        result.roots[0] = (-b + sqrt(-4 * p / 3)) / (4 * a);
        result.roots[1] = (-b - sqrt(-4 * p / 3)) / (4 * a);
        return result;
    }
    else {
        double A = pow(sqrt(-p / 3), 3);
        double B = q / (2 * A);
        double theta1 = acos(B) / 3;
        double theta2 = theta1 - atan(1) * 4 * 2 / 3;
        double theta3 = theta1 + atan(1) * 4 * 2 / 3;

        result.numRoots = 4;
        result.roots[0] = (-b - A * cos(theta1)) / (4 * a);
        result.roots[1] = (-b - A * cos(theta2)) / (4 * a);
        result.roots[2] = (-b - A * cos(theta3)) / (4 * a);
        result.roots[3] = (-b + sqrt(-4 * p / 3)) / (4 * a);
        return result;
    }
}

int main() {
    double a, b, c, d, e;

    while (std::cin >> a >> b >> c >> d >> e) {
        try {
            EquationRoot4 roots = Solve4(a, b, c, d, e);

            std::cout << "Number of roots: " << roots.numRoots << std::endl;
            for (int i = 0; i < roots.numRoots; i++) {
                std::cout << "Root " << i + 1 << ": " << roots.roots[i] << std::endl;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}

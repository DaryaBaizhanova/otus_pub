#include "solve.h"
#include <iostream>
#include <string>
#include <cmath>

CSolve::CSolve()
{

}

std::vector<double> CSolve::solve(double a, double b, double c, double eps)
{
    std::vector<double> res;
    double x1, x2;

    string err = "";
    if (a == eps) {
        err = "\'a\' не может быть равно " +  std::to_string(eps);
        throw coeff_a_is_zero_error(err);
    }

    if (std::isnan(a) || std::isnan(b) || std::isnan (c) || std::isnan(eps)) {
        err = "значение не может быть NaN";
        throw coeff_is_non_numeric_error(err);
    }

    if (std::isinf(a) || std::isinf(b) || std::isinf (c) || std::isinf(eps)) {
        err = "значение не может быть INFINITY";
        throw coeff_is_non_numeric_error(err);
    }
    //a * x^2 + b * x + c = 0

    double d = b * b - 4 * a * c; // дискриминант

    if ( d > eps ) { // 2 корня
        x1 = ( -1 * b + sqrt(b * b - 4 * a * c) ) / (2 * a);
        x2 = ( -1 * b - sqrt(b * b - 4 * a * c) ) / (2 * a);
        res.push_back(x1);
        res.push_back(x2);
    } else {
        if (d <= eps && d >= 0) { // 1
            x1 = x2 = -b / (2 * a);
            res.push_back(x1);
        } else { // 0
            res.clear();
        }
    }

    return res;
}

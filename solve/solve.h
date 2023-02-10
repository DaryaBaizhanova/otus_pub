#include <vector>
#include <stdexcept>

using namespace std;

class coeff_a_is_zero_error : public std::logic_error {
public:
    using _Mybase = std::logic_error;
    explicit coeff_a_is_zero_error(const std::string& _Message) : _Mybase(_Message.c_str()) {}
};
class coeff_is_non_numeric_error : public std::logic_error {
public:
    using _Mybase = std::logic_error;
    explicit coeff_is_non_numeric_error(const std::string& _Message) : _Mybase(_Message.c_str()) {}
};

class CSolve
{
public:
    explicit CSolve();
    std::vector<double> solve(double a, double b, double c, double eps);
};

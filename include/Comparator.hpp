#ifndef _COMPARATOR_HPP_
#define _COMPARATOR_HPP_

/**
 * @brief Functor class to count amount logic statements like comparison of elements in `if()` or `while()`
 */
class StatementCounter
{
    public:
    inline static size_t amount_of_calls = 0;
    size_t obj_amount_of_calls = 0;
    inline static std::string type = "Bool statements counter";
    bool operator()(bool statement)
    {
        ++amount_of_calls;
        ++obj_amount_of_calls;
        return statement;
    }
};

StatementCounter _;
StatementCounter __;

/*
    Just call it like `if(_(_(a == b) && (b == c)))` if you want to count all the binary statements.
    Or, lets say you want to count all the `if()` calls, you may wrapp the statement with a single one _() 
*/

template <typename T>
class G
{
public:
    inline static size_t amount_of_comparisons = 0;
    inline static std::string type = "Strongly great";
    bool operator()(T a, T b)
    {
        ++G<T>::amount_of_comparisons;
        return a > b;
    }
};

template <typename T>
class GE
{
public:
    inline static size_t amount_of_comparisons = 0;
    inline static std::string type = "Great or equal";
    bool operator()(T a, T b)
    {
        ++GE<T>::amount_of_comparisons;
        return a >= b;
    }
};

template <typename T>
class E
{
public:
    inline static size_t amount_of_comparisons = 0;
    inline static std::string type = "Equal";
    bool operator()(T a, T b)
    {
        ++E<T>::amount_of_comparisons;
        return a == b;
    }
};

template <typename T>
class L
{
public:
    inline static size_t amount_of_comparisons = 0;
    inline static std::string type = "Strongly less";
    bool operator()(T a, T b)
    {
        ++L<T>::amount_of_comparisons;
        return a < b;
    }
};

template <typename T>
class LE
{
public:
    inline static size_t amount_of_comparisons = 0;
    inline static std::string type = "Less or equal";
    bool operator()(T a, T b)
    {
        ++LE<T>::amount_of_comparisons;
        return a <= b;
    }
};

/*
    Functional objects for several base types
    Call: int_greater(int a, int b); It return true or false
    Pass it as argument to quick_sort (or even std::sort)
    Example: quick_sort(my_vector, int_greater)
    Or: quick_sort(my_vector, GE<type_of_vector>())
    Declare: G<Foo> Foo_less;
    PS: Foo::operator<() must be declared
*/

G<char> char_greater;
GE<char> char_greater_or_equal;
L<char> char_less;
LE<char> char_less_or_equal;
E<char> char_equal;

G<short> int16_greater;
GE<short> int16_greater_or_equal;
L<short> int16_less;
LE<short> int16_less_or_equal;
E<short> short_equal;

G<long> int32_greater;
GE<long> int32_greater_or_equal;
L<long> int32_less;
LE<long> int32_less_or_equal;
E<long> int32_equal;

G<long long> int64_greater;
GE<long long> int64_greater_or_equal;
L<long long> int64_less;
LE<long long> int64_less_or_equal;
E<long long> int64_equal;

G<float> float_greater;
GE<float> float_greater_or_equal;
L<float> float_less;
LE<float> float_less_or_equal;
E<float> float_equal;

G<double> double_greater;
GE<double> double_greater_or_equal;
L<double> double_less;
LE<double> double_less_or_equal;
E<double> double_equal;

G<long double> long_double_greater;
GE<long double> long_double_greater_or_equal;
L<long double> long_double_less;
LE<long double> long_double_less_or_equal;
E<long double> long_double_equal;

#endif // _COMPARATOR_HPP_

#include "ScalarConverter.hpp"

#include <cerrno>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other){}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {}

ScalarConverter::~ScalarConverter() {}

static bool isPrintableChar(char c)
{
    return c >= 32 && c <= 126;
}

static bool isCharLiteral(const std::string& s)
{
    return  ((s.size() == 3 && s[0] == '\'' && s[2] == '\''));
}

static char toCharValue(const std::string& s)
{
    return  (s[1]);
}

static bool isPseudoLiteral(const std::string& s)
{
    return s == "-inff" || s == "+inff" || s == "nanf"
        || s == "-inf" || s == "+inf" || s == "nan";
}

static bool isIntegerLiteral(const std::string& s)
{
    if (s.empty())
        return false;

    char* end = NULL;
    long value = std::strtol(s.c_str(), &end, 10);
    if (value > INT_MAX || value < INT_MIN)
        return false;
    return end != s.c_str() && *end == '\0';
}

static bool isFloatLiteral(const std::string& s)
{
    if (s.empty() || s[s.size() - 1] != 'f')
        return false;


    std::string str = s.substr(0, s.size() - 1);
    errno = 0;
    char* end = NULL;
    std::strtof(str.c_str(), &end);
    return end != str.c_str() && *end == '\0' && errno != ERANGE;
}

static bool isDoubleLiteral(const std::string& s)
{
    if (s.empty() || s.find('.') == std::string::npos)
        return false;

    errno = 0;
    char* end = NULL;
    double value = std::strtod(s.c_str(), &end);
    (void)value;
    return end != s.c_str() && *end == '\0' && errno != ERANGE;
}


void ScalarConverter::convert(const std::string& literal)
{
    if (isCharLiteral(literal))
    {
        char c = toCharValue(literal);

        std::cout << "char: ";
        if (!isPrintableChar(c))
            std::cout << "Non displayble" << std::endl;
        else
            std::cout << c << std::endl;

        std::cout << "int: " << static_cast<int>(static_cast<unsigned char>(c)) << std::endl;
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "float: " << static_cast<float>(static_cast<unsigned char>(c)) << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(static_cast<unsigned char>(c)) << std::endl;
        return;
    }

    if (isPseudoLiteral(literal))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;

        if (literal == "nan" || literal == "nanf")
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        else if (literal == "-inf" || literal == "-inff")
        {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        else
        {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        }
        return;
    }

    if (isIntegerLiteral(literal))
    {
        long value = std::strtol(literal.c_str(), NULL, 10);

        std::cout << "char: ";
        if (value < 0 || value > 127 || !isPrintableChar(static_cast<char>(value)))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << static_cast<char>(value) << std::endl;

        std::cout << "int: ";
        if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(value) << std::endl;

        std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: ";
        if (value > std::numeric_limits<float>::max() || value < -std::numeric_limits<float>::max())
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<float>(value) << "f" << std::endl;

        std::cout << "double: ";
        if (value > std::numeric_limits<double>::max() || value < -std::numeric_limits<double>::max())
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<double>(value) << std::endl;
        return;
    }

    if (isFloatLiteral(literal))
    {
        float value = std::strtof(literal.c_str(), NULL);

        std::cout << "char: ";
        if (value < 0 || value > 127 || !isPrintableChar(static_cast<char>(value)))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << "'" << static_cast<char>(value) << "'" << std::endl;

        std::cout << "int: ";
        if (value > static_cast<float>(std::numeric_limits<int>::max())
            || value < static_cast<float>(std::numeric_limits<int>::min()))
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(value) << std::endl;

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "float: " << value << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(value) << std::endl;
        return;
    }

    if (isDoubleLiteral(literal))
    {
        double value = std::strtod(literal.c_str(), NULL);

        std::cout << "char: ";
        if (value < 0 || value > 127 || !isPrintableChar(static_cast<char>(value)))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << "'" << static_cast<char>(value) << "'" << std::endl;

        std::cout << "int: ";
        if (value > static_cast<double>(std::numeric_limits<int>::max())
            || value < static_cast<double>(std::numeric_limits<int>::min()))
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(value) << std::endl;

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
        std::cout << "double: " << value << std::endl;
        return;
    }

    throw std::invalid_argument("Invalid literal");
}
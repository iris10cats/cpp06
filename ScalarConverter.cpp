#include <ScalarConverter.hpp>
#include <stdexcept>
#include <sstream>
#include <cctype>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isInteger(const std::string& literal) {
    std::istringstream iss(literal);
    int value;
    return (iss >> value) && (iss.eof());
}

static bool isFloat(const std::string& literal) {
    std::istringstream iss(literal);
    float value;
    return (iss >> value) && (iss.eof());
}

static bool isDouble(const std::string& literal) {
    std::istringstream iss(literal);
    double value;
    return (iss >> value) && (iss.eof());
}

static bool isChar(const std::string& literal) {
    return (literal.length() == 1 && !std::isdigit(literal[0]));
}

static bool isSpecialFloat(const std::string& literal) {
    return (literal == "nanf" || literal == "inff" || literal == "-inff" || literal == "+inff");
}

static bool isSpecialDouble(const std::string& literal) {
    return (literal == "nan" || literal == "inf" || literal == "-inf" || literal == "+inf");
}

void ScalarConverter::convert(const std::string& literal) {

    if (literal.empty()) {
        throw std::invalid_argument("Input literal is empty.");
    }
    
   
}
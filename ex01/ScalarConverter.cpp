#include "ScalarConverter.hpp"
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) {
    (void)other;
}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { 
    (void)other;
    return *this;
}
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

static void print_casts(const std::string& literal) {
    if (isChar(literal) ) {
        char c = literal[0];
        std::cout<< "char: "<< c << std::endl;
        std::cout<< "int: "<< static_cast<int>(c) << std::endl;
        std::cout<< "float: "<< static_cast<float>(c) << ".0f" << std::endl;
        std::cout<< "double: "<< static_cast<double>(c) << ".0" << std::endl;
    } else if (isInteger(literal)) {
        int i = atoi(literal.c_str());
        std::cout<< "char: "<< (std::isprint(i) ? std::string(1, static_cast<char>(i)) : std::string("Non displayable")) << std::endl;
        std::cout<< "int: "<< i << std::endl;
        std::cout<< "float: "<< static_cast<float>(i) << ".0f" << std::endl;
        std::cout<< "double: "<< static_cast<double>(i) << ".0" << std::endl;
    } else if (isFloat(literal)) {
        float f = std::strtof(literal.c_str(), NULL);
        std::cout<< "char: "<< (std::isprint(static_cast<int>(f)) ? std::string(1, static_cast<char>(f)) : std::string("Non displayable")) << std::endl;
        std::cout<< "int: "<< static_cast<int>(f) << std::endl;
        std::cout<< "float: "<< f << "f" << std::endl;
        std::cout<< "double: "<< static_cast<double>(f) << std::endl;
    } else if (isDouble(literal)) {
        double d = std::strtod(literal.c_str(), NULL);
        std::cout<< "char: "<< (std::isprint(static_cast<int>(d)) ? std::string(1, static_cast<char>(d)) : std::string("Non displayable")) << std::endl;
        std::cout<< "int: "<< static_cast<int>(d) << std::endl;
        std::cout<< "float: "<< static_cast<float>(d) << "f" << std::endl;
        std::cout<< "double: "<< d << std::endl;
    } else if (isSpecialFloat(literal)) {
        float f = (literal == "nanf") ? NAN : (literal == "+inff" || literal == "inff") ? INFINITY : -INFINITY;
        std::cout<< "char: impossible" << std::endl;
        std::cout<< "int: impossible" << std::endl;
        std::cout<< "float: "<< f << "f" << std::endl;
        std::cout<< "double: "<< static_cast<double>(f) << std::endl;
    } else if (isSpecialDouble(literal)) {
        double d = (literal == "nan") ? NAN : (literal == "+inf" || literal == "inf") ? INFINITY : -INFINITY;
        std::cout<< "char: impossible" << std::endl;
        std::cout<< "int: impossible" << std::endl;
        std::cout<< "float: "<< static_cast<float>(d) << "f" << std::endl;
        std::cout<< "double: "<< d << std::endl;
    } else {
        throw std::invalid_argument("Invalid literal format.");
    }
}


void ScalarConverter::convert(const std::string& literal) {

    if (literal.empty()) {
        throw std::invalid_argument("Input literal is empty.");
    }
    print_casts(literal);   
   
}
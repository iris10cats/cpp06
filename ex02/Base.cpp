#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <exception>
#include <ctime>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {}

Base* generate() {
    srand(static_cast<unsigned int>(time(NULL)));
    int random = rand() % 3;
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}

void identify(Base* p) {
    if (p == NULL) {
        std::cout<<"pointer is null"<<std::endl;
        return; }
    if (dynamic_cast<A*>(p))
        std::cout <<"A"<<std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout<<"B"<<std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout<<"C"<<std::endl;
    else
        std::cout<<"pointer is different"<< std::endl;

}

void identify(Base& p) {
    try {
        dynamic_cast<A&>(p);
        std::cout << "A"<<std::endl;
    }
    catch (const std::exception&) {
        try {
            dynamic_cast<B&>(p);
            std::cout << "B"<<std::endl;
        }
        catch (const std::exception&) {
            try {
                dynamic_cast<C&>(p);
                std::cout << "C"<<std::endl;
            }
            catch (const std::exception&) {
                std::cout << "different pointer" << std::endl;
            }
        }
    }
}
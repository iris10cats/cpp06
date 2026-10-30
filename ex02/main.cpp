#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"


int main() {
    Base* ptr = generate();
    A a;
    B b;
    C c;

    std::cout<<"indentify pointer:"<<std::endl;
    identify(ptr);

    std::cout<<"identify reference:"<<std::endl;
    identify(*ptr);

    identify(a);
    identify(b);
    identify(c);
    identify(&a);
    identify(&b);
    identify(&c);


    delete ptr;
    return 0;
}
#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>
#include <stdint.h>

int main() {
    Data data;
    Data* restored;
    data.value = 2131;
    data.name = "example_name";
    uintptr_t integer;

  //  std::cout<< integer<<std::endl;
    integer = Serializer::serialize(&data);
    std::cout << "Serialized integer: " << std::endl;
    std::cout << integer << std::endl;

    restored = Serializer::deserialize(integer);
    std::cout << "Restored pointer: " << restored << std::endl;
    std::cout << "integer: " << integer << std::endl;
    std::cout << "Restored data: " << std::endl;
    std::cout << restored->value << " " << restored->name << std::endl;
    
    return 0;
}
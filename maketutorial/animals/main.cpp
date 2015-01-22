/**
 * @file main.cpp
 * @author Lisa Sproat
 */

#include "dog.hpp"
#include <iostream>
#include <utility> // std::pair

int main(){
    Dog my_dog = Dog("Skye");
    my_dog.bark();
    my_dog.run(30, 10);
    my_dog.read_tag();
    std::pair<int, int> loc = my_dog.radio_collar();
    std::cout << "[Main] Location: (" << loc.first << ", "
              << loc.second << ")" << std::endl;
}

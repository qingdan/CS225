/**
 * @file dog.cpp
 * @author Lisa Sproat
 */

#include "dog.hpp"

using std::cout;

Dog::Dog(std::string name_){
    cout << "[Dog::Dog] Congratulations on your new dog!\n";
    // All dogs are born at age 0
    age = 0;
    // And in our world, all dogs are born at the cartesian
    // position (0, 0)
    x = 0;
    y = 0;

    this->name = name_;
}

void Dog::bark(){
    cout << "[Dog::bark] " << this->name << " says, \"Woof!\"\n";
}

void Dog::run(int x_, int y_){
    cout << "[Dog::run] Your dog is running away!\n";
    x = x_;
    y = y_;
}

void Dog::read_tag(){
    cout << "[Dog::read_tag] Hi, my name is " << this->name
              << std::endl;
}

std::pair<int, int> Dog::radio_collar(){
    cout << "[Dog::radio_collar] Locating your dog...\n";
    return std::make_pair(x, y);
}

/**
 * @file dog.hpp
 * @author Lisa Sproat
 */

#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include <utility> // for std::pair

class Dog{
 public:
    /**
     * Name-based Dog constructor
     * Creates a new Dog with the given name
     * @param name The name of the Dog
     */
    Dog(std::string name);

    /**
     * Cause the Dog to bark.
     */
    void bark();

    /**
     * Move the Dog to a new cartesian position.
     * @param x X-coordinate for the Dog's new position
     * @param y Y-coordinate for the Dog's new position
     */
    void run(int x, int y);

    /**
     * Read the Dog's tag.
     */
    void read_tag();

    /**
     * Locate the Dog.
     * @return A pair containing the Dog's current position.
     */
    std::pair<int, int> radio_collar();
    
 private:
    int x, y;
    int age;
    std::string name;
    
};

#endif

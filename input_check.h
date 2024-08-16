// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header file for the input_check namespace
// Contains functions: correct_character_check, real_number_check

#ifndef INPUT_CHECK_H
#define INPUT_CHECK_H

#include<iostream> 
#include<string>
#include <sstream>

namespace input_check
{  
  char correct_character_check(std::string& input, char char1, char char2);  
  double real_number_check();
}

#endif
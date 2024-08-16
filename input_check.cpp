// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the input_check namespace

#include"input_check.h"


namespace input_check
{  
  char correct_character_check(std::string &input, char char1, char char2)
  {
    while(true)
    {
      try
      {
        // Check if they haven't input a single character as requested
        if (input.length() != 1) throw input;
        char character;
        character = input[0];
        // Check if the input is a character we want
        if (character == char1 || character == char2) return character; else throw character;
      } 
      catch (...) 
      {
        std::cout<<"Please enter a character that is a "<<char1<<" or "<<char2<<": \n";
        std::getline(std::cin, input);
      }
    }
  }

  double real_number_check()
  {
    while(true)
    {
      try
      {
        double energy{};
        std::string user_input;
        std::cout<<"Enter the initial energy for the event (in GeV):\n";
        getline(std::cin, user_input);
        std::istringstream input_stream(user_input);
        // Try to extract doubles from string stream
        input_stream >> energy;
        // If fails, throw here
        if (input_stream.fail()) {throw input_stream;}
        // Check if anyhting left in stream, e.g. for inputs like 12.2hygbh
        if (input_stream.eof() == false) {throw input_stream;}
        return energy;
      } 
      catch (...) 
      {
        std::cout<<"Please enter a number\n";
      }
    }
  }
}
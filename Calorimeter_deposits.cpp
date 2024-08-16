// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the calorimeter deposits class

#include<iostream>
#include"Calorimeter_deposits.h"

// Parameterised Constructor
Calorimeter_deposits::Calorimeter_deposits(double particle_em1, double particle_em2, double particle_had1, double particle_had2)
{
  set_em1(particle_em1);
  set_em2(particle_em2);
  set_had1(particle_had1);
  set_had2(particle_had2);  
}

// Copy constructor
Calorimeter_deposits::Calorimeter_deposits(const Calorimeter_deposits &original)
{
  em1 = original.em1;
  em2 = original.em2;
  had1 = original.had1;
  had2 = original.had2;
}

// Move constructor
Calorimeter_deposits::Calorimeter_deposits(Calorimeter_deposits&& original)
{
  em1 = original.em1;
  original.em1 = 0;

  em2 = original.em2;
  original.em2 = 0;

  had1 = original.had1;
  original.had1 = 0;

  had2 = original.had2;
  original.had2 = 0;
}

// Overload Assignment operator for deep copying
Calorimeter_deposits& Calorimeter_deposits::operator=(Calorimeter_deposits& original)
{
  if(&original == this) return *this; // no self assignment
  em1 = original.em1;
  em2 = original.em2;
  had1 = original.had1;
  had2 = original.had2;
  return *this;
}
  
// Overload Assignment operator to move objects 
Calorimeter_deposits& Calorimeter_deposits::operator=(Calorimeter_deposits&& original)
{
  if(&original == this) return *this; // no self assignment
  
  em1 = original.em1;
  original.em1 = 0;

  em2 = original.em2;
  original.em2 = 0;

  had1 = original.had1;
  original.had1 = 0;

  had2 = original.had2;
  original.had2 = 0;
  return *this; // Return the same object, which now contains the moved values  
}


// Printing function
void Calorimeter_deposits::print_calorimeter_deposits() const
{
  std::cout<<"Calorimeter deposits [EM,EM2,HAD1,HAD2] = ["<<em1<<", "<<em2<<", "<<had1<<", "<<had2<<"] GeV\n";
}
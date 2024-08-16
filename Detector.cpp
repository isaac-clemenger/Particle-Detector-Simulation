// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the detector class

#include<iostream>
#include"Detector.h"

// Constructors

// Copy constructor
Detector::Detector(const Detector &original) 
{
  // Static variables don't go here, as are part of the class itself and not a particular object
}

// Move constructor
Detector::Detector(Detector&& original) 
{}

// Overload Assignment operator for deep copying
Detector& Detector::operator=(Detector& original)
{
  if(&original == this) return *this; // no self assignment
  return *this;
}

// Move assignment
Detector& Detector::operator=(Detector&& original)
{
  if(&original == this) return *this;
  return *this;    
}


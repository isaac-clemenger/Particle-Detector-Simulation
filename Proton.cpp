// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the proton class

#include<iostream>
#include"Proton.h"

// Constructors
// Parameterised Constructor
Proton::Proton(int particle_id, double particle_energy) :
Calorimeter_interacting{particle_id, +1, particle_energy}
{
  tracks_detected = {true,true,true};
}


// Copy constructor
Proton::Proton(const Proton &original) :
Calorimeter_interacting(original)
{
  tracks_detected = original.tracks_detected;
}

// Move constructor
Proton::Proton(Proton&& original) :
Calorimeter_interacting(std::move(original))
{
  tracks_detected = std::move(original.tracks_detected);
}

// Overload Assignment operator for deep copying
Proton& Proton::operator=(Proton& original)
{
  if(&original == this) return *this; // no self assignment
  Calorimeter_interacting::operator=(original);
  tracks_detected = original.tracks_detected;
  return *this;
}

// Move assignment
Proton& Proton::operator=(Proton&& original)
{
  if(&original == this) return *this;
  Calorimeter_interacting::operator=(std::move(original));
  tracks_detected = std::move(original.tracks_detected);
  return *this;    
}

void Proton::print_particle_data() const
{
  std::cout<<"  Proton: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";
  std::cout<<"    The proton's true energy in the tracker: "<<energy<<" GeV\n";
  std::cout<<"    The proton's true calorimeter deposits were: ";
  calorimeter_deposits->print_calorimeter_deposits();
  std::cout<<"    The proton's true energy in the muon chmaber was: 0 GeV\n";
  

}
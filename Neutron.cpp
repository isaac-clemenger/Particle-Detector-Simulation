// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the neutron class

#include<iostream>
#include"Neutron.h"

// Constructors
// Parameterised Constructor
Neutron::Neutron(int particle_id, double particle_energy) :
Calorimeter_interacting{particle_id, 0, particle_energy}
{}


// Copy constructor
Neutron::Neutron(const Neutron &original) :
Calorimeter_interacting(original)
{}

// Move constructor
Neutron::Neutron(Neutron&& original) :
Calorimeter_interacting(std::move(original))
{}

// Overload Assignment operator for deep copying
Neutron& Neutron::operator=(Neutron& original)
{
  if(&original == this) return *this;
  Calorimeter_interacting::operator=(original);
  return *this; 
}

// Move assignment
Neutron& Neutron::operator=(Neutron&& original)
{
  if(&original == this) return *this;
  Calorimeter_interacting::operator=(std::move(original));
  return *this; 
}

void Neutron::print_particle_data() const
{
  std::cout<<"  Neutron: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";
  std::cout<<"    The neutron's true energy in the tracker was: 0 GeV\n";
  std::cout<<"    The neutron's calorimeter deposits were: ";
  calorimeter_deposits->print_calorimeter_deposits();
  std::cout<<"    The neutron's true energy in the muon chamber was: 0 GeV\n";
}
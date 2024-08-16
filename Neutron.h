// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the neutron class
// Publically inherits from class Calorimeter_interacting

#ifndef NEUTRON_H
#define NEUTRON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Calorimeter_interacting.h"

class Neutron: public Calorimeter_interacting
{
public:
  // Default constructor
  Neutron() :
    Calorimeter_interacting{} {charge = 0;}
  // Parameterised Constructor
  Neutron(int particle_id, double particle_energy);
  // Destructor 
  ~Neutron()
  {}

  // Copy constructor
  Neutron(const Neutron &original);

  // Move constructor
  Neutron(Neutron&& original);

  // Overload Assignment operator for deep copying
  Neutron& operator=(Neutron& original);

  // Overload Assignment operator to move objects 
  Neutron& operator=(Neutron&& original);            

  // Function to print info about a neutron
  void print_particle_data() const override;
};

#endif

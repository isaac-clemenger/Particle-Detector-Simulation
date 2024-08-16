// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header file for the photon class
// Publically inherits from Calorimeter_interacting

#ifndef PHOTON_H
#define PHOTON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Calorimeter_interacting.h"

class Photon: public Calorimeter_interacting
{
public:
  // Default constructor
  Photon() :
    Calorimeter_interacting{} {charge = 0, calorimeter_deposits->set_had1(0), calorimeter_deposits->set_had2(0);}
  // Parameterised Constructor
  Photon(int particle_id, double particle_energy);
  // Destructor 
  ~Photon()
  {}

  // Copy constructor
  Photon(const Photon &original);

  // Move constructor
  Photon(Photon&& original);

  // Overload Assignment operator for deep copying
  Photon& operator=(Photon& original);

  // Overload Assignment operator to move objects 
  Photon& operator=(Photon&& original);  

  // Photon only deposits in em calorimeter, so need to override
  void set_calorimeter_deposits(const double particle_energy) override; 

  // Function to print info about an photon
  void print_particle_data() const override;
};

#endif

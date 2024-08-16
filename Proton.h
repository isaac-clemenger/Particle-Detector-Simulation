// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the proton class
// Contains variables: tracks_detected
// Publically inherits from class Calorimeter_interacting

#ifndef PROTON_H
#define PROTON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Calorimeter_interacting.h"

class Proton: public Calorimeter_interacting
{
private:
  std::vector<bool> tracks_detected;
public:
  // Default constructor
  Proton() :
    Calorimeter_interacting{}, tracks_detected{true,true,true} {charge = +1;}
  // Parameterised Constructor
  Proton(int particle_id, double particle_energy);
  // Destructor 
  ~Proton()
  {}

  // Copy constructor
  Proton(const Proton &original);

  // Move constructor
  Proton(Proton&& original);

  // Overload Assignment operator for deep copying
  Proton& operator=(Proton& original);

  // Overload Assignment operator to move objects 
  Proton& operator=(Proton&& original);  

  // Getters
  std::vector<bool> get_tracks_detected() const{return tracks_detected;}

  // Function to print info about a proton
  void print_particle_data() const override;
};

#endif

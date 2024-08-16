// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header file for the electron class
// Contains variables: tracks_detected
// Publically inherits from class Caloimeter_interacting

#ifndef ELECTRON_H
#define ELECTRON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Calorimeter_interacting.h"

class Electron: public Calorimeter_interacting
{
private:
  std::vector<bool> tracks_detected;
public:
  // Default constructor
  Electron() :
    Calorimeter_interacting{}, tracks_detected{true,true,true} {charge = -1, calorimeter_deposits->set_had1(0), calorimeter_deposits->set_had2(0);}
  // Parameterised Constructor
  Electron(int particle_id, double particle_energy);
  // Destructor 
  ~Electron()
  {}

  // Copy constructor
  Electron(const Electron &original);

  // Move constructor
  Electron(Electron&& original);

  // Overload Assignment operator for deep copying
  Electron& operator=(Electron& original);

  // Overload Assignment operator to move objects 
  Electron& operator=(Electron&& original);  

  // Getters
  std::vector<bool> get_tracks_detected() const {return tracks_detected;}

  // Setters   
  void set_calorimeter_deposits(const double particle_energy) override;       

  // Function to print info about an electron
  void print_particle_data() const override;
};

#endif

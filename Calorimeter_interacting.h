// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the calorimeter interacting class
// Contains variables: calorimeter_deposits
// Publically inherits from class particle

#ifndef CALORIMETER_INTERACTING_H
#define CALORIMETER_INTERACTING_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Particle.h"
#include"Calorimeter_deposits.h"

class Calorimeter_interacting: public Particle
{
// Protected as there will be another tier of inheritance below this
protected:
  std::unique_ptr<Calorimeter_deposits> calorimeter_deposits;  
public:
  // Default constructor
  Calorimeter_interacting() :
    Particle{}, calorimeter_deposits{} {}
  // Parameterised constructor
  Calorimeter_interacting(int particle_id, int particle_charge, double particle_energy);
  // Destructor
  virtual ~Calorimeter_interacting()
  {}

  // Copy constructor
  Calorimeter_interacting(const Calorimeter_interacting &original);

  // Move constructor
  Calorimeter_interacting(Calorimeter_interacting&& original);

  // Overload Assignment operator for deep copying
  Calorimeter_interacting& operator=(Calorimeter_interacting& original);

  // Overload Assignment operator to move objects 
  Calorimeter_interacting& operator=(Calorimeter_interacting&& original);  

  // Getters
  Calorimeter_deposits get_calorimeter_deposits() const{return *calorimeter_deposits;}

  // Setters
  // Need to override this for electrons and photons to keep hadronic deposits as 
  virtual void set_calorimeter_deposits(const double particle_energy);
  
  // Function to print info about a particle
  virtual void print_particle_data() const override;
};

#endif
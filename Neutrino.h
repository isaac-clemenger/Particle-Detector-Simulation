// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the neutrino class
// Contains variables: has_interacted
// Publically inherits from class particle

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Particle.h"

class Neutrino: public Particle
{
// Protected as there will be another tier of inheritance below this
protected:
  bool has_interacted; 
public:
  // Default constructor
  Neutrino() :
    Particle{},  has_interacted{} {}
  // Parameterised constructor
  Neutrino(int particle_id, double particle_energy, bool particle_has_interacted);
  // Destructor
  ~Neutrino()
  {}

  // Copy constructor
  Neutrino(const Neutrino &original);

  // Move constructor
  Neutrino(Neutrino&& original);

  // Overload Assignment operator for deep copying
  Neutrino& operator=(Neutrino& original);

  // Overload Assignment operator to move objects 
  Neutrino& operator=(Neutrino&& original);  

  // Getters
  bool get_has_interacted() const {return has_interacted;}

  // Setters
  void set_has_interacted(const bool particle_has_interacted) {has_interacted = particle_has_interacted;}

  // Function to print info about a particle
  void print_particle_data() const override;
};

#endif
// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the particle class, 
// Contains variables: id, charge, energy 
// This is an abstract base class

#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

// Define constants
const double speed_of_light_in_vacuo{2.99792458e8};

class Particle
{
protected:
  int id, charge;  
  double energy;
public:
  // Default constructor
  Particle() = default;
  // Parameterised constructor
  Particle(int particle_id, int particle_charge, double particle_energy);
  // Destructor
  virtual ~Particle() {}

  // Copy constructor
  Particle(const Particle &original);

  // Move constructor
  Particle(Particle&& original);

  // Overload Assignment operator for deep copying
  Particle& operator=(Particle& original);

  // Overload Assignment operator to move objects 
  Particle& operator=(Particle&& original);

  // Getter functions (accessors) to:
  int get_id() const {return id;}
  int get_charge() const {return charge;}
  double get_energy() const {return energy;}

  // Setter functions, to change value of data members
  void set_id(const int particle_id) {id = particle_id;}
  void set_charge(const int particle_charge) {charge = particle_charge;}
  void set_energy(const double particle_energy) {energy = check_energy(particle_energy);}

  // Function to charge particles to antiparticles
  virtual void switch_to_anti();

  // Function that ensures the velocity is physical  
  double check_energy(double energy);

  // Function to print info about a particle
  virtual void print_particle_data() const = 0;
};

#endif
// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the particle class

#include<iostream>
#include"Particle.h"

// Memeber functions

// Function that ensures the velocity is physical
double Particle::check_energy(double energy)
{
  if (energy < 0)
  { 
    std::cout<<"This energy is non physical\n";
    // Throw so we can catch it in the try catch function in the main
    throw energy;
  } 
  else 
  {
    return energy;
  } 
}

// Function that makes particles antiparticles
void Particle::switch_to_anti()
{
  charge = charge * -1;
}

// Constructors
// Parameterised constructor
Particle::Particle(int particle_id, int particle_charge, double particle_energy)
{
  set_id(particle_id);
  set_charge(particle_charge);
  set_energy(particle_energy);
} 

// Copy constructor
Particle::Particle(const Particle &original)
{
  id = original.id;
  charge = original.charge;
  energy = original.energy;
}

// Move constructor
Particle::Particle(Particle&& original)
{
  id = original.id;
  original.id = 0;

  charge = original.charge;
  original.charge = 0;

  energy = original.energy;
  original.energy = 0; 
}

// Overloaded operators

// Overload Assignment operator for deep copying
Particle& Particle::operator=(Particle& original)
{
  if(&original == this) return *this; // no self assignment
  id = original.id;
  charge = original.charge;
  energy = original.energy;
  return *this; // Return the same object, which now contains the copied values
}  

// Overload Assignment operator to move objects 
Particle& Particle::operator=(Particle&& original)
{
  if(&original == this) return *this; // no self assignment

  id = original.id;
  original.id = 0;

  charge = original.charge;
  original.charge = 0;

  energy = original.energy;
  original.energy = 0; 
  return *this; // Return the same object, which now contains the moved values
}


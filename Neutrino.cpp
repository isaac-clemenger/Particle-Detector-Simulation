// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the neutrino class

#include<iostream>
#include"Neutrino.h"

// Constructors
// Parameterised constructor
Neutrino::Neutrino(int particle_id, double particle_energy, bool particle_has_interacted) :
Particle{particle_id, 0, particle_energy}
{
  set_has_interacted(particle_has_interacted);
}

// Copy constructor
Neutrino::Neutrino(const Neutrino &original) :
Particle(original)
{
  has_interacted = original.has_interacted;
}

// Move constructor
Neutrino::Neutrino(Neutrino&& original) :
Particle(std::move(original))
{
  has_interacted = original.has_interacted;
  original.has_interacted = 0;
}

// Overload Assignment operator for deep copying
Neutrino& Neutrino::operator=(Neutrino& original)
{
  if(&original == this) return *this; // no self assignment
  Particle::operator=(original);
  has_interacted = original.has_interacted;
  return *this;
}

// Move assignment
Neutrino& Neutrino::operator=(Neutrino&& original)
{
  if(&original == this) return *this;
  Particle::operator=(std::move(original));
  has_interacted = original.has_interacted;
  original.has_interacted = 0;
  return *this;    
}

// Function that prints particle data
void Neutrino::print_particle_data() const
{
  std::cout<<"  Neutrino: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";
  if (has_interacted) {std::cout<<"  The neutrino did interact\n";}
  else {std::cout<<"  The neutrino did not interact\n";}
  std::cout<<"    The neutrino's true energy in the tracker was: 0 GeV\n";
  std::cout<<"    The neutrino's true calorimeter deposits are: Calorimeter deposits [EM1,EM2,HAD1,HAD2] = [0,0,0,0] GeV\n";
  std::cout<<"    The neutrino's true energy in the muon chamber was: 0 GeV\n";
  return;
}
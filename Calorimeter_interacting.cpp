// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the calorimeter_interacting class

#include<iostream>
#include"Calorimeter_interacting.h"
#include"random.h"

// Constructors
// Parameterised constructor
Calorimeter_interacting::Calorimeter_interacting(int particle_id, int particle_charge, double particle_energy) :
Particle{particle_id, particle_charge, particle_energy}
{
  calorimeter_deposits = std::make_unique<Calorimeter_deposits>();
  set_calorimeter_deposits(particle_energy);  
}

// Copy constructor
Calorimeter_interacting::Calorimeter_interacting(const Calorimeter_interacting &original) :
Particle(original)
{
  calorimeter_deposits = std::make_unique<Calorimeter_deposits>(*(original.calorimeter_deposits));
}

// Move constructor
Calorimeter_interacting::Calorimeter_interacting(Calorimeter_interacting&& original) :
Particle(std::move(original))
{
  calorimeter_deposits = std::move(original.calorimeter_deposits);
  original.calorimeter_deposits = nullptr;
}

// Overload Assignment operator for deep copying
Calorimeter_interacting& Calorimeter_interacting::operator=(Calorimeter_interacting& original)
{
  if(&original == this) return *this; // no self assignment
  Particle::operator=(original);
  calorimeter_deposits = std::make_unique<Calorimeter_deposits>(*(original.calorimeter_deposits));
  return *this;
}

// Move assignment
Calorimeter_interacting& Calorimeter_interacting::operator=(Calorimeter_interacting&& original)
{
  if(&original == this) return *this;
  Particle::operator=(std::move(original));
  calorimeter_deposits = std::move(original.calorimeter_deposits);
  original.calorimeter_deposits = nullptr;
  return *this;    
}

// Setters
void Calorimeter_interacting::set_calorimeter_deposits(const double particle_energy)
{
  if (calorimeter_deposits != nullptr)
  {
    std::vector<double> rand_energies = random::gen_n_numbers(4);
    calorimeter_deposits->set_em1(rand_energies[0]*particle_energy);
    calorimeter_deposits->set_em2(rand_energies[1]*particle_energy);
    calorimeter_deposits->set_had1(rand_energies[2]*particle_energy);
    calorimeter_deposits->set_had2(rand_energies[3]*particle_energy);
  }
}

// Function that prints particle data
void Calorimeter_interacting::print_particle_data() const 
{
  std::cout<<"  Calorimeter interacting particle: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";
  std::cout<<"    The particle's true energy in the tracker: "<<energy<<" GeV\n";
  std::cout<<"    The particle's true calorimeter deposits are: ";
  calorimeter_deposits->print_calorimeter_deposits();
  std::cout<<"    The particle's true energy in the muon chmaber was: 0 GeV\n";
  return;
}
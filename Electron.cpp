// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the electron class

#include<iostream>
#include"Electron.h"
#include"random.h"


// Constructors
// Parameterised Constructor
Electron::Electron(int particle_id, double particle_energy) 
{
  calorimeter_deposits = std::make_unique<Calorimeter_deposits>();
  set_id(particle_id);
  set_charge(-1);
  set_energy(particle_energy);
  set_calorimeter_deposits(particle_energy);
  tracks_detected = {true,true,true};
}


// Copy constructor
Electron::Electron(const Electron &original) :
Calorimeter_interacting(original)
{
  tracks_detected = original.tracks_detected;
}

// Move constructor
Electron::Electron(Electron&& original) :
Calorimeter_interacting(std::move(original))
{
  tracks_detected = std::move(original.tracks_detected);
}

// Overload Assignment operator for deep copying
Electron& Electron::operator=(Electron& original)
{
  if(&original == this) return *this; // no self assignment
  Calorimeter_interacting::operator=(original);
  tracks_detected = original.tracks_detected;
  return *this;
}

// Move assignment
Electron& Electron::operator=(Electron&& original)
{
  if(&original == this) return *this;
  Calorimeter_interacting::operator=(std::move(original));
  tracks_detected = std::move(original.tracks_detected);
  return *this;    
}

// Electron only deposits in em layers of calorimeter, so override setter to reflect this.
void Electron::set_calorimeter_deposits(const double particle_energy)
{
  if (calorimeter_deposits != nullptr)
  {
    std::vector<double> rand_energies = random::gen_n_numbers(2);
    calorimeter_deposits->set_em1(rand_energies[0]*particle_energy);
    calorimeter_deposits->set_em2(rand_energies[1]*particle_energy);
    calorimeter_deposits->set_had1(0);
    calorimeter_deposits->set_had2(0);
  }
}


void Electron::print_particle_data() const
{
  std::cout<<"  Electron: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<< " GeV]\n";
  std::cout<<"    The electron's true energy in the tracker: "<<energy<<" GeV\n";
  std::cout<<"    The electron's calorimeter deposits were: ";
  calorimeter_deposits->print_calorimeter_deposits();
  std::cout<<"    The electron's true energy in the muon chmaber was: 0 GeV\n";
}
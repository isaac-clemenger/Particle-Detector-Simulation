// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the photon class

#include<iostream>
#include"Photon.h"
#include"random.h"

// Constructors
// Parameterised Constructor
Photon::Photon(int particle_id, double particle_energy) 
{
  calorimeter_deposits = std::make_unique<Calorimeter_deposits>();
  set_id(particle_id);
  set_charge(0);
  set_energy(particle_energy);
  set_calorimeter_deposits(particle_energy);
}


// Copy constructor
Photon::Photon(const Photon &original) :
Calorimeter_interacting(original)
{}

// Move constructor
Photon::Photon(Photon&& original) :
Calorimeter_interacting(std::move(original))
{}

// Overload Assignment operator for deep copying
Photon& Photon::operator=(Photon& original)
{
  if(&original == this) return *this;
  Calorimeter_interacting::operator=(original);
  return *this; 
}

// Move assignment
Photon& Photon::operator=(Photon&& original)
{
  if(&original == this) return *this;
  Calorimeter_interacting::operator=(std::move(original));
  return *this; 
}

// Electron only deposits in em layers of calorimeter, so override setter to reflect this.
void Photon::set_calorimeter_deposits(const double particle_energy)
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

void Photon::print_particle_data() const
{
  std::cout<<"  Photon: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";
  std::cout<<"    The photon's true energy in the tracker was: 0 GeV\n";
  std::cout<<"    The photon's calorimeter deposits were: ";
  calorimeter_deposits->print_calorimeter_deposits();
  std::cout<<"    The photon's true energy in the muon chmaber was: 0 GeV\n";
}
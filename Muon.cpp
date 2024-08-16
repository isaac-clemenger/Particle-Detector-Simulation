// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the muon class

#include<iostream>
#include"Muon.h"

// Constructors
// Parameterised Constructor
Muon::Muon(int particle_id, double particle_energy) :
Particle{particle_id, -1, particle_energy}
{
  tracks_detected = {true, true, true};
  muon_chamber_interactions = {true, true};
}


// Copy constructor
Muon::Muon(const Muon &original) :
Particle(original)
{
  tracks_detected = original.tracks_detected;
  muon_chamber_interactions = original.muon_chamber_interactions;
}

// Move constructor
Muon::Muon(Muon&& original) :
Particle(std::move(original))
{
  tracks_detected = std::move(original.tracks_detected);
  muon_chamber_interactions = std::move(original.muon_chamber_interactions);

}

// Overload Assignment operator for deep copying
Muon& Muon::operator=(Muon& original)
{
  if(&original == this) return *this; // no self assignment
  Particle::operator=(original);
  tracks_detected = original.tracks_detected;
  muon_chamber_interactions = original.muon_chamber_interactions;
  return *this;
}

// Move assignment
Muon& Muon::operator=(Muon&& original)
{
  if(&original == this) return *this;
  Particle::operator=(std::move(original));
  tracks_detected = std::move(original.tracks_detected);
  muon_chamber_interactions = std::move(original.muon_chamber_interactions);
  return *this;    
}

void Muon::print_particle_data() const
{
  std::cout<<"  Muon: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";
  std::cout<<"    The muon's true energy in the tracker was: "<<energy<<" GeV\n";
  std::cout<<"    The muon's true calorimeter deposits are: Calorimeter deposits [EM1,EM2,HAD1,HAD2] = [0,0,0,0] GeV\n";
  std::cout<<"    The muon's true energy in the muon chamber was: "<<energy<<" GeV\n";
}
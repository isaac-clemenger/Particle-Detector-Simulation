// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the calorimeter interacting class
// Contains variables: tracks_detcted, muon_chamber_interactions
// Publically inherits from class particle

#ifndef MUON_H
#define MUON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Particle.h"

class Muon: public Particle
{
// Protected as there will be another tier of inheritance below this
protected:
  std::vector<bool> tracks_detected;
  std::vector<bool> muon_chamber_interactions;
public:
  // Default constructor
  Muon() :
    Particle{}, tracks_detected{true,true,true}, muon_chamber_interactions{true,true} {charge = -1;}
  // Parameterised constructor
  Muon(int particle_id, double particle_energy);
  // Destructor
  ~Muon()
  {}

  // Copy constructor
  Muon(const Muon &original);

  // Move constructor
  Muon(Muon&& original);

  // Overload Assignment operator for deep copying
  Muon& operator=(Muon& original);

  // Overload Assignment operator to move objects 
  Muon& operator=(Muon&& original);  

  // Getters
  std::vector<bool> get_tracks_detected() const {return tracks_detected;}
  std::vector<bool> get_muon_chamber_interactions() const {return muon_chamber_interactions;}

  // Function to print info about a particle
  void print_particle_data() const override;
};

#endif
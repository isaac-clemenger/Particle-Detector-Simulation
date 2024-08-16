// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the muon_chamber class
// Contains variables: muon_chamber_total_detected_energy, muon_chamber_total_particles_detected
// Publically inherits from class boolean_detector

#ifndef MUON_CHAMBER_H
#define MUON_CHAMBER_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Boolean_detector.h"


class Muon_chamber: public Boolean_detector
{
  protected: 
    static double muon_chamber_total_detected_energy;
    static int muon_chamber_total_particles_detected;
  public:
    // Default constructor    
    Muon_chamber() :
      Boolean_detector{} {number_of_layers = 2, efficiencies = {0.9,0.9};}
    // Copy constructor
    Muon_chamber(const Muon_chamber &original);
    // Move constructor
    Muon_chamber(Muon_chamber&& original);
    // Overload Assignment operator for deep copying
    Muon_chamber& operator=(Muon_chamber& original);
    // Move assignment
    Muon_chamber& operator=(Muon_chamber&& original);
    // Destructor
    ~Muon_chamber() {}

    // Getters
    double get_total_detected_energy() const override {return muon_chamber_total_detected_energy;}

    // Printing
    void print_particle_detection_data(int id) override;

    // Print total detected and total detected
    void print_total_detected_particles_and_energy() const override;
    
    // Function to make Muon_chamber detect particles 
    void run_detector(std::shared_ptr<Particle> particle) override;

};

#endif
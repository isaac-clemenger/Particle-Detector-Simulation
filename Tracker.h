// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the tracker class
// Contains variables: tracker_total_detected_energy, tracker_total_particles_detected
// Publically inherits from class boolean_detector

#ifndef TRACKER_H
#define TRACKER_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Boolean_detector.h"


class Tracker: public Boolean_detector
{
  protected:  
    static double tracker_total_detected_energy;
    static int tracker_total_particles_detected;
  public:
    // Default constructor    
    Tracker() :
      Boolean_detector{} {number_of_layers = 3, efficiencies = {0.9,0.9,0.9};}
    // Copy constructor
    Tracker(const Tracker &original);
    // Move constructor
    Tracker(Tracker&& original);
    // Overload Assignment operator for deep copying
    Tracker& operator=(Tracker& original);
    // Move assignment
    Tracker& operator=(Tracker&& original);
    // Destructor
    ~Tracker() {}

    // Getters
    double get_total_detected_energy() const override {return tracker_total_detected_energy;}

    // Printing
    void print_particle_detection_data(int id) override;

    // Print total detected and total detected
    void print_total_detected_particles_and_energy() const override;

    // Function to make Tracker detect particles 
    void run_detector(std::shared_ptr<Particle> particle) override;

};

#endif
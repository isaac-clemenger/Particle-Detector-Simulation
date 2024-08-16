// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the detector class
// This class is an abstract base class

#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<map>
#include"Particle.h"

class Detector
{
  protected: 
  public:
    // Default constructor    
    Detector() = default;
    // Copy constructor
    Detector(const Detector &original);
    // Move constructor
    Detector(Detector&& original);
    // Overload Assignment operator for deep copying
    Detector& operator=(Detector& original);
    // Move assignment
    Detector& operator=(Detector&& original);
    // Destructor
    virtual ~Detector() {}

    // Getters
    virtual double get_total_detected_energy() const = 0;

    // Function to get check if id is present
    virtual bool was_id_detected(int id) = 0;

    // Printing
    virtual void print_particle_detection_data(int id) = 0;

    // Print total detected and total detected
    virtual void print_total_detected_particles_and_energy() const = 0;

    // Function to make detector detect particles 
    // Pass by reference as particles will be in vector of unique pointers (polymorphism), so reference avoids copying unique pointer
    virtual void run_detector(std::shared_ptr<Particle> particle) = 0;

    // Function to find the invisible energy for a detector
    virtual double calculate_invsible_energy(double initial_energy) = 0;
};

#endif
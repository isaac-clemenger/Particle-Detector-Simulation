// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the em_calorimeter class
// Publically inherits from class calorimeter

#ifndef EM_CALORIMETER_H
#define EM_CALORIMETER_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Calorimeter.h"


class Em_calorimeter: public Calorimeter
{
  public:
    // Default constructor    
    Em_calorimeter() = default;
    // Copy constructor
    Em_calorimeter(const Em_calorimeter &original);
    // Move constructor
    Em_calorimeter(Em_calorimeter&& original);
    // Overload Assignment operator for deep copying
    Em_calorimeter& operator=(Em_calorimeter& original);
    // Move assignment
    Em_calorimeter& operator=(Em_calorimeter&& original);
    // Destructor
    ~Em_calorimeter() {}

    // Function to make Calorimeter detect particles 
    void run_detector(std::shared_ptr<Particle> particle) override;

    // Print total detected and total detected
    void print_total_detected_particles_and_energy() const;

    // Printing
    void print_particle_detection_data(int id) override;
};

#endif
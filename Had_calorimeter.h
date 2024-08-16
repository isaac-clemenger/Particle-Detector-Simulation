// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the had_calorimeter class
// Publically inherits from class calorimeter

#ifndef HAD_CALORIMETER_H
#define HAD_CALORIMETER_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Calorimeter.h"


class Had_calorimeter: public Calorimeter
{
  public:
    // Default constructor    
    Had_calorimeter() = default;
    // Copy constructor
    Had_calorimeter(const Had_calorimeter &original);
    // Move constructor
    Had_calorimeter(Had_calorimeter&& original);
    // Overload Assignment operator for deep copying
    Had_calorimeter& operator=(Had_calorimeter& original);
    // Move assignment
    Had_calorimeter& operator=(Had_calorimeter&& original);
    // Destructor
    ~Had_calorimeter() {}

    // Function to make Calorimeter detect particles 
    void run_detector(std::shared_ptr<Particle> particle) override;

    // Printing
    void print_particle_detection_data(int id) override;

    // Print total detected and total detected
    void print_total_detected_particles_and_energy() const;
};

#endif
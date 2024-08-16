// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the boolean_detector class
// Contains variables: detected_ids_and_energy, number_of_layers, efficiencies, detection_in_layers
// Publically inherits from class detector
// This is an abstract class

#ifndef BOOLEAN_DETECTOR_H
#define BOOLEAN_DETECTOR_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<map>
#include"Detector.h"



class Boolean_detector: public Detector
{
  protected: 
    // id and energy are associated with each other, so makes sense to wrap them in a container together
    typedef std::map<int, double> ids_and_energy_map;
    ids_and_energy_map detected_ids_and_energy;  
    int number_of_layers;
    // Assign efficiency to each layer
    std::vector<double> efficiencies;
    // Vector of bools to store detections
    std::vector<bool> detection_in_layers;
  public:
    // Default constructor    
    Boolean_detector() :
      Detector{} {}
    // Copy constructor
    Boolean_detector(const Boolean_detector &original);
    // Move constructor
    Boolean_detector(Boolean_detector&& original);
    // Overload Assignment operator for deep copying
    Boolean_detector& operator=(Boolean_detector& original);
    // Move assignment
    Boolean_detector& operator=(Boolean_detector&& original);
    // Destructor
    virtual ~Boolean_detector() {}

    // Function to get check if id is present
    bool was_id_detected(int id) override;

    // Printing
    virtual void print_particle_detection_data(int id) = 0;

    // Function to make Boolean_detector detect particles 
    virtual void run_detector(std::shared_ptr<Particle> particle) = 0;

    // Function to simulate boolean detection with efficiencies
    // This is a bool such that in the classes below we know if the particle was detected, so can update the static variables accordingly
    bool bool_detection_with_efficiencies(std::shared_ptr<Particle> particle);

    // Function to find the invisible energy for a detector
    double calculate_invsible_energy(double initial_energy) override;
};

#endif
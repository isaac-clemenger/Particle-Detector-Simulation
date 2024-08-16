// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the calorimeter class
// Contains variables: detected_ids_and_energy, calorimeter_total_detected_energy, calorimeter_total_particles_detected
// Publically inherits from class detector

#ifndef CALORIMETER_H
#define CALORIMETER_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Detector.h"
#include"Calorimeter_deposits.h"


class Calorimeter: public Detector
{
  protected: 
    typedef std::map<int, std::vector<double>> ids_and_energy_map;
    ids_and_energy_map detected_ids_and_energy;  
    static double calorimeter_total_detected_energy;
    static int calorimeter_total_particles_detected;
  public:
    // Default constructor    
    Calorimeter() = default;
    // Copy constructor
    Calorimeter(const Calorimeter &original);
    // Move constructor
    Calorimeter(Calorimeter&& original);
    // Overload Assignment operator for deep copying
    Calorimeter& operator=(Calorimeter& original);
    // Move assignment
    Calorimeter& operator=(Calorimeter&& original);
    // Destructor
    virtual ~Calorimeter() {}

    // Getter
    double get_total_detected_energy() const override {return calorimeter_total_detected_energy;}

    // Function to get check if id is present
    bool was_id_detected(int id);

    // Function to simulate the efficiency of the calorimeter
    void calorimeter_efficiency(Calorimeter_deposits &deposits);

    // Function to find the invisible energy for a detector
    double calculate_invsible_energy(double initial_energy) override;
};

#endif
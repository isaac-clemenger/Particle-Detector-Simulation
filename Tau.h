// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the tau class
// Contains variables: decay_products
// Publically inherits from class particle

#ifndef TAU_H
#define TAU_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include"Particle.h"

class Tau: public Particle
{
  private:
    std::vector<std::shared_ptr<Particle>> decay_products;
  public:
    // Default constructor
    Tau() :
      Particle{} {charge = -1;}  
    // Parameterised constructor
    Tau(int particle_id, double particle_energy);
    
    // Copy constructor
    Tau(const Tau &original);

    // Move constructor
    Tau(Tau&& original);

    // Overload Assignment operator for deep copying
    Tau& operator=(Tau& original);

    // Move assignment
    Tau& operator=(Tau&& original);
    // Destructor
    ~Tau(){}

    // Function to create decay products
    int create_decay_products(double &invisible_energy);  

    // Need to override to be able to switch the decay products
    void switch_to_anti() override; 

    // Need a function that will add the decay products to the vector of particles
    int add_decays(std::vector<std::shared_ptr<Particle>> &particles, double &invisible_energy);

    // Print function
    void print_particle_data() const override;
};

#endif
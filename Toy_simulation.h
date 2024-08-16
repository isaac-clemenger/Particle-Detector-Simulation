// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for the toy_simulation class
// Contains variables: particles, detector, initial_energy, event_particles, total_particles
// correctly_identified_particles, total_initial_energy, invisible_energy

#ifndef TOY_SIMULATION_H
#define TOY_SIMULATION_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<map>
#include<utility>
#include<cstdlib> 
#include<time.h> 
#include<list>
#include"Electron.h"
#include"Proton.h"
#include"Neutron.h"
#include"Photon.h"
#include"Muon.h"
#include"Neutrino.h"
#include"Tau.h"
#include"Tracker.h"
#include"Em_calorimeter.h"
#include"Had_calorimeter.h"
#include"Muon_chamber.h"
#include"random.h"

class Toy_simulation
{
  private:
    std::vector<std::shared_ptr<Particle>> particles;
    std::vector<std::shared_ptr<Detector>> detector;
    double initial_energy;
    std::vector<std::string> event_particles;
    // Need these for all simulations, so need to be static
    static double total_particles;
    static double correctly_identified_particles;
    static double total_initial_energy;
    // Also record true invisible energy when creating particles, as this should just be due to neutrinos
    double invisible_energy{};
  public:
    // Default constructor    
    Toy_simulation() {create_detector();}
    // Parametrised constructor
    Toy_simulation(std::vector<std::string> simulation_event_particles, double simulation_initial_energy);
    // Destructor
    ~Toy_simulation() {}         

    //Setters
    void set_initial_energy(double simulation_initial_energy) {initial_energy = check_energy(simulation_initial_energy);}
    void set_event_particles(const std::vector<std::string> simulation_event_particles) {event_particles = simulation_event_particles;}

    // Function that creates detector as vector of the three sub detectors
    void create_detector();

    // Function to create particles based on inputs
    void create_particles();

    // To be made:
    // Function to run particles through detector
    void simulate_detection();

    // function that checks what particles were detected
    void deduce_what_was_detected();

    // Function to switch particles to anti particles 
    void make_anti(bool anti_check, int index);

    // Ensure initial energy is positive before setting
    double check_energy(double energy);

    // Print particles
    void print_particles() const;

    // Print detector info for specific particle
    void print_particle_detection(int id);

    // Print data for all events
    void print_final_data() const;

    // Function to check if we correctly identified the particle
    template <class c_type> bool what_particle_is_this(std::shared_ptr<Particle> particle);

    // Function to find and print the invisible energy for an event
    void print_event_invisible_energy();
};

#endif
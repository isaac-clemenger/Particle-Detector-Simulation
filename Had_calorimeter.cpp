// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the had_calorimeter class

#include<iostream>
#include<memory>
#include"Had_calorimeter.h"
#include"Calorimeter_interacting.h"

// Constructors
// Copy constructor
Had_calorimeter::Had_calorimeter(const Had_calorimeter &original) :
Calorimeter(original)
{}

// Move constructor
Had_calorimeter::Had_calorimeter(Had_calorimeter&& original) :
Calorimeter(std::move(original))
{}

// Overload Assignment operator for deep copying
Had_calorimeter& Had_calorimeter::operator=(Had_calorimeter& original)
{
  if(&original == this) return *this; // no self assignment
  Calorimeter::operator=(original);  
  return *this;
}

// Move assignment
Had_calorimeter& Had_calorimeter::operator=(Had_calorimeter&& original)
{
  if(&original == this) return *this;
  Calorimeter::operator=(std::move(original));
  return *this;    
}

// Function to make Calorimeter detect particles, as it doesn't detect electrons or photons 
void Had_calorimeter::run_detector(std::shared_ptr<Particle> particle)
{ 
  auto calorimeter_interacting_particle = std::dynamic_pointer_cast<Calorimeter_interacting>(particle);
  if (calorimeter_interacting_particle == nullptr) {return;}
  Calorimeter_deposits particles_deposits = calorimeter_interacting_particle->get_calorimeter_deposits();
  // Electrons and photons set their hadronic bits to zero, so use the getter to check if photon or electron, and exit
  if (particles_deposits.get_had1() == 0) {return;}
  calorimeter_efficiency(particles_deposits);
  std::vector<double> had_deposits{particles_deposits.get_had1(), particles_deposits.get_had2()};
  calorimeter_total_detected_energy += (had_deposits[0] + had_deposits[1]);
  detected_ids_and_energy.insert(std::pair<int, std::vector<double>>(particle->get_id(), had_deposits));  
}

// Printing
void Had_calorimeter::print_particle_detection_data(int id) 
{
  std::map<int, std::vector<double>>::iterator detector_scan_it{detected_ids_and_energy.find(id)};
  if (detector_scan_it != detected_ids_and_energy.end())
  {
    std::cout<<" HAD1: "<<(detector_scan_it->second)[0]<<" HAD2: "<<(detector_scan_it->second)[1]<<"\n";
  }
  else
  {
    std::cout<<" HAD1: 0 HAD2: 0 GeV\n";
  }
}

// Print total detected and total detected
void Had_calorimeter::print_total_detected_particles_and_energy() const
{
    std::cout<<"    The total energy detected by the calorimeter: "<<calorimeter_total_detected_energy<<"\n\n";   
}


// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the em_calorimeter class

#include<iostream>
#include<memory>
#include"Em_calorimeter.h"
#include"Calorimeter_interacting.h"

// Constructors
// Copy constructor
Em_calorimeter::Em_calorimeter(const Em_calorimeter &original) :
Calorimeter(original)
{}

// Move constructor
Em_calorimeter::Em_calorimeter(Em_calorimeter&& original) :
Calorimeter(std::move(original))
{}

// Overload Assignment operator for deep copying
Em_calorimeter& Em_calorimeter::operator=(Em_calorimeter& original)
{
  if(&original == this) return *this; // no self assignment
  Calorimeter::operator=(original);  
  return *this;
}

// Move assignment
Em_calorimeter& Em_calorimeter::operator=(Em_calorimeter&& original)
{
  if(&original == this) return *this;
  Calorimeter::operator=(std::move(original));
  return *this;    
}

void Em_calorimeter::run_detector(std::shared_ptr<Particle> particle)
{ 
  auto calorimeter_interacting_particle = std::dynamic_pointer_cast<Calorimeter_interacting>(particle);
  if (calorimeter_interacting_particle == nullptr) {return;}
  Calorimeter_deposits particles_deposits = calorimeter_interacting_particle->get_calorimeter_deposits();
  calorimeter_efficiency(particles_deposits);
  std::vector<double> em_deposits{particles_deposits.get_em1(), particles_deposits.get_em2()};
  // If all particles detected in calorimeter get detected in em part, so make em part record total detected
  calorimeter_total_particles_detected++;
  calorimeter_total_detected_energy += (em_deposits[0] + em_deposits[1]);
  detected_ids_and_energy.insert(std::pair<int, std::vector<double>>(particle->get_id(), em_deposits));      
}

// Printing
void Em_calorimeter::print_particle_detection_data(int id) 
{
  std::map<int, std::vector<double>>::iterator detector_scan_it{detected_ids_and_energy.find(id)};
  if (detector_scan_it != detected_ids_and_energy.end())
  {
    std::cout<<"    The energy detected by the calorimeter is EM1: "<<(detector_scan_it->second)[0]<<" EM2: "<<(detector_scan_it->second)[1];
  }
  else
  {
    std::cout<<"    The energy detected by the calorimeter is EM1: 0 EM2: 0 ";
  }
}

// Print total detected and total detected
void Em_calorimeter::print_total_detected_particles_and_energy() const
{
  std::cout<<"    The total particles detected by the calorimeter: "<<calorimeter_total_particles_detected<<"\n";   
}

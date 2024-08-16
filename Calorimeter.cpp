// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the calorimeter class

#include<iostream>
#include<memory>
#include"Calorimeter.h"
#include"Calorimeter_interacting.h"
#include"random.h"

// Static variables to record total for all events
double Calorimeter::calorimeter_total_detected_energy{};
int Calorimeter::calorimeter_total_particles_detected{};

// Constructors
// Copy constructor
Calorimeter::Calorimeter(const Calorimeter &original) :
Detector(original)
{
  detected_ids_and_energy = original.detected_ids_and_energy; 
}

// Move constructor
Calorimeter::Calorimeter(Calorimeter&& original) :
Detector(std::move(original))
{ 
  detected_ids_and_energy = std::move(original.detected_ids_and_energy); 
}

// Overload Assignment operator for deep copying
Calorimeter& Calorimeter::operator=(Calorimeter& original)
{
  if(&original == this) return *this; // no self assignment
  Detector::operator=(original);  
  detected_ids_and_energy = original.detected_ids_and_energy; 
  return *this;
}

// Move assignment
Calorimeter& Calorimeter::operator=(Calorimeter&& original)
{
  if(&original == this) return *this;
  detected_ids_and_energy = std::move(original.detected_ids_and_energy); 
  return *this;    
}

// Function to get check if id is present
bool Calorimeter::was_id_detected(int id)
{
  std::map<int, std::vector<double>>::iterator detector_scan_it{detected_ids_and_energy.find(id)};
  return (detector_scan_it != detected_ids_and_energy.end());
}

void Calorimeter::calorimeter_efficiency(Calorimeter_deposits &deposits)
{  
  deposits.set_em1(deposits.get_em1()*random::gen_decimal_in_range(95,100));
  deposits.set_em2(deposits.get_em2()*random::gen_decimal_in_range(95,100));
  deposits.set_had1(deposits.get_had1()*random::gen_decimal_in_range(95,100));  
  deposits.set_had2(deposits.get_had2()*random::gen_decimal_in_range(95,100));
}

// Function to find the invisible energy for a detector
double Calorimeter::calculate_invsible_energy(double initial_energy)
{
  double detected_energy{0};
  ids_and_energy_map::iterator invisible_energy_it;
  for (invisible_energy_it = detected_ids_and_energy.begin(); invisible_energy_it != detected_ids_and_energy.end(); invisible_energy_it++)
  {
    detected_energy += ((invisible_energy_it->second)[0] + (invisible_energy_it->second)[1]); 
  }
  return initial_energy - detected_energy;
}

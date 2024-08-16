// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the boolean_detector class

#include<iostream>
#include<map>
#include<utility>
#include"Boolean_detector.h"
#include"random.h"

// Constructors
// Copy constructor
Boolean_detector::Boolean_detector(const Boolean_detector &original)  :
Detector(original)
{
  detected_ids_and_energy = original.detected_ids_and_energy;   
  efficiencies = original.efficiencies;  
  detection_in_layers = original.detection_in_layers;
  number_of_layers = original.number_of_layers;
}

// Move constructor
Boolean_detector::Boolean_detector(Boolean_detector&& original) :
Detector(std::move(original))
{
  detected_ids_and_energy = std::move(original.detected_ids_and_energy);
  efficiencies = std::move(original.efficiencies);
  detection_in_layers = std::move(original.detection_in_layers);
  number_of_layers = original.number_of_layers;
  original.number_of_layers = 0;
}

// Overload Assignment operator for deep copying
Boolean_detector& Boolean_detector::operator=(Boolean_detector& original)
{
  if(&original == this) return *this; // no self assignment
  Detector::operator=(original);
  detected_ids_and_energy = original.detected_ids_and_energy;  
  efficiencies = original.efficiencies;  
  detection_in_layers = original.detection_in_layers;
  number_of_layers = original.number_of_layers;
  return *this;
}

// Move assignment
Boolean_detector& Boolean_detector::operator=(Boolean_detector&& original)
{
  if(&original == this) return *this;
  Detector::operator=(std::move(original));
  detected_ids_and_energy = std::move(original.detected_ids_and_energy);
  efficiencies = original.efficiencies;  
  detection_in_layers = original.detection_in_layers;
  number_of_layers = original.number_of_layers;
  return *this;    
}


bool Boolean_detector::was_id_detected(int id)
{
  std::map<int, double>::iterator detector_scan_it{detected_ids_and_energy.find(id)};
  return (detector_scan_it != detected_ids_and_energy.end());
}


// Function to simulate boolean detection with efficiencies
bool Boolean_detector::bool_detection_with_efficiencies(std::shared_ptr<Particle> particle)
{
  int layers_detected{0};  
  // Use rng to simulate the detector efficiency 
  double rand{random::gen_rand_0_and_1()};  
  for (int i{}; i < number_of_layers; i++)
  {  
    if (rand < efficiencies[i])
    {
      detection_in_layers.push_back(true);  
      layers_detected++;
    }
  }
  // if not detected in more than 1 layer then particle is not detected
  if ((number_of_layers - layers_detected > 1) == false)
  {
    detected_ids_and_energy.insert(std::pair<int, double>(particle->get_id(), particle->get_energy()));    
    // Particle was detected
    return true;
  }
  else
  {
    // Particle wasn't detected
    return false;
  }
}


// Function to find the invisible energy for a detector
double Boolean_detector::calculate_invsible_energy(double initial_energy)
{
  double detected_energy{0};
  ids_and_energy_map::iterator invisible_energy_it;
  for (invisible_energy_it = detected_ids_and_energy.begin(); invisible_energy_it != detected_ids_and_energy.end(); invisible_energy_it++)
  {
    detected_energy += (invisible_energy_it->second); 
  }
  return initial_energy - detected_energy;
}
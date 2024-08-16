// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the tracker class

#include<iostream>
#include"Tracker.h"

// Define statics
double Tracker::tracker_total_detected_energy{};
int Tracker::tracker_total_particles_detected{};

// Constructors
// Copy constructor
Tracker::Tracker(const Tracker &original) :
Boolean_detector(original)
{}

// Move constructor
Tracker::Tracker(Tracker&& original) :
Boolean_detector(std::move(original))
{}

// Overload Assignment operator for deep copying
Tracker& Tracker::operator=(Tracker& original)
{
  if(&original == this) return *this; // no self assignment
  Boolean_detector::operator=(original);  
  return *this;
}

// Move assignment
Tracker& Tracker::operator=(Tracker&& original)
{
  if(&original == this) return *this;
  Boolean_detector::operator=(std::move(original));
  return *this;    
}


// Function that prints particle data
// Printing
void Tracker::print_particle_detection_data(int id) 
{
  std::map<int, double>::iterator detector_scan_it{detected_ids_and_energy.find(id)};
  if (detector_scan_it != detected_ids_and_energy.end())
  {
    std::cout<<"    The energy detected by the tracker is "<<detector_scan_it->second<<" GeV\n";
  }
  else
  {
    std::cout<<"    The energy detected by the tracker is 0 GeV\n";
  }
}

// Print total detected and total detected
void Tracker::print_total_detected_particles_and_energy() const
{
  std::cout<<"    The total particles detected by the tracker: "<<tracker_total_particles_detected<<"\n";
  std::cout<<"    The total energy detected by the tracker: "<<tracker_total_detected_energy<<" GeV\n\n";
}


// Function to detect particles
void Tracker::run_detector(std::shared_ptr<Particle> particle)
{
  if (particle->get_charge() != 0)
  {
    if (bool_detection_with_efficiencies(particle)) 
    {
      tracker_total_particles_detected++;
      tracker_total_detected_energy += particle->get_energy();
    }
  }
  else
  {
    detection_in_layers = {false, false, false};
  }
}
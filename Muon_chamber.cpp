// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the muon_chamber class

#include<iostream>
#include<memory>
#include"Muon_chamber.h"
#include"Muon.h"

// Define statics
double Muon_chamber::muon_chamber_total_detected_energy{};
int Muon_chamber::muon_chamber_total_particles_detected{};

// Constructors
// Copy constructor
Muon_chamber::Muon_chamber(const Muon_chamber &original) :
Boolean_detector(original)
{}

// Move constructor
Muon_chamber::Muon_chamber(Muon_chamber&& original) :
Boolean_detector(std::move(original))
{}

// Overload Assignment operator for deep copying
Muon_chamber& Muon_chamber::operator=(Muon_chamber& original)
{
  if(&original == this) return *this; // no self assignment
  Boolean_detector::operator=(original);  
  return *this;
}

// Move assignment
Muon_chamber& Muon_chamber::operator=(Muon_chamber&& original)
{
  if(&original == this) return *this;
  Boolean_detector::operator=(std::move(original));
  return *this;    
}



// Printing
void Muon_chamber::print_particle_detection_data(int id) 
{
  std::map<int, double>::iterator detector_scan_it{detected_ids_and_energy.find(id)};
  if (detector_scan_it != detected_ids_and_energy.end())
  {
    std::cout<<"    The energy detected by the muon chamber is "<<detector_scan_it->second<<" GeV\n";
  }
  else
  {
    std::cout<<"    The energy detected by the muon chambers is 0 GeV\n";
  }
}

// Print total detected and total detected
void Muon_chamber::print_total_detected_particles_and_energy() const
{
  std::cout<<"    The total particles detected by the muon chamber: "<<muon_chamber_total_particles_detected<<"\n";
  std::cout<<"    The total energy detected by the muon chamber: "<<muon_chamber_total_detected_energy<<" GeV\n\n";    
}

// Function to make Muon_chamber detect particles 
void Muon_chamber::run_detector(std::shared_ptr<Particle> particle)
{
    // Attempt to cast particle ptr as a muon ptr
    auto Muon_chamber_interacting_particle = std::dynamic_pointer_cast<Muon>(particle);
    // If this fails, will give a nullptr, so throw these as they aren't muons
    if (Muon_chamber_interacting_particle == nullptr) {detection_in_layers = {false, false};return;}
    // Now know these are all muons, so detect these
    if (bool_detection_with_efficiencies(particle))
    {
      muon_chamber_total_particles_detected++;
      muon_chamber_total_detected_energy += particle->get_energy();
    }
}

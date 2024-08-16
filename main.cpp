// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
/*
This project simulates a simplified particle detector in C++. The particles considered are: 
electrons, muons, taus, neutrinos, protons, neutrons, and photons. They are detected one by one, 
simulating a "particle gun" like scenario. The code adheres to principles of object orientated 
programming, using inheritance chains for both the particles and the detectors. 
*/

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<map>
#include<utility>
#include<cstdlib> 
#include<time.h> 
#include"Toy_simulation.h"
#include"input_check.h"

// Main program
int main()
{
  // New random seed each time
  std::srand(time(nullptr)); 
  while(true)
  { 
    std::vector<std::string> particles_in_event{};
    double input_energy{};
    while (true)
    {
      std::string particle_name_in_event{""};
      bool more_particles{false};
      std::cout<<"Enter the name of the particle in the event (should be all lower case, antiparticles all one word, e.g. antielectron):\n";
      std::getline(std::cin, particle_name_in_event);
      particles_in_event.push_back(particle_name_in_event);
      std::cout<<"Would you like to enter another particle for the event? (enter y/n)\n";
      std::string yes_or_no{""};
      std::getline(std::cin, yes_or_no);
      input_check::correct_character_check(yes_or_no,'y','n');
      // Break input loop if user says no
      if (yes_or_no[0] == 'n') {break;}
    }
    try
    {
      Toy_simulation sim(particles_in_event, input_check::real_number_check());
      sim.simulate_detection();
      sim.deduce_what_was_detected();
    }
    catch(...)
    {
      std::cout<<"invalid inputs\n";
    }
    std::cout<<"Would you like to simulate another event? (enter y/n)\n";
    std::string yes_or_no{""};
    std::getline(std::cin, yes_or_no);
    input_check::correct_character_check(yes_or_no,'y','n');
    // Break input loop if user says no
    if (yes_or_no[0] == 'n') {break;}
  }
  Toy_simulation sim{};
  sim.print_final_data();
  return 0;
}

// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the toy_simulation class

#include"Toy_simulation.h"

// Static variables
double Toy_simulation::total_particles{};
double Toy_simulation::correctly_identified_particles{};
double Toy_simulation::total_initial_energy{};

// Constructors
// Parametrised constructor
Toy_simulation::Toy_simulation(std::vector<std::string> simulation_event_particles, double simulation_initial_energy) 
{
  set_initial_energy(simulation_initial_energy);
  set_event_particles(simulation_event_particles);
  create_detector();
  create_particles();
} 

void Toy_simulation::create_detector()
{
  detector.push_back(std::make_shared<Tracker>());
  detector.push_back(std::make_shared<Em_calorimeter>());
  detector.push_back(std::make_shared<Had_calorimeter>());
  detector.push_back(std::make_shared<Muon_chamber>());
}

void Toy_simulation::make_anti(bool anti_check, int index)
{
  if (anti_check == true)
  {
    particles[index]->switch_to_anti(); 
  }  
}

void Toy_simulation::create_particles()
{
  int particles_in_event{static_cast<int>(event_particles.size())};
  std::vector<double> random_energies{random::gen_n_numbers(particles_in_event)};  
  int assign_ids{1};
  // As taus decay, creating more particles, this prevents us from using assign_ids as a good index, so need another
  int random_index{0};
  bool set_anti{false};
  for (auto particle_it{event_particles.begin()}; particle_it < event_particles.end(); particle_it++)
  {
    // check if the particle is an antiparticle or not 
    if ((*particle_it).substr(0,4) == "anti")
    {
      (*particle_it) = (*particle_it).substr(4); 
      set_anti = true;  
    }

    if (*particle_it == "electron")
    {
      particles.push_back(std::make_shared<Electron>(Electron(assign_ids, initial_energy * random_energies[random_index])));  
      make_anti(set_anti, assign_ids-1);      
    }
    else if (*particle_it == "muon")
    {
      particles.push_back(std::make_shared<Muon>(Muon(assign_ids, initial_energy * random_energies[random_index])));
      make_anti(set_anti, assign_ids-1);  
    }
    else if (*particle_it == "tau")
    {
      assign_ids =  Tau(assign_ids, initial_energy * random_energies[random_index]).add_decays(particles, invisible_energy);    
      make_anti(set_anti, assign_ids-1);
    }
    else if (*particle_it == "neutrino")
    {
      particles.push_back(std::make_shared<Neutrino>(Neutrino(assign_ids, initial_energy * random_energies[random_index],  false))); 
      make_anti(set_anti, assign_ids-1); 
      invisible_energy += initial_energy * random_energies[random_index];
    }
    else if (*particle_it == "photon")
    {
      particles.push_back(std::make_shared<Photon>(Photon(assign_ids, initial_energy * random_energies[random_index])));    
      make_anti(set_anti, assign_ids-1);
    }
    else if (*particle_it == "proton")
    {
      particles.push_back(std::make_shared<Proton>(Proton(assign_ids, initial_energy * random_energies[random_index])));
      make_anti(set_anti, assign_ids-1);
    }  
    else if (*particle_it == "neutron")
    {
      particles.push_back(std::make_shared<Neutron>(Neutron(assign_ids, initial_energy * random_energies[random_index])));
      make_anti(set_anti, assign_ids-1);  
    }
    else
    {
      std::cout<<"Please enter a valid particle name that is included in this simulation\n";
      throw particles;
    }
    assign_ids++;
    random_index++;
  }  
  // We add 1 to assign ids when loop ends, so end up with 1 extra particle
  assign_ids = assign_ids - 1;
  // Account for the fact that the tau decays so we get more particles, as otherwise in theory could have efficiency > 1
  // Hence we use assign ids and not the index
  total_particles += assign_ids;
  total_initial_energy += initial_energy;
}

void Toy_simulation::simulate_detection() 
{
  for (auto particle_sim_it{particles.begin()}; particle_sim_it < particles.end(); particle_sim_it++)
  {
    for (auto detector_sim_it{detector.begin()}; detector_sim_it < detector.end(); detector_sim_it++)
    {
      (*detector_sim_it) -> run_detector(*particle_sim_it);
    }
  }
}

void Toy_simulation::deduce_what_was_detected()
{
  std::cout<<"\n-------------------------------------------------------------------------------------------------------\n";
  std::cout<<"Information for this event:\n";
  for (auto deduce_particle_it{particles.begin()}; deduce_particle_it < particles.end(); deduce_particle_it++)
  {
    // Keep track of what layer we're in, either tracker, em calorimeter, had calorimeter, muon chamber
    int index{0};
    std::vector<bool> where_particle_was_detected{false,false,false,false};
    for (auto in_this_detector_it{detector.begin()}; in_this_detector_it < detector.end(); in_this_detector_it++)
    {   
      if ((*in_this_detector_it)->was_id_detected((*deduce_particle_it)->get_id()) == true)
      {
        where_particle_was_detected[index] = true;  
      }
      index++;
    }
    // Now narrow down what particle it was based on what layers it was detected in
    if (where_particle_was_detected[0] == true)
    {
      if (where_particle_was_detected[2] == true)
      {
        (*deduce_particle_it)->print_particle_data();
        print_particle_detection((*deduce_particle_it)->get_id());
        std::cout<<"  Particle detected as proton\n";
        if (what_particle_is_this<Proton>(*deduce_particle_it)) {correctly_identified_particles++;}
      }
      else if (where_particle_was_detected[3] == true)
      {
        (*deduce_particle_it)->print_particle_data();
        print_particle_detection((*deduce_particle_it)->get_id());
        std::cout<<"  Particle detected as muon\n";
        if (what_particle_is_this<Muon>(*deduce_particle_it)) {correctly_identified_particles++;}
      }
      else
      {
        (*deduce_particle_it)->print_particle_data();
        print_particle_detection((*deduce_particle_it)->get_id());
        std::cout<<"  Particle detected as electron\n";
        if (what_particle_is_this<Electron>(*deduce_particle_it)) {correctly_identified_particles++;}
      }
    }
    else if (where_particle_was_detected[2] == true)
    {
      (*deduce_particle_it)->print_particle_data();
      print_particle_detection((*deduce_particle_it)->get_id());
      std::cout<<"  Particle detected as neutron\n";
      if (what_particle_is_this<Neutron>(*deduce_particle_it)) {correctly_identified_particles++;}
    }
    else if (where_particle_was_detected[1] == true)
    {
      (*deduce_particle_it)->print_particle_data();
      print_particle_detection((*deduce_particle_it)->get_id());
      std::cout<< " Particle detected as photon\n";
      if (what_particle_is_this<Photon>(*deduce_particle_it)) {correctly_identified_particles++;}
    }
    else
    {
      (*deduce_particle_it)->print_particle_data();
      print_particle_detection((*deduce_particle_it)->get_id());
      std::cout<<"  Particle "<<(*deduce_particle_it)->get_id()<<" was not detected\n";
    }
    std::cout<<"\n";
  }  
  // Also print the invisble energy for the event
  print_event_invisible_energy();
}


double Toy_simulation::check_energy(double energy)
{
  if (energy < 0)
  { 
    std::cout<<"This energy is non physical\n";
    // Throw so we can catch it in the try catch function in the main
    throw energy;
  } 
  else 
  {
    return energy;
  } 
}


void Toy_simulation::print_particles() const
{
  for (auto print_particle_it(particles.begin()); print_particle_it < particles.end(); print_particle_it++)
  {
    (*print_particle_it) -> print_particle_data();
  }
}

// Print detector info for specific particle
void Toy_simulation::print_particle_detection(int id)
{
  for (auto detector_print_it(detector.begin()); detector_print_it < detector.end(); detector_print_it++)
  {
    (*detector_print_it)->print_particle_detection_data(id);
  }
}


// Print data for all events
void Toy_simulation::print_final_data() const
{
  std::cout<<"\n-------------------------------------------------------------------------------------------------------\n";
  std::cout<<"Information for all events: \n";
  std::cout<<"  Totals for the sub detectors:\n";
  // Give the total energy detection by the greatest energy detected by one of the detectors, so store in a list to sort easily
  std::list<double> total_detected_energies{};
  for (auto detector_print_it(detector.begin()); detector_print_it < detector.end(); detector_print_it++)
  {
    (*detector_print_it)->print_total_detected_particles_and_energy();
    total_detected_energies.push_back(((*detector_print_it)->get_total_detected_energy()));
  }
  std::cout<<"  The overall identification efficiency was: "<<(correctly_identified_particles/total_particles)*100<<"%\n";
  // .sort gives elements lowest to highest, use .reverse to get largest element at beginning
  total_detected_energies.sort();
  total_detected_energies.reverse();
  std::cout<<"  The percentage of energy detected was: "<<((*(total_detected_energies.begin()))/total_initial_energy)*100<<"%\n";
}

template <class c_type> bool Toy_simulation::what_particle_is_this(std::shared_ptr<Particle> particle)
{
  auto real_particle_type = std::dynamic_pointer_cast<c_type>(particle);
  // Will not give a nullptr if we can cast to the particle's type
  if (real_particle_type != nullptr) {return true;}
  return false;
}

// Function to find and print the invisible energy for an event
void Toy_simulation::print_event_invisible_energy()
{
  // Want lowest invisble enegry across the detectors to be the overall for an event, use list as easy to sort
  std::list<double> detected_invisible_energies{};
  for (auto invisible_energy_it(detector.begin()); invisible_energy_it < detector.end(); invisible_energy_it++)
  {
    detected_invisible_energies.push_back((*invisible_energy_it)->calculate_invsible_energy(initial_energy));
  }
  // .sort() gives ascending order, so lowest will be zeroth element
  detected_invisible_energies.sort();
  std::cout<<"  The true invisible energy for this event was: "<<invisible_energy<<" GeV\n";
  std::cout<<"  The detected invisible energy for this event was: "<<*(detected_invisible_energies.begin())<<" GeV\n";
}
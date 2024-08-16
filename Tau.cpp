// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the tau class

#include<iostream>
#include<memory>
#include"Tau.h"
#include"Neutrino.h"
#include"Muon.h"
#include"Electron.h"
#include"Calorimeter_interacting.h"
#include"random.h"

// Constructors
// Parameterised constructor
Tau::Tau(int particle_id, double particle_energy) :
Particle{particle_id, -1, particle_energy}
{}

// Copy constructor
Tau::Tau(const Tau &original) :
Particle(original)
{
  // Need to take more care for decay products as is a vector of pointers
  decay_products = original.decay_products;
}

// Move constructor
Tau::Tau(Tau&& original) :
Particle(std::move(original))
{
  // Need to take more care for decay products as is a vector of pointers
  decay_products = std::move(original.decay_products);
  for (int i{}; i < (original.decay_products).size(); i++)
  {
    original.decay_products[i] = nullptr;
  }
}

// Overload Assignment operator for deep copying
Tau& Tau::operator=(Tau& original)
{
  if(&original == this) return *this; // no self assignment
  Particle::operator=(original);
  // Need to take more care for decay products as is a vector of pointers
  decay_products = original.decay_products;
  return *this;
}

// Move assignment
Tau& Tau::operator=(Tau&& original)
{
  if(&original == this) return *this;
  Particle::operator=(std::move(original));
  // Need to take more care for decay products as is a vector of pointers
  decay_products = std::move(original.decay_products);
  for (int i{}; i < (original.decay_products).size(); i++)
  {
    original.decay_products[i] = nullptr;
  } 
  return *this;    
}

// Function to create decay products
int Tau::create_decay_products(double &invisible_energy)
{  
  // As ids are assigned manually in the sim class, and we add more particles with ids so need to keep track of the final id assigned here
  int last_decay_product_id{0};
  // Taus decay leptonically 35% of the time, hadronically 65%, simulate this through rng
  double decay_type_rand{random::gen_rand_0_and_1()};
  if (decay_type_rand > 0.65) // Tau decays leptonically
  {
    // Three decay products in leptonic decay so need three random numbers that add to one
    std::vector<double> random_energies{random::gen_n_numbers(3)};
    decay_products.push_back(std::make_shared<Neutrino>(Neutrino(id, energy * random_energies[0],  false)));
    invisible_energy += energy * random_energies[0];
    // By lepton universatliy, muons and electrons should have equal probability of being generated here
    double leptonic_decay_rand{random::gen_rand_0_and_1()};
    if (leptonic_decay_rand > 0.5)
    {
      decay_products.push_back(std::make_shared<Neutrino>(Neutrino(id + 1, energy * random_energies[1],  false)));
      decay_products.push_back(std::make_shared<Electron>(Electron(id + 2, energy * random_energies[2])));
      invisible_energy += energy * random_energies[1];
    }
    else
    {
      decay_products.push_back(std::make_shared<Neutrino>(Neutrino(id + 1, energy * random_energies[1], false)));
      decay_products.push_back(std::make_shared<Muon>(Muon(id + 2, energy * random_energies[2])));  
      invisible_energy += energy * random_energies[1];
    }
    last_decay_product_id = id + 2;
  }
  else // Tau decays hadronically
  {
    // Two decay products in hadronic decay so need two random numbers that add to one
    std::vector<double> random_energies{random::gen_n_numbers(2)};
    decay_products.push_back(std::make_shared<Neutrino>(Neutrino(id, energy * random_energies[0],  false)));
    decay_products.push_back(std::make_shared<Calorimeter_interacting>(Calorimeter_interacting(id + 1, 0, energy * random_energies[1])));
    last_decay_product_id = id + 1;
    invisible_energy += energy * random_energies[0];
  }

  // Need to ammend decay products based on whether we have tau or antitau, as have created for regular tau
  if (charge == 1)
  {
    for(auto decay_it(decay_products.begin()); decay_it < decay_products.end(); decay_it++)
    {
      (*decay_it) -> switch_to_anti();
    } 
  }
  return last_decay_product_id;
}

// Switch decay products to anti particles too
void Tau::switch_to_anti()
{
  charge = charge * -1;
  for(auto decay_it(decay_products.begin()); decay_it < decay_products.end(); decay_it++)
  {
    (*decay_it) -> switch_to_anti();
  } 
}

// Need a function that will add the decay products to the vector of particles
int Tau::add_decays(std::vector<std::shared_ptr<Particle>> &particles, double &invisible_energy)
{
  int last_decay_product_id{0};
  // Make sure particle has decayed before adding products, this could happen if was made in default constrctor
  if (decay_products.size() == 0)
  {
    last_decay_product_id = create_decay_products(invisible_energy);
  } 
  for (int i{}; i < decay_products.size(); i++)
  {
    particles.push_back(decay_products[i]);
  }
  return last_decay_product_id;
}

// Print function
void Tau::print_particle_data() const 
{
  std::cout<<"  Tau: [id,q,E] = ["<<id<<", "<<charge<<", "<<energy<<" GeV]\n";  
  std::cout<<"  Decay products: \n";
  for(auto decay_it(decay_products.begin()); decay_it < decay_products.end(); decay_it++)
  {
    (*decay_it) -> print_particle_data();  
  }
}
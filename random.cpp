// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Source file for the random namespace

#include"random.h"

namespace random
{
  // rand() gives ints so need to cast to a double to allow division  
  double gen_rand_0_and_1() {return static_cast<double>(rand()) / RAND_MAX;}  

  std::vector<double> gen_n_numbers(int n)
  {
    // Keep sum to normalise random numbers  
    double sum{0};  
    std::vector<double> random_numbers(n);
    for(auto rand_it{random_numbers.begin()}; rand_it < random_numbers.end(); rand_it++)
    {
      *rand_it = rand();
      sum += *rand_it;
    }  
    // Normalise the random numbers, so they add to 1
    for(auto norm_it{random_numbers.begin()}; norm_it < random_numbers.end(); norm_it++)
    {
      *norm_it = *norm_it / sum; 
    }
    return random_numbers;  
  }  

  double gen_decimal_in_range(int min, int max)
  {
    double random{static_cast<double>(min + rand() % (max - min + 1))};
    return random/100;
  }
}
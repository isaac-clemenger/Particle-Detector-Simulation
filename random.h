// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header file for the random namespace
// Contains functions: gen_rand_0_and_1, gen_n_numbers, gen_decimal_in_range

#ifndef RANDOM_H
#define RANDOM_H

#include<iostream> 
#include<cstdlib> 
#include<time.h> 
#include<vector>

namespace random
{  
  double gen_rand_0_and_1();  
  std::vector<double> gen_n_numbers(int n);  
  double gen_decimal_in_range(int min, int max);  
}

#endif
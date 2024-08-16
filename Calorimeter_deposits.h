// PHYS 30762 Programming in C++
// Detector Simulation Project
// Isaac Clemeneger 11/05/2024
// Header for calorimeter deposits class
// Contains variables: em1, em2, had1, had2, representing a particles deposits in the calorimeter
// Publically inherits from Particle

#ifndef CALORIMETER_DEPOSITS_H
#define CALORIMETER_DEPOSITS_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

class Calorimeter_deposits
{
private:
  double em1, em2, had1, had2;
public:
  // Default constructor
  Calorimeter_deposits() = default;

  // Parameterised Constructor
  Calorimeter_deposits(double particle_em1, double particle_em2, double particle_had1, double particle_had2);

  // Copy constructor
  Calorimeter_deposits(const Calorimeter_deposits &original);

  // Move constructor
  Calorimeter_deposits(Calorimeter_deposits&& original);

  // Overload Assignment operator for deep copying
  Calorimeter_deposits& operator=(Calorimeter_deposits& original);
  
  // Overload Assignment operator to move objects 
  Calorimeter_deposits& operator=(Calorimeter_deposits&& original);

  // Getters
  double get_em1() const {return em1;}
  double get_em2() const {return em2;}
  double get_had1() const {return had1;}
  double get_had2() const {return had2;}

  // Setters
  void set_em1(const double particle_em1) {em1 = particle_em1;}
  void set_em2(const double particle_em2) {em2 = particle_em2;}
  void set_had1(const double particle_had1) {had1 = particle_had1;}
  void set_had2(const double particle_had2) {had2 = particle_had2;}
    
  // Printing function
  void print_calorimeter_deposits() const;  
};

#endif
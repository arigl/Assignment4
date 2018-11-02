/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Creates a Student class that holds variables for Queue times 
 */


#include <iostream>
#include "Student.hpp"

using namespace std;

Student::Student()
{
  timeNeeded = 0;
  timeSpent = 0;
  timeWaited = 0;
  arrivalTime = 0;
}

Student::Student(int needs, int arrived)
{
  timeNeeded = needs;
  arrivalTime = arrived;
  timeSpent = 0;
  timeWaited = 0;
}

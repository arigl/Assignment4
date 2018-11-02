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
  timeNeeded = 0; //time the student needs 
  timeSpent = 0; //time the student has spent there 
  timeWaited = 0; //time the student has waited
  arrivalTime = 0; //the time the student got there 
}

Student::Student(int needs, int arrived)
{
  timeNeeded = needs;
  arrivalTime = arrived;
  timeSpent = 0;
  timeWaited = 0;
}

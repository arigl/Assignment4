/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Determines variables for Student Class 
 */


#include <iostream>
using namespace std;

class Student
{
  public:
    Student();
    Student(int needs, int arrived);

    int timeNeeded;
    int timeSpent;
    int timeWaited;
    int arrivalTime;
};

/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Takes in arguments for a filename and executes the rest of the program 
 */


#include <iostream>
#include <fstream>
#include "GenQueue.h"
#include "Simulation.hpp"


int main(int argc, char** argv){
  string fileName;

  fileName = argv[1];

  Simulation s(fileName);
  s.moveLine();

  cout << "The average student wait time is: " << s.meanWait << " minutes!" << endl;
  cout << "The median student wait time is: " << s.medianWait << " minutes!" << endl;
  cout << "The longest student wait time is: " << s.longestWait << " minutes!" << endl;
  cout << s.waitedOverTen << " student(s) waited over 10 minutes" << endl;
  cout << "" << endl;
  cout << "Windows were idle for an average of " << s.averageIdle << " minutes!" << endl;
  cout << "The longest window idle time is: " << s.longestIdle << endl;
  cout << s.idleOverFive << " windows were idle for over 5 minutes" << endl;
}

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

  // CANT ADD ARGUMENTS IN HERE, KEEP GETTING STOI ERROR :(
  fileName = argv[1];

  Simulation s(fileName);
  s.moveLine();

  cout << "The mean student wait time is: " << s.meanWait << endl;
  cout << "The median student wait time is: " << s.medianWait << endl;
  cout << "The longest student wait time is: " << s.longWait << endl;
  cout << "The number of students waiting over 10 minutes is: "<< s.tenPlus << endl;
  cout << "The mean window idle time is:  " << s.meanIdle << endl;
  cout << "The longest window idle time is: " << s.longestIdle << endl;
  cout << "Number of windows idle for over 5 minutes: "<< s.fivePlus << endl;
}

/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Defines variables for Simulation.cpp
 */


#include <iostream>
#include "Student.hpp"
#include "genQueue.h"

using namespace std;

class Simulation
{
  public:
    Simulation();
    Simulation(string fileName);//populate in here

    int numberPeople;
    int totalPeople;
    int windowCount;
    int timer;
    int arrv;
    int counter;
    int medianWait;
    int longestWait;
    int overTen;
    int overFive;

    double meanWait;
    double meanIdle;
    double longestIdle;


    string fileName;
    string currentLine;

    ifstream people;

    GenQueue<Student> entered;
    GenQueue<Student> regLine;

    int *idleTimes;
    int *waitTimes;
    bool *windows;
    Student *personAtWindow;

    void calculate();
    void addToLine();
    void moveLine(); //This should be the main loop
    void clearWindows();
    void updateIdleWindows();
    void outputStats();
    void updateWaitTime();
    void printLine();//debugging purposes

    bool windowsAreEmpty();

    int windowsOpen();

    double findMedian();


};

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
    Simulation(string fileName);

    int numberPeople; // number of people currently there
    int total; // total amount of people exsisted
    int windowAmount; // amount of windows
    int timer; //flow of time for customers
    int arrv; // counter varible
    int counter; // counter variable
    int medianWait; //median of the waiting times
    int longWait; //longest wait time
    int tenPlus; //over ten ticks
    int fivePlus; //over five ticks

    double meanWait; //average wait time
    double meanIdle; //average idle time
    double longestIdle; //longest idle time

    string fileName; // file name
    string currentLine; // iterates through file

    ifstream inFile; //file stream

    GenQueue<Student> begin; //students intering queue
    GenQueue<Student> end; // students exsisting queue

    int *idleArray; // array of idle students
    int *waitArray; //array of waiting students
    bool *windows; //which windows are open
    Student *personAtWindow; //the student at the window

    void calculate();
    void add();
    void move();
    void clearWindows();
    int checkWindows();

    double longestWait();
    double overTen();
    double overFive();
    double longestIdleWait();
    double median();

    bool windowsAreEmpty();

    int windowsOpen();
};

/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Goes through a queue of students, and finds various statistics
 */

#include <iostream>
#include <fstream>
#include "Simulation.hpp"
#include "GenQueue.h"
#include <algorithm>

using namespace std;

Simulation::Simulation()
{
 // Variable explanations are in the header file 
  numberPeople = 0;
  timer = 0;
  meanWait = 0;
  medianWait = 0;
  longWait = 0;
  meanIdle = 0;
  longestIdle = 0;
  tenPlus = 0;
  fivePlus = 0;
}

//from the file, takes how many people have arrived
Simulation::Simulation(string file)
{
  arrv = 0;
  counter = 0;
  fileName = file; //sets fileName to the arguments 
  longWait = 0;
  longestIdle = 0;
  meanWait = 0;
  medianWait = 0;
  meanIdle = 0;
  numberPeople = 0;
  timer = 0;
  total = 0;
  tenPlus = 0;
  fivePlus = 0;
  calculate();
}

double Simulation::overTen()
{
 /*
 Iterates through the people waiting, and counts if there are more than 10
  */
  for(int i = 0; i < total; i++) 
  {
    if(waitArray[i] > 10)
    {
      tenPlus++;
    }
  }
}

double Simulation::overFive()
{
  /*
 Iterates through the people idle, and counts if there are more than 5
  */
  for(int j = 0; j < windowAmount; j++)
  {
    if(idleArray[j] > 5)
    {
      fivePlus++;
    }
  }
}

double Simulation::longestIdleWait()
{
  /*
 Iterates through the people idle, and looks for the longest
  */
  for(int j = 0; j < windowAmount; j++)
  {
    if(longestIdle < idleArray[j])
    {
      longestIdle = idleArray[j];
    }
  }
}

double Simulation::longestWait()
{
   /*
 Iterates through the people waiting, and looks for the longest
  */
  for(int i = 0; i < total; i++)
  {
    if(longWait < waitArray[i])
    {
      longWait = waitArray[i];
    }
  }
}

bool Simulation::windowsAreEmpty()
{
   /*
Checks to see which windows are empty, and return true if they are all empty, if not, false 
*/
  for(int i = 0; i < windowAmount; i++)
  {
    if(windows[i] == true)
    {
      return false;
    }
  }
  return true;
}

int Simulation::checkWindows()
{
  /*
 Checks to see the amount of windows that are occupied 
  */
  for(int i = 0; i < windowAmount; i++)
  {
    if(windows[i] == false)
    {
      return i;
    }
  }
  return -1;
}

double Simulation::median()
{
   /*
 Determines the median by finding the sorting, and then finding the middle value 
  */
  sort(waitArray, waitArray + total - 1);
  if((total % 2) == 1)
  {
    return waitArray[(total/2)];
  }
  else
  {
    return ((waitArray[total/2]+waitArray[(total/2)-1]));
  }
}

void Simulation::calculate()
{
   /*
 Opens a file, creates arrays for the windows and idle. Creates a student with variables detailed in the respective header
  */
  inFile.open(fileName); //opens the file
  inFile >> currentLine;
  windowAmount = stoi(currentLine);
  personAtWindow = new Student[windowAmount];
  windows = new bool[windowAmount];
  idleArray = new int[windowAmount];
  int peopleArriving;
  /*
 Iterates through each line, assigning variables in order according to the assignment description
  */
  while(!inFile.eof())
  {
    inFile >> currentLine;
    arrv = stoi(currentLine);

    inFile >> currentLine;
    peopleArriving = stoi(currentLine);
 
    for(int i = 0; i < peopleArriving; i++)
    {
       /*
      After the second line, it begins to add each student and the correspodning time 
      */
      inFile >> currentLine;
      Student p(stoi(currentLine), arrv);
      total++;
      begin.enqueue(p);
    }
  }
  waitArray = new int[total];
}

void Simulation::clearWindows()
{
   /*
   Sends people to the windows, and clears the person currently their based on how long and preference 
  */
  for(int i = 0; i < windowAmount; i++)
  {
    if(windows[i] == true)
    {
      if (personAtWindow[i].timeSpent == personAtWindow[i].timeNeeded)
      {
        windows[i] = false;
        Student temp = personAtWindow[i];
        if(temp.timeWaited == 0)
        {
          waitArray[numberPeople] = 0;
        }
        else
        {
          waitArray[numberPeople] =  temp.timeWaited - 1;
        }
        numberPeople++; //increments the number of people helped
      }
    }
  }
}

void Simulation::add()
{
   /*
 Add a student to the Queue
  */
  Student p = begin.vFront();
  while(p.arrivalTime == timer)
  {
    end.enqueue(p);
    begin.dequeue();
    p = begin.vFront();
  }
}


void Simulation::move()
{
    /*
 Move a student from the idle to the window 
  */
    while(!begin.isEmpty()|| !end.isEmpty() || !windowsAreEmpty())
    {
      if(!begin.isEmpty())
      {
        add();
      }

      clearWindows();

      while(checkWindows() != -1 && !end.isEmpty())
      {
        Student temp = end.vFront();
        int openWindow = checkWindows();
        windows[openWindow] = true;
        personAtWindow[openWindow] = temp;
        end.dequeue();
      }

      for(int i = 0; i < windowAmount; i++)
      {
        personAtWindow[i].timeSpent++;
      }

      GenQueue<Student> copy;
      while(!end.isEmpty())
      {
        Student temp1 = end.vFront();
        end.dequeue();
        copy.enqueue(temp1);
      }

      while(!copy.isEmpty())
      {
        Student temp = copy.vFront();
        copy.dequeue();
        temp.timeWaited++;
        end.enqueue(temp);
      }

      for(int i = 0; i < windowAmount; i++)
      {
        if(windows[i] == false)
        {
          idleArray[i]++;
        }
      }

      if(timer == 5)
      {
        Student test = end.vFront();
      }
      timer++;
    }

 /*
 Various functions to find summary results 
  */
    longestWait(); 

    overTen();

    longestIdleWait();

    overFive();

    for(int j = 0; j < windowAmount; j++)
    {
      meanIdle = meanIdle + idleArray[j];
    }

    for(int i = 0; i < total; i++)
    {
      meanWait = meanWait + waitArray[i];
    }

    meanWait = meanWait/total;
    medianWait = median();
    meanIdle = meanIdle/windowAmount;
}

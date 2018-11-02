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
  numberPeople = 0;
  timer = 0;

  meanWait = 0;
  medianWait = 0;
  longestWait = 0;
  meanIdle = 0;
  longestIdle = 0;
  overTen = 0;
  overFive = 0;
}

//from the file, takes how many people have arrived
Simulation::Simulation(string file)
{
  arrv = 0;
  counter = 0;
  fileName = file;
  longestWait = 0;
  longestIdle = 0;
  meanWait = 0;
  medianWait = 0;
  meanIdle = 0;
  numberPeople = 0;
  timer = 0;
  totalPeople = 0;
  overTen = 0;
  overFive = 0;
  calculate();
}


int Simulation::windowsOpen()
{
  for(int i = 0; i < windowCount; i++)
  {
    if(windows[i] == false)
    {
      return i;
    }
  }
  return -1;
}

double Simulation::findMedian()
{
  sort(waitTimes, waitTimes + totalPeople-1);
  if((totalPeople % 2) == 1)
  {
    return waitTimes[(totalPeople/2)];
  }
  else
  {
    return ((waitTimes[totalPeople/2]+waitTimes[(totalPeople/2)-1]));
  }
}

bool Simulation::windowsAreEmpty()
{
  for(int i = 0; i < windowCount; i++)
  {
    if(windows[i] == true)
    {
      return false;
    }
  }
  return true;
}

void Simulation::calculate()
{
  people.open(fileName); //opens the file
  people >> currentLine;
  windowCount = stoi(currentLine);
  personAtWindow = new Student[windowCount];
  windows = new bool[windowCount];
  idleTimes = new int[windowCount];
  int peopleArriving;

  while(!people.eof())
  {
    people >> currentLine;
    arrv = stoi(currentLine);
    people >> currentLine;
    int peopleArriving = stoi(currentLine);

    for(int i = 0; i < peopleArriving; i++)
    {
      people >> currentLine;
      Student p(stoi(currentLine), arrv);
      totalPeople++;
      entered.enqueue(p);
    }
  }
  waitTimes = new int[totalPeople];
}

void Simulation::clearWindows()
{
  for(int i = 0; i < windowCount; i++)
  {
    if(windows[i] == true)
    {
      if (personAtWindow[i].timeSpent == personAtWindow[i].timeNeeded)
      {
        windows[i] = false;
        Student temp = personAtWindow[i];
        if(temp.timeWaited == 0)
        {
          waitTimes[numberPeople] = 0;
        }
        else
        {
          waitTimes[numberPeople] =  temp.timeWaited - 1;
        }
        numberPeople++; //increments the number of people helped
      }
    }
  }
}

void Simulation::addToLine()
{
  Student p = entered.vFront();
  while(p.arrivalTime == timer)
  {
    regLine.enqueue(p);
    entered.dequeue();
    p = entered.vFront();
  }
}

void Simulation::moveLine()
{
    while(!entered.isEmpty()|| !regLine.isEmpty() || !windowsAreEmpty())
    {
      if(!entered.isEmpty())
      {
        addToLine();
      }

      clearWindows();

      while(windowsOpen() != -1 && !regLine.isEmpty())
      {
        Student temp = regLine.vFront();
        int openWindow = windowsOpen();
        windows[openWindow] = true;
        personAtWindow[openWindow] = temp;
        regLine.dequeue();
      }

      for(int i = 0; i < windowCount; i++)
      {
        personAtWindow[i].timeSpent++;
      }

      GenQueue<Student> copy;
      while(!regLine.isEmpty())
      {
        Student temp1 = regLine.vFront();
        regLine.dequeue();
        copy.enqueue(temp1);
      }

      while(!copy.isEmpty())
      {
        Student temp = copy.vFront();
        copy.dequeue();
        temp.timeWaited++;
        regLine.enqueue(temp);
      }

      for(int i = 0; i < windowCount; i++)
      {
        if(windows[i] == false)
        {
          idleTimes[i]++;
        }
      }

      if(timer == 5)
      {
        Student test = regLine.vFront();
      }
      timer++;
    }
    for(int i = 0; i < totalPeople; i++)
    {
      meanWait += waitTimes[i];
      if(longestWait < waitTimes[i])
      {
        longestWait = waitTimes[i];
      }
      if(waitTimes[i] > 10)
      {
        overTen++;
      }
    }

    for(int j = 0; j < windowCount; j++)
    {
      meanIdle += idleTimes[j];
      if(longestIdle < idleTimes[j])
      {
        longestIdle = idleTimes[j];
      }
      if(idleTimes[j] > 5)
      {
        overFive++;
      }
    }
    meanWait = meanWait/totalPeople;
    medianWait = findMedian();
    meanIdle = meanIdle/windowCount;
}

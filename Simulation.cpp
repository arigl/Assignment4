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
  peopleHelped = 0;
  ticks = 0;
  meanWait = 0;
  medianWait = 0;
  longestWait = 0;
  averageIdle = 0;
  longestIdle = 0;
  waitedOverTen = 0;
  idleOverFive = 0;
}

//from the file, takes how many people have arrived
Simulation::Simulation(string file)
{
  ticks = 0;
  peopleHelped = 0;
  arrivalTick = 0;
  totalPeople = 0;
  counter = 0;
  meanWait = 0;
  medianWait = 0;
  longestWait = 0;
  averageIdle = 0;
  longestIdle = 0;
  waitedOverTen = 0;
  idleOverFive = 0;
  fileName = file;
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
    arrivalTick = stoi(currentLine);
    people >> currentLine;
    int peopleArriving = stoi(currentLine);

    for(int i = 0; i < peopleArriving; i++)
    {
      people >> currentLine;
      Student p(stoi(currentLine), arrivalTick);
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
          waitTimes[peopleHelped] = 0;
        }
        else
        {
          waitTimes[peopleHelped] =  temp.timeWaited - 1;
        }
        peopleHelped++; //increments the number of people helped
      }
    }
  }
}

void Simulation::addToLine()
{
  Student p = entered.vFront();
  while(p.arrivalTime == ticks)
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

      if(ticks == 5)
      {
        Student test = regLine.vFront();
      }
      ticks++;
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
        waitedOverTen++;
      }
    }

    for(int j = 0; j < windowCount; j++)
    {
      averageIdle += idleTimes[j];
      if(longestIdle < idleTimes[j])
      {
        longestIdle = idleTimes[j];
      }
      if(idleTimes[j] > 5)
      {
        idleOverFive++;
      }
    }
    meanWait = meanWait/totalPeople;
    medianWait = findMedian();
    averageIdle = averageIdle/windowCount;
}

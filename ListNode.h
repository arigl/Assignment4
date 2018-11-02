/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Makes a list that works within a Queue, to order students in a line
 */

#ifndef ListNode_H
#define ListNode_H
#include <iostream>
using namespace std;

template <class T>
class ListNode
{
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();

    T data;
    ListNode<T> *next;
    ListNode<T> *prev;
};


template<class T>
ListNode<T>::ListNode()
{

}

template<class T>
ListNode<T>::ListNode(T d)
{
  next = NULL;
  prev = NULL;
  data = d;
}


template<class T>
ListNode<T>::~ListNode()
{
  next = NULL;
  prev = NULL;
}
#endif

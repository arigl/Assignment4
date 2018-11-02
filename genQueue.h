/*
 Alex Rigl
 Student ID: 2300146
 Email: crigl@chapman.edu
 Class: CPSC 350
 Section: 2
 Assignment 4: Register Office Simulation
 Purpose: Makes a Queue, that works in conjunction with a Double linked list to manage students in a line
 */

#ifndef GenQueue_H
#define GenQueue_H

#include <iostream>
#include "DoublyLinkedList.h"
#include "ListNode.h"
using namespace std;

template <class T>
class GenQueue
{
  public:
    unsigned int numElements;
    ListNode<T> *front;
    ListNode<T> *back;

    GenQueue();
    ~GenQueue();

    void enqueue(T d);
    T dequeue();

    T vFront();
    T vBack();

    void printQ();
    bool isEmpty();
    unsigned int getSize();
};

template <class T>
GenQueue<T>::GenQueue() {
  numElements = 0;
  front = NULL;
  back = NULL;
}

template <class T>
GenQueue<T>::~GenQueue()
{

}

template <class T>
void GenQueue<T>::enqueue(T d) {
  ListNode<T> *node = new ListNode<T>(d);
  if(numElements == 0) {
      front = node;
  }
  else {
      back->next = node;
      node->prev = back;
  }

  back = node;
  ++numElements;
}

template <class T>
T GenQueue<T>::dequeue() {

  if(!isEmpty()) {
    ListNode<T> *node = front;

    T temp = node->data;

    if(front->next == NULL)
    {
      front = NULL;
      back = NULL;
    }
    else
    {
      front->next->prev = NULL;
      front = front->next;
    }

    delete node;
    numElements--;
    return temp;
  }
  else
  {
    return T();
  }
}

template <class T>
T GenQueue<T>::vFront()
{
  if(isEmpty() == false)
  {
    return front->data;
  }
  return T();
}

template <class T>
T GenQueue<T>::vBack()
{
  if(isEmpty() == false)
  {
    return back->data;
  }
  return T();
}

template <class T>
void GenQueue<T>::printQ()
{
  if(isEmpty() == false)
  {
    ListNode<T> *curr = front;
    while(true)
    {
      if(curr != NULL)
      {
        curr->data.printPerson();
        curr = curr->next;
      }
      else
      {
        break;
      }
    }
    }
    else
    {
      cout << "Queue is empty!" << endl;
    }
}

template <class T>
bool GenQueue<T>::isEmpty() {
  return (numElements == 0);
}

template <class T>
unsigned int GenQueue<T>::getSize() {
  return numElements;
}
#endif

/*
 * Name: AJ Garner  
 * Date Submitted: 1/26/23
 * Lab Section:  004
 * Assignment Name: Lab 1: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
  start = nullptr;
  mySize = 0;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
  Node<T> * iterator = start;
  Node<T> * prev = start;
  while(iterator->next != nullptr){
    iterator = iterator->next;
    delete prev;
    prev = iterator;
  }
  delete iterator; //also prev
}

//Return the size of this list
template <class T>
int List<T>::size(){
  return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
  if(mySize == 0)
    return true;
  else
    return false;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
  Node<T> *node = new Node<T>(value);
  node->next = start;
  start = node;
  mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
  Node<T> *node = new Node<T>(value);
  Node<T> * iterator = start;

  if(empty()){
    start = node;
  }
  else {

  while(iterator->next != nullptr){

    iterator = iterator->next;
  }

  iterator->next = node;
  }
  mySize++;
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
  Node<T> *node = new Node<T>(value);

  if(j == 0){
    insertStart(value);
  }
  else {
    Node<T> * iterator = start;

    for(int i = 0; i < j -1; i++){
      iterator = iterator->next;
    }
    node->next = iterator->next;
    iterator->next = node;
  }
  mySize++;
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
  Node<T> *stuff = start;
  start = stuff->next;
  delete stuff;
  mySize--;
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
  Node<T> *lol = start;
  while(lol->next != nullptr){
    lol = lol->next;
  }
  delete lol->next;
  lol->next = nullptr;
  mySize--;
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
  Node<T> * iterator = start;
  Node<T> * garbage;
  for(int i = 0; i < j-1; i++){
    iterator = iterator->next;
  }
  garbage = iterator->next;
  iterator->next = iterator->next->next;
  delete garbage;
  mySize--;
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
  if(!empty()){
   T FirstValue =  start->value ;
   return FirstValue;
  }
  return T ();
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
  if(!empty()){
    Node<T> *lol = start;
    while(lol->next != nullptr){
    lol = lol->next;
    }
    return lol->value;
  }
  return T ();  
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
  if(!empty()){
    Node<T> * iterator = start;
    for(int i = 0; i < j; i++){
      iterator = iterator->next;  
    }
    return iterator->value;
  }
  return T ();  
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){
  Node<T> * iterator = start;
  for(int i = 0; i < mySize; i++){
    if(iterator->value != key)
      iterator = iterator->next;
    else
      return i;
  }
  return -1;
}

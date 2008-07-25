//test01.cpp - a test program to evaluate 
//the class written
//1 - The first test verify that constructors work fine; 

#include <iostream>
using namespace std;

#ifndef ROOTSIM_H
#include "rootsim.h"
#endif

#ifndef SIMCLOCK_H
#include "simclock.h"
#endif

#ifndef  CELLNODE_H
#include "cellnode.h"
#endif

int main(){
  rootSim a;
  simClock* one = new simClock;
/* 1 - Testing declarations */
  cellNode** circleElements; 
  circleElements = new cellNode* [12];
  for(short i = 0; i < 12; i++)
    circleElements[i] = new cellNode;

/* 2 - Connecting the cellnodes */
  for(short i = 0; i < 11; i++)
    circleElements[i]->set_contacts(*circleElements[i+1], 2, 3);
  circleElements[11]->set_contacts(*circleElements[0], 2, 3);

 

  delete one;
  one = NULL;
  for(short i = 0; i < 12; i++)
    delete circleElements[i];
  delete [] circleElements;
  circleElements = NULL;
}
	

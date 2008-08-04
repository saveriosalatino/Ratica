//test01.cpp - a test program to evaluate
//the class written
//1 - The first test verify that constructors work fine;

#include <iostream>
#include <vector>
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

/* 3 - Initialiting the morphogen substances */
  for(short i = 0; i < 11; i++)
    circleElements[i]->set_morfogenSubstance(0.0);
  circleElements[11]->set_morfogenSubstance(100.0);

/* 4 - Testing diffusion */
  //Use for the label of a graph
  cout << "time#\t";
  for(short i = 0; i < 12; i++)
    cout << i << '\t';
  cout << endl;

  while (one->getTime() != 100){
    cout << one->getTime() << '\t';

    for(short i = 0; i < 12; i++)
      cout << circleElements[i]->get_morfogenSubstance() << '\t';
    cout << endl;

      for(short i = 0; i < 11; i++){
       circleElements[i]->morfogen_Diffusion(0.005, *(circleElements[i]->get_contacts(2,0)));
       circleElements[i+1]->morfogen_Diffusion(0.005, *(circleElements[i]->get_contacts(3,0)));
      }

    one->increaseTime();
  }
/* 5 - Testing duplication */

  vector<cellNode> forDupl;

  forDupl.push_back(1);//element that duplicate itself

  //first duplication
  forDupl.push_back(1);
  forDupl[0].cell_Division(1, forDupl[1], one->getTime());
  //second duplication
  forDupl.push_back(1);
  one->increaseTime();
  forDupl[0].cell_Division(2, forDupl[2], one->getTime());
  //second duplication
  forDupl.push_back(1);
  one->increaseTime();
  forDupl[0].cell_Division(3, forDupl[3], one->getTime());


  //Printing the forDupl elements
  cout << "-----------------------------------"<< endl;
  for(short i=0; i < forDupl.size(); i++)
   cout << "i" << '\t' << &forDupl[i] << endl;

  //Printing the connections of forDupl elements
  for (short i=0; i < forDupl.size(); i++){
	  cout << "-----------------------------------"<< endl;
	  for(short j=0; j < 6; j++){
		  cout << j << '\t' << forDupl[i].get_contacts(j).size() << '\t';
		  for(short k=0; k < forDupl[i].get_contacts(j).size(); k++)
			  cout << forDupl[i].get_contacts(j, k) << '\t';
		  cout << endl;
	  }
  }


  //end program
  delete one;
  one = NULL;
  for(short i = 0; i < 12; i++)
    delete circleElements[i];
  delete [] circleElements;
  circleElements = NULL;
}


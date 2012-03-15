/***************************************************************************
 *   Copyright (C) 2008 by Pietro Brunetti   							   *
 *   pietro.brunetti@unical.it   										   *
 *                                                                         *
 *   test02.cpp - test the division                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <fstream>
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

/**
  * This function is for print a configuration of cellNode
  * using dot language.
  * The configuration is @p v, the number of active cellNode is
  * @p it. For the stream we use @p ostr.
  *
  * To print the picture of you can use a command like
  *
  * dot -Tpng -o embryo03.png -v embryo03.dot
  */

void printConfig(const vector<cellNode*>& v, short it, ofstream & ostr);

int main(){
	simClock* two = new simClock;


	/* 5 - Testing duplication */

	vector<cellNode*> forDupl(128);
	short num_init = 0;



	cout << "-----------------------------------"<< endl;
	cout << "First duplication" << endl;
	forDupl[0] = new cellNode;
	num_init++;

	ofstream ostr0000;
	ostr0000.open("./embryo0000.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0000);
	ostr0000.close();


	forDupl[1] = new cellNode;
	num_init++;

	forDupl[0]->cell_Division(1, *forDupl[1], two->getTime());
	ofstream ostr0100;
	ostr0100.open("./embryo0100.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0100);
	ostr0100.close();

	cout << "-----------------------------------"<< endl;
	cout << "Second duplication" << endl;
	forDupl[2] = new cellNode;
	num_init++;
	forDupl[3] = new cellNode;
	num_init++;

	two->increaseTime();

	forDupl[0]->cell_Division(2, *forDupl[2], two->getTime());
	ofstream ostr0150;
	ostr0150.open("./embryo0150.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0150);
	ostr0150.close();

	forDupl[1]->cell_Division(2, *forDupl[3], two->getTime());
	ofstream ostr0200;
	ostr0200.open("./embryo0200.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0200);
	ostr0200.close();

	cout << "-----------------------------------"<< endl;
	cout << "Third duplication" << endl;
	forDupl[4] = new cellNode;
	num_init++;
	forDupl[5] = new cellNode;
	num_init++;
	forDupl[6] = new cellNode;
	num_init++;
	forDupl[7] = new cellNode;
	num_init++;

	two->increaseTime();

	forDupl[0]->cell_Division(3, *forDupl[4], two->getTime());
	ofstream ostr0225;
	ostr0225.open("embryo0225.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0225);
	ostr0225.close();

	forDupl[1]->cell_Division(3, *forDupl[5], two->getTime());
	ofstream ostr0250;
	ostr0250.open("embryo0250.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0250);
	ostr0250.close();

	forDupl[2]->cell_Division(3, *forDupl[6], two->getTime());
	ofstream ostr0275;
	ostr0275.open("embryo0275.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0275);
	ostr0275.close();


	forDupl[3]->cell_Division(3, *forDupl[7], two->getTime());
	ofstream ostr0300;
	ostr0300.open("embryo0300.dot", ios::out|ios::trunc);
	printConfig(forDupl, num_init, ostr0300);
	ostr0300.close();

	for(short i = 0; i < num_init; i++){
		delete forDupl[i];
		forDupl[i]=NULL;
	}
	for(unsigned i = num_init; i < forDupl.size(); i++)
		forDupl[i]=NULL;
	delete two;
	two = NULL;
}

void printConfig(const vector<cellNode*>& v, short it, ofstream & ostr){

	//Printing the forDupl elements using dot language

	//Name of dot graph
        ostr << "digraph cells\n{" <<endl;
    //labeling, used to convert address to number
	    for(short i=0; i < it; i++)
	    		ostr << long(v[i])
	    		     << "[label=\"" << i << "\"]"
	    		     << endl;
    //the connections, to visualize links.
		ostr << endl;
	    for (short i=0; i < it; i++){
			for(short j=0; j < 6; j++){
				if (v[i]->get_contacts(j).size() > 0)
				ostr <<  "edge [label=\"" << j << "\"]" <<endl;
				for(unsigned k=0; k < v[i]->get_contacts(j).size(); k++)
					ostr << dec << long(v[i]) << " -> " << dec << long(v[i]->get_contacts(j, k)) << endl;
			}
			ostr << endl;
		}
//		ostr << '}' << endl;
}

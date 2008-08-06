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
	simClock* two = new simClock;


	/* 5 - Testing duplication */

	vector<cellNode> forDupl;

	cellNode zigote;
	cellNode blastomeres[127];

	cout << "-----------------------------------"<< endl;
	cout << "initial data" << endl;
    cout << 0 << '\t' << &zigote << endl;
    for (short i = 0; i < 7; i++)
    	cout << i+1 << '\t' << &blastomeres[i] << endl;

    cout << "-----------------------------------"<< endl;
    cout << "first tree vector elements" <<  endl;
	forDupl.push_back(zigote);//element that duplicate itself
    //first duplication
	forDupl.push_back(blastomeres[0]);
	cout << "0\t" << &forDupl[0] << endl;
	cout << "1\t" << &forDupl[1] << endl;
	cout << "2\t" << &forDupl[2] << endl;
//	cout << &zigote << endl;

	cout << "-----------------------------------"<< endl;
	cout << "After first duplication" << endl;
	forDupl[0].cell_Division(1, forDupl[1], two->getTime());
	cout << "0\t" << &forDupl[0] << endl;
	cout << "1\t" << &forDupl[1] << endl;
	//second duplication
	forDupl.push_back(blastomeres[1]);
	two->increaseTime();
	forDupl[0].cell_Division(2, forDupl[2], two->getTime());
	cout << "After second duplication" << endl;
	cout << "0\t" << &forDupl[0] << endl;
	cout << "2\t" << &forDupl[2] << endl;
	//second duplication
	forDupl.push_back(blastomeres[2]);
	two->increaseTime();
	forDupl[0].cell_Division(3, forDupl[3], two->getTime());
	cout << "After third duplication" << endl;
	cout << "0\t" << &forDupl[0] << endl;
	cout << "3\t" << &forDupl[3] << endl;

	//Printing the forDupl elements
	cout << "-----------------------------------"<< endl;
	cout << "each elements of the vector" << endl;
    for(unsigned i=0; i < forDupl.size(); i++)
	   cout << i << '\t' << &forDupl[i] << endl;

	//Printing the connections of forDupl elements
    cout << "for each element each link" << endl;
	for (unsigned i=0; i < forDupl.size(); i++){
		cout << "-----------------------------------"<< endl;
		cout << i << '\t' << &forDupl[i] << endl;
		for(short j=0; j < 6; j++){
			cout << j << '\t' << forDupl[i].get_contacts(j).size() << '\t';
			for(unsigned k=0; k < forDupl[i].get_contacts(j).size(); k++)
				cout << forDupl[i].get_contacts(j, k) << '\t';
			cout << endl;
		}
	}

	delete two;
	two = NULL;
}

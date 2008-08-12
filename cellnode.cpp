/***************************************************************************
 *   Copyright (C) 2008 by Pietro Brunetti   *
 *   pietro.brunetti@unical.it   *
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
#include "cellnode.h"

cellNode::cellNode(double morphogen_concentration, int type, int geometry, int time)
 : rootSim(),
   morfogenSubstance(morphogen_concentration),
   type(type),
   geometry(geometry),
   birth_time(time){}


/*cellNode::~cellNode()
{
}*/

void cellNode::set_contacts(cellNode& other, unsigned direct1, unsigned direct2)
{
  if(direct1 < 6 && direct2 < 6){
    contacts[direct1].push_back(&other);
    other.contacts[direct2].push_back(this);
  }
//TODO:else error message
}

void cellNode::set_morfogenSubstance(double const mS)
{
 morfogenSubstance = mS;
}

double cellNode::get_morfogenSubstance() const
{
	return morfogenSubstance;
}

cellNode* cellNode::get_contacts(unsigned dir, unsigned pos)
{
	if (dir < 6 && pos < contacts[dir].size())
		return contacts[dir][pos];
	else
		exit(5);
	//TODO: : Insert an error message
}

vector <cellNode*> cellNode::get_contacts(unsigned dir)
{
	if (dir < 6)
		return contacts[dir];
	else
		exit(5);
	//TODO: : Insert an error message
}

void cellNode::morfogen_Diffusion(double const k, cellNode& toward)
{
 toward.morfogenSubstance += k*morfogenSubstance;
 morfogenSubstance -= k*morfogenSubstance;
}

void cellNode::cell_Differentation(int const nt)
{
 type = nt;
}

void cellNode::cell_Division(int const division_type, cellNode& sister, int const time)
{
 birth_time = time;
 sister.birth_time = time;

 unsigned dir, pos;

 switch(division_type) //For each division plane
 {
  case 1: //division plane 1: orthogonal directions are 0 and 1

	sister.contacts[0].clear();

	moveContacts(*this, sister, 1);

	set_contacts(sister, 1, 0);

    if(contacts[2].size() == 1){
    	getDirection(*contacts[2][0], *this, dir, pos);
    	contacts[2][0]->set_contacts(sister, dir, 2);
    }
    if(contacts[2].size() > 1)
    	moveContacts(*this, sister, 2, contacts[2].size()/2);

    if(contacts[3].size() == 1){
        getDirection(*contacts[3][0], *this, dir, pos);
        contacts[3][0]->set_contacts(sister, dir, 3);
    }
    if(contacts[3].size() > 1)
		moveContacts(*this, sister, 3, contacts[3].size()/2);

    if(contacts[4].size() == 1){
    	getDirection(*contacts[4][0], *this, dir, pos);
        contacts[4][0]->set_contacts(sister, dir, 4);
    }
    if(contacts[4].size() > 1)
    	moveContacts(*this, sister, 4, contacts[4].size()/2);

    if(contacts[5].size() == 1){
    	getDirection(*contacts[5][0], *this, dir, pos);
        contacts[5][0]->set_contacts(sister, dir, 5);
    }
    if(contacts[5].size() > 1)
    	moveContacts(*this, sister, 5, contacts[5].size()/2);
    break;


  case 2:

	sister.contacts[2].clear();

	moveContacts(*this, sister, 3);

    set_contacts(sister, 3, 2);

    if(contacts[0].size() == 1){
    	getDirection(*contacts[0][0], *this, dir, pos);
        contacts[0][0]->set_contacts(sister, dir, 0);
    }
    if(contacts[0].size() > 1)
    	moveContacts(*this, sister, 0, contacts[0].size()/2);

    if(contacts[1].size() == 1){
        getDirection(*contacts[1][0], *this, dir, pos);
        contacts[1][0]->set_contacts(sister, dir, 1);
    }
    if(contacts[1].size() > 1)
    	moveContacts(*this, sister, 1, contacts[1].size()/2);

    if(contacts[4].size() == 1){
        getDirection(*contacts[4][0], *this, dir, pos);
        contacts[4][0]->set_contacts(sister, dir, 4);
    }
    if(contacts[4].size() > 1)
    	moveContacts(*this, sister, 4, contacts[4].size()/2);

    if(contacts[5].size() == 1){
    	getDirection(*contacts[5][0], *this, dir, pos);
        contacts[5][0]->set_contacts(sister, dir, 5);
    }
    if(contacts[5].size() > 1)
    	moveContacts(*this, sister, 5, contacts[5].size()/2);
    break;


  case 3:

	sister.contacts[4].clear();

	moveContacts(*this, sister, 5);

	set_contacts(sister,5, 4);

	if(contacts[0].size() == 1){
		getDirection(*contacts[0][0], *this, dir, pos);
	    contacts[0][0]->set_contacts(sister, dir, 0);
	}
	if(contacts[0].size() > 1)
    	moveContacts(*this, sister, 0, contacts[0].size()/2);

	if(contacts[1].size() == 1){
		getDirection(*contacts[1][0], *this, dir, pos);
	    contacts[1][0]->set_contacts(sister, dir, 1);
	}
	if(contacts[1].size() > 1)
    	moveContacts(*this, sister, 1, contacts[1].size()/2);


	if(contacts[2].size() == 1){
		getDirection(*contacts[2][0], *this, dir, pos);
	    contacts[2][0]->set_contacts(sister, dir, 2);
	}
	if(contacts[2].size() > 1)
    	moveContacts(*this, sister, 2, contacts[2].size()/2);

	if(contacts[3].size() == 1){
		getDirection(*contacts[3][0], *this, dir, pos);
	    contacts[3][0]->set_contacts(sister, dir, 3);
	}
	if(contacts[3].size() > 1)
    	moveContacts(*this, sister, 3, contacts[3].size()/2);

    break;

   default:
    //TODO: Insert an error message
    break;
 }
}
/*
void cellNode::divideContacts(cellNode & ori, cellNode & copy, unsigned index, unsigned limit)
 {
	if(index < 6 &&
	   limit < ori.contacts[index].size() &&
	   ori.contacts[index].size() > 1)
	 {
		 //vector<cellNode*>::iterator start, end;
		 //start = (ori.contacts[index]).begin();
		 //end = (ori.contacts[index]).begin()+limit;

		 //copy.contacts[index].assign(start, end);
		 //ori.contacts[index].erase(start, end);
		 moveContacts(ori, cellNode & to, unsigned dir1, unsigned limit)
	 }
	else exit(5);
    //TODO:else error message
}
*/
bool cellNode::getDirection(const cellNode& whereSearch, const cellNode& whoSearch,
		   unsigned& dir, unsigned& pos){
	for(unsigned i = 0; i < 6; i++){
		for(unsigned j = 0; j < whereSearch.contacts[i].size(); j++){
			if(whereSearch.contacts[i][j] == &whoSearch){
				dir = i;
				pos = j;
				return true;
			}
		}
	}
	return false;
}

void cellNode::moveContacts(cellNode & from, cellNode & to, unsigned dir1)
{
	//dir2 e pos2 are direction and position of each reverse link
	// to from by dir1
	unsigned dir2, pos2;

	if(dir1 < 6){
		for(unsigned i = 0; i < from.contacts[dir1].size(); i++){
			getDirection(*(from.contacts[dir1][i]), from, dir2, pos2);
			to.set_contacts(*(from.contacts[dir1][i]), dir1, dir2);
			vector<cellNode*>::iterator start;
			start = (from.contacts[dir1][i]->contacts[dir2]).begin();
			from.contacts[dir1][i]->contacts[dir2].erase(start+pos2);
		}
		contacts[dir1].clear();
	}
	else exit(5);
	//TODO:else error message
}

void cellNode::moveContacts(cellNode & from, cellNode & to, unsigned dir1, unsigned limit)
{
	//dir2 e pos2 are direction and position of each reverse link
	// to from by dir1
	unsigned dir2, pos2;
	if(dir1 < 6 && limit < from.contacts[dir1].size()){
		for(unsigned i = 0; i < limit; i++){
			getDirection(*(from.contacts[dir1][i]), from, dir2, pos2);
			to.set_contacts(*(from.contacts[dir1][i]), dir1, dir2);
			vector<cellNode*>::iterator start;
			start = (from.contacts[dir1][i]->contacts[dir2]).begin();
			from.contacts[dir1][i]->contacts[dir2].erase(start+pos2);
		}
		vector<cellNode*>::iterator start, end;
		start = (from.contacts[dir1]).begin();
		end = (from.contacts[dir1]).begin()+limit;

		from.contacts[dir1].erase(start, end);

	}
	else exit(5);
	//TODO:else error message
}

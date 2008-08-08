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
  if(direct1 < 6 && direct2 <6){
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

 switch(division_type)
 {
  case 1:
	//clear the contacts of opposite cells
	for(unsigned i = 0; i < contacts[1].size(); i++){
		unsigned dir, pos;
		if (getDirection(*(contacts[1][i]), *this, dir, pos)){
				contacts[1][i]->contacts[dir].erase(pos);
		}
	}

	sister.contacts[0].clear();
    sister.contacts[1] = contacts[1];
    contacts[1].clear();

    set_contacts(sister, 0, 1);

    divideContacts(*this, sister, 2, contacts[2].size()/2);
    divideContacts(*this, sister, 3, contacts[3].size()/2);
    divideContacts(*this, sister, 4, contacts[4].size()/2);
    divideContacts(*this, sister, 5, contacts[5].size()/2);
    break;

  case 2:
    //clear the contacts of opposite cells
	  for(unsigned i = 0; i < contacts[3].size(); i++){
	  		unsigned dir, pos;
	  		if (getDirection(*(contacts[3][i]), *this, dir, pos)){
	  				contacts[3][i]->contacts[dir].erase(pos);
	  		}
	  	}

	sister.contacts[2].clear();
    sister.contacts[3] = contacts[3];
    contacts[3].clear();

    set_contacts(sister, 2, 3);

    divideContacts(*this, sister, 0, contacts[0].size()/2);
    divideContacts(*this, sister, 1, contacts[1].size()/2);
    divideContacts(*this, sister, 4, contacts[4].size()/2);
    divideContacts(*this, sister, 5, contacts[5].size()/2);
    break;

   case 3:
	//clear the contacts of opposite cells
	   for(unsigned i = 0; i < contacts[5].size(); i++){
	   		unsigned dir, pos;
	   		if (getDirection(*(contacts[5][i]), *this, dir, pos)){
	   				contacts[5][i]->contacts[dir].erase(pos);
	   		}
	   	}
	sister.contacts[4].clear();
    sister.contacts[5] = contacts[5];
    contacts[5].clear();

    set_contacts(sister,4, 5);

    divideContacts(*this, sister, 0, contacts[0].size()/2);
    divideContacts(*this, sister, 1, contacts[1].size()/2);
    divideContacts(*this, sister, 2, contacts[2].size()/2);
    divideContacts(*this, sister, 3, contacts[3].size()/2);
    break;

   default:
    //TODO: Insert an error message
    break;
 }
}

void cellNode::divideContacts(cellNode & ori, cellNode & copy, unsigned index, unsigned limit)
 {
	if(index < 6 &&
	   limit < ori.contacts[index].size())
     {
	  if(ori.contacts[index].size() == 1){
		 unsigned dir, pos;
		 if (getDirection(*(ori.contacts[index][0]), ori, dir, pos))
			copy.set_contacts(*ori.contacts[index][0],index, dir);
		 if (!getDirection(*(ori.contacts[index][0]), ori, dir, pos)){
			 exit(5);
			 //TODO: Insert an error message
		 }
	 }
	 if(ori.contacts[index].size() > 1)
	 {
		 vector<cellNode*>::iterator start, end;
		 start = (ori.contacts[index]).begin();
		 end = start + limit;
		 copy.contacts[index].assign(start, end);
		 ori.contacts[index].erase(start, end);
	 }
    }
    //TODO:else error message
}

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

/**
 * @file rootsim.h
 * @brief Base class to derive classes used in simulations.
 * @author Pietro Brunetti
*<!---------------------------------------------------------------------------
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
 *------------------------------------------------------------------------- -->*/
#ifndef ROOTSIM_H
#define ROOTSIM_H

/**
 * @class rootSim
 * @brief base class to derive the other classes.
 * rootSim is a class used to be the base for each other class in the programs.
 * In this manner is simple initialize objects and use polymophism to implement an simple
 * interface for all the objects that simulations need.
 * For the moment rootSim is not full implemented, but it can have some virtual fuction: 
 * void rootSim::cn_init() to initialize simulation object values;
 * void rootSim::cn_loop() to excute  in order the function for each object;
 * void rootSim::cn_chooseNext() to search and use the next automata, 
 * all automaton excecute cn_loop  each time step.
 */
class rootSim{
public:
    //simSpace();

    //~simSpace();
   /**
    * This initializes a base object.
    */   
    void cn_init();
   /**
    * This loops the processes of each object
    */  
    void cn_loop();
   /**
    * For choose an other object of the same type in the simulation.
    */   
    void cn_chooseNext();	
private:
  
};

#endif

/**
 * @file simclock.h
 * @brief A class for the timer in simulations.
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
 
#ifndef SIMCLOCK_H
#define SIMCLOCK_H

#ifndef ROOTSIM_H
#include "rootsim.h"
#endif

/**
 * @class simClock
 * @brief The timer for the simulations
 * This class is used to implement the simulation timer and derived from rootSim. 
 * There is only one member unsigned time, declared as static and two methods. 
 * The first method returns the value of time, void simClock::getTime(). 
 * The second method increases the value of time void simClock::increaseTime().
 */
class simClock:  public rootSim
{
public:
    simClock(unsigned t = 0);

    //~simClock();
   /**
    * It returns the values of time
    */
   unsigned getTime();
   
   /**
    * In the simulations this permits the time to pass.
    */
   void increaseTime();
private:
   unsigned time;
};

#endif

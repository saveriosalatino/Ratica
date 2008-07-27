/** @file cellnode.h
 * @brief Automata that account for a plant cell.
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
 *------------------------------------------------------------------------- -->
*/


#ifndef CELLNODE_H
#define CELLNODE_H

#include <vector>
using namespace std;

#ifndef SIMCLOCK_H
#include "simclock.h"
#endif

#ifndef ROOTSIM_H
#include "simspace.h"
#endif
/**
 * @class cellNode
 * @brief An interconnected automata that account for a Plant Cell.
 * This class is derived from rootSim
 * With cellNode we implements objects that account for plant cell
 * and the date members reflect this:
 * double morfogenSubstance is concentration of a morfogen substance;
 * int type specifies for cellular type;
 * unsigned birth_time, the time of the last division for this  cell.
 *
 * To create networks of interacting cells, we use this data members:
 * int geometry, there are two coordination geometry orthogonal and polar;
 * vector <cellNode*> contacts are the possible contacts;
 *
 * At last:
 * static unsigned motherID and
 * unsigned id.
 * These are used to identify each cell.
 */
class cellNode : public rootSim
{
public:
    /**
     * Create a new cell, optionally with given values
     * @p morphogen_concentration , @p type , and @p geometry .
     *
     * If the attributes are not specified, the @p morphogen_concentration
     * is equal to 0.0, the @p type is stem, and
     * the @p geometry is polar.
     *
     * birthTime is initializes using getTime() and id is imposed
     * as equal to motherID.
     * After, motherID is increases by one.
     * The values of contact_index[] are imposed
     * equal to zero.
     * The cellNode initialized accounts for a cell without
     * other cells in contact.
     *
     * Each cell can contact an other cell to do it we have
     * implemented the  function
     * void contact (cellNode& , unsigned, unsigned),
     * the directions of the contact are specify using
     * the last two unsigned values.
     * This function controls that the directions is a valid value
     * and the number of contacts for the direction are lesser than ten.
     * After this we connect the two using the first
     * free position.
     *
     * @param morphogen_concentration a floating point double precision
     * for the concetration of the morphogen
     *
     * @param type an integer for the cellular type
     *
     * @param geometry an integer for the type of
     * geometrical coodination axes
     *
     * @param time an integer for the birth_time
     * It's simple use simClock::getTime() to obtain
     * the actual time for an object simClock.
     *
     * @see simClock::getTime()
     *
     * @see contact()
     */
   cellNode(double morphogen_concentration = 0.0, int type = 0, int geometry = 0, int time = 0);

   /**
    * This function is for connect to different cellNodes.
    * The cellNode connected by calling cell is @p other .
    * The calling cell use @p direct1 for the new connection.
    * @p other use @p direct2 for the reverse connection.
    *
    * The condition to entabilish this contact is that
    * the @p direction1 and @p direction2 have a valid value
    * ( > 0 and < 6) and that the number of contacts
    * for this directions there is minor than ten.
    */
   void set_contacts(cellNode& other, unsigned direct1, unsigned direct2);

   /**
    * To set morfogenSubstance with @p mS value.
    */
   void set_morfogenSubstance(double const mS);

   /**
    * To get morfogenSubstance.
    */
   double get_morfogenSubstance() const;

   /**
    * It is for a simple passive transport of a substance from the one cell
    * (the cellNode that call the function) to an other cell (called toward).
    * The velocity of diffusion is equal to k*concentration of morphogen_Substace.
    *
    * @param k the diffusion constant.
    *
    * @param toward a cellNode in contact that receive the diffusion.
    */
   void morfogen_Diffusion(double const k, cellNode& toward);

   /**
    * This function is used to change the type
    * tp @p nt .
    *
    * @param nt the new cellular type.
    */
   void cell_Differentation(int const nt);

   /**
    * This function is used to implement the divion of a cellNode
    * to two children cellNodes. One of this is the calling cellNode,
    * the other
    * The birt_time of the calling object and @p sister are initialized
    * using simClock::getTime() .
    * After make a shift in @p division_type to determine the division plane,
    * the function cancels each contact of the calling cellNode
    * for the direction used to contacting @p sister .
    *
    * If @p division_type is equal to 1 @p sister inherits all contacts
    * of the direction 1 of calling cellNode,
    * using cellNode::copyContacts(cellNode const & ori, cellNode & copy, unsigned index).
    * All contacts for direction 0 remain for the calling cellNode.
    * Calling cellNode contact @p sister using
    * direction 0 and this contact calling cellnode using direction 1.
    * Contacts for other dorections are fairly divided between calling cellNode
    * and @p sister using  cellNode::void divideContacts(cellNode const & ori,
    * cellNode & copy, unsigned index, unsigned limit).
    *
    * If @p division_type is equal to 2 @p sister inherits all contacts
    * of the direction 3 of calling cellNode,
    * using cellNode::copyContacts(cellNode const & ori, cellNode & copy, unsigned index).
    * All contacts for direction 2 remain for the calling cellNode.
    * Calling cellNode contact @p sister using
    * direction 2 and this contact calling cellnode using direction 3.
    * Contacts for other dorections are fairly divided between calling cellNode
    * and @p sister using  cellNode::void divideContacts(cellNode const & ori,
    * cellNode & copy, unsigned index, unsigned limit).
    *
    * If @p division_type is equal to 3 @p sister inherits all contacts
    * of the direction 5 of calling cellNode,
    * using cellNode::copyContacts(cellNode const & ori, cellNode & copy, unsigned index).
    * All contacts for direction 4 remain for the calling cellNode.
    * Calling cellNode contact @p sister using
    * direction 5 and this contact calling cellnode using direction 4.
    * Contacts for other dorections are fairly divided between calling cellNode
    * and @p sister using  cellNode::void divideContacts(cellNode const & ori,
    * cellNode & copy, unsigned index, unsigned limit).
    *
    * @param division_type accounts for the division plane.
    * For the moment only three planes are possible.
    *
    * @param sister is one of child duplicated cells.
    *
    * @see contact()
    *
    * @see divideContacts()
    *
    */
   void cell_Division(int const division_type, cellNode& sister, int const time);

private:
   double morfogenSubstance;
   int type;
   int geometry;
   unsigned birth_time;

   vector <cellNode*> contacts [6];
   /**
    * this version of the program use relative
    * direction:
    *  0 - up;
    *  1 - down;
    *  2 - left -clockwise;
    *  3 - right - anticlockwise;
    *  4 - inner - centripetal;
    *  5 - extern - centrifugal.
    *
    *  contact_index contains the index that
    *  limitis each directions in contacts
    * */
   //unsigned contact_index [6];

   //static unsigned motherID = 0;
   //unsigned id;


   /**
    * It's used to move the first @p limit contacts of @p index direction
    * from @p ori to @p copy .
    * The function controlls first that @p index is a valid direction
    * (< 6) and that limits is almost equal to the number of @p ori contacts
    * for the @p limit direction.
    *
    * @param ori cellNode that provides the contacts
    *
    * @param copy cellNode that receive the contacts from @p ori
    *
    * @param index unsigned that accounts for the directions of the copied contacts
    *
    * @param limit is the number of the links moved.
    */
   void divideContacts(cellNode & ori, cellNode & copy, unsigned index, unsigned limit);
};

#endif

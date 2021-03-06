/*
 *  Eindhoven University of Technology
 *  Eindhoven, The Netherlands
 *
 *  Name            :   sadf_transition.h
 *
 *  Author          :   Bart Theelen (B.D.Theelen@tue.nl)
 *
 *  Date            :   10 October 2006
 *
 *  Function        :   SADF Transition
 *
 *  History         :
 *      10-10-06    :   Initial version.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * In other words, you are welcome to use, share and improve this program.
 * You are forbidden to forbid anyone else to use, share and improve
 * what you give them.   Happy coding!
 */

#ifndef SADF_TRANSITION_H_INCLUDED
#define SADF_TRANSITION_H_INCLUDED

// Include type definitions

#include "../sadf/sadf_graph.h"

// Forward declaration

class SADF_Configuration;

// SADF_Transition Definition

class SADF_Transition
{

    public:
        // Constructor

        SADF_Transition(SADF_Configuration *D, const CDouble P, const CDouble T);

        // Destructor

        ~SADF_Transition() { };

        // Access to instance variables

        SADF_Configuration *getDestination() const
        {
            return Destination;
        };
        CDouble getProbability() const
        {
            return Probability;
        };
        CDouble getTimeSample() const
        {
            return TimeSample;
        };

        void setProbability(const CDouble P)
        {
            Probability = P;
        };

    private:
        // Instance Variables

        SADF_Configuration *Destination;
        CDouble Probability;
        CDouble TimeSample;
};

#endif

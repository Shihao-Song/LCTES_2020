/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   reverse_channels.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   March 3, 2008
 *
 *  Function        :   Reverse the channels in an SDF graph.
 *
 *  History         :
 *      08-03-03    :   Initial version.
 *
 * $Id: reverse_channels.cc,v 1.1 2008-03-06 10:52:03 sander Exp $
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

#include "reverse_channels.h"
namespace SDF
{


    /**
     * reverseChannelsInSDFgraph ()
     * The function returns a copy of the SDF graph in which the direction of all
     * channels has been reversed.
     */
    extern
    TimedSDFgraph *reverseChannelsInSDFgraph(TimedSDFgraph *gr)
    {
        TimedSDFgraph *g;

        // Create a copy of the graph gr
        SDFcomponent comp(gr->getParent(), gr->getName(), gr->getId());
        g = gr->clone(comp);

        // Reverse all channels in the graph
        for (SDFchannelsIter iter = g->channelsBegin();
             iter != g->channelsEnd(); iter++)
        {
            SDFchannel *c = *iter;
            SDFport *srcPort = c->getSrcPort();
            SDFport *dstPort = c->getDstPort();

            // Disconnect source and destination ports of channel
            c->connectSrc(NULL);
            c->connectDst(NULL);

            // Reverse direction of ports
            srcPort->setType("in");
            dstPort->setType("out");

            // Reconnect ports to channels
            c->connectSrc(dstPort);
            c->connectDst(srcPort);
        }

        return g;
    }

}//namespace SDF

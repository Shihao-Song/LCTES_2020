/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   message.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   January 6, 2006
 *
 *  Function        :   Message
 *
 *  History         :
 *      06-01-06    :   Initial version.
 *
 * $Id: message.cc,v 1.1 2008-03-20 16:16:20 sander Exp $
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

#include "message.h"
namespace SDF
{
    /**
     * print ()
     * Output a message to the given stream.
     */
    ostream &Message::print(ostream &out) const
    {
        out << "(" << getId() << ", " << getSrcNodeId();
        out << ", " << getDstNodeId() << ", " << getStreamId();
        out << ", " << getSeqNr() << ", " << getStartTime() << ", ";
        out << getDuration() << ", " << getSize() << ")";

        return out;
    }

}//namespace SDF
/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   mcmkarp.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   November 8, 2005
 *
 *  Function        :   Compute the MCM for an HSDF graph using Karp's
 *                      algorithm.
 *
 *  History         :
 *      08-11-05    :   Initial version.
 *
 * $Id: mcmkarp.cc,v 1.1.1.1.2.2 2010-08-18 07:51:48 mgeilen Exp $
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

#include "mcmgraph.h"
#include "../../base/hsdf/check.h"
#include "../../base/algo/components.h"

namespace SDF
{
    /**
     * mcmKarp ()
     * The function computes the maximum cycle mean of an MCMgGraph using Karp's
     * algorithm.
     */
    CDouble maximumCycleMeanKarp(MCMgraph *mcmGraph)
    {
        int k, n;
        int **d;
        double l, ld;
        MCMnode *u;

        // Allocate memory
        n = mcmGraph->nrVisibleNodes();
        d = new int* [n + 1];
        for (int i = 0; i < n + 1; i++)
            d[i] = new int [n];

        // Initialize
        for (k = 1; k < n + 1; k++)
            for (int u = 0; u < n; u++)
                d[k][u] = -INT_MAX;
        for (int u = 0; u < n; u++)
            d[0][u] = 0;

        // Compute the distances
        for (k = 1; k < n + 1; k++)
        {
            for (MCMnodesCIter iter = mcmGraph->getNodes().begin();
                 iter != mcmGraph->getNodes().end(); iter++)
            {
                MCMnode *v = *iter;

                for (MCMedgesIter e = v->in.begin();
                     e != v->in.end(); e++)
                {
                    MCMnode *u = (*e)->src;

                    d[k][v->id] = MAX(d[k][v->id], d[k - 1][u->id] + ((int)(*e)->w));
                }
            }
        }

        // Compute lamda using Karp's theorem
        l = -INT_MAX;
        for (MCMnodesCIter iter = mcmGraph->getNodes().begin();
             iter != mcmGraph->getNodes().end(); iter++)
        {
            u = *iter;
            ld = INT_MAX;
            for (k = 0; k < n; k++)
            {
                ld = MIN(ld, (double)(d[n][u->id] - d[k][u->id]) / (double)(n - k));
            }
            l = MAX(l, ld);
        }

        // Cleanup
        for (int i = 0; i < n + 1; i++)
            delete [] d[i];
        delete [] d;

        return l;
    }

    /**
     * mcmKarp ()
     * The function computes the maximum cycle mean of a HSDF graph using Karp's
     * algorithm.
     */
    static
    CDouble mcmKarp(TimedSDFgraph *g)
    {
        MCMgraphs components;
        MCMgraph *mcmGraph;
        CDouble mcm;

        // Transform the HSDF to a weighted directed graph
        mcmGraph = transformHSDFtoMCMgraph(g);

        // Extract the strongly connected component from the graph
        // According to the Max-Plus book there is exactly one strongly
        // connected component in the graph when starting from a strongly
        // connected (H)SDF graph.
        stronglyConnectedMCMgraph(mcmGraph, components);

        // Remove all hidden edges and nodes from the graph and assign new id's
        relabelMCMgraph(mcmGraph);

        mcm = maximumCycleMeanKarp(mcmGraph);

        // Cleanup
        delete mcmGraph;

        // return the result
        return mcm;
    }


    /**
     * maximumCycleMeanKarp ()
     * The function computes the maximum cycle mean of a HSDF graph using Karp's
     * algorithm.
     */
    CDouble maximumCycleMeanKarp(TimedSDFgraph *g)
    {
        CDouble mcmGraph;

        // Check that graph g is an HSDF graph
        if (!isHSDFgraph(g))
            throw CException("Graph is not an HSDF graph.");

        // Check that the graph g is a strongly connected graph
        if (!isStronglyConnectedGraph(g))
            throw CException("Graph is not strongly connected.");

        mcmGraph = mcmKarp(g);

        return mcmGraph;
    }
}//namespace SDF
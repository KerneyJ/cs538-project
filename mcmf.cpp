#include <iostream>
#include "mcmf.hpp"

MinCostMaxFlow::MinCostMaxFlow(
    vector<vector<int>> cap, 
    vector<vector<int>> sat
) {
    this->capacity = cap;
    this->satisfaction = sat;
    this->num_students = cap.size();
    this->num_classes = cap.at(0).size();

    this->flow.assign(num_students, vector<int>(num_classes));

    this->dad.assign(num_students, 0);
    this->pi.assign(num_students, 0);
}

bool MinCostMaxFlow::pathExists(int src, int sink) {

    // Initialise found[] to false
    this->marked.assign(num_students, false);

    // Initialise the dist[] to INF
    this->dist.assign(num_students + 1, __INT_MAX__/2);

    // Distance from the source node
    dist[src] = 0;
    int N = max(num_classes, num_students);

    // Iterate until src reaches N
    while (src != N) {

        int best = N;
        marked[src] = true;

        for (int k = 0; k < N; k++) {

            // If already found
            if (marked[k])
                continue;

            // Evaluate while flow
            // is still in supply
            if (flow[k][src] != 0) {

                // Obtain the total value
                int val = dist[src] + pi[src] - pi[k] + satisfaction[k][src];

                // If dist[k] is > minimum value
                if (dist[k] > val) {

                    // Update
                    dist[k] = val;
                    dad[k] = src;
                }
            }

            if (flow[src][k] < capacity[src][k]) {

                int val = dist[src] + pi[src] - pi[k] - satisfaction[src][k];

                // If dist[k] is > minimum value
                if (dist[k] > val) {

                    // Update
                    dist[k] = val;
                    dad[k] = src;
                }
            }

            if (dist[k] < dist[best])
                best = k;
        }

        // Update src to best for
        // next iteration
        src = best;
    }

    for (int k = 0; k < N; k++)
        pi[k] = min(pi[k] + dist[k], __INT_MAX__);

    // Return the value obtained at sink
    return marked[sink];
}

vector<int> MinCostMaxFlow::findMaxFlow(int s, int t) {

    int total_flow = 0; 
    int total_cost = 0;

    // If a path exist from src to sink
    while (pathExists(s, t)) {

        // Set the default amount
        int amt = __INT_MAX__;

        for (int x = t; x != s; x = dad[x]) {
            if(flow[x][dad[x]] != 0) {
                amt = min(amt, flow[x][dad[x]]);
            } else {
                amt = min(amt, capacity[dad[x]][x] - flow[dad[x]][x]);
            }
        }

        for (int x = t; x != s; x = dad[x]) {

            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                total_cost += amt * satisfaction[x][dad[x]];
            } else {
                flow[dad[x]][x] += amt;
                total_cost -= amt * satisfaction[dad[x]][x];
            }
        }
        total_flow += amt;
    }

    // Return pair total cost and sink
    return vector<int>({total_flow, total_cost});
}
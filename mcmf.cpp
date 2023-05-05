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

    this->marked.assign(num_students, false);
    this->dist.assign(num_students + 1, INT32_MIN/2);

    dist[src] = 0;
    int N = max(num_classes, num_students);

    // Iterate until src reaches N
    while (src != N) {

        int best = N;
        marked[src] = true;

        for (int k = 0; k < N; k++) {

            if (marked[k])
                continue;

            if (flow[k][src] != 0) {
                int val = dist[src] + pi[src] - pi[k] - satisfaction[k][src];

                if (val > dist[k]) {
                    dist[k] = val;
                    dad[k] = src;
                }
            }

            if (flow[src][k] < capacity[src][k]) {
                int val = dist[src] + pi[src] - pi[k] + satisfaction[src][k];

                if (val > dist[k]) {
                    dist[k] = val;
                    dad[k] = src;
                }
            }

            if (dist[k] > dist[best])
                best = k;
        }

        src = best;
    }

    for (int k = 0; k < N; k++)
        pi[k] = max(pi[k] + dist[k], INT32_MIN);

    return marked[sink]; // if we found a path to the sink
}

vector<int> MinCostMaxFlow::findMaxFlow(int s, int t) {

    int total_flow = 0; 
    int total_cost = 0;

    while (pathExists(s, t)) {
        int amt = INT32_MIN;

        for (int x = t; x != s; x = dad[x]) {
            if(flow[x][dad[x]] != 0) {
                amt = max(amt, flow[x][dad[x]]);
            } else {
                amt = max(amt, capacity[dad[x]][x] - flow[dad[x]][x]);
            }
        }

        for (int x = t; x != s; x = dad[x]) {

            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                total_cost -= amt * satisfaction[x][dad[x]];
            } else {
                flow[dad[x]][x] += amt;
                total_cost += amt * satisfaction[dad[x]][x];
            }
        }
        total_flow += amt;
    }

    return vector<int>({total_flow, total_cost});
}
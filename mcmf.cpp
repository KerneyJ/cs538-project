#include "mcmf.hpp"; 

//     // Driver Code
//     public static void main(String args[])
//     {
 
//         // Creating an object flow
//         MinCostMaxFlow flow = new MinCostMaxFlow();
 
//         int s = 0, t = 4;
 
//         int cap[][] = { { 0, 3, 1, 0, 3 },
//                         { 0, 0, 2, 0, 0 },
//                         { 0, 0, 0, 1, 6 },
//                         { 0, 0, 0, 0, 2 },
//                         { 0, 0, 0, 0, 0 } };
 
//         int cost[][] = { { 0, 1, 0, 0, 2 },
//                          { 0, 0, 0, 3, 0 },
//                          { 0, 0, 0, 0, 0 },
//                          { 0, 0, 0, 0, 1 },
//                          { 0, 0, 0, 0, 0 } };
 
//         int ret[] = flow.getMaxFlow(cap, cost, s, t);
 
//         System.out.println(ret[0] + " " + ret[1]);
//     }
// }

bool MinCostMaxFlow::pathExists(int src, int sink) {

    // Initialise found[] to false
    fill(solution.begin(), solution.end(), false);

    // Initialise the dist[] to INF
    fill(dist.begin(), dist.end(), __INT_MAX__);

    // Distance from the source node
    dist[src] = 0;
    int N = max(num_classes, num_students);

    // Iterate until src reaches N
    while (src != N) {

        int best = N;
        solution[src] = true;

        for (int k = 0; k < N; k++) {

            // If already found
            if (solution[k])
                continue;

            // Evaluate while flow
            // is still in supply
            if (flow[k][src] != 0) {

                // Obtain the total value
                int val
                    = dist[src] + pi[src]
                        - pi[k] - cost[k][src];

                // If dist[k] is > minimum value
                if (dist[k] > val) {

                    // Update
                    dist[k] = val;
                    dad[k] = src;
                }
            }

            if (flow[src][k] < capacity[src][k]) {

                int val = dist[src] + pi[src]
                            - pi[k] + cost[src][k];

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
    return solution[sink];
}
 


vector<int>  MinCostMaxFlow::findMaxFlow(
    vector<vector<int>> cap, 
    vector<vector<int>> cost, 
    int s, int t
) {
    this->capacity = cap;
    this->cost = cost;
    this->num_students = cap.size();
    this->num_classes = cap.at(0).size();

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
                amt = min(amt, cap[dad[x]][x] - flow[dad[x]][x]);
            }
        }

        for (int x = t; x != s; x = dad[x]) {

            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                total_cost -= amt * cost[x][dad[x]];
            }
            else {
                flow[dad[x]][x] += amt;
                total_cost += amt * cost[dad[x]][x];
            }
        }
        total_flow += amt;
    }

    // Return pair total cost and sink
    return { total_flow, total_cost };
}
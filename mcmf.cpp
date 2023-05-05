#include <iostream>
#include "mcmf.hpp"

MinCostMaxFlow::MinCostMaxFlow(
    vector<vector<int>> cap, 
    vector<vector<int>> sat
) {
    this->capacity = cap;
    this->satisfaction = sat;
    this->N = cap.size();

    this->flow.assign(N, vector<int>(N));

    this->dad.assign(N, 0);
    this->pi.assign(N, 0);

    this->num_students = 0;
    for(int i = 1; i < N; i++){
        if(cap[0][i] == 0)
            break;
        this->num_students++;
    }
    this->num_classes = N - num_students - 2;

	printf("\nSize of matrix:     %dx%d\n", N, N);	
	printf("Number of students: %d\n", this->num_students);	
	printf("Number of classes:  %d\n", this->num_classes);	
}

void MinCostMaxFlow::printResults() {
    printf("\n--------RESULTS--------\n");	

    if(N < 10) {
        printf("\nFlow:\n");	
        for(int i = 0; i < flow.size(); i++){
            for(int j = 0; j < flow[i].size(); j++){
                printf("%i,", flow[i][j]);
            }
            printf("\n");
        }
    }
    
    printf("\nMatchings: \n");	
    for(int i = 1; i <= num_students; i++) {
        for(int j = 1; j <= num_classes; j++) {
            if(flow[i][j + num_students]) {
            	printf("student %d -> class %d, satisfaction: %d.\n", i, j, satisfaction[i][j + num_students]);	
            }
        }
    }

	printf("\nTotal matchings:    %d\n", total_flow);
	printf("Total satisfaction: %d\n", total_sat);
}

bool MinCostMaxFlow::pathExists(int src, int sink) {

    this->marked.assign(N, false);
    this->dist.assign(N + 1, INT32_MIN/2);

    dist[src] = 0;

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
        pi[k] = max(pi[k] + dist[k], INT32_MIN/2);

    return marked[sink]; // if we found a path to the sink
}

void MinCostMaxFlow::computeMaxFlow(int s, int t) {

    total_flow = 0; 
    total_sat = 0;

    while (pathExists(s, t)) {
        int amt = INT32_MAX;

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
                total_sat -= amt * satisfaction[x][dad[x]];
            } else {
                flow[dad[x]][x] += amt;
                total_sat += amt * satisfaction[dad[x]][x];
            }
        }
        total_flow += amt;
    }
}
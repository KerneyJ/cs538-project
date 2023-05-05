#include "vector"
using namespace std;

class MinCostMaxFlow {
    public:
        MinCostMaxFlow(vector<vector<int>> cap, vector<vector<int>> cost);
        vector<int> findMaxFlow(int s, int t);

    private:
        bool pathExists(int src, int sink);
        int num_students, num_classes;  // size of problem
        vector<vector<int>> cost;       // edge costs
        vector<vector<int>> capacity;   // edge capacities

        vector<vector<int>> flow;       // edge flows
        vector<bool> marked;            // marked edges in search

        vector<int> dad;
        vector<int> dist;
        vector<int> pi;
};
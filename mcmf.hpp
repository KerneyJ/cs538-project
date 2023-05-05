#include "vector"
using namespace std;

class MinCostMaxFlow {
    public:
        vector<int> findMaxFlow(vector<vector<int>>, vector<vector<int>>, int s, int t);

    private:
        bool pathExists(int src, int sink);
        int num_students, num_classes;  // size of problem
        vector<vector<int>> cost;       // edge costs
        vector<vector<int>> capacity;   // edge capacities

        vector<vector<int>> flow;       // edge flows
        vector<bool> solution;  // found edges

        vector<int> dad;
        vector<int> dist;
        vector<int> pi;
};
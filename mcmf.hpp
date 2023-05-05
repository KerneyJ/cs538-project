

class MinCostMaxFlow {
    private:
        int N;              // size of problem
        bool solution[];    // found edges
        int capacity[][];   // edge capacities
        int flow[][];       // edge flows
        int cost[][];       // cost

        // Stores the distance from each node
        // and picked edges for each node
        int dad[], dist[], pi[];
};
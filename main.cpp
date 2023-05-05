#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mcmf.hpp"

int main(int argc, char** argv){
	if(argc < 2){
		std::cout << "No datafile argument provided" << std::endl;
		return 0;
	}
	std::ifstream datafile;
	std::string line, temp;
	datafile.open(argv[1]);
	/*
	while(std::getline(ss,temp,',')){
		std::cout << temp << std::endl;
	}*/
	std::vector<std::vector<int>> cost;
	std::vector<std::vector<int>> cap;

	// parse cost
	while(std::getline(datafile, line)){
		std::vector<int> temp_cost;
		if(line == "-")
			break;
		std::stringstream ss(line);
		while(std::getline(ss, temp, ','))
			temp_cost.push_back(std::stoi(temp));
		cost.push_back(temp_cost);
	}

	// parse cap
	while(std::getline(datafile, line)){
		std::vector<int> temp_cap;
		if(line == "-")
			break;
		std::stringstream ss(line);
		while(std::getline(ss, temp, ','))
			temp_cap.push_back(std::stoi(temp));
		cap.push_back(temp_cap);
	}

    printf("\n--------INPUTS--------\n");	
	MinCostMaxFlow mcmf = MinCostMaxFlow(cap, cost);

    if(cap.size() < 10) {
        printf("\nCapacity Matrix:\n");	
        for(int i = 0; i < cap.size(); i++){
            for(int j = 0; j < cap[i].size(); j++){
                printf("%i ", cap[i][j]);
            }
            printf("\n");
        }

        printf("\nSatisfaction Matrix:\n");	
        for(int i = 0; i < cost.size(); i++){
            for(int j = 0; j < cost[i].size(); j++){
                printf("%i ", cost[i][j]);
            }
            printf("\n");
        }
    }

	printf("\nCalculating flow...\n");	
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	int t1 = time(0);

	mcmf.computeMaxFlow(0, cap.size()-1);

	gettimeofday(&stop, NULL);

	mcmf.printResults();
	printf("Execution time:     %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000);
	return 0;
}

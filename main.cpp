#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	;
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

	for(int i = 0; i < cap.size(); i++){
		for(int j = 0; j < cap[i].size(); j++){
			printf("%i,", cap[i][j]);
		}
		printf("\n");
	}
	return 0;
}

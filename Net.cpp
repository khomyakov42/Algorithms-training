#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;
int size;
signed long net[20][20];
bool solution[20];
signed long maxTraffic = 0;

void Compute(){
	signed long traffic = 0;
	for(int i = 0; i < size; i++){
		if(solution[i])
			for(int j = 0; j < size; j++)
				if(!solution[j])
					traffic += net[i][j];
	}
	
	if(maxTraffic < traffic)
		maxTraffic = traffic;
}

void FindSolution(int index){
	if(index > size - 2)
		return;
	
	if(solution[index]){
		solution[index] = false;
		FindSolution(index + 1);
		return;
	}
	else
		solution[index] = true;
	
	Compute();
	
	FindSolution(0);
}

int main(){
	ifstream In("input.txt");
	ofstream Out("output.txt");
	
	In >> size;
	
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			In >> net[i][j];

	In.close();
	
	FindSolution(0);
	
	Out << maxTraffic;
	Out.close();
}
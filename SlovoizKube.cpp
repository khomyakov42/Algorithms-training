#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
string word = "";
string cubes[12];
int countCubes;
vector<int> partialSolution[12];
int itr[12];
int len = 0;

void BuildPartialSolution(int number){
	for(int i = 0; i < len; i++)
		for(int j = 0; j < 6; j++)
			if(word[i] == cubes[number][j]){
				partialSolution[i].push_back(number);
				break;
			}
}

int GetNumberNextElement(int letter){
	int count = partialSolution[letter].size();
	bool noExist;
	if(letter < 0)
		return -1;

	for(int i = itr[letter] + 1; i < count; i++){
		noExist = true;
		for(int j = 0; j < letter; j++)
			if(partialSolution[letter][i] == partialSolution[j][itr[j]]){
				noExist = false;
				break;
			}
		if(noExist)
			return i;
	}
	return -1;
}

bool Compute(int index){
	if(index >= len)
		return true;
	if(index < 0)
		return false;

	itr[index] = GetNumberNextElement(index);
	if(itr[index] == -1)
		return Compute(index - 1); 

	return Compute(index + 1);
}


int main(){
	ofstream Out("output.txt");
	ifstream In("input.txt");
	
	In >> countCubes;
	In >> word;
	len = word.length();

	for(int i = 0; i < countCubes; i++){
		In >> cubes[i];
		BuildPartialSolution(i);
		itr[i] = -1;
	}
	In.close();

/*	for(int i = 0; i < len; i++){
		for(int j = 0; j < partialSolution[i].size(); j++){
			cout << partialSolution[i][j];
			cout << ' ';
		}
		cout << "\n";
	}*/

	for(int i = 0; i < len; i++)
		if(partialSolution[i].size() == 0){
			Out << '0';
			Out.close();
			return 0;
		}
	
	if(Compute(0))
		for(int i = 0; i < len; i++){
			Out << partialSolution[i][itr[i]] + 1;
			Out << ' ';
		}
	else
		Out << '0';
	Out.close();
		
}
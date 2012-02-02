#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;
typedef struct{
	char answer[15];
	int countCorrectAnswer;
}TResults;

int countH;
int countQ;
TResults result[1000];
char solution[15];

bool TestAnswer(){
	int countCorrectAnswer;
	for(int i = 0; i < countH; i++){
		countCorrectAnswer = 0;
		for(int j = 0; j < countQ; j++)
			if(solution[j] == result[i].answer[j])
				countCorrectAnswer++;
		if(countCorrectAnswer != result[i].countCorrectAnswer)
			return false;		
	}
	return true;
}

void Compute(int index){
	if(index > countQ)
		return;
	
	if(solution[index] == '-')
		solution[index] = '+';
	else{
		solution[index] = '-';
		Compute(index + 1);
		return;
	}

	if(TestAnswer())
		return;

	Compute(0);
}

int main(){
	ifstream In("input.txt");
	ofstream Out("output.txt");
	In >> countH;
	In >> countQ;

	for(int i = 0; i < countH; i++){
		In >> result[i].answer;
		In >> result[i].countCorrectAnswer;
	}
	In.close();
	
	for(int i = 0; i < countQ; i++)
		solution[i] = '-';
	
	if(!TestAnswer())
		Compute(0);

	Out << solution;
	Out.close();
}
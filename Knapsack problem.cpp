#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
unsigned long int n, w;
vector<unsigned long int> numbers;
bool sol[40];
bool solution_found = false;

int sum(int index){
	int res = 0;
	for(int i = index; i < n; i++)
		res += numbers[i];
	return res;
}

bool Compute(int index, int s){
	if(s == w)
		return true;

	if(index != n)
		for(int i = 1; i >= 0; i--){
			sol[index] = i;
			int k = s + (sol[index]? numbers[index]: 0);

			if(k <= w && sum(index) + s >= w)
				if(Compute(index + 1, k))
					return true;
		}

	return false;
}

int main(){
	FILE *In = fopen("input.txt", "r");
	FILE *Out = fopen("output.txt", "w");
	
	fscanf(In,"%d %d", &n, &w);
	for(int i = 0; i < n; i++){
		int x;
		fscanf(In, "%d", &x);
		numbers.push_back(x);
	}
	fclose(In);
	
	if(Compute(0, 0))
		for(int i = 0; i < n; i++)
			fprintf(Out, "%d ", sol[i]? 1: 0);
	else
		fprintf(Out, "%d", -1);


	fclose(Out);
}
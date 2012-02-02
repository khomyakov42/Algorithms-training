#include<vector>
#include<stdio.h>
#define middle 2001

using namespace std;
vector<int> number;
int result, n;
int sol[1000];
bool partialsol[middle * 2][1000];

int comp(int a, int b, int code){
	switch (code){
		case 0: 
			return a + b;
		case 1: 
			return a * b;
		case 2: 
			return a - b;
		case 3:
			return b == 0? 1001: a / b;
	}
}

bool Find(int index, int sum){
	if(index == n - 1){
		if(sum == result)
			return true;
	}
	else
		for(int i = 0; i < 4; i++){
			sol[index] = i;

			int s = comp(sum, number[index + 1], i);
			
			if(abs(s) > 1000)
				continue;

			if(!partialsol[middle + s][index])
				if(Find(index + 1, s))
					return true;
				else
					partialsol[middle + s][index] = true;				
		}

	return false;
}

int main(){
	FILE *In = fopen("input.txt", "r");
	FILE *Out = fopen("output.txt", "w");

	while(!feof(In)){
		int x;
		fscanf(In, "%d\n", &x);
		number.push_back(x);			
	}
	result = number[number.size() - 1];
	number.pop_back();
	n = number.size();

	if(Find(0, number[0]))
		for(int i = 0; i < n - 1; i++)
			switch (sol[i]){
				case 0: 
					fprintf(Out,"%s", "+");
					break;
				case 1: 
					fprintf(Out,"%s", "*");
					break;
				case 2: 
					fprintf(Out,"%s", "-");
					break;
				case 3:
					fprintf(Out,"%s", "/");
					break;
			}
	else
		fprintf(Out, "%s", "IMPOSSIBLE");
	fclose(Out);
}
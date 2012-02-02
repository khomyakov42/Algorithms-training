#include<iostream>
#include<vector>

#define inf 1000 * 100 + 1
using namespace std;
int main(){
	int n, m;
	int W[101][101];

	FILE *In = fopen("input.txt", "r");
	FILE *Out = fopen("output.txt", "w");
	
	fscanf(In,"%d %d", &n, &m);

	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++)
			W[i][j] = inf;
		int v1, v2, w;
		fscanf(In, "%d %d %d", &v1, &v2, &w);
		W[v1][v2] = w;
	}

	for(int k = 1; k < n; k++)
		for(int i = 1; i < n; i++)
			for(int j = 1; j < n; j++)
				W[i][j] = min(W[i][k] + W[k][j], W[i][j]);
	

	fclose(In);
	fclose(Out);
}
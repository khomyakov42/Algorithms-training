#include<cstdlib>
#include<fstream>

using namespace std;

int main(){
	const int inf = 100001;
	int n, m;
	int W[101][101];
	FILE *In = fopen("input.txt", "r");
	FILE *Out = fopen("output.txt", "w");

	fscanf(In, "%d %d", &n, &m);

	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			W[i][j] = i == j? 0: inf;

	for(int i = 0; i < m; i++){
		int v1, v2, w;
		fscanf(In, "%d %d %d", &v1, &v2, &w);
		W[v1][v2] = w;
	}

	fclose(In);

	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(W[i][k] < inf && W[k][j] < inf)
					W[i][j] = min(W[i][j], W[i][k] + W[k][j]);

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			if(W[i][j] >= inf)
				fprintf(Out, "  ");
			else
				fprintf(Out, "%d ", W[i][j]);
				
		fprintf(Out, "\n");
	}
	
	fclose(Out);
}
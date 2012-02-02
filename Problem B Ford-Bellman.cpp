#include<fstream>
#include<cstdlib>

using namespace std;

typedef struct{
	int v1, v2, w;
} TypeEdge;

int main(){
	const unsigned long int inf = 100000001;
	int n, m, s;
	TypeEdge A[100001];
	int d[100001];
	FILE *In = fopen("input.txt", "r");
	FILE *Out = fopen("output.txt", "w");

	fscanf(In, "%d %d %d", &n, &m, &s);

	for(int i = 0; i < n + 1; i++)
		d[i] = inf;

	for(int i = 0; i < m; i++)
		fscanf(In, "%d %d %d", &A[i].v1, &A[i].v2, &A[i].w);

	d[s] = 0;
	for(int i = 0; i < n - 1; i++)
		for(int j = 0; j < m; j++)
			if(d[A[j].v1] < inf)
				d[A[j].v2] = min(d[A[j].v2], d[A[j].v1] + A[j].w);
	
	for(int i = 1; i < n + 1; i++)
		if(d[i] < inf)
			fprintf(Out, "%d ", d[i]);
		else
			fprintf(Out, "-1 ");

	fclose(Out);
	fclose(In);
}
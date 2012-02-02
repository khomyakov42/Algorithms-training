#include<vector>

using namespace std;
typedef struct{
	int value, wieght;
} MyT;

MyT coin[10001];
int result = 10000001;
int weight[10001];
int W, n;

void Compute(int index, int v, int w){
	if(w == W){
		result = v;
		return;
	}
	if(index <= n)
		while(w <= W && v < result && v < weight[w]){
			Compute(index + 1, v , w);
			weight[w] = v;
			w += coin[index].wieght;
			v += coin[index].value;
		}
}

int main(){
	FILE *In = fopen("input.txt", "r");
	FILE *Out = fopen("output.txt", "w");
	int e, f;

	fscanf(In, "%d %d %d", &e, &f, &n);
	W = f - e;

	for(int i = 0; i < 10001; i++)
		weight[i] = 10000001;

	for(int i = 1; i <= n; i++)
		fscanf(In,"%d %d", &coin[i], &coin[i].wieght);
	fclose(In);

	Compute(1, 0, 0);

	fprintf(Out, "%d", result == 10000001? -1: result);
	fclose(Out);
}
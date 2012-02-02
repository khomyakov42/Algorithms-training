#include<cstdio>
#include<vector>
using namespace std;
#define inf 1000000000

int main(){
   FILE *in = fopen("input.txt", "r");
   FILE *out = fopen("output.txt", "w");
   int n;
   int p[100];
   int res[100][100];

   fscanf(in, "%d", &n);

   for(int i = 0; i < n; i++)
      fscanf(in, "%d", &p[i]);

   for(int i = 0; i < 100; i++)
      for(int j = 0; j < 100; j++)
         res[i][j] = inf;

   for(int i = 0; i < n - 1; i++)
      res[i][i + 1] = 0;

   for(int i = 2; i < n; i++)
      for(int j = 0; j < n - i; j++)
         for(int k = j + 1; k < j + i; k++)
            res[j][j + i] = min(res[j][j + i], res[j][k] + p[j] * p[k] * p[j + i] + res[k][j + i]);

            
   fprintf(out, "%d", res[0][n - 1]);      
   fclose(out);
   fclose(in);
}

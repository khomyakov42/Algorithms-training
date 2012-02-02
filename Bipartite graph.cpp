#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#define SIZE 100001

using namespace std;
signed n, m;
vector<signed> vertex[SIZE];
bool part[SIZE];
bool visited[SIZE];
queue<signed> q;

int main(){

	FILE *In = fopen("input.txt", "r");
	ofstream Out("output.txt");

	fscanf(In,"%d %d", &n, &m);
	for(signed i = 0; i < m; i++){
		signed v1, v2;
		fscanf(In, "%d %d", &v1, &v2);
		vertex[v1].push_back(v2);
		vertex[v2].push_back(v1);
	}
	fclose(In);
	
	if(n == 1){
		Out << "NO";
		Out.close();
		return 0;
	}

	for(signed i =	1; i <= n; i++)
		if(!visited[i]){
			q.push(i);
			visited[i] = true;
			part[i] = false;
			while(!q.empty()){
				signed v = q.front();
				q.pop();

				signed size = vertex[v].size();
				for(signed j = 0; j < size; j++)
					if(!visited[vertex[v][j]]){
						q.push(vertex[v][j]);
						visited[vertex[v][j]] = true;
						part[vertex[v][j]] = !part[v];
					}
					else
						if(part[v] == part[vertex[v][j]]){
							Out << "NO";
							Out.close();
							return 0;
						} 
			}
		}

	Out << "BIPARTITE";  
	Out.close();
}
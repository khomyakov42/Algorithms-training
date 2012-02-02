#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#define SIZE 100001

using namespace std;
signed n, m;
vector<signed> vertex[SIZE];
vector<signed> vertex2[SIZE];
bool visited[SIZE];
bool vertexDepend[SIZE];
vector<signed> result;

void DFS(signed v){
	visited[v] = true;

	result.push_back(v);

	signed size1 = vertex[v].size();
	for(signed i = 0; i < size1; i++)
		if(!visited[vertex[v][i]]){
			bool next = true;
			signed size2 = vertex2[vertex[v][i]].size();
			for(signed j = 0; j < size2; j++)
				if(!visited[vertex2[vertex[v][i]][j]]){
					next = false;
					break;
				}
			if(next)
				DFS(vertex[v][i]);
		}
}

int main(){
	ifstream In("input.txt");
	ofstream Out("output.txt");

	In >> n; 
	In >> m;
	for(signed i = 0; i < m; i++){
		signed v1, v2;
		In >> v1;
		In >> v2;
		vertex[v1].push_back(v2);
		vertex2[v2].push_back(v1);
		vertexDepend[v2] = true;
	}
	In.close();

	for(signed i = 1; i <= n; i++)
		if(!vertexDepend[i]){
			DFS(i);
		}
	
	if(result.size() != n){
			Out << -1;
			Out.close();
			return 0;
		}

	for(signed i = 0; i < result.size(); i++){
		Out << result[i];
		Out << " ";
	}
	Out.close();
}
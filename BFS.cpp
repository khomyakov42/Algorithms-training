#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

signed n, m ,s;
vector<signed> *vertex = NULL;
bool visited[100001];
queue<signed> q, solution;

int main(){
	ifstream In("input.txt");
	ofstream Out("output.txt");

	In >> n;
	In >> m;
	In >> s;

	vertex = new vector<signed>[n+1];

	if(n == 0){
		Out << -1;
		Out.close();
		return 0;
	}

	for(signed i = 0; i < m; i++){
		signed v1, v2;
		In >> v1;
		In >> v2;
		vertex[v1].push_back(v2);
		vertex[v2].push_back(v1);
	}

	q.push(s);
	solution.push(s);
	visited[s] = true;
	while(!q.empty()){
		signed v = q.front();
		q.pop();

		for(signed i = 0; i < vertex[v].size(); i++)
			if(!visited[vertex[v][i]]){
				q.push(vertex[v][i]);
				visited[vertex[v][i]] = true;
				solution.push(vertex[v][i]);
			}
	}
	
	for(signed i = 1; i <= n; i++)
		if(!visited[i]){
			Out << -1;
			Out.close();
			return 0;
		}

	while(!solution.empty()){
		Out << solution.front() << ' ';
		solution.pop();
	}

	Out.close();
	
}
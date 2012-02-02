#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

const int INF = 100000000;

struct Edge {
  int road, v, time, flow, limit, backward;
  Edge(int r_, int v_, int t_, int f_, int l_, int b_): 
    road(r_), v(v_), time(t_), flow(f_), limit(l_), backward(b_) {}
};

using namespace std;

vector< std::vector<Edge> > E;

vector<int> dist, parents,  edges, potentials;
vector<bool> vis;

bool dijkstra() {
	fill(dist.begin(), dist.end(), INF);
	fill(vis.begin(), vis.end(), false);

	dist[0] = 0;
	while (true) {
		int min = -1, min_dist = INF;

		for (int i = 0; i < dist.size(); ++i) {
			if (!vis[i] && dist[i] < min_dist) {
				min_dist = dist[i];
				min = i;
			}
		}

		if (min == -1)
			break;

		vis[min] = true;
		for (int i = 0; i < E[min].size(); ++i) {
			Edge &end = E[min][i];
			int d = dist[min] + end.time + potentials[min] - potentials[end.v];

			int backward = end.flow;
			if (!vis[end.v] && end.flow < end.limit && dist[end.v] > d) {
				dist[end.v] = d;
				parents[end.v] = min;
				edges[end.v] = i;
			}
		}
  }
  
	for (int i = 0; i < potentials.size(); ++i) {
		potentials[i] += dist[i];
	}

	return dist.back() != INF;
}

int main() {
	ifstream fi("brides.in");
	ofstream fo("brides.out");

	int cities, roads, sons;
	fi >> cities >> roads >> sons;

	dist.resize(cities);
	parents.resize(cities);
	edges.resize(cities);
	vis.resize(cities);
	potentials.resize(cities, 0);
	E.resize(cities);

	for (int i = 0; i < roads; ++i) {
		int v, u, time;
		fi >> v >> u >> time;

		auto e1 = Edge(i + 1, u - 1, time, 0, 1, E[u - 1].size());
		auto e2 = Edge(i + 1, v - 1, -time, 0, 0, E[v - 1].size());
		E[v - 1].push_back(e1);
		E[u - 1].push_back(e2);

		auto e3 = Edge(i + 1, v - 1, time, 0, 1, E[v - 1].size());
		auto e4 = Edge(i + 1, u - 1, -time, 0, 0, E[u - 1].size());
		E[u - 1].push_back(e3);
		E[v - 1].push_back(e4);
	}

	int flow = 0, cost = 0;
	while (flow < sons && dijkstra()) {
		int mf = INF;

		for (int i = dist.size() - 1; i != 0; i = parents[i]) 
			mf = std::min(mf, E[parents[i]][edges[i]].limit - E[parents[i]][edges[i]].flow);

		mf = std::min(mf, sons - flow);
		for (int i = dist.size() - 1; i != 0; i = parents[i]) {
			Edge &end = E[parents[i]][edges[i]];
			cost += end.time;
			end.flow += mf;
			E[end.v][end.backward].flow -= mf;
		}
		flow += mf;
	}

	if (flow == sons) {
		fo << fixed << setprecision(5) << double(cost) / sons;
		for (int i = 0; i < sons; ++i) {
			vector<int> path;
			int min = 0;
			while (min != cities - 1) {
				for (int j = 0; j < E[min].size(); ++j) {
					Edge &end = E[min][j];
					if (end.flow > 0) {
						end.flow = 0;
						min = end.v;
						path.push_back(end.road);
					}
				}
			}

			fo << (int)path.size();
			for (int j = 0; j < path.size(); ++j) {
				fo << " " << path[j];
			}
			fo << endl;
		}
	} else {
		fo << -1 << endl;
	}

	fo.close();
	fi.close();
}

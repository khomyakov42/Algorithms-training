#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <numeric>
#include <stack>
#include <fstream>

using namespace std;

template<class TVertex>
vector<pair<TVertex, TVertex>> hk(map<TVertex, vector<TVertex>> &G, vector<TVertex> &G1, vector<TVertex> &G2) {
	typedef vector<TVertex> Adjacency;
	typedef map<TVertex, Adjacency> Graph;
	typedef map<TVertex, TVertex> Pairs;
	typedef map<TVertex, int> Distances;
	typedef pair<TVertex, TVertex> Pair;

	struct Three{
		TVertex v;
		Adjacency::iterator itr;
		bool result;
	};
	const int INF = numeric_limits<int>::max();
	const TVertex FAKE_VERTEX = TVertex(0);

	Pairs pair;
	Distances dist;
	vector<Pair> result;
	queue<TVertex> Q;
	stack<Three> S;

	for (Graph::iterator v = G.begin(); v != G.end(); ++v) {
		pair[v->first] = FAKE_VERTEX;
	}

	while (true) {
		for (Adjacency::iterator v = G1.begin(); v != G1.end(); ++v) {
			if (pair[*v] == FAKE_VERTEX) {
				dist[*v] = 0;
				Q.push(*v);
			}
			else {
				dist[*v] = INF;
			}
		}

		dist[FAKE_VERTEX] = INF;

		while (!Q.empty()) {
			int v = Q.front(); Q.pop();

			for (Adjacency::iterator u = G[v].begin(); u != G[v].end(); ++u) {
				if (dist[pair[*u]] == INF) {
					dist[pair[*u]] = dist[v] + 1;
					if (pair[*u] != FAKE_VERTEX) {
						Q.push(pair[*u]);
					}
				}
			}
		}

		if (dist[FAKE_VERTEX] == INF) {
			break;
		}

		for (Adjacency::iterator w = G1.begin(); w != G1.end(); ++w) {
			if (pair[*w] != FAKE_VERTEX) {
				continue;
			}

			Three el = {*w, G[*w].begin(), false};
			S.push(el);

			while (!S.empty()) {
				el = S.top();

				if (el.result) {
					int u = *(el.itr - 1);
					pair[el.v] = u;
					pair[u] = el.v;
					S.pop();
					if (!S.empty()) {
						S.top().result = true;
					}
					continue;
				}

				if (el.itr != G[el.v].end()) {
					int u = *el.itr;
					S.top().itr = ++el.itr;

					if (dist[pair[u]] == dist[el.v] + 1) {
						dist[u] = 0;
						if (pair[u] != FAKE_VERTEX) {
							Three nel = {pair[u], G[pair[u]].begin(), false};
							S.push(nel);
						} else {
							S.top().result = true;
						}
					}
				} else {
					dist[el.v] = INF;
					S.pop();
				}
			}
		}
	}

	for (Adjacency::iterator v = G1.begin(); v != G1.end(); ++v) {
		if (pair[*v] != FAKE_VERTEX) {
			result.push_back(Pair(*v, pair[*v]));
		}
	}
	return result;
}

int test_hk() {
	int q, p, m;
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	map<int, vector<int>> G;
	vector<int> G1, G2;

	fi >> q >> p >> m;

	for (int i = 0, u, v; i < m; ++i) {
		fi >> u >> v;

		v *= -1;
		G[u].push_back(v);
	}
	for (int i = 1; i <= p + q; ++i) {
		if (i <= q) {
			G1.push_back(i);
		} else {
			G2.push_back(i - p - q - 1);
		}
	}

	vector<pair<int, int>> res = hk(G, G1, G2);
	fo << res.size() << endl;
	for (vector<pair<int, int>>::iterator p = res.begin(); p != res.end(); ++p) {
		fo << abs(p->first) << " " << abs(p->second) << endl;
	}
	return 0;
}
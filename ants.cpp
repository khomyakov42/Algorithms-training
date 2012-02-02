#include <map>
#include <hash_map>
#include <list>
#include <iostream>
#include <fstream>
#include <math.h>
#include <numeric>

using namespace std;

//alpha - betta - p - 
list<int> shortcut(map<int, map<int, int>> &G, int start, int n = 100, double a = 1, double b = 1, double p = 0, double q = 1) {
	map<int, map<int, double>> F;
	list<pair<int, int>> best_path;
	int curr = start, next, L = numeric_limits<int>::max();

	for (map<int, map<int, int>>::iterator i = G.begin(); i != G.end(); ++i) {
		for (map<int, int>::const_iterator j = i->second.begin(); j != i->second.end(); ++j) {
			F[i->first][j->first] = 1;
		}
	}

	
	
	for (int i = 0; i < n; ++i) {
		list<pair<int, int>> path;
		int l = 0;
		hash_map<int, bool> visit;

		curr = start;
		
		while (true) {
			vector<pair<int, double>> P;
			double d = 0;

			visit[curr] = true;

			for (map<int, int>::iterator v = G[curr].begin(); v != G[curr].end(); ++v) {
				if (visit.find(v->first) == visit.end()) {
					P.push_back(pair<int, double>(v->first, 100 * powf(F[curr][v->first], b) / powf(G[curr][v->first], a)));
					d += F[curr][v->first] / G[curr][v->first]; 
				}
			}

			double r = rand() % 100;
			double cr = 0;
			for (vector<pair<int, double>>::iterator i = P.begin(); i != P.end(); ++i) {
				cr += i->second / d;
				if (cr >= r) {
					next = i->first;
					break;
				}
			}

			if (curr == next) { break; }
			
			l += G[curr][next];
			path.push_back(pair<int, int>(curr, next));
			curr = next;
		}

		for (list<pair<int, int>>::iterator e = path.begin(); e != path.end(); ++e) {
			F[e->first][e->second] += q / l;
			F[e->second][e->first] += q / l;
		}

		if (L > l && path.size() == G.size() - 1) {
			best_path = path;
		}
	}

	list<int> res;

	if (best_path.size() != G.size() - 1) {
		return res;
	}

	for (list<pair<int, int>>::iterator i = best_path.begin(); i != best_path.end(); ++i) {
		res.push_back(i->first);
	}

	return res;
}

#define _(a, b, c)  G[a][b] = G[b][a] = c;

void print(list<int> &l) {
	for (list<int>::iterator i = l.begin(); i != l.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

int test_ants() {
	int n, m;
	map<int, map<int, int>> G;
	
	_(1, 2, 1)
	_(2, 3, 1)
	_(3, 4, 1)
	_(4, 5, 1)
	_(5, 1, 1)
	_(1, 3, 10)
	_(3, 5, 10)
	_(5, 2, 10)
	_(2, 4, 10)
	_(4, 1, 10)

	print(shortcut(G, 1)); G.clear();

	_(1, 2, 100)
	_(2, 3, 100)
	_(3, 4, 100)
	_(4, 1, 100)
	_(2, 4, 1)

	print(shortcut(G, 1)); G.clear();

	_(1, 2, 28)
	_(2, 3, 49)
	_(2, 4, 55)
	_(2, 5, 17)
	_(2, 16, 23)
	_(2, 6, 13)
	_(2, 7, 76)
	_(2, 11, 32)
	_(1, 3, 31)
	_(3, 4, 83)
	_(4, 6, 70)
	_(4, 5, 60)
	_(5, 6, 19)
	_(1, 16, 19)
	_(6, 7, 18)
	_(6, 8, 60)
	_(7, 8, 30)
	_(7, 11, 16)
	_(11, 8, 40)
	_(11, 9, 10)
	_(11, 10, 20)
	_(11, 12, 8)
	_(11, 14, 16)
	_(11, 15, 8)
	_(9, 8, 50)
	_(9, 10, 30)
	_(10, 12, 13)
	_(10, 17, 110)
	_(12, 14, 7)
	_(12, 13, 5)
	_(13, 14, 5)
	_(14, 15, 9)
	_(15, 16, 7)
	_(16, 17, 18)
	_(16, 18, 10)
	_(16, 19, 16)
	_(17, 18, 1)
	_(17, 19, 12)
	_(18, 19, 11)

	print(shortcut(G, 1));
	
	getchar();
	return 0;
}

#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
string sourse, s, sol;

int main(){
	ifstream In("input.txt");
	ofstream Out("output.txt");

	In >> sourse;
	In >> s;
	In.close();

	sol = s + "#" + sourse;
	std::vector<long int> l(sol.size());
	
	for(long int i = 1; i < sol.size(); i++) {
		long int j = l[i-1];
		while(j > 0 && sol[i] != sol[j])
			j = l[j-1];
		if(sol[i] == sol[j])
				j++;
		l[i] = j;

		if(j == s.size()){
			Out << i - 2*s.size() + 1;
			Out.close();
			return 0;
		}
	}

	Out << -1;
	Out.close();
} 
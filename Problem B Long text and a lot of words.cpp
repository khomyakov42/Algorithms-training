#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
string sourse;
long int n;

long int KMP(string s){
	string sol = s + "#" + sourse;
	vector<long int> l(sol.size());

	for(long int i = 1; i < sol.size(); i++) {
		long int j = l[i-1];
		while(j > 0 && sol[i] != sol[j])
			j = l[j-1];
		if(sol[i] == sol[j])
				j++;
		
		if(j == s.size())
			return i - 2*s.size();

		l[i] = j;
	}
	return -1;
}

int main(){
	ifstream In("input.txt");
	ofstream Out("output.txt");

	In >> sourse;
	In >> n;

	for(int i = 0; i < n; i++){
		string s;
		In >> s;

		if(KMP(s) < 0)
			Out << "0 ";
		else
			Out << "1 ";		
	}

	In.close();
	Out.close();
} 
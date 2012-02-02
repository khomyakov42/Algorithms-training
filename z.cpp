#include<vector>
#include<iostream>

#define middle 2001

using namespace std;
struct T{
   int val, code;
};

int comp(int a, int b, int code){
	switch (code){
		case 0: 
			return a + b;
		case 1: 
			return a - b;
	}
}

int main(){
   FILE *in = fopen("input.txt", "r");
   FILE *out = fopen("output.txt", "w");
   vector<T> v(3);
   vector<int> sol;
   int n;

   sol.push_back(13564);
   sol.push_back(1650);
   sol.push_back(8261);
   sol.push_back(4616);
   sol.push_back(2016);
   sol.push_back(11934);
   sol.push_back(3943);
   sol.push_back(11625);

   fscanf(in, "%d", &n);
   for(int i = 0; i < n; i++)
      fscanf(in, "%d %d", &v[i].val, &v[i].code);

   int code = 0;
   for(int i = 0; i < v.size(); i++)
      for(int j = i + 1; j < v.size(); j++)
         for(int k = 0; k < 2; k++){
            int code = comp(v[i].code, v[j].code, k);
            
            if(code >= 10 || code < 0)
               continue;
            
            T x;
            x.code = code;
            x.val = comp(v[i].val, v[j].val, k);
            if(abs(x.val) > 100000000)
               continue;

            for(int i = 0; i < sol.size(); i++)
               if(x.val == sol[i])
                  printf("%d = %d", sol[i], x.code);

            bool con = false;
            for(int z = 0; z < v.size(); z++)
               if(v[z].val == x.val){
                  con = true;
                  break;
               }

            if(con)
               break;
            v.push_back(x);
            fprintf(out, "%d = %d\n", x.val, x.code);
            printf("%d\n",v.size());
         }

   for(int i = 0; i < v.size(); i++)
      fprintf(out, "%d = %d", v[i].val, v[i].code);

   fclose(out);
   return 0;
}
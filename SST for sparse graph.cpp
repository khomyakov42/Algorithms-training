#include<cstdio>
#include<vector>
using namespace std;
#define max 100000
#define inf max * 1000 + 1
template<class T>
class Set{
   private:
      size_t size;
   public:
      vector<vector<T>> sets;
      Set(){size = 0;};
      ~Set(){};

      void MakeSet(T x){
         vector<T> v;
         v.push_back(x);
         sets.push_back(v);
         size++;
      }

      int Find(T x){
         for(int i = 0; i < sets.size(); i++)
            for(int j = 0; j < sets[i].size(); j++)
               if(x == sets[i][j])
                  return i;
      }

      void Unite(int s1, int s2){
         sets[s1].reserve(sets[s1].size() + sets[s2].size());
         for(int k = 0; k < sets[s2].size(); k++)
            sets[s1].push_back(sets[s2][k]);

         sets[s2].clear();
         size--;
      }

      size_t countSets(){
         return size;
      }
};

int main(){
   FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
   int n, m;
   vector<pair<int, pair<int, int>>> V, Vertex;
   Set<int> s;
   int res = 0;
   int Weight = 0;

   fscanf(in, "%d %d", &n, &m);
   for(int i = 0; i < m; i++){
      pair<int, pair<int, int>> v;
      fscanf(in, "%d %d %d", &v.second.first, &v.second.second, &v.first);
      V.push_back(v);
      Weight += v.first;
   }

   for(int i = 0; i < n; i++)
      s.MakeSet(i + 1);

   for(int i = 0; i < m; i++){
      for(int j = 0; j < m; j++)
         if(V[i].first < V[j].first){
            pair<int, pair<int, int>> x;
            x = V[i];
            V[i] = V[j];
            V[j] = x;
         }
   }

   for(int i = 0; i < m; i++){
      int v1 = V[i].second.first, v2 = V[i].second.second, w = V[i].first;
      int s1 = s.Find(v1), s2 = s.Find(v2);
      if(s1 != s2){
         res += w;
         s.Unite(s1, s2);
      }
   }

 /*  if(m < n - 1)
      res = -1;*/

   fprintf(out, "%d", res);
   fclose(in);
   fclose(out);
}
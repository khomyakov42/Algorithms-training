#include<fstream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<list>
#include<cassert>
 
#define inf  100000 * 1000 + 100
#define max 100001
struct TEdge{
   int v, w;
};

using namespace std;
unsigned long d[max];
bool visited[max];
vector<TEdge> W[max];

template<class T>
class Heap{
   private:
      void Swap(T &a, T &b){
         T x = a;
         a = b;
         b = x;
      };

      static int Compare(T x, T y){
         if(x < y)
            return -1;
         else
            if(y > x)
               return 1;
            else
               return 0;
      }
      typedef int (*ptr_func)(T, T);
   public:
      vector<T> Container;
      ptr_func cmp;
      Heap(ptr_func _cmp = &(Compare)){cmp = _cmp;};
      ~Heap(){};

      void push(T _val){
         Container.push_back(_val);

         int i = Container.size() - 1;
         while((*cmp)(Container[i], Container[(i - 1) / 2]) == -1){
            Swap(Container[i], Container[(i -1) / 2]);
            i = (i - 1) / 2;
         }
      }

      void pop(size_t _key){
         Container[_key] = Container[Container.size() - 1];
         Container.pop_back();
         int i = _key, l = 2 * i + 1, r = 2 * i + 2;
         size_t size = Container.size();
         while(r < size && ((*cmp)(Container[i], Container[l]) == 1 || 
         (*cmp)(Container[i], Container[r]) == 1))
            
            if((*cmp)(Container[l], Container[r]) == -1){
               Swap(Container[i], Container[l]);
               i = l;
               l = 2 * i + 1;         
               r = 2 * i + 2;
            }
            else{
               Swap(Container[i], Container[r]);
               i = r;
               l = 2 * i + 1;
               r = 2 * i + 2;
            }
      }

      T front(){
         return Container[0];
      }

      bool empty(){
         return Container.size() == 0;
      }
};

int Compare(int a, int b){
   if(d[a] < d[b])
      return -1;
   if(d[a] > d[b])
      return 1;
   return 0;
}

int main(){
   FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
   int n, m, s;
   Heap<int> q(&Compare);

   fscanf(in, "%d %d %d", &n, &m, &s);
   for(int i = 0; i < n + 1; i++){
      d[i] = inf;
      visited[i] = false;
   }

   for(int i = 0; i < m; i++){
      int v1, v2, w;
      TEdge x;
      fscanf(in, "%d %d %d", &v1, &v2, &w);
      x.w = w;
      x.v = v2;
      W[v1].push_back(x);
   }
   fclose(in);
 
   int cur = s;
   d[s] = 0;
   q.push(s);

   while(!q.empty()){
      visited[cur] = true;
      cur = q.front();
      q.pop(0);     
 
      for(int i = 0; i < W[cur].size(); i++)
         if(!visited[W[cur][i].v] && d[W[cur][i].v] > W[cur][i].w + d[cur]){
            d[W[cur][i].v] = W[cur][i].w + d[cur];
            q.push(W[cur][i].v);
         }
   }   

   for(int i = 1; i < n + 1; i++)
      fprintf(out, "%d ", d[i] >= inf? -1: d[i]);
 
   fclose(out);
   fclose(in);
}

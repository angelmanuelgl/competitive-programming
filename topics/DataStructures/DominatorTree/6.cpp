/*
    * Domintator Tree
    * https://cses.fi/problemset/task/1703
    * angelmanuelgl
*/

#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;

class DominatorTree {
public:
    // grafo de 1 a N
    static const int N = 2e5 + 9;

    vector<int> g[N];

    //t = dominator tree of the nodes reachable from root
    vector<int> t[N], rg[N], bucket[N]; 

    int tPar[N];
    //semidominator, parent in dfs tree, immediate dominator
    //parent in dsu, nodo with minimum sdom in the path until current union
    int sdom[N], par[N], idom[N], dsu[N], label[N];
    int id[N], rev[N], T;

    // para calcular rapido si uno domina a otro
    int tin[N],tout[N], tiempo_dfs=0;


    int find_(int u, int x = 0) {
        if(u == dsu[u]) return x ? -1 : u;
        int v = find_(dsu[u], x+1);
        if(v < 0)return u;
        
        if(sdom[label[dsu[u]]] < sdom[label[u]]) 
            label[u] = label[dsu[u]];

        dsu[u] = v;
        return x ? v : label[u];
    }

    void dfs(int u) {
        T++; id[u] = T;
        rev[T] = u; label[T] = T;
        sdom[T] = T; dsu[T] = T;
        for(int i = 0; i < g[u].size(); i++) {
            int w = g[u][i];
            if(!id[w]) dfs(w), par[id[w]] = id[u];
            rg[id[w]].push_back(id[u]);
        }
    }

    void clearStructures(int n){
        for(int i = 0; i <= n; i++) {
            t[i].clear(), g[i].clear(), rg[i].clear(), bucket[i].clear();
            tPar[i] = i;
            sdom[i] = par[i] = idom[i] = dsu[i] = label[i] = id[i] = rev[i] = 0;
        }
    }

    // raiz, numero de nodos
    void build(int r, int n){
        dfs(r);
        n = T;
        for(int i = n; i >= 1; i--) {
            for(int j = 0; j < rg[i].size(); j++) 
                sdom[i] = min(sdom[i], sdom[find_(rg[i][j])]);

            if(i > 1) bucket[sdom[i]].push_back(i);

            for(int j = 0; j < bucket[i].size(); j++) {
                int w = bucket[i][j];
                int v = find_(w);
                if(sdom[v] == sdom[w]) idom[w] = sdom[w];
                else idom[w] = v;
            }
            if(i > 1) dsu[i] = par[i];
        }
        for(int i = 2; i <= n; i++) {
            if(idom[i] != sdom[i]) 
                idom[i]=idom[idom[i]];

            t[rev[i]].push_back(rev[idom[i]]);
            t[rev[idom[i]]].push_back(rev[i]);
            tPar[rev[i]] = rev[idom[i]];
        }
    }
        // utilidades
    bool alcancable( int a){
        return id[a];
    }

    // para poder responder si a domina a b (a es ancestro de b)
    // Un nodo v es ancestro de un nodo u SSI e
    // tin[u] <= tin[u] y tout[u] << tout[v]
    // O(h) potencialment O(N)
    // usar eso da TLE

    void DFS_in_out(int actual=1, int padre =0){
        tiempo_dfs++;
        tin[actual] = tiempo_dfs;
        for( int hijo: t[actual]){
            if( hijo != padre )
                DFS_in_out(hijo, actual);
        } 
        tiempo_dfs++;
        tout[actual] = tiempo_dfs;
    }

    bool AdominaB(int a, int b){
        if( !alcancable(a)  || !alcancable(b) ) return false;
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }
    

};

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// uso :  g++ -DLOCAL K.cpp


// para evitar overflow en el stack
DominatorTree domTree;


int main(){
    #ifdef LOCALp
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif


    

}
/*
    * Domintator Tree
    * https://codeforces.com/gym/101741/problem/L
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
    
    //
    int tam_sub[N];
    void DFS_tam(int nodo = 1, int padre = 0){
        tam_sub[nodo] = 1;
        for( int hijo: t[nodo] ){
            if( hijo != padre){
                DFS_tam(hijo, nodo); 
                tam_sub[nodo] += tam_sub[hijo];
            }
              
        }
    }

};
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// DADO UN GRAFO con pesos, construir el MINIMUN PATH DIGRAF
// constuye un grafo dirigido que contiene los caminos mins
// segun yo es algo asi como la union de todos los expandngg tree

struct edge{
    int from, to;
    ll w;
    const bool operator<(const edge &b) const{
        return w > b.w;
    }
};
struct pos{
    int from;
    ll c;
    const bool operator<(const pos &b) const{
        return c > b.c;
    }
};
struct GrafoCaminosMinimos{
    int n,m;
    static const int MAXN = 2e5 + 10;
    vector<edge> graph[MAXN];
    vector<edge> aristas;
    int aristaUsada[MAXN] ; // 0 No se uso // 1 si // -1 en la direccion contraria 
    // vector<int> minPathGraph[MAXN];
    ll dist[MAXN];
    
    void clearStructures( int nn, int mm){
        n = nn; m = mm;

        memset( aristaUsada, 0, MAXN);
        // todo: hacer un iniicliazador que recee todo
    }
    void push_back( int u, int v, ll w){
        graph[u].pb( {u,v,w} );
        graph[v].pb( {v,u,w} );

        aristas.pb({u,v,w});
    }


    void dijkstra( int a ){
        bool vis[MAXN] = {};
        fill( dist, dist+MAXN, LLONG_MAX);
        priority_queue<pos> q;
        q.push( pos{a,0} );
        dist[a] = 0;
        
        while( !q.empty() ){
            pos act = q.top();
            q.pop();
            if( vis[act.from] ) continue;
            vis[act.from] = true;
            for( edge &e : graph[act.from]){
                if( dist[e.to] <= dist[e.from] + e.w) continue;
                dist[e.to] = dist[act.from] + e.w;
                q.push( pos{e.to, dist[e.to]});
            }   

        }
    }

    // tomamos solo las aristas que si usan los caminos minimoss
    void build( int a){
        dijkstra(a);

        for( int i=0; i<m; i++){
            int u = aristas[i].from;
            int v = aristas[i].to;
            ll w  = aristas[i].w;
            // deberiamo verifica rque ninguno tiene distancia infiintia LLONGMAX pero por dato se alcanzan todos
            // u -> v // 
            if(  dist[u] + w == dist[v] ){
                // minPathGraph[u].pb(v);
                aristaUsada[i] = 1;
            }
            // v -> u
            if(  dist[v] + w ==  dist[u] ){
                // minPathGraph[v].pb(u);
                aristaUsada[i] = -1;
            }
        }
    }
};


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// uso :  g++ -DLOCAL K.cpp




// para evitar overflow en el stack
DominatorTree domTree;
GrafoCaminosMinimos minCamin;

int main(){
    #ifdef LOCALp
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n, m; cin >> n >>m;
    
   minCamin.clearStructures(n,m);

    for( int i=1; i<=m; i++){
        int u,v,w; cin >> u >> v >>w;
        minCamin.pb(u,v,w);
    }
    
    // construir el grafo dirigido de caminos minimos
    minCamin.build(1);

    DEBUG{
        cout << "resultado DIJKSTRA\n";
        for( int i=0; i<=n; i++){
           cout << "d[ " << i << " ] = " <<  minCamin.dist[i]  <<"\n";
        }
        cout << "\n";
    }

    // si aumentamos el precio en la arista (u,v) u -> v
    // la arista no esta en minCamin 
    //      * entonces no afecta en nada
    // si esta en mincamin
    //      * entonces se aumentaran precios de todos los nodos que obliatoriamente pasan por esa arista
    //      * sea n un nodo,  pasar obligatoriamente por la arista (u,v) ene la camino 1 --> n
    //           <=> pasa obligatoriamente por u y pasa obligatoriamente por v
    //           <=> v no tiene mas aristas entrando y n es dominado por v
    //           <=> (u domina a v) y (v domina a n)
    //      * la arista (u,v) si u = idom(v) agrega tamSubArbolDominatorTree(v)
    

    // pasamos el minCamin al domTree
    domTree.clearStructures(n);
    
    


    //p para cada nodo recorrer cada uno de sus adyacentes
    // for( int from=1; from<=n; from++ ){
    //     for( int to : minCamin.minPathGraph[from] )
    //         domTree.g[from].pb(to);
    // }
    DEBUG cout << "DAG de caminos minimos\n";
    for( int i=0; i<m; i++){
        // tomar la arista
        edge unaCarretera = minCamin.aristas[i];
        int u = unaCarretera.from;
        int v = unaCarretera.to;
        ll w  = unaCarretera.w;

        // si no se uso no la agregamos
        if( minCamin.aristaUsada[i] == 0 ) continue;
        // la otra direccion
        if( minCamin.aristaUsada[i] == -1) swap(u,v);

        // agregarla
        DEBUG cout << u << " -> " << v << "\n";
        domTree.g[u].pb(v);
    }
    DEBUG cout << "\n";

    // constrior el dominator Tree
    domTree.build(1,n);


    DEBUG{
        cout << " DOMTRee\n";
        for( int i=0; i<=n; i++){
           cout << "idom[ " << i << " ] = " <<  domTree.tPar[i]  <<"\n";
        }
        cout << "\n";
    }

    
    // calcular los tamaos de los subarboles del dominator tree
    domTree.DFS_tam(1,0);


    DEBUG{
        cout << "tamano sub arbol DOMTRee\n";
        for( int i=0; i<=n; i++){
           cout << "tam[ " << i << " ] = " <<  domTree.tam_sub[i]  <<"\n";
        }
        cout << "\n";
    }

    

    // dar respuesta para cada arista // en orden
    for( int i=0; i<m; i++){
        edge unaCarretera = minCamin.aristas[i];
        int u = unaCarretera.from;
        int v = unaCarretera.to;
        ll w  = unaCarretera.w;


        // si no se uso en el DAG de caminos minimos no improta que se aumente el costo
        if( minCamin.aristaUsada[i] == 0 ){
            cout << "0\n";
            continue;
        }
        if( minCamin.aristaUsada[i] == -1) swap(u,v);
        
        // si si se uso arista (u,v) u -> v

        // si para llegar a v tengo que usar u
        if(  domTree.tPar[v] == u  ){
            cout << domTree.tam_sub[v] << '\n';
        }
        // si no, no me afecta
        else{
            cout << "0\n";
        }

    }

}
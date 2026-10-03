/*  
    * Contest: 
    * URL: https://www.codechef.com/AMR16MOS/problems/AMR16J
    * Problem: Bob vs ATM

    * Topic: Game Theory | Green Hackenbush
    * Algorithm: Apply the following transformation
                (())()
                0 - 1 - 2

                0 - 1

                (()()())( (())() ) : 
                      / 2
                0 - 1 -3
                     \ 4 

                0 - 5 - 6
                      \ 7

                the tree have at most N/2 nodes and at almost N/2 +1 edges

                Each node is a valid sequence, and each node is
                a child of another if it's a subsequence of this
                 
                Note that it's equivalent the game of green hackenbush
                O( (N+M) * alpha(N) ) 
    * Complexity: O( N *alpha(N) )
    * Status: ACCEPTED
    * angelmanuelgl
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distr(1, LLONG_MAX);
const int MOD = 1e9 + 7;
// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)
//
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p){return os << '(' << p.fi << ", " << p.se << ')';}
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v){string sep; for(const T &x : v) os << sep << x, sep = " "; return os;}
#define print(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}


struct dsu{
    struct action{
        int x_p, y_p;
        int rank_y;
    };
    vi RA, P;
    vector<action> actions;
    dsu(int n){
        RA.resize(n, 1);
        P.resize(n);
        iota(all(P), 0);
    }
    int root(int x){
        return x == P[x] ? x : P[x] = root(P[x]);
    }
    void join(int x, int y, bool recording){
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(RA[x] >= RA[y]) swap(x, y);
        if(recording) actions.pb({x, y, RA[y]});
        RA[y] += RA[x];
        P[x] = y;
    }
    void rollback(int cnt){
        while(cnt-- > 0 && sz(actions)){
            action act = actions.back();
            actions.pop_back();
            RA[act.y_p] = act.rank_y;
            P[act.x_p] = act.x_p;
        }
    }
};

// struct edge{
//     int from, to;
// };
typedef pii edge;
#define from first
#define to second

typedef vector<edge> ve;


struct ghb_r{
    int cntRepre, root, value;
    vi compactados, paridad, nim; vvi tree;
};
ghb_r ghb(int n, vector<edge> edges, const vi &suelo={} ){
    vi norm(n); vvi adj(n); iota( all(norm), 0 );
    for( int  u : suelo) norm[u] = 0;
    for( int  i = 0; i < sz(edges); i++ ){
        edge &e = edges[i];
        e.from = norm[e.from], e.to = norm[e.to];
        adj[e.from].pb(i);
        if(e.from != e.to) adj[e.to].pb(i);
    }
    vi pen,dep(n,-1),low(n),par(n, -1),paredg(n, -1),nex(n,0);
    dsu uf(n); pen.pb(0); dep[0] = low[0] = 0;
    while( sz(pen)  ){
        int u = pen.back();
        if( nex[u] < sz(adj[u])  ){
            int id = adj[u][nex[u]++];
            if(id == paredg[u]) continue;
            const edge &e = edges[id];
            int v = (e.from == u ? e.to : e.from);
            if( v == u ) continue;
            if( dep[v] == -1  ){
                par[v] = u, paredg[v] = id;
                dep[v] = low[v] = dep[u] + 1; pen.pb(v);
            }
            else if(dep[v] < dep[u])
                low[u] = min(low[u], dep[v]);
        }else{
            pen.pop_back();
            int p = par[u];
            if(p == -1) continue;
            low[p] = min(low[p], low[u]);
            if(low[u] <= dep[p]) uf.join(p, u, false);
        }
    }
    ghb_r r; vi id(n, -1); r.cntRepre = 0;
    for( int  u = 0; u < n; u++ ){
        if(dep[u] == -1) continue;
        int ro = uf.root(u);
        if(id[ro] == -1) id[ro] = r.cntRepre++;
    }
    r.compactados.assign(n, -1);
    for( int  u = 0; u < n; u++ ){
        int v = norm[u];
        if(dep[v] != -1) r.compactados[u] = id[uf.root(v)];
    }
    r.root = r.compactados[0];
    r.tree.resize(r.cntRepre);r.paridad.assign(r.cntRepre,0);
    for(const edge &e : edges ){
        if(dep[e.from] == -1) continue;
        int a = id[uf.root(e.from)], b = id[uf.root(e.to)];
        if(a == b) r.paridad[a] ^= 1;
        else{ r.tree[a].pb(b); r.tree[b].pb(a); }
    }
    for( int  u = 0; u < r.cntRepre; u++ ){
        if(!r.paridad[u]) continue;
        int leaf = sz(r.tree);
        r.tree.pb(vi{u});
        r.tree[u].pb(leaf);
    }
    vi order={r.root},npar(sz(r.tree),-1);npar[r.root]=r.root;
    for( int  i = 0; i < sz(order); i++ ){
        int u = order[i];
        for( int  v : r.tree[u] ){ 
            if(v == npar[u]) continue;
            npar[v] = u; order.pb(v);
        }
    }
    r.nim.assign(sz(r.tree), 0);
    for( int  i = sz(order) - 1; i > 0; i-- ){
        int u = order[i]; r.nim[npar[u]] ^= (r.nim[u]+1);
    }
    r.value = r.nim[r.root];
    return r;
}




void encontrar_finales(string &s, vi& end){
    int n = sz(s);
    end.resize(n,-1);
    stack<int> pila;

    for( int i=n-1; i>=0; i-- ){
        if(  s[i] == ')' ) 
            pila.push(i);
        else{
            end[i] = pila.top(); 
            pila.pop();
        }
    }
}

void crear_grafo(ve &edges, int &nodes, string &s, vi &end,
                int padre, int l, int r){
    int n = sz(s);

    if( !( l < r) ) return;
    
    for( int i=l; i<=r; ){
        print(i,s[i]);
        if( s[i]  == ')'   ){
            cerr << "NO DEBERIA PASAR s_i es cierre  ),. debe ser ( \n";
            return;
        }
        
        // ( -> i
        // ) -> end[i]
        int ini = i;
        int fin = end[i];
        // creamos un nuevo nodos
        int new_nodo = nodes++;

        // lo enlazamos con su padre
        edges.pb({padre,new_nodo});

        // recursivmaente
        crear_grafo( edges, nodes, s, end, new_nodo, ini+1, fin-1);
        

        // saltar al sigueinte final
        i = fin + 1;
    }
    
        
}

int main(){
    ios_base::sync_with_stdio(0); 
    cout.tie(0);
    cin.tie(0);

    int t; cin >> t; 
    
    while( t-- ){
        DEBUG cout << "\n\n. . . [ . . . CASO . . .  ] . . . \n" ; 
        string s; cin >> s;  
        print(s); 
        vi end;
        encontrar_finales(s, end);
        print(end);

        ve edges; int nodes = 1; //[0,nodes);
        crear_grafo(edges, nodes, s, end, 0,  0, sz(s)-1 );
        print(edges);

        ghb_r ans = ghb(nodes, edges);
        cout << ( (ans.value)? "ATM\n": "Bob\n" );


    }   

}
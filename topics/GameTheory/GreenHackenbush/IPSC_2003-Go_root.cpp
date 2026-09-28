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

struct edge{
    int from, to;
};
struct hackenbush_result{
    int cntRepresentantes, root, value;
    vi compactados, paridad, nim;
    vvi tree;
};
hackenbush_result green_hackenbush(int n, vector<edge> edges, const vi &mas_suelo = {}){
    vi norm(n);
    iota(all(norm), 0);
    for(int u : mas_suelo) norm[u] = 0;
    vvi adj(n);
    for(int i = 0; i < sz(edges); i++){
        edge &e = edges[i];
        e.from = norm[e.from], e.to = norm[e.to];
        adj[e.from].pb(i);
        if(e.from != e.to) adj[e.to].pb(i);
    }
    vi pendiente = {0}, depth(n, -1), low(n), parent(n, -1), parent_edge(n, -1), next(n,0);
    dsu unionf(n);
    depth[0] = low[0] = 0;
    while( sz(pendiente) ){
        int u = pendiente.back();
        if(next[u] < sz(adj[u])){
            int id = adj[u][next[u]++];
            if(id == parent_edge[u]) continue;
            const edge &e = edges[id];
            int v = (e.from == u ? e.to : e.from);
            if(v == u) continue;
            if(depth[v] == -1){
                parent[v] = u;
                parent_edge[v] = id;
                depth[v] = low[v] = depth[u] + 1;
                pendiente.pb(v);
            }
            else if(depth[v] < depth[u])
                low[u] = min(low[u], depth[v]);
        }else{
            pendiente.pop_back();
            int p = parent[u];
            if(p == -1) continue;
            low[p] = min(low[p], low[u]);
            if(low[u] <= depth[p]) unionf.join(p, u, false);
        }
    }
    hackenbush_result res;
    vi id(n, -1);
    res.cntRepresentantes = 0;
    for(int u = 0; u < n; u++){
        if(depth[u] == -1) continue;
        int r = unionf.root(u);
        if(id[r] == -1) id[r] = res.cntRepresentantes++;
    }
    res.compactados.assign(n, -1);
    for(int u = 0; u < n; u++){
        int v = norm[u];
        if(depth[v] != -1) res.compactados[u] = id[unionf.root(v)];
    }
    res.root = res.compactados[0];
    res.tree.resize(res.cntRepresentantes);
    res.paridad.assign(res.cntRepresentantes, 0);
    for(const edge &e : edges){
        if(depth[e.from] == -1) continue;
        int a = id[unionf.root(e.from)], b = id[unionf.root(e.to)];
        if(a == b) res.paridad[a] ^= 1;
        else{
            res.tree[a].pb(b);
            res.tree[b].pb(a);
        }
    }
    for(int u = 0; u < res.cntRepresentantes; u++){
        if(!res.paridad[u]) continue;
        int leaf = sz(res.tree);
        res.tree.pb(vi{u});
        res.tree[u].pb(leaf);
    }
    vi order = {res.root}, par(sz(res.tree), -1);
    par[res.root] = res.root;
    for(int i = 0; i < sz(order); i++){
        int u = order[i];
        for(int v : res.tree[u]){ 
            if(v == par[u]) continue;
            par[v] = u;
            order.pb(v);
        }
    }
    res.nim.assign(sz(res.tree), 0);
    for(int i = sz(order) - 1; i > 0; i--){
        int u = order[i];
        res.nim[par[u]] ^= (res.nim[u]+1);
    }
    res.value = res.nim[res.root];
    return res;
}


int main(){
    ios_base::sync_with_stdio(0); 
    cout.tie(0);
    cin.tie(0);

    int t,n,m,u,v; cin >> t; // casos de prueba

    
    while( t-- ){
        cin >> n >> m;

        vector<edge> edges;

        for( int i=0; i<m; i++){
            cin >> u >> v;
            edges.pb( {u,v} );
        }

        vi mas_suelo = {1};
        hackenbush_result ans = green_hackenbush(n+1, edges, mas_suelo);

        if( ans.value ) cout << "Alice\n";
        else cout << "Bob\n";
    }

}
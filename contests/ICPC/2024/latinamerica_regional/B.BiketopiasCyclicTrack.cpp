/*  
    * Contest: 2024-2025 ICPC Latin American Regional Programming Contest
    * URL: https://codeforces.com/gym/105505
    * Problem: Biketopia's Cyclic Track

    * Topic: DFS - tree | math | infite descense | contradition | constructive
    * Algorithm: DFS tree, the lowest back-edge
    * Complexity: O(n)

    * Status: ACCEPTE
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- Short Macros ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()


// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUG1 DEBUG cout <<
#define DEBUG2 DEBUG1 "\n" << 
#define DEBUG3 DEBUG1 "\n";
#define NODEBUG if(!debug)

// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) via SFINAE
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Logger Function
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

enum estado{ NOVISITADO, VISITANDO, VISITADO };
vi estado;
vi profu;
struct edge
{
    int from, to, id;
};
typedef vector<edge> ve;
typedef vector<ve> vve;

ostream& operator<<(ostream &os, const edge &v) {
    os << "{ " << v.from << " -> " << v.to << "  , "<< v.id << " }"; 
    return os;
}

edge max_depth_back_edge = {-1,-1,-1};

void actualiza( edge e ){
    int v = e.to;
    
    int v_act = max_depth_back_edge.to;
    if( v_act == -1  || profu[v] > profu[ v_act ] ){
        max_depth_back_edge = e;
        print(max_depth_back_edge);
    }
}


void dfs_tree( vve & listady, vi & padre, ve &edge_padre, int u=0, int p=-1){
    print( u,p );
    if( p!= -1) profu[u] = profu[p] +1;
    else profu[u] = 0;
    padre[u ] = p;
    estado[u] = VISITANDO;

    // recorremos sus vecinos
    for( edge e : listady[u] ){
        int v = e.to;
        if( v == p )continue;

        // si es no visitado lo agregamos al dfs tree
        if( estado[v] == NOVISITADO ){
            edge_padre[v] = e;
            dfs_tree( listady, padre, edge_padre, v, u);
        }
        // es back-edge
        if( estado[v] == VISITANDO )
            actualiza( e);
    }
    estado[u] = VISITADO;
}

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n, m; cin >> n >> m;

    vve listady( n );
    int u,v;
    for( int i=0; i<m; i++){
        cin >> u >> v; u--; v--;
        listady[u].pb({u,v,i+1});
        listady[v].pb({v,u,i+1});
    }


    vi padre(n);
    ve edge_padre(n);
    estado.resize(n, NOVISITADO);
    profu.resize(n, 0);
    print(estado);
    dfs_tree( listady ,padre, edge_padre);

    print(padre);
    print(profu);
    print(max_depth_back_edge);

    // tomamos la back-edge mas abajo mas progunda
    int it = max_depth_back_edge.from;
    int ancestro = max_depth_back_edge.to;
    int id = max_depth_back_edge.id;

    // imprimimos el cmaino
    vi ans = {id};
    while(  it != ancestro  ){
        ans.pb(  edge_padre[it].id );
        print( it, padre[it] , edge_padre[it]);
        it = padre[it];
    } 

    cout << sz(ans) << "\n";
    for( int i=0; i<sz(ans); i++){
        cout << ans[i] << " \n"[i==sz(ans)-1];
    }

}
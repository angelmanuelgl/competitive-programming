/*  
    * Contest: 
    * URL: https://www.codechef.com/AMR16MOS/problems/AMR16J
    * Problem: Bob vs ATM

    * Topic: Game Theory | Green Hackenbush
    * Algorithm: for weight > 1
                note that if T is a tree with nim[T] = x
                u -(w)- T 
                 \ 
                 (others branches)
                
                is equvialent to (the Colon principle)

                u -(w)- Nim pile of size x
                 \ 
                 (others branches)

                if w == 1,the standard Green Hackenbush algortihm aplies
                otherwise ( when w > 1):""
                
                u -(w)-  Nim pile of size x
                 \ 
                (others branches)

                is equvialent to

                u -(w) - p_1 - p_2 - ...-  p_x
                  \ 
                  (others branches)

                 is equvialent to ( u and p_1 form a cicle, the fusion principle)

                  m lazos
                 / 
                u  - p_2 - ...-  p_x
                  \ 
                  (others branches)
                
                is equvialent to 

                k1 k2 .. km
                \ / / 
                  u  - p_2 - ...-  p_x
                  \ 
                  (others branches)

                id m % 2 == 0, then k1, .. km, will cancel out, leaving
                ( becasse 1 xor 1 = 0)
                 u  - p_2 - ...-  p_x
                  \ 
                 (others branches)

                other case if m%2 == 1, we have
                 k1
                / 
                u  - p_2 - ...-  p_x
                \ 
                (others branches)


            so yo can aply 
            
            vi nim (sz(r.tree), 0);
            DFS( ):
                ... 
                if( w == 1 ){
                    nim[parent[u]] ^= (r.nim[u]+ 1 ); 
                else
                    nim[parent[u]] ^= (r.nim[u]);
                    int restantes = w%2;
                    nim[parent[u]] ^= (restantes);
                
            in the clasic Green Hackenbush algortihm
                   
                
    * Complexity: O( (N+M) * alpha(N) ) 
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
typedef vector<vpii> vvpii;
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
    ll w;
};
// typedef pii edge;
// #define from first
// #define to second

typedef vector<edge> ve;


struct ghb_r{
    int cntRepre, root=0, value;
    vi nim; vvpii tree;
};
ghb_r ghb(int n, vector<edge> edges, const vi &suelo={} ){
          pen.pop_back();
    ghb_r r;

    r.cntRepre = n;
    r.root = 0;
    
    // .. continuar algoritmo
    r.tree.resize(r.cntRepre);
    for(const edge &e : edges ){
        int a = e.from;
        int b = e.to;
        ll w = e.w;
        
        r.tree[a].pb({b,w});
        r.tree[b].pb({a,w}); 
    }

    vpii order={ {r.root, 0} };
    vi npar(sz(r.tree),-1);
    npar[r.root]=r.root;
    for( int  i = 0; i < sz(order); i++ ){
        int u = order[i].fi;
        for( pii  arista : r.tree[u] ){ 
            int v = arista.fi;
            ll w = arista.se;
            if( v == npar[u] ) continue;
            npar[v] = u; 
            order.pb({v,w});
            // u -> v con peso w
        }
    }
    r.nim.assign(sz(r.tree), 0);
    for( int  i = sz(order) - 1; i > 0; i-- ){
        int u = order[i].fi; 
        ll w = order[i].se; 
        if( w == 1){
            r.nim[npar[u]] ^= (r.nim[u]+ 1 ); 
        }else{
            r.nim[npar[u]] ^= (r.nim[u]);
            int restantes = w%2;
            r.nim[npar[u]] ^= (restantes);
        }   
        
    }
    r.value = r.nim[r.root];
    return r;
}


int main(){
    ios_base::sync_with_stdio(0); 
    cout.tie(0);
    cin.tie(0);

    int t; cin >> t; 
    int caso = 1;
    while( caso++ <= t ){
        DEBUG cout << "\n\n. . . [ . . . CASO " << caso <<  " . . .  ] . . . \n" ; 
        int n,m,u,v,w; cin >> n;
        m = n-1;
        ve edges;
        for( int i=0; i<m; i++){
            cin >> u >> v >> w;
            
          
            edges.pb({u,v,w});
        }
       
        ghb_r ans = ghb(n, edges);
        cout << "Case " << caso-1 << ": ";
        cout << ( (ans.value)? "Emily\n": "Jolly\n" );


    }   

}
/*  
    * Contest: 2026 ICPC Gran Premio de Mexico 2da Fecha
    * URL: https://codeforces.com/gym/106540/problem/A
    * Problem: B – Baus Stream

    * Topic: Trie, Tree DP, Knapsack
    * Algorithm: - dp[u][i] = min searches to delete i usernames from subtree u.
                 - merge each child v: ndp[a+b] = min(ndp[a+b], dp[u][a] + dp[v][b])
                   in O( min(K,A)* min (K, B) )
                 - taking prefix u deletes cnt[u] usernames in one search.
                 - ans: dp[root][k].
                 - Tree-knapsack merges cost O(nK) in total (amortized) not O( S K^2 )
                 - add nodes in trie O(SK)
    * Complexity: O( SK) time, O( S*K ) memory     S = total input length
    * Status: ACCEPTED
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
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
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
#define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;



const int SIGMA = 'z' - 'a' +1;
// const int MAXNODOS =   1e2 + 5;
// const int MAXK = 1e2;
const int MAXNODOS =   1e5 + 5;
const int MAXK = 1e4 + 5;
struct trie{
    // u --(c) --> nodos[u][c]
    int hijo[MAXNODOS][SIGMA] = {};
    bool esfinal[MAXNODOS] = {};

    int root = 1;
    int cnt_nodos = 1;
  
    void insert( string &s){
        int actual = root;
        DEBUG cout << s << "\n";
        for( char cha : s){
            int c = cha - 'a';
            // si aun no esta agregado
            if( !hijo[actual][c]  ) hijo[actual][c] = ++cnt_nodos;
            actual = hijo[actual][c];
            DEBUG cout << "  " << cha << " " << c << " " << actual  << "    ";

        }
        esfinal[ actual ] = true;

        DEBUG cout <<  "\n" << s << "\n";
    }

    void imprimir( void ){
        vi pend = {1};
        vector<char> pendc = {'r'};
        for( int i=0 ; i<sz(pend); i++){
            int u = pend[i];
            DEBUG cout << u << ", " << pendc[i] << "  : ";

            for( int c=0; c<SIGMA; c++ ){
                if( !hijo[u][c] ) continue;
                cout << hijo[u][c] << "," << (char)(c+'a') << "  ";
                pend.pb(hijo[u][c]);
                pendc.pb(c+'a');
            }
            DEBUG cout << "\n";
        }
    }

    int cnt[MAXNODOS]; // conta rpalabras en subarbol
    void dfs_cnt_terminales(int u = 1){
        cnt[u] = (esfinal[u])? 1:0 ;
        for( int c=0; c<SIGMA; c++ ){
            int v = hijo[u][c];
            if( !v ) continue;
            dfs_cnt_terminales( v );
            cnt[u] += cnt[v];
        }
        DEBUG cout << u <<  " "  << cnt[u] << "\n";
    }

    vi dp[MAXNODOS]; 
    // dp[u][i] = nminimo numero de busquedas para elimianr exatamente i prefijos
    
    void dfs_dp(int u , int k){
        dp[u] = {0};
        // ---  eliminar prefijos juntado subarboles ---

    
        // procesamos cada nodo hijo
        for( int c = 0; c<SIGMA; c++){
            int v = hijo[u][c];
            if( !v ) continue;
            dfs_dp( v , k);

            // queremos eliminar a lo mas k prefijos
            // podemos eliminar a lo mas "cnt_palabras_subarbol" prefijos
            vi nuevo_dpu( min(k,cnt[u])+1, INT_MAX);
            

            // O ( K ^2 ) 
            // O( cnt^2 )
            for( int a = 0; a < sz(dp[u]); a++){
            for( int b = 0; b < sz(dp[v]); b++){
                if( a+ b > k ) continue;
                // si podemos eliminear a usarios
                // si con el nodo v podemos eliminat b usuairos
                // podemos eliminar a + b usuarios juntando las buisquedas
                int posible =  dp[u][a] + dp[v][b];
                // revisar que no hubo overflow
                if( dp[u][a] == INT_MAX || dp[v][b] == INT_MAX)
                    continue;
                
                // vamos tomando el mejor
                nuevo_dpu[a + b]  = min(posible, nuevo_dpu[a + b]);
            }}


            // despues de cada hijo lo actualizamos
            swap( dp[u], nuevo_dpu );

        }

  

        // --- eliinar todo el subarbol del nodo actual con una busqueda ---
        if( u != root && cnt[u] <= k){
            // si no cabe
            if( dp[u].size() <= cnt[u] )
                dp[u].resize(cnt[u] + 1, INT_MAX);
            // agregamos la opcion de eliminar todos cnt[u] con 1movimeinto
            dp[u][cnt[u]] = min(dp[u][cnt[u]], 1);
        }
    }

    int ans( int k ){
        return dp[root][k];
    }
};

// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n, k; cin >> n >> k;

    trie mytrie;
    string s;
    for( int i=0; i<n; i++){
        cin >> s;
        mytrie.insert(s);
    }

    DEBUG mytrie.imprimir();

    mytrie.dfs_cnt_terminales();
    mytrie.dfs_dp(1,k);


    cout << mytrie.ans(k) << "\n";
}
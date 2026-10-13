/*  
    * Contest: 
    * URL: 
    * Problem: 

    * Topic: 
    * Algorithm: 
    * Complexity: 

    * Status: 
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- --- Type Aliases --- ---
typedef int64_t ll;
typedef __int128 lll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- --- Short Macros --- ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for( int i=a; i< (b); ++i )

// --- --- DEBUGER SETUP --- ---
#ifdef LOCAL
    bool debug = true;
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUGC DEBUG cout <<
#define SALTO DEBUGC "\n";
#define NODEBUG if(!debug)

namespace DebugColors {
    const string RED = "\033[1;31m";
    const string GREEN = "\033[1;32m";
    const string YELLOW = "\033[1;33m";
    const string CYAN = "\033[1;36m";
    const string RESET = "\033[0m";
}
#define COL DEBUGC DebugColors::YELLOW << 
#define COLEND DEBUGC DebugColors::RESET << "\n";

// --- --- LOGGER SETUP --- ---
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

// --- --- CONSTANTES --- ---
const int MOD = 1e9 + 7;


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

// g++-16 -DLOCAL -Wl,-stack_size,0x20000000 I.InversionInsight.cpp
// para cualquer n con x = 190 basta

const int MAXN = 200000;
const int MAXX = 191;
const ll MAXK = 4e18;

lll dp[MAXN+1][MAXX+1];
ll max_x_para_n[MAXN+1];

bool imprimir(int i){
    if( i<100 ) return true;
    if( i <1000) return  !( i% 5);
    if( i <10000) return !( i% 50);
    if( i <100000) return!( i% 500);
    if( i <1000000) return !( i% 5000);
    return  !( i% 50000);
}

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        // ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif
    

    int n; cin >> n;
    ll k; cin >> k;

    ll max_x = 0;
    ll acum = 0;

    // llenar dp
    for( int i=1; i<=n ;i++){
        acum = 1;
        dp[i][0] = 1;
        for( int x=1; x<= min( (ll)MAXX, (ll)(i-1)*i/2   ); x++){
            lll posans = dp[i][x-1] + dp[i-1][x];
            if( x- i >=0 ) posans -= dp[i-1][x-i];
            max_x_para_n[i] = x;
            dp[i][x] = (ll)min(posans, (lll)MAXK);
            if( acum > MAXK - posans ){  
                break;
            }
            acum+= posans;

           
        }
        max_x = max( max_x, max_x_para_n[i]);
    }

    // revisar que el max_x sea decreciente
    // revisar esto nos asegura(nos da un indicio)que dp fue calculado bie
    DEBUG{
    print( max_x );
    int ant = -1;
    for( int i=0; i<=n; i++){  
        if( imprimir(i) ){
            if( ant < max_x_para_n[i] ) COL "";
            print(i, max_x_para_n[i]);
            if( ant < max_x_para_n[i] ) COLEND;
        } 
        ant = max_x_para_n[i];
    }
    }

    // revisar que si encontramso biena. que blqoeu pertence
    DEBUG{
        rep(x,0,20) cout << (ll)dp[n][x] << " ";
        SALTO
  
        rep(kk, 1, k){
            lll permutaciones_menores = 0;
            int bloque_actual = 0;
            for( int x=0; x<=MAXX; x++){
                // print(x, permutaciones_menores);
                bloque_actual = x;
                // para pasar al sigueinte bloque tengo que
                // tener un indice k mayor que todo lo anteiro
                if( ! ( kk > permutaciones_menores + dp[n][x]) ) break;

                permutaciones_menores += dp[n][x];
            }

            
            ll new_k = kk - permutaciones_menores;
            print(kk, bloque_actual, new_k);
        }
    }

    lll permutaciones_menores = 0;
    int bloque_actual = 0;
    for( int x=0; x<=MAXX; x++){
        // print(x, permutaciones_menores);
        bloque_actual = x;
        // para pasar al sigueinte bloque tengo que
        // tener un indice k mayor que todo lo anteiro
        if( ! ( k > permutaciones_menores + dp[n][x]) ) break;

        permutaciones_menores += dp[n][x];
    }

    
    ll new_k = k - permutaciones_menores;
    print(k, bloque_actual, new_k);

    ll x = bloque_actual; // cantidad de inversiones en este bloque // hay a lo mas (n-1)*n/2

}
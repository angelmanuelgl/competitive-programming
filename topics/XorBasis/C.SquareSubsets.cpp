/*  
    * Contest: tutorial de XOR BASIS
    * URL: https://codeforces.com/blog/entry/68953 
    * Problem: Problem 1 (Division 2 — C) C. Square Subsets
    * Topic: bitmask | xor | combinatorics | dp |math | dp on subsets 
    * Complexity: O( 2^P * A) P = 19 A <=20
    * Status: ACCETED
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- --- --- --- Type Aliases --- --- --- ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- --- --- --- Short Macros --- --- --- ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for( int i=a; i< (b); ++i )

const int MOD = 1e9 + 7;

// --- --- --- --- LOGGER SETUP --- --- --- --- 
// Daclare before   
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v);
// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) SFINAE
template<typename C, typename T>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Colors
constexpr const char *RST="\033[0m", *GREEN="\033[1;32m", 
*YELLOW="\033[1;33m",*CYAN="\033[1;36m",*RED="\033[1;31m";
// Logger Function
template<typename ...Args>
void logger(const char* col, string vars, Args&&... values){
    cerr << col << '[' << vars << "] =" << RST;
    ((cerr << " [" << values << ']'), ...);
    cerr << '\n';
}

// --- --- --- --- DEBUGGER SETUP --- --- --- ---    
#ifdef LOCAL
    #define DEBUG   if (true)
    #define SALTO   (cerr << '\n')  
    #define LOG(...)   logger("", #__VA_ARGS__, __VA_ARGS__)
    #define LOGC(c, ...) logger(c, #__VA_ARGS__, __VA_ARGS__)    
    #define COL(c, ...) (cerr << c << __VA_ARGS__ << RST << '\n')
#else
    #define DEBUG   if (false) 
    #define SALTO
    #define LOG(...)
    #define LOGC(...)
    #define COL(...)
#endif

#define set_bit(S, j) (S|= (1<<(j)));
#define clear_bit(S, j) (S& ~(1<<(j)));

ll exp_bin( ll base, ll exp){
    ll res = 1;
    while( exp > 0){
        if( exp & 1) res = (res*base) %MOD;
        base = (base*base)%MOD;
        exp >>=1;
    }
    return res;
}

int MAXP = 19; //19
vi primo ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
// // // // // // // // // // // // // // // // // // // // //
// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif
    
    LOGC( YELLOW, (1<<19) * 70 * 8 /1024 / 1024 );

    int n; cin >> n;
    int m = 70; // = 70

 
    vi a(n+1);
  
    vi cnt(m+1,0);
    rep(i,1,n+1){
        cin >> a[i];
        cnt[ a[i] ]++;
    }


    // formas de elegir una cantidad impar/par del elemento is 
    // O( A log N )
    vll formas_elegir_impar(m+1);
    vll formas_elegir_par(m+1);
    rep( i, 1, m+1){
        if( cnt[i] == 0){
             formas_elegir_par[i]  = 1;
             formas_elegir_impar[i]  = 0;
             continue;
        }
        // binom(cnt,0) +  binom(cnt,2) + binom(cnt,4) + ...
        formas_elegir_par[i] = exp_bin(2,cnt[i]-1);
        // binom(cnt,1) +  binom(cnt,3) + binom(cnt,5) + ...
        formas_elegir_impar[i] = formas_elegir_par[i];
    }


    LOG(formas_elegir_par);
    LOG(formas_elegir_impar);
    SALTO;
    // mapear cada numero a (Z_2) ^ 9
    // indicando en el i-eismo bit si la potencia ki del i-esimo primo
    // i = p1^k1 * p2^k2 * ... * pi^ki * ... p19^k19
    // O( A log A )
    vi mapeo(m+1);
    rep( i, 1, m+1){
        
        mapeo[i] = 0; // (0,0,0,0,0)
        
        rep( j, 0, MAXP){
            int p = primo[j];
            // i =   ... * p^exp  * ... 
            int num = i, exp = 0;
            while( num % p == 0 ){
                num/= p;
                exp++;
            }
            if(  exp % 2 == 1   )
                set_bit( mapeo[i], j);
            
        }

        LOG( i, bitset<19>(mapeo[i]) );

    }   

    SALTO;


    ll MAXS = (1<< MAXP);
    ll FULL = MAXS-1;
    LOGC( RED, bitset<20>(MAXS));
    LOGC( RED, bitset<20>(FULL));


    // calcular la dp
    // O( 2^P * A ). / P =19 A = 70s
    // dp[i][s] = cantidad de subconjuntos que suman s y usando
    //             los valores 1,2,3, ... , i           
    vvll dp( 2, vll(MAXS,0) ); // es uan dp de 70 x 2^19, NOC ABE
    dp[0][0] = 1; // el vacio
    
    rep(i, 1, m+1){
        // LOGC( RED,i );=
        rep( s , 0, MAXS){
            // usamos una cantidad par de veces el elemento i
            dp[ i%2 ][ s ]  =  ( formas_elegir_par[i] * dp[ !(i%2) ][s])% MOD;
            // si usamos una cantidad impar de veces el elemnto i
            int z = s ^ mapeo[i]; // s xor mapeo(i)
            dp[ i%2 ][s] = ( dp[i%2][s] +  ( formas_elegir_impar[i] * dp[ !(i%2) ][z])% MOD ) %MOD;
            
            // LOG( i, bitset<5>(s), bitset<5>(z), dp[i][s] );
        }
 
        // SALTO;
    }

    // rep(i, 1, m+1) LOG(dp[i]);
    // le restamos un uno por el conutno vacios
    cout << dp[ m%2 ][0] -1 << "\n";

    
}
/*  
    * Contest: tutorial de XOR BASIS
    * URL: https://codeforces.com/blog/entry/68953 
    * Problem: Problem 1 (Division 2 — C) C. Square Subsets
    * Topic: | xor basis | linear algebra |
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

#define is_on(S,j) ( S & (1<<(j) ) )
#define set_bit(S, j) (S|= (1<<(j)));
#define clear_bit(S, j) (S& ~(1<<(j)));

// n <= 2e5 < =2^18
const int d = 32;

struct xorbasis{
    int basis[d]={};// basis[i]: v\inBase cuyo lsb es i
    int sz = 0;       // size actual de la base (= rango r)

    xorbasis(void){
        rep(i,0,d) basis[i] = 0;
    }
    bool insertVector(int mask){
        // LOGC(RED,mask);
        for( int i = 0; i < d; i++ ){
            // LOG(i, is_on(mask,i), basis[i]);
            if( !is_on(mask,i) )continue; // continue if lsb(mask)!=i
            if( !basis[i] ){ // no hay vector en la base con ese bit
                basis[i] = mask;
                ++sz;
                return true;
            }
            mask ^= basis[i]; // si ya hay, quitarle ese bit a mask
        }
        return false;
    }
    int dim( void ){
        return sz;
    }
};
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
    
  
    int n; cin >> n;
    vi a(n);
    rep(i,0,n){
        cin >> a[i];
    }
  
    // mapear cada numero a (Z_2) ^ 9
    // indicando en el i-eismo bit si la potencia ki del i-esimo primo
    // i = p1^k1 * p2^k2 * ... * pi^ki * ... p19^k19
    // O( A log A )
    vi mapeo(n);
    rep( i, 0, n){    
        mapeo[i] = 0; // (0,0,0,0,0)  
        rep( j, 0, MAXP){
            int p = primo[j];
            // i =   ... * p^exp  * ... 
            int num = a[i], exp = 0;
            while( num % p == 0 ){
                num/= p;
                exp++;
            }
            if(  exp % 2 == 1   )
                set_bit( mapeo[i], j); 
        }
        LOG( a[i], bitset<19>(mapeo[i]) );
    }   

    SALTO;

    // lo agregamos a la base
    xorbasis base;
    rep(i,0,n){
        base.insertVector(mapeo[i]);
    }

    // quermeos formar (0,0,0,0,0) con sumas de elemntos de la base
    cout << exp_bin(2, n - base.dim()) - 1<< "\n";
 

    
}
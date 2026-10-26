/*  
    * Contest: 2025 ICPC Gran Premio de Mexico 2da Fecha
    * URL: https://codeforces.com/gym/105979
    * Problem: F. Fixing logs
    * URL: https://codeforces.com/gym/105979/problem/F
    * Topic: Matching | Hall's Theorem | Greedy
    * Algorithm: Usar Teorema de hall para ver que existe un mathcing
    *             si y solo ( X==Y  y si ai + bi <= X )
    *             donde X es la suma de todos los ai y Y es la suma de toods los Y
    *             separar casos, si no se cumple X==Y (es decir si no cumple ai + bi <= X)
    *             y si X != Y, para encontrar los minimos movimeintos en los que se cumple
    * Complexity: O(N)
    * Status: ACCEPTED
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
    
    vll a(n), b(n);
    ll x = 0, y = 0;
    rep(i,0,n){
        cin >> a[i] >> b[i];
        x += a[i];
        y += b[i];
    }
    ll op2 = max(x,y) - min(x,y);
    ll op1 = 0 ;
    ll cuantas = (x == y)? 2 : 1; 
    rep(i,0,n){
        op1 += cuantas*max(0ll, a[i]+b[i] - min(x,y));
    }

    ll ans = max(op1, op2);
    cout << ans << "\n";
}
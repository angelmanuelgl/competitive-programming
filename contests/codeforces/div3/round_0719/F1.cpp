/*  
    * Contest: Codeforces Round 719 (Div. 3)
    * URL: https://codeforces.com/contest/1520
    * Problem: F1. Guess the K-th Zero (Easy version)
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
#define rep(i,a,b) for( int i=a; i< (b); ++i )

// --- DEBUGER SETUP ---
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


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        // ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n, t,k ; cin >> n >> t >> k;
    /// buscamos el k-esimo 0


    // f( i ) = cantidad de 0 a la izquerda [1,i] incluyendo i
    //  f( i ) < k  => false
    //  f( i ) >= k  => true
    // buscamos el primer i tal que f(i) >= k

    int l = 0; // siempre falso
    int r = n; // siempre verdadero


    while( l+1 <r){
        int m = (l+r)/2;
        
        cout << "? 1 " << m << "\n";
        cout.flush();

        int f_m = -1; 
        cin >> f_m; // me responde la cantidad de unos
        f_m = m - f_m; // asi se la cantidad de ceros

        print( l, r, m, f_m, k);
        if( f_m >= k ) r = m; // r siempre verdadero
        else l = m; // siempre falso 
    }

    cout << "! " << r << "\n";
    cout.flush();
    
}
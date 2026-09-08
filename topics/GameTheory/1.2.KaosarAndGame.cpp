/*  
    * Contest: Game theory training sessions | CS
    * URL: https://eolymp.com/en/problems/12261
    * Problem:  Kaosar And Game

    * Topic: Game Teory
    * Algorithm:  - First we identify the winning and lossing positions
                    in the case wehere p=q=0
                  - Then, we observe that if one playes has more
                    "fake junmps" than the other, they can swap positions
    * Complexity: O(1) for each query

    * Status: ACCEPTs
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

    int t; cin >> t;

    while( t-- ){
        int n, k, p, q;

        cin >> n >> k >> p >> q;

        // O(N)
        // // 1 posicion ganadora // 0 posicion perdedora
        // vector<int> posiciones(n+1,0);
        // posiciones[n] = 1; // posicion ganadora

        // // llevar le conteo de los k sigueintes
        // int cnt_perdedoras = 0;
        // for( int i=n-1; i>0; i--){
        //     // si lo puedo mover a una posciion perdedoras
        //     if( cnt_perdedoras > 0 ) posiciones[i] = 1;
        //     else posiciones[i] = 0;
            
            
        //     if( posiciones[i] == 0 ) cnt_perdedoras++;
        //     if(  i+ k < n  && posiciones[i+k] == 0 ) cnt_perdedoras--;

        // }
        // print(n); print(k);
        // print(posiciones);


        // imrpimiendo el patron podemos ver que 
        // las ppsicines perdedoras son
        // las congruentes con 1 mod k+1
        // esto lo podemos verificar en O(1)

        // la posicion n enreliad es con idx 1
        // la posicion n-1 le queda idx 2
        // ... 
        // la posocion 2 le queda idx n-1
        // la posicion 1 le queda idx n

        // queremos saber si la posicion 1 ocn idx n es ganadora

        // si comienzo en  una posicion ganadora
        // y tengo almenos la misma cantidad de comodines que el
        if(  ( n% (k+1) != 0 )  && (p>=q)   ){
            cout << "YES\n";
            continue;
        }
        // si empeizo en una posicion perdedora
        // pero tengo mas comodines que el
        if(  ( n% (k+1) == 0 )  && (p>q)   ){
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }

    
}
/*
    
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    15. Find Number Of Pair of Friends
    https://www.spoj.com/problems/IITKWPCH/
    IITKWPCH - Find Number Of Pair of Friends

*/

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;



// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
//  S_i = {(x,y) :  x y y comparten digito i } 

//S_i \cap S_j \cap ... \cap S_k  = = {(x,y) :  x y y comparten digito i, j, .., k } 

// Calcula  el tam de |S_i \cap S_j \cap ... \cap s_k | 
// en mask estan encendidos los bits i,j,..,k que se usan
template <typename T>
ll combinaIntersecciones (ll n, int m, int mask, T* arr) {
    // toma los valores que esten encendidos
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        // .. 
    }}
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    ll ans = 0;
    // ...
    return ans;
}

// S_i = { (x,y) :  x y y comparten digito i  }
// Calcula  | UNION_{i=0}^M S_i |
template <typename T>
ll PIE(ll N, int M, T* arr) { // M = | arr | 
    ll total = 0;
    int limit = (1 << M);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(N,M, mask, arr);
        // si cantidad de bits encendido es Impar: suma si es Par es resta
        if( __builtin_popcount(mask) & 1 ) total += value;
        else  total -= value;
    }
    return total;
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    #ifdef LOCALp
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin >> t;

    while( t-- ){
        int n; cin >> n;
        int numeros[n];
        for(int i=0; i<n; i++) cin >> numeros[i];

        int cnt_digitos[2 << 10 ];

        for( int i=0 )
    }


}
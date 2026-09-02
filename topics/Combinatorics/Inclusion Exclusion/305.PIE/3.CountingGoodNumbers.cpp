/*
    https://codeforces.com/contest/2125/problem/C
    C. Count Good Numbers
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez
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

bool debug =  false;
#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
//  S_i = { x :  arr[i], x, b satisfacen algo } 
// por ejemplo S_i = { x :  arr[i] | x y  x <= n  } 
// Calcula  el tam de |S_i \cap S_j \cap ... \cap s_k | 
// en mask estan encendidos los bits i,j,..,k que se usan
template <typename T>
ll combinaIntersecciones (ll l, ll r, int m, int mask, T* arr) {
    ll mcm = 1;
    // toma los valores que esten encendidos
    DEBUG cout << "conjuntos a intersectar " << bitset<8>(mask) << ' ';
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        mcm *= arr[i];
        DEBUG cout << arr[i] << ' ';
    }}
   
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    // numeros divisibles por mcm en l r
    ll ans = r/mcm - (l-1)/mcm;
    DEBUG cout << "\n tam:" << ans << '\n';
    return ans;
}

// S_i = { n :  arr[i] y n satisfacen algo }
// Calcula  | UNION_{i=0}^M S_i |
template <typename T>
ll PIE(ll l, ll r, int M, T* arr) { // M = | arr | 
    ll total = 0;
    int limit = (1 << M);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(l, r ,M, mask, arr);
        // si cantidad de bits encendido es Impar: suma si es Par es resta
        if( __builtin_popcount(mask) & 1 ) total += value;
        else total -= value;
    }
    return total;
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ifstream cin("in.txt");

    int t; cin >> t;

    while( t-- ){
        ll l,r; cin >> l >> r;
        int m = 4;
        int arr[m] = { 2,3,5,7 };
        ll ans = r-l+1 - PIE(l,r, m, arr );

        DEBUG cout <<  PIE(l,r, m, arr ) << '\n';
        cout << ans << '\n';
    }
}
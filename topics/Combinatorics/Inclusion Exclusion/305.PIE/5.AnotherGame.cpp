/*
    https://www.spoj.com/problems/NGM2/
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

bool debug =  true;
#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

ll mygcd(ll a, ll b) {
    while( b ){
        a %= b;
        swap(a, b);
    }
    return a;
}

ll mylcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return( a / mygcd(a, b)) * b; 
}
//  S_i = { x :  arr[i], x, b satisfacen algo } 
// por ejemplo S_i = { x :  arr[i] | x y  x <= n  } 
// Calcula  el tam de |S_i \cap S_j \cap ... \cap s_k | 
// en mask estan encendidos los bits i,j,..,k que se usan
template <typename T>
ll combinaIntersecciones (ll n, int m, int mask, T* arr) {
    // toma los valores que esten encendidos
    ll mcm = 1;
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        mcm = mylcm( mcm, arr[i]);
        if(  mcm > n )  return 0;
    }}
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    ll ans = n/ mcm; // cantidad de numeros que son diviibles por mcm
    // ...
    return ans;
}

// S_i = { n :  arr[i] y n satisfacen algo }
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ifstream cin("in.txt");

    ll n; int k; cin >> n >> k;
    ll a[k]; for( ll & x : a ) cin >> x;

    ll multiplosDeTodos = PIE(n,k, a);
    cout << n - multiplosDeTodos << '\n';
}
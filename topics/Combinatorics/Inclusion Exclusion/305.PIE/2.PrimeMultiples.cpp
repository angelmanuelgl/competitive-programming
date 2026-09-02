/*
    
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
ll combinaIntersecciones (ll n, int m, int mask, ll* arr) {
    DEBUG cout << bitset<8>(mask) << '\n';
    DEBUG cout << " primos: ";
    ll mcm = 1;
    // toma los valores que esten encendidos
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        if(  arr[i] > n/mcm  ) return 0;
        mcm *= arr[i];
        DEBUG cout << arr[i] << ' ';
    }
    }
    DEBUG cout << '\n';
    DEBUG cout << " tam = " <<  n/ mcm << '\n';
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    ll ans = n / mcm;
    return ans;
};

// S_i = { n :  arr[i] y n satisfacen algo }
// Calcula  | UNION_{i=0}^M S_i |
template <typename T>
ll PIE(ll N, int M, T* arr) { // M = | arr | 
    ll total = 0;
    int limit = (1 << M);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(N,M, mask, arr);

        // si cantidad de bits encendido es Impar: suma 
        if( __builtin_popcount(mask) & 1 ){
            total += value;
        }else { // Par: resta
            total -= value;
        }
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

    ll n; cin >> n; 
    int k; cin >> k;
    ll arr[k];
    for(ll & x : arr) cin >> x;
    ll ans = PIE(n,k,arr);
    cout <<  ans << '\n';

}
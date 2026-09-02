/*
    http://acm.hdu.edu.cn/showproblem.php?pid=4135
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list    	
8. Co-prime
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
ll combinaIntersecciones (ll l,ll r, int m, int mask,vector<ll> arr) {
    // toma los valores que esten encendidos
    ll mcm = 1;
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        mcm = mylcm( mcm, arr[i]);
        if(  mcm > r )  return 0;
    }}
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    ll ans = r/ mcm - (l-1)/mcm ; // cantidad de numeros que son diviibles por mcm
    // ...
    return ans;
}

// S_i = { n :  arr[i] y n satisfacen algo }
// Calcula  | UNION_{i=0}^M S_i |
ll PIE(ll l, ll  r, int M, vector<ll> arr) { // M = | arr | 
    ll total = 0;
    int limit = (1 << M);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(l,r,M, mask, arr);
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

    ifstream cin("in.txt");
    int t; cin >> t;


    for( int c = 1; c <= t ; c++){
        ll l,r; cin >> l >> r;
        ll n; cin >> n;
       
        // tomar los primos que dividen a n
        vector<ll> divisoresPrimos;
        for( int i=2; i<= sqrt(n); i++){
            if( n%i == 0){
                divisoresPrimos.pb(i);
                while( n%i == 0 ) n/=i;
            }
        }
        if( n>1 ) divisoresPrimos.pb(n);

        int m = divisoresPrimos.size();

        ll numerosConPrimosEnComun = PIE( l, r, m , divisoresPrimos);
        ll primosRelativos= r - l  + 1 -numerosConPrimosEnComun;

        cout <<  "Case #" << c << ": " <<  primosRelativos << '\n';

    }
}
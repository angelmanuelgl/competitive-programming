/*
    https://atcoder.jp/contests/abc246/tasks/abc246_f
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

const int MOD = 998244353;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
//  S_i = { x :  arr[i], x, b satisfacen algo } 
// por ejemplo S_i = { x :  arr[i] | x y  x <= n  } 
// Calcula  el tam de |S_i \cap S_j \cap ... \cap s_k | 
// en mask estan encendidos los bits i,j,..,k que se usan

ll exp_bin(ll base, ll exp){
    if( !base) return base;
    ll res = 1;
    while( exp > 0 ){
        if( exp &  1 ) res = (res*base)%MOD;
        base = (base*base) %MOD;
        exp >>=1;
    }
    return res;
}


ll combinaIntersecciones (ll n, int m, int mask, vector<string> arr) {
    DEBUG cout <<   bitset<16>(mask) << '\n';
    // toma los valores que esten encendidos
    int cnt_letras[ 'z' - 'a'  +1 ];
    for( int & x : cnt_letras ) x =0;

    int cntStrings= 0;
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        for( char c : arr[i] ) cnt_letras[c - 'a']++;
        cntStrings++;
    }}
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    int cantdadLetras_eninterseccionString= 0;
    for( int  x : cnt_letras ){
        DEBUG cout << x << ' ';
        if( x == cntStrings ){
            DEBUG cout << x << ' ';
            cantdadLetras_eninterseccionString++;
        }
    } DEBUG cout << '\n';

    ll ans = exp_bin(cantdadLetras_eninterseccionString, n );
    // ...

    DEBUG cout << "cntStrings " << cntStrings;
    DEBUG cout << "   cantdadLetras_eninterseccionString " << cantdadLetras_eninterseccionString;
    DEBUG cout << "   ans " << ans << '\n';
    return ans;
}

// S_i = { n :  arr[i] y n satisfacen algo }
// Calcula  | UNION_{i=0}^M S_i |
ll PIE(ll N, int M, vector<string> arr) { // M = | arr | 
    ll total = 0;
    int limit = (1 << M);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(N,M, mask, arr);
        // si cantidad de bits encendido es Impar: suma si es Par es resta
        if( __builtin_popcount(mask) & 1 ) total = (total+value)%MOD;
        else  total =  (total - value +MOD ) %MOD;
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

    int n; ll l;
    cin >> n >>l;

    vector<string> arr(n);
    for( string & x : arr) cin >> x;

    ll ans = PIE(l, n, arr );
    cout <<  ans << '\n';
}
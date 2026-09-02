/*
    11806 - Cheerleaders // onlinejudge.org
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

const int MOD = 1000007;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
const int MAX = 400; // Suficiente para una cuadrícula de 20x20
long long C[MAX + 1][MAX + 1];

void binomios(){
    for( int i = 0; i <= MAX; i++) {//  siempre es 1
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}
ll binomio_n_k( int n, int k){
    if (k < 0 || k > n) return 0;
    return C[n][k];
}
//  S_0 = la fila superior vacia
//  S_1 = la fila inferior vacia
//  S_2 = la columna izquierda vacia
//  S_4 = la columna derecha vacia
int combinaIntersecciones (int n, int m, int k, int mask) {

    // si solo hay uno
    if( __builtin_popcount(mask) == 1 ){
        // si es fila
        if( (mask & 1) || (mask & 2) ) return (n-1)*m;
        // si es columna
        if( (mask & 4) || (mask & 8) ) return n*(m-1);
    }
    // si no ocupo dos lados
    if( __builtin_popcount(mask) == 2 ){
        // si ambos son filas
        if( (mask & 1) && (mask & 2) ) return (n-2)*m;
        // si ambas columna
        if( (mask & 4) && (mask & 8) ) return n*(m-2);
        // entonces debe ser una fila y una columna
        return (n-1)*(m-1);
    }
    // si no ocupo tres lados
    if( __builtin_popcount(mask) == 3 ){
        // si el unico aldo si ocupo  es una  fila
        if( !(mask & 1) || !(mask & 2) ) return (n-1)*(m-2);
        // si el unico aldo si ocupo  es unacolumna
        if( !(mask & 4) || !(mask & 8) ) return (n-2)*(m-1);
    }
    // si no ocupo las 4 arillas
    if( __builtin_popcount(mask) == 4 ){
        return (m-2)*(n-2);
    }
}

// S_i = { n :  arr[i] y n satisfacen algo }
// Calcula  | UNION_{i=0}^M S_i |
ll PIE(int n, int m, int k, int N) { // M = | arr | 
    ll total = 0;
    int limit = (1 << N);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(n,m, k, mask);
        // DEBUG cout << bitset<8>(mask) << " " << value << " " <<  binomio_n_k(value, k) << '\n';
        value = binomio_n_k(value, k);
        // si cantidad de bits encendido es Impar: suma si es Par es resta
        if( __builtin_popcount(mask) & 1 ) total = (total + value) %MOD;
        else total =  (total - value + MOD) %MOD;
    }
    return total;
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    binomios();

    // ifstream cin("in.txt");

    int t; cin >>  t;
    for( int caso = 1; caso <= t; caso++){
        int l,r,k; cin >> l >> r >> k; 
        if( k > l*r){
            cout <<  "Case " << caso << ": 0\n";
            continue;
        }
        ll xd = PIE(l,r, k, 4);
        ll ans = binomio_n_k(l*r, k ) - xd;
        ans = (ans + MOD)%MOD;
        cout << "Case " << caso << ": " << ans << '\n';
        // cout << "caso " << caso << ": " << binomio_n_k(l*r, k ) << '\n';
        // cout << "caso " << caso << ": " << xd << '\n';
    }

}
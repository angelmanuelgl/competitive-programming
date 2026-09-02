/*
    10325 - The Lottery   /// onlinejudge.org
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez
    lo quize hacer general pero talvez fue medio mamada xd
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

// Calcula  | UNION S_m |
template <typename T, typename F>
long long PIE(int M, T* data, F combinaIntersecciones) { // M = | data | 
    long long total = 0;
    int limit = (1 << M);

    for (int mask = 1; mask < limit; ++mask) {       
        long long value = combinaIntersecciones(M, mask, data);

        // bits encendidaos  Impar: suma //
        if( __builtin_popcount(mask) & 1 ){
            total += value;
        }else { // Par: resta
            total -= value;
        }
    }
    return total;
}

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

// Calcula  |S_i \cap S_j \cap ... \cap s_k | 
// en mask van que i,j,..,k se usan
// S_i = { n :  arr[i] | n }
ll intersecciones (int m, int mask, ll* arr) {
    ll minimoComunMultiplo = 1;

    // toma los valores que esten encendidos
    for( int i=0; i<m; i++){
    if( mask & (1 << i) ){ // el bit i esta encendido    
        minimoComunMultiplo = mylcm( minimoComunMultiplo, arr[i]);
        if( minimoComunMultiplo > n ) return 0;
    }
    }
    return n / minimoComunMultiplo;
};



// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    // ifstream cin("in.txt");


    int m;
    while( cin >> n >> m ){
        ll arr[m];
        for( ll & x: arr ) cin >> x;
    
        ll ans = PIE(m, arr, intersecciones);
        cout << n- ans << '\n';
    }
}
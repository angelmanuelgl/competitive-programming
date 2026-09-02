/*  
    Inclusion and Exclusion // 307. Inclusion Exclusion on Multiples
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez
    3. 
    https://cses.fi/problemset/task/3161
    

    1. ->  cantidad de parejas que tienen gcd = k (para caulqueir k, solo rpeguntaba k=1)
    3. -> cantidad de subconjutnos que tienen gcd = k
    
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

const int m = 1e6 + 5;
int frec[m] = { }; 
int mult[m] = {}; 
ll parejas[m] = {};
ll dp[m] = {};


ll exp_bin(ll base, ll exp){
    ll res = 1;
    while( exp> 0){
        if( exp & 1) res = (res*base) %MOD;
        base = (base*base) %MOD;
        exp >>= 1;
    }
    return res;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // ifstream cin("in.txt");

    int n; cin >> n;
    int arr[n];

    // frecuencias de []
    for( int  x : arr ){
        cin >> x;
        frec[x]++;
    } 

    // cantidad de multiplos de []
    // como la criba nlog n
    for( int d=1; d<m; d++){
        for( int multiplo = d; multiplo < m ; multiplo +=d ){
            mult[d] += frec[multiplo];
            mult[d] %=MOD;
        }
    }

    // parejas de numeros que son divisoress entre []
    // cantidad de parejas tales que [] divide a su gcd
    for( int d=1; d<m; d++){
        ll ans = exp_bin( 2, mult[d] ) -1;
        ans =  (ans +MOD)%MOD;
        
        parejas[d] = ans ;

    }

    // cantidad de parejas tales que [] es su gcd

    for( int d=m-1; d >=1; d--){
        dp[d] = parejas[d];
         for( int multiplo = d*2; multiplo < m ; multiplo +=d ){
            dp[d] -= dp[ multiplo ];
            dp[d] = (dp[d] +MOD ) %MOD;
        }
    }

    for( int i=1; i<=n; i++)
        cout << dp[i] << " \n"[i==n];
    

}
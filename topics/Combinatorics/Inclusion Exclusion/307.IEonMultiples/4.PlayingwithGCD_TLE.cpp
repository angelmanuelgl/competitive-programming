/*  
    Inclusion and Exclusion // 307. Inclusion Exclusion on Multiples
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    
    1. ->  cantidad de parejas que tienen gcd = 1 
    4. -> cantidad de parejas que tienen gcd = 1 (solo varios T casos) *y enrealdiad preguntas gcd \neq 1)

    pero el 1 er para una lista, este es para un rango [1,N]

    / / USAR LA MISMA IDEA DA TLE
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

const int m = 1e5 + 5;
ll parejas[m] = {};
ll dp[m] = {};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // ifstream cin("in.txt");

    int t; cin >> t ;
    int caso =0;

    while( ++caso <= t ){

    int n; cin >> n;
    int arr[n];

    // frecuencias de 

    // cantidad de multiplos de []  piso( n/[])

    // parejas de numeros que son divisoress entre []
    // cantidad de parejas tales que [] divide a su gcd

    for( int d=1; d<=n; d++){
        parejas[d] = 1ll * (n/d) * (n/d -1) /2; // parejas (x,y) = (y,x) la misma
        parejas[d] += 1ll * (n/d) ; // parejas (x,x)
    }

    // cantidad de parejas tales que [] es su gcd
    // cantidad de parejas tales que su gcd es []
    for( int d=n; d >=1; d--){
        dp[d] = parejas[d];
         for( int multiplo = d*2; multiplo < m ; multiplo +=d ){
            dp[d] -= dp[ multiplo ];
        }
    }

    
    ll total = 1ll*n*(n-1)/2 + n;
    ll ans = total- dp[1];
    cout << "Case " << caso << ": " << ans << '\n';

    }

}
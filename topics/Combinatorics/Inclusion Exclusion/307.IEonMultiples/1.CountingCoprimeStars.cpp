/*  
    Inclusion and Exclusion // 307. Inclusion Exclusion on Multiples
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    https://cses.fi/problemset/task/2417
    dado una lista de n nuero positvos 
    contar el numero de parjeas que son coprimos 

    
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
int frec[m] = {}; 
int mult[m] = {}; 
ll parejas[m] = {};
ll dp[m] = {};

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
        }
    }

    // parejas de numeros que son divisoress entre []
    // cantidad de parejas tales que [] divide a su gcd

    for( int d=1; d<m; d++){
        parejas[d] = 1ll * mult[d] * (mult[d]-1) / 2;
    }

    // cantidad de parejas tales que [] es su gcd

    for( int d=m-1; d >=1; d--){
        dp[d] = parejas[d];
         for( int multiplo = d*2; multiplo < m ; multiplo +=d ){
            dp[d] -= dp[ multiplo ];
        }
    }

    cout << dp[1] << '\n';
    

}
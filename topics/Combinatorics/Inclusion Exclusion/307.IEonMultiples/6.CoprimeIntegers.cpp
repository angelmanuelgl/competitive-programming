/*  
    
    Inclusion and Exclusion // 307. Inclusion Exclusion on Multiples
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


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

const int MAXV = 1e7+2;
// const int MAXV = 200;
ll parejas[MAXV];
ll dp[MAXV];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int a,b,x,y; cin >> a >> b >> x >> y;
    a--; x--;
    // pareajs[d] = parejas de (n,m) que ambos sin divisibles entre d
    //            = parejas de (n,m) tq d | gcd(n,m)
    for( int d=1; d<MAXV; d++ ){
        int multiplos_1 = b/d - a/d; // multplos de d en [a,b]
        int multiplos_2 = y/d - x/d; // multplos de d en [x,y]
        parejas[d] = 1ll * multiplos_1 * multiplos_2;
        DEBUG cout << d << ' ' << parejas[d] << '\n';
    }

    // dp[d] = parejas de (n,m) tal que d = gcd(n,m)
    for( int d=MAXV-1; d>=1; d--){
        dp[d] = parejas[d];
        for( int multiplo = d*2; multiplo<MAXV; multiplo+=d){
            dp[d] -= dp[multiplo];
        }
    }
    
    cout << dp[1] << '\n';
}
/*
    https://codeforces.com/problemset/problem/888/D
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

int MOD = 1e9 + 7;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

ll exp_bin(ll base, ll exp){
    ll res = 1;
    while( exp > 0 ){
        if( exp &1 ) res = (res*base) %MOD;
        base = ( base*base ) %MOD;
        exp >>= 1;
    }
    return res;
}

const int MAXN = 5;
ll fact[ 5 ] = { 1, 1, 2, 6, 24};
ll subfact[ 5 ] = { 1, 0 , 1, 2, 9 };



ll nCk( int n, int k ){ // modificado
    if( k <0 || k > n ) return 0;
    ll ans = 1;
    for( int i= 0 ; i< k; i++) ans *= (n-i);
    return ans/ fact[k];
}

ll Dnk( int n, int k ){
    // Dbk is the number of permutations of { 1, ..., n } that have exactly k fixed points.
    return nCk(n, n-k) * subfact[n-k];
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    
    int n,k; cin >> n >> k ;
    
    ll ans = 0;
    for( int i=0; i<=k ; i++ ){
        ans += Dnk(n,n-i);
    }


    cout << ans <<  '\n';

}
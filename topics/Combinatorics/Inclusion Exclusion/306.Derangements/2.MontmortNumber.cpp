/*
    https://judge.yosupo.jp/problem/montmort_number_mod
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

const int MAXN = 1e6;
ll fact[MAXN + 1], invfact[MAXN + 1],subfact[MAXN+1];

void factoriales(){
    // subfactoriales !n
    subfact[0] = 1, subfact[1] = 0; 
    for( int i = 2; i <= MAXN; i++ ){
        subfact[i] = (i - 1) * (subfact[i-1] + subfact[i-2]) % MOD;
    }
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n,m; cin >> n >> m;
    MOD = m;
    factoriales();
    
   for( int i=1; i<=n; i++ ){
        cout << subfact[i] << " \n"[ i == n ];
   }



}
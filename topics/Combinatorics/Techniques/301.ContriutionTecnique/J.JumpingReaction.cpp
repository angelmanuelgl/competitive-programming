/*
   https://codeforces.com/gym/104375/problem/J
    topic-list/contribution_technique   6. J. Jumping Reaction
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

const int inv2 = 500000004;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ifstream cin("in.txt");
    
    int n,q; cin >> n >> q;

    ll sum_prefijo[n+1], sum_cuadrado_prefijo[n+1];
    sum_prefijo[0] = sum_cuadrado_prefijo[0] = 0;

    for( int i=1; i<=n; i++){
        ll tmp; cin >> tmp;
        sum_prefijo[i] = (sum_prefijo[i-1] + tmp)%MOD;
        tmp = (tmp*tmp)%MOD;
        sum_cuadrado_prefijo[i] = (sum_cuadrado_prefijo[i-1] + tmp)%MOD;
    }
    DEBUG{
        cout << " sum_prefijo : ";
        for(ll x :sum_prefijo) cout << x << ' '; cout <<'\n';

        cout << " sum_cuadrado_prefijo : ";
        for(ll x :sum_cuadrado_prefijo) cout << x << ' '; cout <<'\n';
    }
    while(q--){
        int l,r; cin >>  l >> r;
        ll sumaDeCuadrados = sum_cuadrado_prefijo[r] - sum_cuadrado_prefijo[l-1];
        sumaDeCuadrados = (sumaDeCuadrados+MOD) %MOD;
        ll cuadradoDeLaSuma = sum_prefijo[r] - sum_prefijo[l-1];
        cuadradoDeLaSuma = (cuadradoDeLaSuma+MOD) %MOD;
        cuadradoDeLaSuma = (cuadradoDeLaSuma*cuadradoDeLaSuma) %MOD;
        

        // cuadradoDeLaSuma =  sumaDeCuadrados + 2*ans
        ll ans = (cuadradoDeLaSuma - sumaDeCuadrados +MOD) %MOD;
        ans = ans * inv2 % MOD;

        cout << ans << '\n';
    }
}
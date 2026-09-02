/*
    https://codeforces.com/gym/105884/problem/J  
    J. LCM Factorization
    topic-list/contribution_technique   5. LCM Factorization
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

void criba( int n, vi &primos){
    primos.clear();
    if( n < 2 ) return;
    vector<bool> no_primo(n+1);
    no_primo[0] = no_primo[1] = true;
    
    for( ll i=3; i*i<=n; i+=2){
        if( no_primo[i] ) continue;
        for(ll j=i*i; j<=n; j+=2*i){
            no_primo[j] = true;
        }
    }

    primos.pb(2);
    for( int i=3; i<=n; i+=2)
        if( !no_primo[i] ) primos.pb(i);

}
ll exp_bin(ll base, ll exp) {
    ll res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
const int MAXN = 1e6;
ll fact[MAXN + 1], invfact[MAXN + 1];

void factoriales() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) fact[i] = (fact[i-1] * i) % MOD;

    invfact[MAXN] = exp_bin(fact[MAXN], MOD - 2); // inverso usando Fermat
    for (int i = MAXN - 1; i >= 0; i--) invfact[i] = (invfact[i+1] * (i+1)) % MOD;
}


ll binomio_n_k(int n, int k) {
    if ( k < 0 || k > n ) return 0;
    return (((fact[n] * invfact[k]) % MOD) * invfact[n - k]) % MOD;
}



// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    factoriales();
    vi primos; 
    criba(MAXN, primos);

    // ifstream cin("in.txt");

    int t; cin >> t;
    for( int i=1; i<=t; i++){
        int n,k; cin >> n >> k;
        int arr[n];
        for( int &x : arr ) cin >> x;

       
        ll ans = 0;
        for( int p: primos ){
            DEBUG cout << "Primo :" << p << "\n";
            ll m = 0; // cantidad de no numeros que no son divididos por p
            for( int x : arr){
                if( x % p != 0 ) m++;
            }
            DEBUG cout << " no aparece :" << m << "\n";
            DEBUG cout << " si aparece :" << n-m << "\n";

            // cantidad de  subconjuntosConAlgunElementoDivisiblePorP
            ll cnt = binomio_n_k( n, k) - binomio_n_k( m, k);
            cnt = (cnt+MOD)%MOD;

            ll contribution = p*cnt %MOD;
            ans  = ( ans + contribution ) %MOD;
        }
        cout <<  ans << '\n';
        



    }

}
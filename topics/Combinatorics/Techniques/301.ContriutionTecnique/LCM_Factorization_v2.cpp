/*
    https://codeforces.com/gym/105884/problem/J  
    J. LCM Factorization
    topic-list/contribution_technique   5. LCM Factorization
    Angel Manuel Gonzalez Lopez
    esta version si paso en tiempo, la anterior no
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

void criba_lineal( int n, vi & primos, vi &lp){
    if( n<2 ) return;
    for( ll i=2; i<=n; i++){
        if(!lp[i]) primos.pb( lp[i]=i );
        for( int j=0; i*primos[j] <= n; j++ ){
            lp[ i * primos[j] ] = primos[j];
            if( primos[j] == lp[i] ) break;
        }
    }
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
const int MAXN = 300100;
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
    vi lp(MAXN+1); 
    criba_lineal(MAXN, primos, lp);

    // DEBUG{
    //     for( int x: primos ) cout << x << ' '; cout <<'\n';
    //     for( int i=0; i<80; i++) cout << " num " << i << "  lp = " << lp[i] << '\n';
    // }
    // ifstream cin("in.txt");

    int vecesQueParece[MAXN];
        
    int t; cin >> t;
    for( int i=1; i<=t; i++){
        int n,k; cin >> n >> k;
        int arr[n];
        for( int &x : arr ) cin >> x;

        vi primosUsados;
        // para cada primo, calcular cuantos numeros que son divisibles por ese primo
        memset(vecesQueParece, 0, sizeof(vecesQueParece));
        for( int i=0; i<n; i++){
            int tmp = arr[i];
            while( tmp > 1){
                int p = lp[tmp];
                if( vecesQuePar3ece[ p   ] == 0 ) primosUsados.pb(p);
                vecesQueParece[ p   ]++;
                while( tmp %p == 0) tmp/= p;
               
            }
        }
    
        // hacer la suma
        ll ans = 0;
        for( int p: primosUsados ){
           // cantidad de numeros que no son divisilbes por p
            ll m = n - vecesQueParece[p]; 
            // cantidad de  subconjuntosConAlgunElementoDivisiblePorP
            ll cnt = binomio_n_k( n, k) - binomio_n_k( m, k);
            cnt = (cnt+MOD)%MOD;

            ll tmp = p*cnt %MOD;
            ans  = ( ans + tmp ) %MOD;
        }
        cout <<  ans << '\n';
        
    }
    
}
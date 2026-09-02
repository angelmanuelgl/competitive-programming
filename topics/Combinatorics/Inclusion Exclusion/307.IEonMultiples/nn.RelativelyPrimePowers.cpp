/*  
    https://codeforces.com/contest/1036/problem/F
    Inclusion and Exclusion // 307. Inclusion Exclusion on Multiples
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    no e sun problema, venia como sugerencia en el blog de codefroces que topic-list ponia como recursos

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
const ll MAXN = 1e18+100;

// busqueda bianria odificada 
// regresa    base ^ exp > n
ll f(  ll base, ll exp, ll n){

    ll res =1;
    while( exp > 0){
        if( exp & 1 ){
            if( res > n ) return true;
            if( base > n) return true;
            
            //! ver si podemos hacer res*base
            // ver si se pasa de n
            // if( res* base > n ) return true;
            if( res > n / base ) return true;  // <<<<======hacer muchas cuentiras para ver que en efecto es  equivalente la comprovacion a res*base > n
            // hacemos la comprobacion antes por si esto se desoroda
            res *= base; // ahora esto es menor igual que n
            
        }
        //! ver si podemos hacer base * base
        if( base > n/ base ){
            // si la base se pasa de n, le podemos poner n+1
            // asi si se vuleve a multiplciar res *= base 
            // se verificara antes is res o base > n y regresan true
            base = n+1;
        }
        else   base *= base;

        exp >>= 1;
    }
    //return res;
    return res > n ;
}

// regresa la cantidad de d-potencias perfectoas menoresIguakles que n
// regresa  el ultimo elemento x tal que x^d <= n
ll binarySearch( ll d, ll n ){
    ll l=0, r = 1;
    
    while( !f(r,  d,n)  ) r*=2;

    while( l+1 < r ){
        ll mid = (l+r)/2;
        
        if( f(mid,  d,n) ) r = mid;
        else  l = mid;
    }

    return l; /// ultimo indice donde f(i) = 0;

}

ll potenciasPerfectas( ll d, ll n){
    if( d== 1) return n;
    if( d== 2) return sqrt(n);
    return binarySearch(d,n);
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);



    // ifstream cin("in.txt");
    int t; cin >> t;
    

    while( t-- ){
        ll n; cin >> n;

        const int  maxd= 60;  // porque 2^60 ya e pasa
        ll dp[maxd+1];
        // por ahora
        // dp[d] = max x tal que x^d <= n
        //       = cantidad de d-potenciasperfectoas menores que d
        //       = numeros tales que gcd( exponenetes en descomposicion en primos) es divisible por d
        
  
        
        for( int d=1; d < maxd; d++ ){
            // cantidd de d-potencias perfectos entre [2,n]
            ll sqrt_d_n = potenciasPerfectas(d, n) -1;
            // cout << "dp[ " << d << " ] = " << sqrt_d_n << "\n";
            dp[d] = sqrt_d_n;
        }

        // se compondra para contar 
        // <--- dp[d] = cantidad de numeros 'd-elegantes' 
        // nota d-elegantes := numeros tales que gcd( exponenetes en descomposicion en primos) = d
        for( int d=maxd-1; d>=1; d--){
            for( int i=2; i*d< maxd; i++){
                dp[d] -= dp[i*d];
            }
        }
        cout << dp[1] << '\n';
    }

}   
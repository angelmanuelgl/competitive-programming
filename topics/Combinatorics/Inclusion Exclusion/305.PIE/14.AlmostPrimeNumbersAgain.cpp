/*
    
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    https://www.spoj.com/problems/KPRIMESB/
    14. Almost Prime Numbers Again
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

#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;



// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

ll mygcd(ll a, ll b) {
    while( b ){
        a %= b;
        swap(a, b);
    }
    return a;
}

ll mylcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return( a / mygcd(a, b)) * b; 
}

//  S_i = { x :  arr[i], x, b satisfacen algo } 
// por ejemplo S_i = { x :  arr[i] | x y  x <= n  } 
// Calcula  el tam de |S_i \cap S_j \cap ... \cap s_k | 
// en mask estan encendidos los bits i,j,..,k que se usan
ll combinaIntersecciones (ll n, int m, int mask, ll* arr) {
    ll mcm = 1;
    // toma los valores que esten encendidos
    for( int i=0; i<m; i++){
    if(  mask & (1 << i) ){
        mcm = mylcm(mcm, arr[i]);
        
        // n/mcm = 0 si 
        if( mcm > n )
            return 0; 
        // .. 
    }}
    // calcula |S_i \cap S_j \cap ... \cap s_k | 
    ll ans = n / mcm;
    // ...
    return ans;
}

// S_i = { n :  arr[i] y n satisfacen algo }
// Calcula  | UNION_{i=0}^M S_i |
ll PIE(ll N, int M, ll* arr) { // M = | arr | 
    ll total = 0;
    int limit = (1 << M);
    for (int mask = 1; mask < limit; ++mask) {       
        ll value = combinaIntersecciones(N,M, mask, arr);
        // si cantidad de bits encendido es Impar: suma si es Par es resta
        if( __builtin_popcount(mask) & 1 ) total += value;
        else  total -= value;
    }
    return total;
}


void criba_lineal_mobius(int n, vi &primos) {
    vi lp(n + 1);
    // mu.assign(n + 1, 0); //
    // mu[1] = 1;          //

    for( ll i = 2; i <= n; ++i ){

        // si no hay primo que lo divida es primo
        if( !lp[i] ){
            primos.pb( lp[i] = i );
            // mu[i] = -1;  //
        }
        
        for( int j = 0; i * primos[j] <= n; ++j ){
            lp[i * primos[j]] = primos[j];
            
            // i * p_j tiene un primo repetido 
            // porque el menor primo que divide a i lp[i] es p_j
            if( primos[j] == lp[i] ){
                // mu[i * primos[j]] = 0; // 
                break;
            }
            // primos distitnos : alternar -1 +1 -1 
            else{
                // mu[i * primos[j]] = -mu[i]; //
            }
        }
    }
}


ll cuantosPrimosMenoresIgualesX(int x, vi &primos) {
    // tomamos el primer mayor estricto que x
    auto it = upper_bound( primos.begin(), primos.end(), x);


    //      [                                         ]
    //        menorIgual  menorIgual  ...  menorIgual   mayorEstricto ...
    //         .begin()               ...               it
    return  it - primos.begin();
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    #ifdef LOCALp
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    
    vi vectorPrimos;
    int MAXN = 1e6+5;
    criba_lineal_mobius(MAXN, vectorPrimos);
    int primos = vectorPrimos.size();
    
    DEBUG{
        for(  int i=0; i<20; i++){
            cout << "p_" << i << "  = " << vectorPrimos[i] << "\n";
        }
        cout <<"\n";
        for(  int i=0; i<49; i++){
            cout << "cuantosPrimosMenores a " << i << " : " <<  cuantosPrimosMenoresIgualesX( i, vectorPrimos) << "\n";
        }

        cout << "\n";
        cout << "\n";
    }

    int t; cin >> t;
    int caso = 1;
    while( caso <= t ){
        ll n; int k; 
        cin >> n >> k;
        ll conjuntoDePrimos[k];
        ll primosDelConjuntoMenoresN = 0;
        for(int i=0; i<k; i++){
            cin >> conjuntoDePrimos[i];
            if( conjuntoDePrimos[i] <= n ) primosDelConjuntoMenoresN++;
        } 

        if( n <= 3){
            cout << "Case " << caso << ": " << 0 << "\n";
            caso++;
            continue;
        }

        ll siMultiplos = PIE(n, k, conjuntoDePrimos);
        ll noMultiplos = n - siMultiplos;
        
   

        ll primos = cuantosPrimosMenoresIgualesX(n, vectorPrimos);
        
        ll primosRepetidos = primos - primosDelConjuntoMenoresN ;

        // los numeros que no son primos 
        // y no son multiplos de los primos del conjunto
        ll noPrimosNoMultiplos = noMultiplos - primosRepetidos;
        
        // los numeros que no son primos ni 1 (Es decir son compuestos) 
        // y no son multiplos de los primos del conjunto
        ll siCompuestosNoMultiplos = noPrimosNoMultiplos - 1; 

        DEBUG{
            cout << "n: " << n << " k: " << k << "\n";
            cout << "primosDelConjuntoMenoresN: " << primosDelConjuntoMenoresN << "\n";
            cout << "siMultiplos: " << siMultiplos << "\n";
            cout << "noMultiplos: " << noMultiplos << "\n";
            cout << "primos: " << primos << "\n";
            cout << "primosRepetidos: " << primosRepetidos << "\n";
            cout << "noPrimosNoMultiplos: " << noPrimosNoMultiplos << "\n";
            cout << "siCompuestosNoMultiplos: " << siCompuestosNoMultiplos << "\n";
        }


        cout << "Case " << caso << ": " << siCompuestosNoMultiplos << "\n";
        caso++;

        DEBUG cout << "\n\n";
    }

}
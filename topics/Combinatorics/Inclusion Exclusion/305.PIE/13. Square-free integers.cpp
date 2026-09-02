/*
    
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez


    13. Square-free integers
    https://www.spoj.com/problems/SQFREE/

*/
/*
    / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
    CON PIE

    queremos contar la cantidade de numeros menores a n tales que
    son square- free := "ningun cuadrado excepto 1 los divide"
                     == "en su descomposicion de primos ninguno tiene potencia mayor igual 2"
                     == "es producto de k primos diferentes"

    el complemeto es = "algun cuadrado perfecto los divide"
                    == "existe p^2 que los divide"
                    == "son multuplos de {2^2,3^3,5^2, 7^2, ....}"
    
    queremos ccontar los multiplos menores a n de esos numeros 

    S : =  {2^2,3^3,5^2, 7^2, ...., p_k^2}
    
    p_k = max primo tal que p_k^2 <= n
        =  max primo tal que p_k <= sqrt(n)

    |S| = pi(sqrt(n))  
    dode pi(x) = cantidad de primos menores o iguales a x

    
    |S| aprox sqrt(n)/log(sqrt(n)) = 10^7/(7*3) = 10^6

    / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
    no pude hacerlo con PIE puro, hagamos mobius
    sea 
    A_d := { x : x <= n, d^2 | x no hay k > d con k^2 | x}
    B_d := { x : x <= n, d^2 | x }

    Notemos que
    B_d = \bigcup_{k multiplo de d} A_d  (<---- VER A DETALLE, HACER CASITOS, NO ES FAICL DE VER ASI NADAMAS)

    definimos
    f(d) := |A_d| cantidad de numeros x tal que d es el numero mas grande tal que d^2 |x
    g(d) := |B_d| cantidad de numeros x tales que d^2| x 

    ( notar que g es trivial g(d) = piso(n/d^2) )

    por la relacion anterior tenemos que
    g(d) = \sum_{k : d | k } f(k)
    g(d) = \sum_{k multiplo de d } f(k)

    Por el teorema de inversion de moebius tenemos

    f(d) = sum_{j=1}^{piso(n/d)} \mu(j) g( j * d)
    f(d) = sum_{k multiplo de d} \mu(k/d) g( k  )



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

// use la criba lineal de la referencia con 3 lineas agregadas

void criba_lineal_mobius(int n, vi &primos, vi &mu) {
    vi lp(n + 1);
    mu.assign(n + 1, 0); //
    mu[1] = 1;          //

    for( ll i = 2; i <= n; ++i ){
        

        // si no hay primo que lo divida es primo
        if( !lp[i] ){
            primos.pb( lp[i] = i );
            mu[i] = -1;  //
        }
        
        for( int j = 0; i * primos[j] <= n; ++j ){
            lp[i * primos[j]] = primos[j];
            
            // i * p_j tiene un primo repetido 
            // porque el menor primo que divide a i lp[i] es p_j
            if( primos[j] == lp[i] ){
                mu[i * primos[j]] = 0; // 
                break;
            }
            // primos distitnos : alternar -1 +1 -1 
            else{
                mu[i * primos[j]] = -mu[i]; //
            }
        }
    }
}


const int MAX_SQRT = 10000002; // sqrt(10^14) = 10^7
// const int MAX_SQRT = 10002; // sqrt(10^14) = 10^7
// 100000000000000  = 1e4
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


    vi primos;
    primos.reserve(700000); //evutar resignanciones

    vi mu;
    criba_lineal_mobius( MAX_SQRT, primos, mu);


    int t; cin >> t;

    // f(d) = sum_{j=1}^{piso(n/d)} \mu(j) g( j * d)
    // f(1) = sum_{j=1}^{n} \mu(j) g( j )
    // donde n := sqrt(n)
    while(t--){
        ll n; cin >> n;
        
        ll f1 = 0;
        ll lim = sqrt(n) ;
        // ajustar pr la impresiision d epunto flotante
        
        while ((lim + 1) * (lim + 1) <= n) lim++;
        while (lim * lim > n) lim--;

        for( ll j=1; j<= lim; j++){
            if( mu[j] == 0 ) continue;
            
            ll gj = n/(j*j);
            f1 += mu[j] * gj;
        }
        

        cout << f1 << "\n";

    }
}

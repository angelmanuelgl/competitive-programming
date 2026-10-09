/*  
    * Contest: 2024-2025 ICPC Latin American Regional Programming Contest
    * URL: https://codeforces.com/gym/105505
    * Problem: E. Evereth Expedition

    * Topic: constuir
    * Algorithm: para construir [1,n] fijate donde se debe poner el uno
                en general para consturir [l,r] con numeros del k,...,n fijate donde debe ir k
    * Complexity: O(n)

    * Status: ACCEPTED
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- Short Macros ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()


// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUG1 DEBUG cout <<
#define DEBUG2 DEBUG1 "\n" << 
#define DEBUG3 DEBUG1 "\n";
#define NODEBUG if(!debug)

// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) via SFINAE
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Logger Function
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

/*

    restantes: cantidad de valores en a[ini, fin] que son diferentes de 0 (originalmente),
               es decir, valores en a[ini, fin] que YA ESTAN PUESTOS desde el inicio
*/

bool llenar( vi &a, int ini, int fin, int poner, int restantes, int idx_izq, int idx_der){
    print( ini, fin, poner);
    print(a);
    print( restantes, idx_izq, idx_der);
    
    if( ini > fin ) return true;


    // si no quedan elementos entonces no importa si lo ponemos a al derecha o izquierda
    if( restantes <= 0 ){
        a[ini] = poner;
        return llenar(a, ini+1, fin, poner+1, 0, -1, -1 );
    }


    // --- ---  ---casos en los que hay algun valor en los extremos --- --- ---

    // algo ... .. .. vacio
    if( a[ini] && !a[fin] ){
        // ya esta el numero a poner
        if( a[ini] == poner) 
            return llenar(a, ini+1, fin, poner+1, restantes-1, -1, idx_der );
        // ponemos el numero a poner
        else{
            a[fin] = poner;
            return llenar(a, ini, fin-1, poner+1, restantes, ini, idx_der );
        }   
    }

    // vacio ... .. .. algo
    if( !a[ini] && a[fin] ){
        // ya esta el numeor a poner
        if( a[fin] == poner) 
            return llenar(a, ini, fin-1, poner+1, restantes-1, idx_izq, -1 );
        // ponemos el numero a poner
        else{
            a[ini] = poner;
            return llenar(a, ini+1, fin, poner+1, restantes, idx_izq, fin );
        }   
    }

    // algo. ... . .. algo
    if( a[ini] && a[fin] ){
        if( a[ini] == poner) 
            return llenar(a, ini+1, fin, poner+1, restantes-1, -1, fin );
        else if( a[fin] == poner) 
            return llenar(a, ini, fin-1, poner+1,restantes-1, ini, -1 );
        else 
            return false;
    }

    // --- --- --- nada en los extremos --- --- ---
    // ahora empieza el caso donde vacio ... vacio 
    // se cumple a[ini] == 0 && a[fin] == 0

    // buscar el indice de mas a la derecha. e izuqierda der a izquierda 
    // en total O(n), asi que O(1) amortizado
    if( idx_izq == -1 ){
        int it = ini ;
        while( !a[it] ) it++;
        idx_izq = it;
    }
    if( idx_der == -1 ){
        int it = fin; 
        while( !a[it] ) it--;
        idx_der = it;
    }

    // --- un restante --- 

    // piensa detalladamente en este caso 
    // notar que las condiciones a verificar y en que orden
    if( restantes ==1 ){
        int idx = idx_izq;

        // lo podemos "debemos"  poner en la derecha
        if( idx - ini <= a[idx] - poner ){
            a[ini] = poner;
            return llenar(a, ini+1, fin, poner+1, restantes, idx_izq, idx_der );
        }
        // lo podemos "debemos" poner en la izquierda
        else if( fin - idx <= a[idx] - poner  ){
            a[fin] = poner;
            return llenar(a, ini, fin-1, poner+1, restantes, idx_izq, idx_der );
        }
        // si no lo podemos "debemos" poner en nignun lado no es psoible
        else{
            return false;
        }
    }

    // --- ahora sabemos que quedan 2  (alemenos)---
    
    // verificar idea greddy :  poner del lado mas chico

    // poner en la izquierda
    if( a[idx_izq]  < a[idx_der] ){
        a[ini] = poner;
        return llenar(a, ini+1, fin, poner+1, restantes, idx_izq, idx_der );
    }

    // ahora sabemos a[idx_izq] > a[idx_der]
    
    // poner en la izquierdda
    a[fin] = poner;
    return llenar(a, ini, fin-1, poner+1, restantes, idx_izq, idx_der );


}


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

   
    int n; cin >> n;
    int cnt_neq0 = 0;
    vi a(n); for( int&x:a){
        cin >> x;
        if( x ) cnt_neq0++;
    }


    bool esPosible = llenar( a, 0, n-1, 1, cnt_neq0, -1, -1 );

    if( !esPosible ){
        cout << "*\n"; return 0;
    }

    for( int i=0; i<n; i++){
        cout << a[i] << " \n"[i==n-1];
    }
    
}
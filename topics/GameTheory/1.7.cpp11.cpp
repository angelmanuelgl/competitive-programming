/*  
    * Contest:  Game theory training sessions | CS
    * URL: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4228
    * Problem: UVA1482: Playing with Stones

    * Topic: Game Theory | Grundy's Numbers
    * Algorithm: - Calculate each Grundy numbers in O(log a_i)
                    by observing the pattern formed between two powers of two.
                 - Calculate the XOR of all elements in O(N)
                 - if it's zerp, i dont have winni move
    * Complexity: O( N log A)  for each test case 
                - N piles <= 100
                - 0 <= a <= A = 10^18
    * Status: ACCEPT
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



// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //


// calcula el mex de los vecinos de un nodo en O(log n)
// sin usar el grafo del juego
// solo usando observaciones matematicas
// val in [2, MAXN+1]
ll patron( ll val, ll pow ){
    // encontrar la posicion en el arbol binario
    ll pivote = pow/2;
    ll tam_bloque = pow/4;
    ll nivel_actual = 0;
    ll indice = 0;
    while (  true ){
        if( val == pivote){
            break;
        }
        indice *= 2;
        if( val > pivote ){
            pivote += tam_bloque;
            indice = indice + 1;
        }
        else if( val < pivote ){
            pivote -= tam_bloque;
            indice = indice;
        }
        nivel_actual++;
        tam_bloque /=2;
    }

    // recrear valor usandos

    // saber cuanto hay de niveles superiroes
    // 1 + 2 + 4 + ... + 2^(nivel_actual -1)

    ll nodos_arriba_estricto = 0;
    if( nivel_actual >= 1)
    nodos_arriba_estricto += (1ll << (nivel_actual) ) -1;

    ll nodos_izquierda_este_nivel = indice +1;

    ll total = nodos_arriba_estricto + nodos_izquierda_este_nivel;
    return total;
}


ll aux(ll val ){ 
    // para potencias de dos da 0
    ll cp = val;
    while( cp%2 == 0   ) cp/=2;
    if( cp == 1) return 0;

    // buscar la potencia de dos que lo encierra
    int exp =1;
    ll pow1 = 2, pow2 = 4;
    while( !( pow1 < val && val < pow2 )  ){
        pow1*=2;
        pow2*=2;
        exp++;
    }

    ll new_val = val - pow1;

    return patron(new_val, pow1);
}
ll calMex(ll val){
    return aux(val+1);
}

// uso :  g++ -DLOCAL A.cpp
int main(){

    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);

    int t; cin >> t;
    while( t--){
        int n; cin >>n;
        vll a(n);  for( ll &x : a) cin >> x;

        ll elxor = 0;
        for( ll x : a)
            elxor = elxor ^ ( calMex(x) );
        
        cout << ((elxor)?"YES\n":"NO\n");
    }


    
}
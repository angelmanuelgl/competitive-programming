/*  
    * Contest: Game theory training sessions | CS
    * URL: https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/powers-of-two-game/problem
    * Problem: Day 4: Powers Game

    * Topic: Game Theory
    * Algorithm: - Check if n is congruent to 0 mod 8
                 - It's easy to see that if n is congruent to 0 mod 8, 
                   the second player wins
                 - Otherwise, I think it's hard to show  that 
                    the first player always wins 
                 - however, you can use minmax to check small cases and convince yourself
    * Complexity: O(1) per each test case, O(T) total

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
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
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
#define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
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

int cnt_vals = 8;
vi valores = {1,2,4,8,16,15,13,9};
vi val2idx( 18, -1 );

// {stado, {val, turno} }
map< pair<vi, pair<bool,int> > , bool > dp;

// state
// es un vector donde te dice la cantidad de cada uno
int minmax( vi state, int val_actual = 0, bool jugadorActual = true ){
    
    // normalizar val_actual en [0, 16]
    val_actual = (val_actual % 17 + 17) % 17;

    // memorizacion
    pair<vi, pair<bool,int> > key = {state, {jugadorActual, val_actual} } ;
    if( dp.count(key) ) return dp[key];




    // quien es quien
    int este_jugador = jugadorActual;
    int el_otro_jugador = !jugadorActual;

    // estado final
    bool is_end = true;

    // escoger alguno
    int cnt[2] = {};
    for( int i=0; i<cnt_vals; i++ ){
        if( !state[i] ) continue;
        is_end = false;
        for( int sig :{-1,1} ){
            int pos_val = val_actual + sig * valores[i];

            // hace movimiento
            state[i]--;
            int ganador = minmax( state, pos_val, !jugadorActual);

            // backtraking
            state[i]++;

            // encontramos movimiento ganador ya no hace falta seguir 
            // un movimeinto en el que gana el jugador actual
            if( ganador == jugadorActual )
                return dp[key] = jugadorActual;
        }
    }


    if( is_end ){
        if( val_actual %17 ) return 1; // gana jugador 1
        return 0; // gana el jugador 2
    }

    // si de todas las posibilidades que escogo:
    // todas me gana el otro entonces gana el otro
    // alguna gano yo entonces gano yo
    return  dp[key] =  !jugadorActual ;
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

    DEBUG{
        int pow = 1;
        for( int i=1; i<=40; i++){
            pow = (pow*2) %17;
            cout << " 2^" << i << " === " <<  pow << " MOD 17\n";
        }
        //si n es multiplo de 16 siempre puede ganar


        // MAPA 
        for( int i=0; i<sz(valores); i++){
            val2idx[ valores[i] ] = i;
        }

        // PROBAR
        int N = 33;
        for( int n=1 ; n<=N; n++){
            vi state( cnt_vals ,0  );
            int pow = 1;
            for( int i=1; i<=n; i++){
                pow = (pow*2) %17; // 2^i
                state[ val2idx[ pow ] ]++;
            }
            // print(state);
            int ganador = minmax( state ); 
            cout << "ganador para n = " << n << " es " << ganador << "\n";
        }
        //// al parece para mutiplos de 8 siempre gana el 2 y para el resto el 1
    }


    // SOLUCION : 
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        cout <<  ( (n%8)? "First\n": "Second\n" ) ;
    }
}
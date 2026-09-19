/*  
    * Contest:  Game theory training sessions | CS
    * URL: https://codeforces.com/gym/101908/problem/B
    * Problem: B. Marbles

    * Topic: Game Theory | Game Theory | Grundy Numbers
    * Algorithm: - (0,0) is not the final state (losing state)
                 - (2,1) y (1,2) are the final states
                 - (x,x) (0,x) (x,0) do not exist
                 - O(M) calculate each Grundy number for each i,j in board
                 - are there M^2 positions
                 - Calculate the XOR of all elements in O(N)
                 - if it's zero, i have winning move
                 - if it's non-zero, i do not have winning move
    
    * Complexity: - O( M^3 + N)
                  - N marbles

    * Status: ACCEPTED (with cf hint)
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


// calcular el mex de un arreglo
int calcularMex( vi & v){
    int n = size(v);
    vector<bool> visitado(n+1, false);
    for( int x: v)
        if( x <= n ) visitado[x] = true;
    for( int i=0; i<=n; i++) 
        if( !visitado[i]) return i;
    return n+1;
}

bool valid( int x, int y){
    if( x == y) return false;
    if( !x || !y) return false;
    return true;
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

    // el tablero es pequeno
    int m = 101;
    int tablero[m+1][m+1];

    // O( m^3 )
    for( int i=1; i<=m; i++){
    for( int j=1; j<=m; j++){
        vi numeros;
        if( (i== 2 && j ==1) || (i==1 && j==2) ){
            tablero[i][j] = 0;
            continue;
        } 

        // los nodos (x,0) (x,x) (0,x) no existen
        if( !valid(i,j) ) continue;

        for( int ii=0; ii<i; ii++)
            if( valid(ii,j) )
            numeros.pb(tablero[ii][j]);

        for( int jj=0; jj<j; jj++)
            if( valid(i,jj) )
            numeros.pb(tablero[i][jj]);

        for( int d=1; d<=min(i,j); d++)
            if( valid(i-d, j-d)  )
            numeros.pb( tablero[i-d][j-d]);

        tablero[i][j] = calcularMex(numeros);
        // DEBUG cout << tablero[i][j]<< " ";
        DEBUG cout << (tablero[i][j]?"_":"X")<< " ";
    }
    DEBUG cout << "\n";
    }




    int n; cin >> n;
    int li,ci;
    int elxor = 0;
    bool ficha_en_pos_ganadora = false;
    for( int i=0; i<n; i++){
        cin >> li >> ci;
        elxor = elxor ^ tablero[li][ci];
        if( li == ci ) ficha_en_pos_ganadora = true;
    }
    cout << ( (elxor||ficha_en_pos_ganadora)? "Y\n":"N\n" );
    
}
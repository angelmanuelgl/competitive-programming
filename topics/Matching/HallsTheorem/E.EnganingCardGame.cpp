/*  
    * Contest: 2026 Argentinian Programming Tournament (TAP)
    * URL: https://codeforces.com/gym/106682
    * Problem: E. Engaging Card Game
    * Topic: Matching | DFS | 
    * Algorithm: Notar que el grafo es bipartito porque no tiene cilcos de grado impar
    *            Ana gana <=> el grafo NO tiene matching perfecto. 
    *            Ademas el grafo no tiene ciclos en general asi que el grafo es un
    *            bosque con un DFS que emparejamos de hojas a raiz
    *            Beto gana <=> todas las componentes terminan con 0 sobrantes en la raiz.
    * Complexity: O( N log MAXA ) vecinos revisados, cada uno con una busqueda.
    *             Con std::map: O( N log MAXA log N ). Con busqueda binaria sobre
    *             el arreglo ordenado o hash: mismo orden o mejor.
    * Status: 
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- --- --- --- Type Aliases --- --- --- ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- --- --- --- Short Macros --- --- --- ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for( int i=a; i< (b); ++i )

const int MOD = 1e9 + 7;

// --- --- --- --- LOGGER SETUP --- --- --- --- 
// Daclare before   
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v);
// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) SFINAE
template<typename C, typename T>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Colors
constexpr const char *RST="\033[0m", *GREEN="\033[1;32m", 
*YELLOW="\033[1;33m",*CYAN="\033[1;36m",*RED="\033[1;31m";
// Logger Function
template<typename ...Args>
void logger(const char* col, string vars, Args&&... values){
    cerr << col << '[' << vars << "] =" << RST;
    ((cerr << " [" << values << ']'), ...);
    cerr << '\n';
}

// --- --- --- --- DEBUGGER SETUP --- --- --- ---    
#ifdef LOCAL
    #define DEBUG   if (true)
    #define SALTO   (cerr << '\n')  
    #define LOG(...)   logger("", #__VA_ARGS__, __VA_ARGS__)
    #define LOGC(c, ...) logger(c, #__VA_ARGS__, __VA_ARGS__)    
    #define COL(c, ...) (cerr << c << __VA_ARGS__ << RST << '\n')
#else
    #define DEBUG   if (false) 
    #define SALTO
    #define LOG(...)
    #define LOGC(...)
    #define COL(...)
#endif

// // // // // // // // // // // // // // // // // // // // //
vi a;// cards
unordered_map<int,int> a2c;//cards2multiplicity
unordered_map<int,bool> vist; // vistados
ll DFS( int nodo, int padre ){
    vist[nodo] = true;
    // contamos lo que emparejaremos con los jijos
    // es decir loq ue los hijos no puedieron empaejas
    ll hijos_para_emparejar = 0;
    // log 1e9 // 2^30 = 1.07e9
    rep( i, 1, 31){
        int pow2m = (1<<i) - 1;
        int v = pow2m - nodo;
        // si efectivamente es un vertice vecino
        if( v>0 && a2c.count(v) && v != padre ){
            int v_no_emparejados = DFS( v, nodo );
            // si algun hijo no pudo ya regresamos -1
            if( v_no_emparejados < 0 ) return -1; 
            // emparjemos lo que sus hjijos no han emparejado
            hijos_para_emparejar += v_no_emparejados ;
        }
    }
    ll no_emparejados_este = a2c[nodo] - hijos_para_emparejar;
    if( no_emparejados_este < 0 ) return -1;
    return no_emparejados_este;
}


// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif


    int n; cin >> n;
    a.resize(n);
    int ci; // there are ci carts with number ai 
    rep(i,0,n){
        cin >> a[i] >> ci;
        a2c[ a[i] ] = ci;
    }

    LOG(a);
    LOG(a2c);

    rep( i, 0, n){
        if( vist[ a[i] ] ) continue;
        ll restantes = DFS( a[i], -1 );
        if( restantes != 0  ){ // ojo que no basta >0 por la flag -1
            // no hay perfect Matching
            cout << "Ana\n";
            return 0;
        }
    }
    // si para cada comp conexa 
    // hubo perfect Matching, simepre hay perfect mathing
    cout << "Beto\n";
    
}
/*  
    * Contest: Codeforces Round 681 (Div. 1, based on VK Cup 2019-2020 - Final)
    * Problem: D. Sum
    * URL: https://codeforces.me/contest/1442/problem/D
    * Topic: divide and conquer dp |  greedy | *2800
    * Algorithm: note that for each array i, I want the best knapsack using all the OTHER arrays.
    *            Divide and conquer on the arrays (like a segment tree) + knapsack dp
    *            Each node keeps a dp with the arrays outside its segment
    * Complexity: O(sum(t_i) + n * k * log n) time, O(n * k) memory.
    * Status: ACCEPTED
    * angelmanuelgl
*/
// 1h10 primner envio (unops 15min degbugeando) // WA test 3
// +8min  (1h18h) debuagar y segundo evnio  // WA test 10
// +11min (1h29) debugar, encontre un error y tercer envio // WA test 10
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

int n, k; 
const int MAXN = 3005, MAXK = 3005;
// const int MAXN = 5, MAXK = 5;
vi t(MAXN); // size // costo
vll w(MAXN); // suma de todos los elementos // peso
vll arreglos[MAXN];
vll acum[MAXN]; // s

const int MAXNODOS = 8192; // 2^13
vll DP[MAXNODOS];


// DP[u][j] = lo maximo que podemos agregar usando j agarradas
//           y usanod los elementos en seg( u )^C
// asi los nodos raices tendran todos los nodos excepto uno
vll dp_aux(MAXK);


// asi DP[ num2nodo[i] ][ j ] = lo maximo que pdoemos agregar con
//                           j agarradas y todos los ementos excepto el i
vi num2nodo(MAXN);


// left = 0 right = n
// invariante: al llamar este nodo con indice pos,
// el valor de dp[ pos ][ . ] estan calculados
// el nodo actual se encarga de llenar a sus hijos
void update( int left, int right , int pos = 1){
    LOGC(YELLOW, pos, left, right);
    if( left >= right ){
        num2nodo[left ] = pos;
        return;
    } 
    int hijo_left = pos*2;
    int hijo_right = pos*2+1;
    LOG( hijo_left, hijo_right);

    // para cada nivel en total O( NK )

    // este segmento es [left, right]
    // me encargo de calcular los hijoss
    int mid = (left+right)/2;
    LOG(left, mid, right);
    LOG(left, mid);
    LOG(mid+1, right);

    // --- --- hijo izquierdo --- left --- [left, mid] --- ---
    // le llenamos [mid+1, right+1]
    int u = hijo_left;
    DP[hijo_left] = DP[pos];
    // O( l K)  = l longitud segmneto
    LOG("hijo izq agregar", mid+1, right);   
    rep( i, mid+1, right+1){
        LOG("agregando", i);
        // agregar el elemento i // O( K )   
        rep( j , 0, k+1){
            // si no uso el arrelgo i
            dp_aux[j] = DP[u][j];
           
            // si uso el arreglo i me cuesta t_i y me da w_i = s_{i,ti}
            if( j - t[i] >=  0) 
                dp_aux[j] = max(dp_aux[j], DP[u][ j-t[i] ] + w[i] );
        }
        
        // sobreescribir al terminar
        rep( j , 0, k+1) DP[u][j] = dp_aux[j];    
    }  


    // --- --- hijo derecho --- right --- [left, mid] --- ---
    // le llenamos [left, mid+1]
    u = hijo_right;
    DP[u] = DP[pos];
    rep( i, left, mid+1){
        // agregar el elemento i // O( K )
        rep( j , 0, k+1){
            // si no uso el arrelgo i
            dp_aux[j] = DP[u][j];
            // si uso el arreglo i me cuesta t_i y me da w_i = s_{i,ti}
            if( j - t[i] >=  0) 
                dp_aux[j] = max(dp_aux[j], DP[u][ j-t[i] ] + w[i] );
        }

        // sobreescribir al terminar
        rep( j , 0, k+1) DP[u][j] = dp_aux[j];  
    }


    update(left, mid, hijo_left ); // [left, mid]
    update(mid+1, right, hijo_right); // [mid+1, right]
} 

// // // // // // // // // // // // // // // // // // // // //
// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif

    cin >> n >> k; // 3e3


    rep(i,0,n){    
        cin >> t[i]; // 1e6
        acum[i].resize( t[i]+1 );
        arreglos[i].resize( t[i]+1 );
        acum[i][0] = 0;
        // leer
        rep( j, 1, t[i]+1){
            cin >> arreglos[i][j];
            acum[i][j] =  acum[i][j-1] + arreglos[i][j];
        }   
        
        w[i] = acum[i][ t[i] ];
    }

    DEBUG{
        
        rep( i, 0, n) LOG( arreglos[i]);
        rep( i, 0, n) LOG( acum[i]);
        rep( i, 0, n) cout << t[i]  << " "; 
        cout <<"\n";
        rep( i, 0, n) cout << w[i]  << " "; 
        cout <<"\n";
        // LOG(t);
        // LOG(w);
    }

    // base 
    DP[1].resize(k+1,0);
    LOG(DP[1]);

    // llenar la dp al estilo divide and conquer
    update(0, n-1);

    COL(RED, "terminar el update");
    ll ans = 0;
    rep( i, 0, n){
        // si no agrramos todos los elemntos de la i-esima torre
        int u = num2nodo[i]; // nodo corresponiente
        LOG(i,u);
        LOG(DP[u]);
        rep( j,0, t[i]+1 ){
            // agarramos los elementos
            // a_{i,0}, a_{i,1}, ... , a_{i, j} 
            if( k-j >= 0 )
                ans = max( ans, acum[i][j] + DP[u][k-j] );
        }
    }

    cout << ans << "\n";

}
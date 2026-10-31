/*  
    * Contest: 2026 ICPC Gran Premio de Mexico Repechaje
    * URL: https://codeforces.com/gym/106710
    * Problem: M. Miguel and His Chess Tournament
    * Topic: Matching | Greedy | Tournament
    * Complexity: O( n^2 log n)
    * Status: ACCEPTED
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

// --- --- --- --- int Macros --- --- --- ---
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


// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif
    
    int n; cin >> n;
    int g = n*(n-1)/2;

    int sum = 0;
    vi b(n); 
    vpii b_idx(n); 
    rep(i,0,n){
        cin >> b[i];
        sum += b[i];
        b_idx[i] = {b[i], i}; 
    }

    // para que haya un partido necesitamos almenos dos participantes
    if( n == 1 ){
        if( b[0] == 0)
            cout << "YES\n0\n";
        else
            cout << "NO\n";
        return 0;
    }


    // hay g partidos, si el total de ganadas (sum) no coincide con el numeor de partido imporible
    if( sum != g){
        cout << "NO\n";
        return 0;
    }


    // verificar si es posible (teorema de landau)
    vi bsort = b;
    sort(all(bsort));
    LOG(bsort);

    // sum = binom(n,2) // \sum_{i=1}^k bi >= binom(k,2) // b1 <= b2 <= ... <= bn
    int sum_1_k = 0;
    rep(k,0,n){
        sum_1_k += bsort[k];
        int K = k+1;
        int binom_k_2 = (K)*(K-1)/2;
        LOG(sum_1_k, binom_k_2);
        if( sum_1_k >= binom_k_2 ) continue;

        cout << "NO\n";
        return 0;
    }


    // GREEDY: tomar el mas grande y que le gane a los mas chicos
    vvi ans( n, vi(n,0) );
    sort(all(b_idx)); // ordenado de menor a mayor y guardando indice
    LOG(b_idx);
    for( int i=n-1; i>=0; i--){
        int ganadas = b_idx[i].fi;
        int perdidas = (i)- ganadas; // (n-1) - ganadas
        int jugador =  b_idx[i].se;
        LOGC( CYAN, i, b_idx[i]);
        LOG(jugador, ganadas, perdidas);

        b_idx[i] = {INT_MAX,-1};

        

        // el jugador le gano a los primeros y perdio contra los ultimos
        // 0 1 2 3 4 .. ganadas - 1, ganadas , ganadas + 1 , ... i-1
        // a los nodos en [perdidas, i-1] ya ganaor un partiod, si bi--;
        
        // i LE GANA A j
        rep(j, 0, ganadas){
            int elotrojugador = b_idx[j].se;
            LOG(jugador, "gana a", elotrojugador);

            // i le gano a j // las victorias de j no cambian 
            ans[ jugador ][ elotrojugador ] = 1;
            ans[ elotrojugador ][ jugador ] = 0;
        }

        // i PIERDE CONTRA
        int cnt = 0;
        rep( j, ganadas , i ){
            int elotrojugador = b_idx[j].se;

            if( b_idx[j].fi == 0  ){
                LOG(i, b_idx[i], jugador, j, b_idx[j], elotrojugador);
                COL(RED,  jugador << "debe perder contra " << elotrojugador << " pero, " << elotrojugador << "solo peude ganar" << b_idx[j].fi );
               
                int x; while( x++);
            }
            // j le gano a i // ya enemos una vicotira para j // bj--
            LOG(elotrojugador, "gana a", jugador);
            b_idx[j].fi--;
            cnt++;

            ans[ jugador ][ elotrojugador ] = 0;
            ans[ elotrojugador ][ jugador ] = 1;

        }
        if( cnt !=  perdidas){
            LOGC( RED, cnt, perdidas);
            int x; while( x++);
        }

        // reordenar
        sort( all(b_idx) );
        LOG( b_idx);
    }

    cout <<"YES\n";
    rep( i, 0, n){
        rep(j, 0, n){
            cout << ans[i][j];
        }
        cout << "\n";
    }


}
/*  
    * Contest: Codeforces Round 1119 (Div. 3)  (ONLINE)
    * URL: https://codeforces.com/contests/2259
    * Problem: E. Treasure Map Destruction (Constructive Version)

    * Topic: constructive, greedy, segmentos en arreglo
    * Algorithm: - identificar donde no podemos poner tesoroes
                 - poner tesoroes en todos lugares donde podamos
                 - verificar si fue una construccion valida
    * Complexity: O(N)

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


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin >> t;

    while( t-- ){
        int n; cin >> n;
        vi a(n+2);
        for( int i=1; i<=n; i++){
            cin >> a[i];
        }

        vi intervalos(n+2,0);
        for( int i=1; i<=n; i++){
            if( a[i] <= 0) continue;

            int L = max( i - a[i] +1,0);
            int R = min( (i + a[i] - 1 ) +1, n+1);
            // no puede haber tersoros en [L,R]
            //     |                                                 |
            //     V                                                 V
            //  i - ai  , i -ai + 1, .... ,   i , ...  , i + ai -1, i +ai
            
            intervalos[L]++;
            intervalos[R]--;           
        }

        // poner tesoroes en todos lugares odne podamos 
        int intervalos_aqui = intervalos[0];
        vi ans(n+2,0);
        ans[0] = ans[n+1] = 0; // no hya barcos
        for( int i=1; i<=n; i++){
            intervalos_aqui += intervalos[i];
             
            if(  (a[i] == -1 || a[i] == 0) && !intervalos_aqui ) 
                ans[i] = 1; // hay tsoro
            else ans[i] = 0;// no hay tesoro
        }
        
        // calcular las distancias para verificar
        vi dist_last_t(n+2, -INT_MAX);
        int idx_last_tesoro = -INT_MAX;

        for( int i=1; i<=n; i++){
            if( ans[i] == 1) idx_last_tesoro = i;
            dist_last_t[i] = min(dist_last_t[i],  i -idx_last_tesoro);
        }

        idx_last_tesoro = INT_MAX;
        for( int i=n; i>=1; i--){
            if( ans[i] == 1) idx_last_tesoro = i;
            dist_last_t[i] = min(dist_last_t[i],  idx_last_tesoro- i );
        }

        // verificar si se cum;le que hay dobde deberia
        // y no hay donde no
        bool hayRespuesta = true;
        for( int i=1; i<=n; i++){
            if( a[i] != -1 && dist_last_t[i] != a[i]) hayRespuesta = false;
        }
        



        if( !hayRespuesta ){
            cout <<"-1\n";
        }else{  
            for( int i=1; i<=n; i++) cout << ans[i] ;
            cout << "\n";
        }

        
    }

    
}
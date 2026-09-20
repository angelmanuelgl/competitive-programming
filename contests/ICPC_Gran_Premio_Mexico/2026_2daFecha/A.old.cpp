/*  
    * Contest: 2026 ICPC Gran Premio de Mexico 2da Fecha
    * URL: https://codeforces.com/gym/106540/problem/A
    * Problem: A. A simple problem

    * Topic: 
    * Algorithm: 
    * Complexity: 

    * Status: in progress
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

const ll MOD =  998244353;


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //
const int LETRAS = 'z' - 'a' + 1;

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

    while(t-- ){
        int n,k; cin >> n >> k;
        string s; cin >> s;

        

        // --- dp[ l ][ c ]
        // antidad de palabras valdiads
        // de longitud l terminan en la
        // posicion i de s

        vvi dp( 2, vi( N,0) );
        
        // --- caso base ---
        // para longitud 1
        // solo podemos iniciar con la primera letra
        // el resto es 0
        dp[ 1 ][ 0 ] = 1;


        // --- transiciones ---
        for( int l=2; l<=k ; l++ ){
            
            // si terminas en la primra psocion antes de ti pido ahber cualquier otra cosa
            dp[ l % 2 ][ 0 ] = 0;
            for( int j = 0; i<N; j++ ){
                dp[ l % 2 ][ 0 ] += dp[ (l-1)%2 ][ j ]; 
                if( dp[l%2][0] > MOD ) dp[l%2][0] %=MOD;
            }
            
            // si terminas en otra posciion, la que esta anrtes de ti esta forzada
            for( int i=0; i< N; i++ ){
                dp[ l%2 ][i] = dp[ (l-1)%2 ][i-1];
            }
        }


        DEBUG{ 
            for( int i=1; i<=k ; i++)
            cout << "dp " << i << " : " <<   dp[i]  <<"\n";
        }

        ll ans = 0;
        for( int c = 0 ; c <LETRAS ;c++){
            ans += dp[k%2][c];
            if( ans >= MOD) ans -= MOD;
        }

        cout << ans << "\n";


    }
    
}
/*  
    * Contest: 2026 ICPC Gran Premio de Mexico 2da Fecha
    * URL: https://codeforces.com/gym/106540/problem/A
    * Problem: A. A simple problem

    * Topic: KMP | strings | dp 
    * Algorithm: dp[ l ] = cantidad de palabras de esas longitud
                 - encontrar la "BASE de prefijos" con KMP // O(N)
                 - para las transcione usar esa base de prefijos
                 - dp[ l ] += dp[ l -longitud de prefijo ] para todo pregijo en la base
                 - hay K estados y N transciones
    * Complexity: O( KN  )

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

const ll MOD =  998244353;



// p[i] = longitud del prefijo mas largo que tambine es sufijo de s[i]
const int MAXN = 2000;
// O( |s| )
vi kmp( const string &s){
    int n = sz(s);
    vi pi(n);
    for( int i=1; i<n; i++){
        int j = pi[i-1];
        while( j && s[i] != s[j] ) j = pi[j-1];
        pi[i] = j + (s[i]== s[j]);
    }
    return pi;
}

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


        // -- encontrar conjunto BASE de prefijos ---
        vi pi = kmp(s);
        vector<bool> prefijoBase(n,0);
        for( int i=0; i<n; i++){
            if( !pi[i]) prefijoBase[i] = true; 
        }



        // --- dp[ l ]
        // antidad de palabras valdias
        // de longitud l 
        vll dp( k+1 );
        
        // --- caso base ---
        // para longitud nula
        dp[ 0 ] = 1;


        print(s);
        print( prefijoBase  );

        // --- transiciones ---

        // para cada longitud
        for( int l=1; l<=k ; l++ ){
            dp[ l ] = 0;
            for( int i=0; i< min(l,n) ; i++ ){
                if( !prefijoBase[i] ) continue;
                
                int longitudPrefijo = i+1;
                dp[ l ] += dp[ l - longitudPrefijo ];

                if( dp[l] >= MOD) dp[l] %= MOD;
            }
        }


        ll ans = dp[ k ];
        cout << ans << "\n";


    }
    
}
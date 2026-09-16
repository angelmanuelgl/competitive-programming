/*  
    * Contest: Game theory training sessions | CS
    * URL: 
    * Problem:  

    * Topic: Game Teory
    * Algorithm: 
    * Complexity: 

    * Status: IN PROCESS
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
    for(const T &x : v) os << sep << (x==LONG_LONG_MAX ? "--" : to_string(x)), sep = " ";
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
const int MAXN = 1000;
const int MAXM = 8;


/*
    PRIMERA APROXIMACION: fuerza bruta con dp 

    O( N^2 * M )
    donde M es el maximo numero de torres que A puede separar
    parece ser que M = 7 es suficiente para n <= 1000
    talvez M = log(N) sea suficiente en general pero no se

    dp[i][j] el minimo valor que A le puede dar B si tiene
    una torre de tam i y A decide separar en j torres
*/
vector< vector<ll> > dp(MAXN, vector<ll>(MAXM, LONG_LONG_MAX));
ll calcular( int i, int j );

vector< ll > dp_respuesta(MAXN, LONG_LONG_MAX);
ll calcular_respuesta( int n );

// obtiene el minimo valor que A le puede dar a B si tiene
// una torre de tam i y A decide separar en j torres
ll calcular( int i, int j){
    if( dp[i][j] != LONG_LONG_MAX ) return dp[i][j];
 
    // queremos el minimo valor que A le puede dar a B
    //  caso base: si se parte en una sola torre entonces es 1 + respuesta[i]
    if( j == 1 )
        return 1 + calcular_respuesta( i );
 
    // poner  _ _ _ _ _ _ k
    // poner en el ultimo monton un monton de tam k y el resto en j-1 montones
    dp[i][j] = LONG_LONG_MAX;
    for( int k = 1; k <= i; k++ ){
        if( j-1 > i-k ) continue;
        // elige el  valor k ganando j^2
        // o elije el valor de la otra parte
        ll pos_ans = max( (ll)j*j + calcular_respuesta( k ), calcular( i-k, j-1)  );
        dp[i][j] = min( dp[i][j], pos_ans );
    }

    return dp[i][j];
}

// obtiene el maximo de dp[i][j] para j : [2:n]
ll calcular_respuesta( int n ){
    if( dp_respuesta[n] != LONG_LONG_MAX ) return dp_respuesta[n];
    ll ans = LONG_LONG_MAX;
    for( int j = 2; j <= min(n, MAXM-1); j++ ){
        ans = min( ans, dp[n][j] );
    }
    return dp_respuesta[n] = ans;
}
// inicializa dp y dp_respuesta y calcular
void init_dp( int n ){
    dp.resize( n+1, vector<ll>(MAXM, LONG_LONG_MAX) );
    dp_respuesta.resize( n+1, LONG_LONG_MAX );

    dp_respuesta[1] = 0;
    dp_respuesta[2] = 4;
    dp[2][2] = 4;

    for( int i = 1; i <= n; i++ ){
        for( int j = 2; j <= min(i, MAXM-1); j++ ){
            dp[i][j] = calcular( i, j );
        }
    }
}


/*
    SEGUNDA APROXIMACION: para cierta cantidad de monedas c, cual es la torre mas alta
    que puedo conseguir
*/

const int MAXTORRES = 2000;
vll dp_maxh(MAXTORRES, 0);

ll hmax( int c){
    if(  dp_maxh[c] != 0 ) return dp_maxh[c];

    ll pos_ans = 0;
    for( int k = 1; k*k <= c; k++){
        pos_ans += hmax( c - k*k );
    }
    dp_maxh[c] = pos_ans;
    return pos_ans;
}

ll maxpow10( ll n ){
    ll ans = 0;
    while( n > 0 ){
        n /= 10;
        ans++;
    }
    return ans;
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
        int n  = 20;
        init_dp( n+1 );
    
        for( int i=2; i<=n; i++ )
            cout << i << " : " <<  dp[i] << "\n";
        
        cout << "repuestas: \n" << dp_respuesta << "\n";
        cout << "\n\n";
    }


    DEBUG{

        dp_maxh[0] = dp_maxh[1] = dp_maxh[2] = dp_maxh[3] = 1;
        hmax(15);
        // cout << dp_maxh << "\n";
        for( int i=1; i<=15; i++ )
            cout << i << " : " <<  dp_maxh[i] << "\n";

        ll tmp = 1e12;
        cout << "  : " << tmp << "\n";
        for( int i = 0; i<130; i++ ){
            tmp = hmax(i);
            cout << i << " : " <<  tmp <<  " " << maxpow10(tmp) << "\n";
        }
    }


    int t; cin >> t;

    dp_maxh[0] = dp_maxh[1] = dp_maxh[2] = dp_maxh[3] = 1;
    int maxC = 130;
    hmax(maxC);

    while(t--){
        ll n; cin >> n;

        // queremos encontrar el menor c tal que hmax(c) >= n

        int c = 1 ;
        while( hmax(c) < n ) c++;
  
        cout << c << "\n";
    }
    
}
/*  
    * Contest: Codeforces Round 1125 (Div. 3)
    * URL: https://codeforces.com/contests/2275
    * Problem: D - Precision Alignment
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef __int128_t lll;
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
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUG1 DEBUG cout <<
#define DEBUG2 DEBUG1 "\n" << 
#define DEBUG3 DEBUG1 "\n";
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


// minima cnaitdad de moviemitpos necesaitos para hacer
// a + b +c >= s
lll aux(ll s, ll a, ll b, ll c){
    // si ya vale s e
    ll sum = a+b+c;
    if( sum >= s) return 0;

    // si todos son iguales no puede crecer
    // es imposible
    if( a == b && b == c )
        return LLONG_MAX;
    
    lll movimientos_avanzar = s - sum;
    // a < b < c 
    // a = b < c
    // a < b = c
    if( a <=b && b <= c){
        lll movimientos_retroceder = 1ll + min(c-b, b-a);
        lll total = movimientos_retroceder*2 + movimientos_avanzar;
        return total;
    }

    // en caulqueir otor caos simepr epodemos subir uno
    return movimientos_avanzar;  
}

// minima cnaitdad de moviemitpos necesaitos para hacer
// min_{1<\i<\n}(ai +bi+ci) >= s
lll f( ll s, vll & a, vll & b, vll & c){
    lll ans = 0;
    for( int i=0; i<sz(a); i++){
        lll tmp = aux( s, a[i],b[i],c[i] );
        if( tmp == LLONG_MAX || ans == LLONG_MAX ) ans = LLONG_MAX;
        else ans += tmp;
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

    int t; cin >> t;
    DEBUG1 LLONG_MAX << "\n";
    DEBUG1 (ll)(1e18) << "\n";
    DEBUG1 (ll)(1e18+6e14) << "\n";
    while(t--){
        DEBUG2 "- - - -- - - -- -------------------\n";
        int n; cin >> n;
        ll k; cin >> k; 
        
        // input
        vll a(n),b(n),c(n); 
        ll s_actual = LLONG_MAX;
        for( int i=0; i<n; i++){
            cin >> a[i] >> b[i] >> c[i];
            s_actual = min(s_actual, a[i]+b[i]+c[i]);
        }


        // f(s) minima cantidd de movimeintos necesarios 
        // para que min_{1<\i<\n}(ai +bi+ci) >= s

        // queremos encontrar el maximo s tal que f(s) <= k


        // antes de hacer la binaria checar si funca
        // ll s = s_actual;
        // while( f(s,  a,b,c) <= k ){
        //     print(s, f(s,  a,b,c));
        //     s++; 
        // } 
        // DEBUG1 "end while\n";
        // print(s, f(s,  a,b,c));
        // s--;
        // print(s, f(s,  a,b,c));
        // cout << s << "\n";


        // queremos encontrar el ultimo valor s tal que f(s)-k <= 0
        // f(s) - k <= 0 false
        // f(s) - k > 0 true
        // CHECK( s ) =  f(s) > k
        // 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1  // 0 = false // 1 = true
        // f(l) = 0 f(r) = 1 // INVARIANTE 

        ll l = s_actual; // para llegar a ese S necesitamos 0 moviemintos 0 > k = false
        ll r = s_actual + k + 1; //  para llegar a ese S necesitamos mas de k moviemitnos cntmov > k = true
        while( l +1 < r ){
            ll m = l + (r-l)/2;
            if( f(m,  a,b,c) > (lll)(k) ) r = m;  // el verdadero 1 siempre es left // INVARIANTE 
            else l = m; // el falso 0 siempre es right // INVARIANTE 
        }
        cout << l << "\n";
    }
    
}
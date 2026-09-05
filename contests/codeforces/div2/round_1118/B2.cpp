/*  
    * Contest: Codeforces Round 1118 (Div. 2)
    * URL: https://codeforces.com/contest/2258
    * Problem: B2. Carrot Chopdown (Hard Version)

    * Topic: 
    * Algorithm: 
    * Complexity: O( M log**2 M)

    * Status: in process
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


ll techo_log_2( ll x ){
    ll pow2 = 1;
    ll exp = 0;

    while( pow2 < x){
        pow2 *= 2;
        exp++;
    }
    return exp;
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

    while(t--){
        int n, m; cin >> n >>m;
        vll cnt(m+2, 0); 
        vll acumm(m+2, 0);
        
        int maxi =0;
        ll pedazos_1 = 0, x;
        for( int i=0; i<n; i++){
            cin >> x;
            // cuantas zanahoras de cada longitud
            cnt[x]++; 
            maxi = max(maxi, (int) x);
            pedazos_1+=x;
        }

        for( int i=1; i<=m; i++){
            acumm[i] = acumm[i-1] + cnt[i];
        }


        print( cnt);
        print( acumm );
        // PARA UNO 
        // provar cada corte

        ll techo_log_2_maxi = techo_log_2( maxi );

        for( int k=1; k<=m; k++){
            if( k >= techo_log_2_maxi  ){
                cout << pedazos_1 << " \n"[k==m];
                continue;
            } 

            DEBUG cout << "resolviendo para  k= " <<  k << "\n";
            ll ans_la_mejor = 0;
            ll pow2_k = 1 << k;


            
            // si k es mayor de log m entones no entra aqui
            ////  O(log M)  
            
         
            // probar con cada longitud final l hasta M/ 2**k

            // digamos que esto topa hasta M 
            for( int x=1; x<= maxi/ pow2_k; x++){
                // nos interesa calcular 
                // sum_{i=1}^ n c(i)
                // con c(i) = 
                // 2^k   si a_i = 2^k * l
                // 2^k -1   si a_i > 2^k * l
                // a_i/l   si a_i < 2^k * l

                // esto es equivalente a
                //  ( sum_{i=1}^ n w(i)  ) + cnt[ 2^k ]
                // con w(i)  = min(2^k -1, a_i/l )

                // lo haremos usamndo por bloques

                // O( M/x)
                ll  ans_x = 0;
                for( int c=0; 1ll*c*x <= maxi; c++ ){
                    int L = max(0, c* x -1);
                    int R = min(maxi, (c+1)*x - 1);
                    ll contador = acumm[R] - acumm[L];
                    ans_x += ( min(1ll*c, pow2_k-1ll) * contador);
                }

                // sumar los iguales

                if(  pow2_k * x  <= m )
                    ans_x += cnt[ pow2_k * x ];

                DEBUG cout << " obteenmos " << ans_x<< "\n";
                // si con esta l fue mejor actualizamos
                ans_la_mejor = max( ans_la_mejor, ans_x);
            }

            cout << ans_la_mejor <<  " ";
                
        } // end for
        
        DEBUG cout << "\n\n";
    } // end case
}
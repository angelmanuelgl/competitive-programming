/*  
    * Contest: Codeforces Round 1118 (Div. 2)
    * URL: https://codeforces.com/contest/2258
    * Problem: B2. Carrot Chopdown (Hard Version)

    * Topic: 
    * Algorithm: 
    * Complexity: O( M log M)

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

// uso :  g++ -DLOCAL K.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.txt");
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
        
        ll maxi =0, total = 0, pedazos_1 = 0, x;
        for( int i=0; i<n; i++){
            cin >> x;
            // cuantas zanahoras de cada longitud
            cnt[x]++; 
            maxi = max(maxi, x);
            total++;
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

            // solo entramos aqui O(log m) veces
            
            DEBUG cout << "resolviendo para  k= " <<  k << "\n";

            // prrobar con cada l // O(M)
            ll ans_la_mejor = 0;
            for( int l=1; l<=maxi; l++){
                // haremos  k cortes de modos que se cortaran en
                // k=1 1l 
                // k=2 1l 2l
                // k=3 1l 2l 3l 4l 
                // k  1l 2l 3l ... .... ... 2**(k-1)*l
                // en realidad eso se puede hacer con k cortes
                DEBUG cout << " intentando l = " << l <<  "  ";

                // ver como queda partido cada bloque
                ll ans_l = 0;
                ll top = ((1<<(k)) -1) * l;
                for( int cut = l ; cut <= min(maxi, top ); cut+=l){
                    ans_l+= total - acumm[cut-1];
                    if( 2*cut <= maxi) 
                        ans_l += cnt[2*cut];
                }


                DEBUG cout << " obteenmos " << ans_l << "\n";
                // si con esta l fue mejor actualizamos
                ans_la_mejor = max( ans_la_mejor, ans_l);
            }

            cout << ans_la_mejor <<  " ";
                
        } // end for
        

    } // end case
}
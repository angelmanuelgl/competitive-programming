/*  
    * Contest: 2023 China Collegiate Programming Contest (CCPC) Guilin Onsite (The 2nd Universal Cup. Stage 8: Guilin)
    * Problem: C. Master of Both IV
    * URL: https://codeforces.com/gym/104768/problem/C
    * Topic: Xor basis | Number Theory | Criba |
    * Algorithm: - subconjuntos con xor 0s
    *            - para cada vi subconjuntos S tales que vi | vk y xor_{i\in S} vi = 0
    * Complexity: O( 18 n LOG N) // 18 = LOG2(MAXVi)
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

const int MOD = 998244353;

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
#define is_on(S,j) ( S & (1<<(j) ) )

// n <= 2e5 < =2^18
const int d = 32;

struct xorbasis{
    int basis[d]={};// basis[i]: v\inBase cuyo lsb es i
    int sz = 0;       // size actual de la base (= rango r)

    xorbasis(void){
        rep(i,0,d) basis[i] = 0;
    }
    bool insertVector(int mask){
        // LOGC(RED,mask);
        for( int i = 0; i < d; i++ ){
            // LOG(i, is_on(mask,i), basis[i]);
            if( !is_on(mask,i) )continue; // continue if lsb(mask)!=i
            if( !basis[i] ){ // no hay vector en la base con ese bit
                basis[i] = mask;
                ++sz;
                return true;
            }
            mask ^= basis[i]; // si ya hay, quitarle ese bit a mask
        }
        return false;
    }
    int dim( void ){
        return sz;
    }
};

const int MAXN = 200005;
ll pow2[MAXN];
// for f in {a..n}; do cp template.cpp $f.cpp; done
// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif
    // precalcualr potencias 2
    int t; cin >> t;

    pow2[0]= 1;
    rep(i, 1, MAXN) pow2[i] = (pow2[i-1]*2)%MOD;
   

    while( t-- ){
        COL(RED, "\ncaso " << t << " ---------");
        int n; cin >> n;
        xorbasis base_general;
        vi cnt(n+1,0);
        vi v(n); 
        for( int &x:v ){
            cin >>x; 
            cnt[x]++;
            if( cnt[x] == 1 ){
                bool insertado = base_general.insertVector(x);
                LOG(x, bitset<5>(x), insertado);
            }
        }
      

        // subconjuntos con xor 0s
        ll cnt_s_xor0 = pow2[ n - base_general.dim() ];
        cnt_s_xor0--; //quitarle el vacio
        LOG( n, base_general.dim(), cnt_s_xor0);

        // quitar repetidos // ya los tenemos contados todos
        sort(all(v));
        v.erase(unique(all(v)), v.end() );
        int newn = sz(v);

        LOG(v);

        // mapear valor a indice
        vi val2idx(n+1, -1);
        rep(i,0,newn){
            val2idx[ v[i] ] = i;
        }

        LOG(val2idx);

        // subconjuntos S tales que vi | vk y xor_{i\in S} vi = vk
        // para cada vk fijo queremos guardar todos sus divisores
        // iterar por las parejas (d,v) d | v<=n // O(n log n)
        
        xorbasis bases[newn];
        vi cnt_divisores(newn,0);

        // no estamos contando (d,d)=(v,v)
        rep(i, 0, newn){
            int d = v[i];
            for( int v = d*2; v<= n; v+=d ){
                int idxv = val2idx[v];
                if( idxv == -1 ) continue;
                // O(32)
                bases[ idxv ].insertVector(d);
                cnt_divisores[ idxv ] += cnt[d];
            }
        }
        LOG( cnt_divisores);

        // agregamos (v,v)
        // nota que si tenemos una subsecuneica que tal que  xor_{i\in S} vi = vk
        // enotnces ya tenemos usados un vk, nos quedan cnt[]-1
        rep(i, 0,newn){
            LOGC( RED, i, v[i] );
            LOG( bases[i].dim(), cnt_divisores[i], cnt[v[i]]  );

            cnt_divisores[i] += (cnt[v[i]]-1);

            LOG( bases[i].dim(), cnt_divisores[i], cnt[v[i]]  );
        }

        // contamos cuantos S tales que vi | vk y xor_{i\in S} vi = v
        // es decir fado vk fijo cuantos S hay tales que vi | vk y  xor_{i\in S}  = 0
        ll cnt_xor_vk = 0;
        rep( i, 0, newn){
            int r =  bases[i].dim();
            LOG(i, v[i], cnt_divisores[i], r);
            
            int this_cnt = pow2[ cnt_divisores[i] - r ];
            cnt_xor_vk =  ( cnt_xor_vk+ this_cnt)%MOD;
        }

        ll ans = (cnt_xor_vk + cnt_s_xor0)%MOD;
        LOGC( CYAN, cnt_s_xor0, cnt_xor_vk, ans);
        cout << ans << "\n";
    }

    
}
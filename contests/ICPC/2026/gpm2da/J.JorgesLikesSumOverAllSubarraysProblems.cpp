/*  
    * Contest: 2026 ICPC Gran Premio de Mexico 2da Fecha
    * URL: https://codeforces.com/gym/106540/problem/A
    * Problem:  J. Jorge likes "sum over all subarrays" problem

    * Topic: Combinatoric | polynomials | NTT
    * Algorithm: - sum_{permutacion} \sum_{intervalo} \prod_{valores en intervalo} 
                 -  \sum_{k=1 .. n } \sum_{S \subset [n], |S| = k } (cnt apariciones de cada conjunto) * (producto elementos del conjunto)
                 -  \sum_{k=1 .. n } \sum_{S \subset [n], |S| = k } w_i * (producto elementos del conjunto)
                 -  \sum_{k=1 .. n } w_k * ( \sum_{S \subset [n], |S| = k }  (producto elementos del conjunto) )
                 -  \sum_{k=1 .. n } w_k *  v_k
                 -  w_k: cada subconjunto aparece como bloque en k!*(n-k+1)!
                    permutaciones: k! ordenes internos y (n-k+1)! externos
                 -  v_k: Construir P(x) = prod(1 + i*x), i=1..n, con
                    divide y venceras, multiplicando polinomios mediante NTT
                 - P[k] suma los productos de los subconjuntos de tamano k
                 - Respuesta: sum ( P[k]*k! *(n-k+1)! ), k=1..n, mod 998244353
                 - Complexity: O(n log^2 n) tiempo y O(n) 

    * Status: 
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



// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //



const int MOD = 998244353;
const int root = 3;

// exponenciacion ibnaria
ll modpow(ll base, ll exp){
    ll ans = 1;
    while (exp > 0){
        if(exp & 1) ans = ans * base % MOD;

        base = base * base % MOD;
        exp >>= 1;
    }
    return ans;
}


// FFT // Kactl
#define rep(i,a,b) for( int i=a; i < (b); i++)

void ntt(vll &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vll rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, MOD >> s)};
        rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % MOD;
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
            a[i + j + k] = ai - z + (z > ai ? MOD : 0);
            ai += (ai + z >= MOD ? z - MOD : z);
        }
}
vll conv(const vll &a, const vll &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
        n = 1 << B;
    int inv = modpow(n, MOD - 2);
    vll L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i,0,n)
        out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
    ntt(out);
    return {out.begin(), out.begin() + s};
}




const int MAXN = 200000;
ll fact[MAXN + 1];

// \prod_{i=1}^{n}{ (1 + ix) } recursivamente
vll recursivamente_construir(int l, int r){
    if( l == r){
        // 1 + l x
        return {1,l};
    }

    int mid = (l+r)/2;

    vll left = recursivamente_construir( l, mid);
    vll right = recursivamente_construir(mid+1, r);

    return conv(left, right);
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


    fact[0] = 1;
    for( int i=1; i<= MAXN; i++){
        fact[i] = i*fact[i-1] % MOD;
    }

    int t; cin >> t;


    while(t--){
        int n; cin >> n;

        vll polinomio = recursivamente_construir(1,n);

        ll ans = 0;
        for( int k=1; k<=n; k++){
            ll termino = (fact[k] * fact[n-k+1] )% MOD;
            termino = ( termino * polinomio[k] ) %MOD;
            ans = (ans + termino) % MOD; 
        }

        cout << ans << "\n";
        
    }
    
}
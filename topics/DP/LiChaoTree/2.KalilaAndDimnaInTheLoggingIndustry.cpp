/*  
    * Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    * Problem: Kalila and Dimna in the Logging Industry
    * ULR: https://codeforces.com/edu/courses
    * Status: Accepted
    * Algorithm: 
    * Complexity: 
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
// Logger Func
template<typename ...Args>
void logger(string vars, Args&&... vals){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << vals, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;



// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //


vi a,ac,b;

struct Func {
	ll m,b;
	ll eval(ll x){
		if( m == LLONG_MAX) return LLONG_MAX;
		return (ll)((__int128_t)m * x + b);
	}
	Func(){ m = LLONG_MAX;}
	Func(ll m_, ll b_): m(m_), b(b_){ }
};
ostream& operator<<(ostream &os, const Func &f){
    return  os << f.m << "x+" << f.b ; 
}
struct LiChaoTree {
	vll vals;
	ll maxV;
	Func *treefunc;
	LiChaoTree(vll &vals_){
		vals = vals_;
		sort(all(vals));
        vals.erase( std::unique( all(vals) ), vals.end() );
		treefunc = new Func[sz(vals) * 4 + 5];
		maxV = sz(vals);
	}
	void addFunction(Func f){ addFunction(f, 1, 0, maxV); }
	void addFunction(Func f, ll v, int l, int r){
		int m = l + (r - l) / 2;
        ll mv = vals[m];
        ll lv = vals[l];
        bool lef = f.eval(lv) < treefunc[v].eval(lv); // min
        bool mid = f.eval(mv) < treefunc[v].eval(mv); // min
        if(mid) swap(treefunc[v], f);
        if(r - l == 1) return;
        else if(lef != mid) addFunction(f, 2 * v, l, m); 
        else addFunction(f, 2 * v + 1, m, r);
	}  
    void addSegFunction( Func fi, int l, int r){//[l,r)->[i,j)
        l = lower_bound(all(vals), (ll)l) - vals.begin();
        r = lower_bound(all(vals), (ll)r) - vals.begin();
        if( l < r ) addSeg(fi,l,r, 1,0,maxV );
    }
    void addSeg(Func fi,int l,int r,int v,int left,int right){
        if( r <= left  || right <= l) return;
        if( l <= left  && right <=  r  ){
            addFunction( fi, v, left, right);
            return; 
        }
        if( left +1 == right)  return;
        int m =  left + (right-left)/2;
        addSeg(fi, l, r, v * 2     , left, m);
        addSeg(fi, l, r, v * 2 + 1 , m, right);
    }
    ll get(ll x){ return get(x, 1, 0, maxV); }
	ll get(ll x, int v, int l, int r){
        ll cur = treefunc[v].eval(x);
        if(r - l == 1) return cur;
        int m = l + (r - l) / 2;
        ll mv = vals[m];
        if(x < mv) return min(cur, get(x, 2 * v, l, m)); //min
        else return min(cur, get(x, 2 * v + 1, m, r)); //min
	}
	~LiChaoTree(){ delete[] treefunc; }
};


// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif


    int n; cin >> n;

    a.resize(n+1);b.resize(n+1);ac.resize(n+1);
    for(  int i=1; i<=n; i++ ) cin >> a[i];
    for(  int i=1; i<=n; i++ ) cin >> b[i];

    // vector de acumulados
    ac[0] = 0;
    for( int i=1; i<=n; i++) ac[i] = ac[i-1] + a[i];

    print(a,b,ac);



    // dp[i] = minima costo para talar el i-simo arbole
    vll dp(n+1,LLONG_MAX);
    // talar el primero siempre da costo 0
    dp[1] = 0;

    /*
        observacion importante si  
        1. talo el i-simo arbol
        2. y luego el j-esimo arbol con   i < j
        costo += b_k * a_i + b_i * a_j
        me convien hacerlo alrevez
        costo += b_k * a_j + b_j * a_i
    */
    
    for( int i=2; i<=n; i++){
        dp[i] = LLONG_MAX;
        DEBUG1 "dp[ " <<  i << " ] =   min{\n"; 

        //  i-esimo arbol lo talamos despues de talar el arbol k
        // 1 2 3 4 ... k (aqui) k+1 k+2
        for( int k=1; k<=i-1; k++){
            // costo por talar los k primeros arboles
            ll costo_anterior = dp[k];

            // costo por talar el k+1 // indice i
            // tiene tam a[i] y cuesta recargar b[k]
            // porque el mas grande que se talo fue el arbol k
            ll costo_este = a[i] * b[k];

            // costo total por talar el i-esimo arbol
            // en el moemnto k+1
            ll costo = costo_anterior + costo_este ;
            dp[i] = min( dp[i], costo );

            DEBUG1 " dp[ " << k << " ]";
            DEBUG1 " +  a[ " << i << " ]";
            DEBUG1 "*b[ " << k << " ]";
            print(costo_anterior,costo_este);
        }

        DEBUG1 "}\n\n";
    }


    print(dp);

    cout << dp[n] << "\n";
    


    
}
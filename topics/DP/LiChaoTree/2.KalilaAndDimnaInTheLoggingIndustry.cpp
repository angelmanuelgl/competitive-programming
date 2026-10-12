/*  
    * Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    * Problem: Kalila and Dimna in the Logging Industry
    * ULR: https://codeforces.com/edu/courses
    * Status: ACCEPTED
    * Algorithm: dp[i] minimum cost to cut completely the i tree
                 ans = dp[0], after all cut is free
    * Complexity: O( N log N)
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
    vll a(n); for( ll &x:a) cin >>x;
    vll b(n); for( ll &x:b) cin >>x;

    print(a,b);

    LiChaoTree lct(a);
    vll dp(n,0);
    dp[0] = 0;
    lct.addFunction( { b[0], dp[0] });
    for( int i=1; i<n; i++){
        // dp[i] = min_{ 0 <= j < i}{ dp[j] + b[j]a[i]}
        dp[i] = lct.get(a[i]);
        lct.addFunction({b[i], dp[i]});
        print( i , dp[i], f );
    }
    print(dp);
    cout << dp[n-1] << "\n";
    
}
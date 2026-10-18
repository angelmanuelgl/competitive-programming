/*  
    * Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    * Problem: Z - Frog 3
    * ULR: hhttps://atcoder.jp/contests/dp/tasks/dp_z
    * Status: ACCEPTED
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

struct Func {
	ll a,c;
	ll eval(ll x){
		if( a == LLONG_MAX) return LLONG_MAX;
		return (ll)((__int128_t)(a-x) * (a-x) + c);
	}
	Func(){ a = LLONG_MAX;}
	Func(ll a_, ll c_): a(a_), c(c_){ }
};
ostream& operator<<(ostream &os, const Func &f){
    return  os << " (" << f.a << "-x)^2+" << f.c; 
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

    int n; ll c; cin >> n >> c;
    vll h(n); for( ll &x:h ) cin >> x;

    print(n,c,h);
    LiChaoTree lct(h);

    vll dp(n); dp[0] = 0;
    lct.addFunction( {h[0], dp[0]+c} );
    for( int i=1; i<n; i++){
        // dp[i] = min_{ 0 <= j < i }( dp[j] + (hj - hi)^2 +c )
        dp[i] = lct.get(h[i]);
        Func f = {h[i], dp[i] +c };
        lct.addFunction(f ); // ( hi -x )^2 + (c+dp[i])
        print(f);
    }
    cout << dp[n-1] << "\n";

    
}
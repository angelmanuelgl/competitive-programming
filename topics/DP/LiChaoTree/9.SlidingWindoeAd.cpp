/*  
    * Contest: Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    
    * Problem: CSES Problem Set | Sliding Window Advertisement
    * URL: https://cses.fi/problemset/task/3227

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
#define rep(i,a,b) for( int i=a; i< (b); ++i )

const int MOD = 1e9 + 7;

// --- --- --- --- LOGGER SETUP --- --- --- ---    
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
// colores
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

// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

// , ..., <- , ..., i
// idx del primero a la izq de i que es menor que i
// idx del ultimo a la izq de i que es mayor igual i // +1
vll calc_left( int n, vll & h ){
    vll ans(n+2,-1);
    stack< pll  > ms; // monotonick stack
    ms.push({0,0});
    for( int i=1; i<=n; i++){
        while( ms.top().fi >= h[i] ) ms.pop();
        ans[i] = ms.top().se + 1;
        ms.push({h[i],i});
        SALTO;
    } 
    return ans;
}

vll calc_right( int n, vll & h ){
    vll ans(n+2,-1);
    stack< pair<ll, int>  > ms; // monotonick stack
    ms.push({0,n+1});
    for( int i=n; i>=1; i--){
        while( ms.top().fi >= h[i] ) ms.pop();
        ans[i] = ms.top().se - 1;
        ms.push({h[i],i});
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

    int n,k; cin >> n >> k;
    vll h(n+2);
    h[0] = h[n+1] = 0;
    rep(i, 1, n+1) cin >> h[i]; 

    LOG(h);

    vll l = calc_left(n,h);
    LOG(l); 

    vll r = calc_right(n,h);
    LOG(r);

}
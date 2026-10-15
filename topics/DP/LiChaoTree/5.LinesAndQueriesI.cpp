/*  
    * Contest: Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    
    * Problem: 5. Lines and Queries I
    * URL: https://cses.fi/problemset/task/3429

    * Status: ACCEPTED
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef int64_t ll;
typedef vector<ll> vll;

// --- Short Macros ---
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for( int i=a; i< (b); ++i )

// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

struct Func {
	ll m,b;
	ll eval(ll x){
		if( m == -LLONG_MAX) return -LLONG_MAX;
		return (ll)((__int128_t)m * x + b);
	}
	Func(){ m = -LLONG_MAX;}
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
        bool lef = f.eval(lv) > treefunc[v].eval(lv); // min
        bool mid = f.eval(mv) > treefunc[v].eval(mv); // min
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
        if(x < mv) return max(cur, get(x, 2 * v, l, m)); //min
        else return max(cur, get(x, 2 * v + 1, m, r)); //min
	}
	~LiChaoTree(){ delete[] treefunc; }
};

// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

struct query{
    ll type, a,b,x;
};

// uso :  g++ -DLOCAL A.cpp
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    
    int n; cin >> n;
    vector<query> vq; query q;
    vector<ll> a;
    rep(i,0,n){
        cin >> q.type;

        if( q.type == 1) cin >> q.a >> q.b;
        else{
            cin >> q.x;
            a.pb(q.x);
        }
        vq.pb(q);
    }

    LiChaoTree lct(a);

    for( query q : vq){
        if( q.type == 1)
            lct.addFunction({q.a,q.b});
        else{
            ll maxi = lct.get(q.x);
            cout << maxi << "\n";
        }
        
    }
}
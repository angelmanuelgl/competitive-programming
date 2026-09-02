#include<bits/stdc++.h>
using namespace std;


typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;



 ///  Actualización de rango y consulta de puntos //indexado en 1
struct FenwickTree {
    vector<ll> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n+1, 0);
    }


    FenwickTree(const vector<ll>& a) : FenwickTree((int)a.size()) {
        for( int i = 1; i <= n; ++i ){
            ll d = a[i - 1] - (i > 1 ? a[i - 2] : 0); // D[i] diferencias
            bit[i] += d;
            int r = i + (i & -i);
            if (r <= n) bit[r] += bit[i];
        }
    }

    // I. add puntual
    void add( int idx, ll val ){
        for( ++idx; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }
    // add rango
    void range_add( int l, int r, ll val ){
        add(l, val);
        if( r+1 < n ) add(r + 1, -val);
    }
    // II. query puntual: idx
    ll point_query( int idx ){
        ll ret = 0;
        for( ++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
};

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n,q; cin >> n >> q;
    vll vec(n);
    for( ll &x : vec) cin >> x;
    FenwickTree ft(vec);

    while( q-- ){
        int type; cin >> type;


        if( type == 1 ){
            int a,b; cin >> a >> b;
            ll u; cin >> u;
            ft.range_add( a-1,b-1, u);

        }else if( type==2 ){
            int k;  cin >> k;
            cout << ft.point_query(k-1) <<'\n';
        }

    }



    return 0;
}


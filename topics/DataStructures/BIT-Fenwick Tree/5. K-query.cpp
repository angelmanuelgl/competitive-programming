#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;

// Actualizacion de puntos y consulta de rango //indexado en 0
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    FenwickTree(vector<int> const &a) : FenwickTree(a.size()){
        for (int i = 0; i < n; i++) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }
    // I. agregar puntual
    void add( int idx, int val ){
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += val;
    }
    // II. query puntual:  [0 , r]
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    // query rangos
    int sum(int l, int r ){
        return sum(r) - sum(l - 1);
    }
};


// iniciar programr 5:54
// hacr todo ofline, ir respondiendde mayor a menor las queires
// al mismo tiempoq ue amrcamos los valores en el segmnt tree
// para solo aher queries rangos [i,j]

// 6:20
struct query{
    int i,j,k,id;

    bool operator<(const query &other){
        return k > other.k; // descendiente por k
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // datos
    int n; cin >> n;
    vpi vals(n);
    for(int i=0; i<n; i++){
        ll x; cin >> x;
        vals[i] = {-x,i};
    }
    sort( all(vals) );

    // queries
    int q; cin >> q;
    vector<query> preguntar(q);
    for( int i=0; i<q; i++){
        int ii,jj,kk; cin >> ii >> jj >> kk;
        preguntar[i] = {ii,jj,kk,i};
    }
    sort(all(preguntar));

    // two pointers
    FenwickTree ft(n);
    vector<int> ans(q);

    int point_val = 0;
    for(  int i=0; i<q; i++  ){
        query qu = preguntar[i];

        // marcar valores del  FT que son >  query.k
        while(  -vals[point_val].fi > qu.k && point_val <n   ){
            ft.add( vals[point_val].se , 1  );
            point_val++;
        }

        // responder mi query
        ans[ qu.id ] = ft.sum( qu.i-1, qu.j-1 );
    }


    for( int i=0; i<q; i++ ){
        cout << ans[i] << " \n"[i==q];
    }


}

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


/// Actualizacion de puntos y consulta de rango //indexado en 0
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

// inic aprogramar 5:01
// end 5:07

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    FenwickTree ft(100005);

    int x,n; cin >> n;

    for( int i=0; i<n; i++){
        cin >> x;

        ft.add(x,1);
        cout << ft.sum(x+1,n) << " \n"[i==n-1];
    }

}

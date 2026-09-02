#include<bits/stdc++.h>
using namespace std;

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

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t,n,q,caso=1;
    cin >> t;

    while(t--){
        cout <<  "Case " << caso++ << ":\n";
        cin >> n >> q;
        vector<int> vec(n);

        for(int i=0; i < n; i++ ) cin >> vec[i];
        FenwickTree FT(vec);

        while(q--){
            int tipo,i,j,v;
            cin >> tipo;

            if( tipo==1 ){ //toma todo de i
                cin >> i;
                int hay = FT.sum(i,i);
                cout << hay << "\n";
                FT.add(i,-1*hay);

            }else if( tipo==2 ){ // agrega v a i;
                cin >> i >> v;
                FT.add(i,v);

            }else if( tipo==3 ){ //suma i a j
                cin >> i >>j ;
                cout << FT.sum(i,j) << "\n";
            }
        }
    }
    return 0;
}

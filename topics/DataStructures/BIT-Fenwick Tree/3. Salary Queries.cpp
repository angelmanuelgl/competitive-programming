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



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,q; cin >> n >> q;

    vi person2salario(n);
    vi salarios;
    map<int,bool> marcas;


    /// Comrpesion de coordenadas para salarios
    for( int &x: person2salario ){
        cin >> x;
        if( !marcas[x] ){
            salarios.push_back(x);
            marcas[x] = true;
        }
    }

    //guardar queries
    vector<char> type(q);
    vi ka(q), xb(q);
    for(int i=0; i<q; i++ ){
        cin >> type[i] >> ka[i] >> xb[i];

        if( type[i] == '!'  ){
            int x = xb[i];
            if( !marcas[x] ){
                salarios.push_back(x);
                marcas[x] = true;
            }
        }
    }
    int m = salarios.size();

    sort( all(salarios) );
    map<int, int> salarios2idx;
    for( int i=0; i<m; i++ ) salarios2idx[ salarios[i] ] = i;

    for (int i = 0; i < n; ++i) person2salario[i] = salarios2idx[ person2salario[i] ];

    /// Fendwick de frecuencias de salarios
    vi frecuenciasSalarios(m,0);
    for( int i=0; i<n; i++ ){
        frecuenciasSalarios[  person2salario[i]  ]++;
    }
    FenwickTree ft(frecuenciasSalarios);



    for( int i=0; i<q; i++ ){

        if( type[i] == '!'){
            int k=ka[i]-1, x=xb[i];

            ft.add( person2salario[k], -1); // quitamos el salarios anteriror
            ft.add( salarios2idx[x], 1); // agregamos el nuevo salario

            person2salario[k] = salarios2idx[x];

        }else if( type[i] == '?'){
            int a=ka[i],b=xb[i];
            int L = int(lower_bound(all(salarios), a) - salarios.begin());
            int R = int(upper_bound(all(salarios), b) - salarios.begin()) - 1;
            cout << ft.sum(L,R) << '\n';
        }
    }


}

#include<bits/stdc++.h>
using namespace std;


struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    //construccion O(N log N)
//    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
//        for (size_t i = 0; i < a.size(); i++)
//            add(i, a[i]);
//    }

    //construccion O(N)
    FenwickTree(vector<int> const &a) : FenwickTree(a.size()){
        for (int i = 0; i < n; i++) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    //Actualización de puntos y consulta de rango //indexado en 0
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

struct FenwickTreeOneBasedIndexing {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTreeOneBasedIndexing(int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<int> a)
        : FenwickTreeOneBasedIndexing(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }

    //  Actualización de rango y consulta de puntos
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    void range_add(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }
    int point_query(int idx) {
//        int ret = 0;
//        for (++idx; idx > 0; idx -= idx & -idx)
//            ret += bit[idx];
//        return ret;
        return sum(idx,idx);
    }
};

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> vec = {1,2,3,4,5,6,7,8};
    FenwickTree FT(vec);

    cout <<  FT.sum(2,4) << '\n';
    FT.add(3,2);
    cout <<  FT.sum(2,4) << '\n';
    cout << 3+4+5 << '\n';

    cout <<'\n';


    vector<int> vec2 = {1,2,3,4,5,6,7,8};
    FenwickTreeOneBasedIndexing FT2(vec2);


    for( int i=0; i<=7; i++ ) cout << FT2.point_query(i) << " \n"[i==7];

    cout <<  FT2.sum(2,4) << '\n';

    for( int i=0; i<=7; i++ ) cout << FT2.point_query(i) << " \n"[i==7];

    FT2.add( 5, 1 );
    for( int i=0; i<=7; i++ ) cout << FT2.point_query(i) << " \n"[i==7];



    return 0;
}

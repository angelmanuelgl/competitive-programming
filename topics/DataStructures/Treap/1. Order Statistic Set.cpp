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


struct treap{
    typedef struct _node{
        long long x;
        int freq, cnt;
        long long p;
        _node *l, *r;
        _node(long long _x): x(_x), p(((long long)(rand()) << 32 )ˆrand()),
        cnt(1), freq(1), l(nullptr), r(nullptr){}
        ~_node (){delete l; delete r;}

        void recalc(){
            cnt = freq;
            cnt += ((l) ? (l->cnt) : 0);
            cnt += ((r) ? (r->cnt) : 0);
        }
    }* node;


    node root;
    node merge(node l, node r){
        if(!l || !r) return l ? l : r;
        if(l->p < r->p){
            r->l = merge(l, r->l);
            r->recalc();
        return r;
        } else {
            l->r = merge(l->r, r);
            l->recalc();
            return l;
        }
    }
    void split_by_value(node n, long long d, node &l, node &r){
        l = r = nullptr;
        if(!n) return;

        if(n->x < d){
            split_by_value(n->r, d, n->r, r);
        l = n;
        } else {
            split_by_value(n->l, d, l, n->l);
            r = n;
            }
        n->recalc();
    }

    void split_by_pos(node n, int pos, node &l, Node &r, int l_nodes = 0){
        l = r = NULL;
        if(!n) return;
        int cur_pos = (n->l) ? (l_nodes + n->l->cnt) : l_nodes;
        if(cur_pos < pos){
            splitFirstNodes(n->r, pos, n->r, r, cur_pos + 1);
            l = n;
        } else {
            splitFirstNodes(n->l, pos, l, n->l, l_nodes);
            r = n;
        }
        n->recalc();
    }

    treap(): root(NULL){}

    void insert_value(long long x){
        node l, m, r;
        split_by_value(root, x, l, m);
        split_by_value(m, x + 1, m, r);
        if(m){
            m->freq++;
            m->cnt++;
        } else
            m = new _node(x);
        root = merge(merge(l, m), r);
    }
    void erase_value(long long x){
        node l, m, r;
        split_by_value(root, x, l, m);
        split_by_value(m, x + 1, m, r);
        if(!m || m->freq == 1){
        delete m;
        m = nullptr;
        } else {
        m->freq--;
        m->cnt--;
        }
        root = merge(merge(l, m), r);
    }
};


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


}

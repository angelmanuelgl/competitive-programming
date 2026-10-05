struct Function {
    ll m, b;
    ll eval(ll x){
        if (m == LLONG_MIN) return LLONG_MIN;
        return (ll)((__int128_t)m * x + b);
    }
    Function(){ m = LLONG_MIN;}
    Function(ll m_, ll b_): m(m_), b(b_){ }
};
struct LiChaoTree{
    vll values;
    int maxV;
    Function *treefunc;
    LiChaoTree(vll &values_){
        values = values_;
        sort(all(values));
        values.erase(unique(all(values)), values.end());
        maxV = sz(values);
        treefunc =new Function[sz(values)*4];
    }
    ll get(ll x){
        return get(x, 1, 0, maxV);
    }
    ll get(ll x, int v, int l, int r){
        ll cur = treefunc[v].eval(x);
        if(r - l == 1) return cur;
        int m = l + (r - l) / 2;
        ll mv = values[m];
        if(x < mv) return max(cur, get(x, 2 * v, l, m));
        else return max(cur, get(x, 2 * v + 1, m, r));
    }
    void addFunction(Function f){
        addFunction(f, 1, 0, maxV);
    }
    void addFunction(Function f, int v, int l, int r){
        int m = l + (r - l) / 2;
        ll mv = values[m];
        ll lv = values[l];
        bool lef = f.eval(lv) > treefunc[v].eval(lv);
        bool mid = f.eval(mv) > treefunc[v].eval(mv);
        if(mid) swap(treefunc[v], f);
        if(r - l == 1) return;
        else if(lef != mid) addFunction(f, 2 * v, l, m);
        else addFunction(f, 2 * v + 1, m, r);
    }
    ~LiChaoTree(){ delete[] treefunc; }
};
/*  
    * Contest: Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    * Problem: Segment Add Get Min
    * Status: Accepted
    * Algorithm:  Li Chao Tree sobre coordenadas comprimidas (solo los p de las consultas de tipo 1),
    *            con inserción de segmentos como Segment Tree descomponiendo [l, r) en O(log M) nodos
    * Complexity: O(Q log^2 M) tiempo para insertar segmentos, O(log M) por consulta, O(M) memoria
    *             (M = numero de valores p distintos, N = segmentos iniciales, Q = consultas)
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


// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUG1 DEBUG cout <<
#define DEBUG2 DEBUG1 "\n" << 
#define DEBUG3 DEBUG1 "\n";
#define NODEBUG if(!debug)

// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) via SFINAE
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Logger Function
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;

struct Function {
	ll m;
	ll b;
	ll eval(ll x){
		if (m == LLONG_MAX) return LLONG_MAX;
		return m*x+b;
	}
	Function(){ m = LLONG_MAX;}
	Function(ll m_, ll b_): m(m_), b(b_){ }

};

ostream& operator<<(ostream &os, const Function &f){
    return  os << f.m << "x+" << f.b ; 
}

struct LiChaoTree {
	vll values;
	ll maxV;
	Function *functions;
	LiChaoTree(vll &values_){
		values = values_;
		sort(all(values));
		functions = new Function[sz(values) * 4 + 5];
		maxV = sz(values);
	}

    void imprimir(void){
        // for(int i=0; i<maxV; i++) DEBUG1  functions[i].m << "x+" << functions[i].b  << " ";
        // cout << "\n"; 
    }
	//Range from l to r - 1
	ll get(ll x){
		return get(x, 1, 0, maxV);
	}
	ll get(ll x, int v, int l, int r){
        DEBUG2 "llamando get\n";
        print(x,v,l,r);
		int m = l + (r - l) / 2;
		ll mv = values[m];

        print(m,mv);
		if ( l +1  == r){
            DEBUG1 "entro l+1==r\n";
            ll regresame =  functions[v].eval(x);
            DEBUG1 "tomar valor y regresar " << regresame << "\n";
			return regresame;
		} else if (x < mv){
			return min(functions[v].eval(x), get(x, 2 * v, l, m));
		} else {
			return min(functions[v].eval(x), get(x, 2 * v + 1, m, r));
		}
	}

	void addFunction(Function f){
		addFunction(f, 1, 0, maxV);
	}

	void addFunction(Function f, ll v, int l, int r){
        // print(v,l,r, functions);
		int m = l + (r - l) / 2;
		ll mv = values[m];
		ll lv = values[l];
		bool lef = f.eval(lv) < functions[v].eval(lv);
		bool mid = f.eval(mv) < functions[v].eval(mv);
		if (mid){//Si el actual pierde en el medio
			swap(functions[v], f);
		}
		if ( l  + 1== r)  return;
		else if (lef != mid){//El cruce esta en el lado izq
			addFunction(f, 2 * v,     l, m);
		} else {
			addFunction(f, 2 * v + 1, m, r);
		}
	}  

    void transformCoordToIndices( int &l , int &r){
        l = lower_bound(all(values), (ll)l) - values.begin();
        r = lower_bound(all(values), (ll)r) - values.begin();
    }

    void addSegmentFunction( Function fi, int li, int ri){
        transformCoordToIndices(li,ri);
        addSegmentFunction(fi,li,ri, 1,0,maxV );
    }

    void addSegmentFunction( Function fi, int l, int r, int v, int left, int right){
      
        DEBUG2 "\nAgregando fucnion .. :\n";
        print( fi, l, r );
        print( v, left, right);
        // agregar fi en intervalo [l,r)
        // en cordenadas no // en indeices si


        // nodo actual : idx = v rango =  [ left , right )
    
        
        if( r <= left  || right <= l) return;
        // completamente contneido 
        if( l <= left  && right <=  r  ){
            DEBUG2 "ahora si agregar aqui\n";
            print( fi,left, right);
            addFunction( fi, v, left, right);
            DEBUG3
            return;  // el resto se hare recursivo
        }
        
        if ( left +1 == right)  return;

        
        int m =  left + (right-left)/2;
        addSegmentFunction(fi, l, r, v * 2     , left, m);
        addSegmentFunction(fi, l, r, v * 2 + 1 , m, right);

    }

	~LiChaoTree(){ delete[] functions; }
};

// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

struct query{
    int tipo;
    ll l,r,a,b; // agregar f(x) = a x + b en [l,r]
    ll v; // minimo f_i(v)

};

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n,q; cin >> n >> q;

    // rectas f(x) = ax + b en segmentos [l,r]
    vll l(n),r(n),a(n),b(n);
    for( int i=0; i<n; i++){
        cin >> l[i] >> r[i] >> a[i] >> b[i];
    }

    // queries
    vector<query> queries(q);
    vll vals;
    set<ll> used;
    for( int i=0; i<q; i++){
        cin >> queries[i].tipo;
        // agregar otra recta
        if( queries[i].tipo == 0 ){
            cin >> queries[i].l >> queries[i].r >> queries[i].a >> queries[i].b;
        }
        // cosulta // min_i f_i(v)
        if( queries[i].tipo == 1){
            int v; cin >> v;
            queries[i].v = v;
            if( !used.count(v) ){ 
                vals.pb( queries[i].v);
                used.insert(v);
            }
        }
    }

    sort( all(vals) );
    print(vals);

    LiChaoTree lct(vals); // O( M log M) // M = sz(vals)

    print(vals);

    // agregar funciones // O( N log M ) // N functions
    for( int i=0; i<n; i++){
        DEBUG2 "agregar funcion:\n";
        print( a[i],b[i], l[i], r[i]);
        lct.addSegmentFunction( {a[i],b[i]}, l[i], r[i] );

        lct.imprimir();
    }

     for( int i=0; i<q; i++){
        // agregar otra recta
        if( queries[i].tipo == 0 ){
            DEBUG2 "quiery add:\n";
            print(queries[i].a,queries[i].b, queries[i].l, queries[i].r);
            lct.addSegmentFunction( {queries[i].a,queries[i].b},queries[i].l,queries[i].r );
            lct.imprimir();
        }
        // cosulta // min_i f_i(v)
        if( queries[i].tipo == 1){
            DEBUG2 "queri consulta\n";
            print( queries[i].v  );
            ll ans = lct.get( queries[i].v );
            if( ans != LLONG_MAX ) cout << ans << "\n";
            else cout << "INFINITY\n";
        }
    }



    
}
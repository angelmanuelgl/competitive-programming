/*
    
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez	
    11. Sky Code 
    https://www.spoj.com/problems/MSKYCODE/?__cf_chl_f_tk=v4DEHspqYQ6.jVz7.5sWiIXkpHu6KWuzdJTbxnjA4Mo-1783214556-1.0.1.1-AzeJombrJRBGK8mWaAYBbMo0ZeMGRjH7Iy3zcJCH8tQ
    
    / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * 
    este problema se puede hacer con PIE

    queremos saber S_1 = { (a,b,c,d) : a,b,c,d\in S,  gcd(a,b,c,d) = 1 }

    calculaos
    S_p = { (a,b,c,d) : a,b,c,d\in S,  gcd(a,b,c,d) = p }
    es facil notar que 
    S_1 = S - UNION_{p>1} S_p

    / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * / * 
    
    pero podemos hacerlo mas facil contando
    f(d)  =  |{ (a,b,c,d) : a,b,c,d\in S,  gcd(a,b,c,d) = d }|
    g(d)  =  |{ (a,b,c,d) : a,b,c,d\in S,  gcd(a,b,c,d) | d }|
    y notar que
    g(d) = SUM_{k: d|k} f(k)
    g(d) = SUM_{k multiplo de d} f(k)
    equivalentemente 
    asi 
    f(d) = g(d) - SUM_{k: d|k, k>d} f(k)
    f(d) = g(d) - SUM_{k es multiplo propio de d} f(k)

    notar que hay que calcular f desde el mayor hasta el menor 
    para que cuando calculemos f(d) ya tengamos todos los f(k) con k > d

    ahora el problema se traduce en calcular 
    g(d)  =  |{ (a,b,c,d) : a,b,c,d\in S,  gcd(a,b,c,d) | d }|
    lo cual es mas sencillo 
    (cantidad de multiplos de d en S)^4
*/

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

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

#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 


// const int MAXN = 1e4 + 5;
const int MAXN =10;
ll frec[MAXN];
ll mult[MAXN];
ll g[MAXN];
ll f[MAXN];




// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// uso :  g++ -DLOCAL K.cpp





int main(){
    #ifdef LOCALp
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n;

    while( cin >>  n  ){
        
        memset(frec, 0, sizeof(frec));
        memset(mult, 0, sizeof(mult));
        memset(g, 0, sizeof(g));
        memset(f, 0, sizeof(f));

        // input // contar frecuencias
        for(int i=0; i<n; i++){
            int a; cin >> a;
            frec[a]++;
        }

        // contamos los multiplo de cada numero
        // o(n log n) como la criba

        for( int i=1; i<MAXN; i++){
            for( int multiplo =i; multiplo < MAXN ; multiplo +=i ){
                mult[i] += frec[multiplo];
            }
        }


        // contamos la cantidad de cuartetos (a,b,c,d) tq gcd(a,b,c,d) | i
        for( int i=1; i<MAXN; i++){
           ll m = mult[i];
            if (m < 4) g[i] = 0;
            else g[i] = m * (m - 1) * (m - 2) * (m - 3) / 24;
            DEBUG cout << " i = " << i << ", mult[i] = " << mult[i] << "  g[i] = " << g[i] << "\n";
        }   


        // calculamos f[i] = cantidad de cuartetos (a,b,c,d) tq gcd(a,b,c,d) = i
        for( int i=MAXN-1; i>=1; i--){
            f[i] = g[i];
            for( int multiplo = i*2; multiplo < MAXN ; multiplo +=i ){
                f[i] -= f[multiplo];
            }
        }


        cout << f[1] << "\n";
    }
}
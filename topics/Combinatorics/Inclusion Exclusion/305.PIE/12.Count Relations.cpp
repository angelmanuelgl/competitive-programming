/*
    
    Principle of Inclusion and Exclusion (PIE)
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    12. Count Relations
    https://www.codechef.com/JAN11/problems/COUNTREL/
*/

/*  
    / / / / / / / / / / / / / / / / / / / /  / / / / /  / / / / / 
    R1  = { (x,y) : x no es subconjunto de y 
                    y no es subconjunto de x 
                    x \cap y = \emptyset }
    R1  = { (x,y) : x != \empyset
                    y != \empyset
                    x \cap y = \emptyset }
  

    Definimos
    U = { (x,y) : x \cap y = \emptyset }
    P1 = {(x,y) : x  = \empyset}
    P2 = {(x,y) : y  = \empyset}

    NOTAR QUE
    R1 = U \setminus (P1 \cup P2)

    Y sabemos las cardinalidades
    |U| = 3^n   (PENSAR EN DETALLE)
    |P1| = |P2| = 2^n
    |P1 \cap P2| = 1

    Por lo tanto
    |R1| = |U| - |P1| - |P2| + |P1 \cap P2| = 3^n -  2 * 2^n    + 1
    = 3^n - 2^(n+1) + 1
    
    * no olvidar dividir entre dos porque son pares no ordenadso

     / / / / / / / / / / / / / / / / / / / /  / / / / /  / / / /
    R2  = { (x,y) : x no es subconjunto de y 
                y no es subconjunto de x 
                x \cap y = \emptyset }

    Notar que 
    R1 \cup R2 = { (x,y) : x no es subconjunto de y 
                        y no es subconjunto de x }  =: S
    R1 \cap R2 = \emptyset

    asi
    |S| = |R1| + |R2| 

    Ahora solo teneos que saber |S|, para ello definimos
    U = { (x,y)^n : }
    A = { (x,y) : x es subconjunto de y }
    B = { (x,y) : y es subconjunto  de x }
    A\cap B = { (x,y) : x = y }
   
    asi
    S = U \setminus( A \cup B \cup C   )
    y adeas A,B,C son disjuntos

    y sabemos las cardialidades\
    |U| = 4^n
    |A|= |B| = 3^n  (PENSAR EN DETALLE)
    |A \cap B| = 2^n 

    Por lo tanto
    |S| = |A| + |B| - |A\cap B| = 4^n  - 3^n - 3^n + 2^n
    = 4^n - 2* 3^n + 2^n

    despejand
    |R2| = |S|- |R1| =  (4^n - 2* 3^n + 2^n) - (3^n - 2^(n+1) + 1)
    = 4^n - 3^(n+1) + 3* 2^n   -1

     * no olvidar dividir entre dos porque son pares no ordenadso

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


const int MOD = 100000007;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
ll exp_bin(ll base, ll exp){
    ll res = 1;
    while(exp > 0){
        if( exp & 1 ) res = (res * base) %MOD;
        base = (base * base) %MOD;
        exp >>= 1;
    }
    return res;
}


ll inverso( ll num){
    ll inv = exp_bin(num, MOD-2);
    return inv;
}

ll dividir( ll a, ll b){
    b = inverso(b);
    a = (a * b) %MOD;
    return a;
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    #ifdef LOCALp
        ifstream cin("in.txt");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin >> t;

    while( t-- ){
        ll n; cin >> n;

        DEBUG{
            cout << "n : " << n <<'\n';
            cout << "4^n : " << exp_bin(4,n) << "\n";
            cout << "3^n : " << exp_bin(3,n) << "\n";
            cout << "2^n : " << exp_bin(2,n) << "\n";
            cout << "2^(n+1) : " << exp_bin(2,n+1) << "\n";
        }
        ll r1 = exp_bin(3,n) - exp_bin(2,n+1) + 1;
        if( r1 < 0) r1+=MOD;
        r1 %=MOD;
        r1 = dividir(r1, 2);

        // ll r2 = exp_bin(4,n) - exp_bin(3,n+1)  + 3*exp_bin(2,n) - 1;
        ll r2 = exp_bin(4,n) - exp_bin(3,n+1); 
        if( r2 < 0 ) r2+= MOD;
        r2 %= MOD;
        r2 = r2  + ( (3*exp_bin(2,n)) %MOD) - 1;
        if( r2 < 0 ) r2+= MOD;
        r2 %= MOD;
        r2 = dividir(r2, 2);

        cout << r1 << " " << r2 << "\n";

        DEBUG cout << "\n";
        
    }


}
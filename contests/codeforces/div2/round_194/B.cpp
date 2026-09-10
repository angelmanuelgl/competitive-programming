/*  
    * Contest: Educational Codeforces Round 194 (Rated for Div. 2)
    * URL: https://codeforces.com/contest/2260
    * Problem: 

    * Topic: Contribution Tecnique 
    * Algorithm: Sum for intervals
    * Complexity: O(Y) 

    * Status: ACCEPT
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef __int128 lll;
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
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
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
#define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;


// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

lll techo( lll x, lll y){
    return (x+y-1)/y;
}

lll sum_gauss( lll l, lll r){
    if( l >= r) return 0;
    if( l< 0 ) return r*(r+1)/2;
    return r*(r+1)/2  - l*(l+1)/2;
}

lll max_i(lll c, lll x, lll y, lll k){
    if( c == 1) return k-1;
    lll denominador = y - c*x;
    if( denominador < 0 ) return -1;
    return min(k-1, denominador/(c-1));

}

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int t; cin >> t;

    while( t-- ){
        ll x,y,k;  cin >> x >> y >>k;


        if( x== y){
            cout << "0\n";
            continue;
        }

        // sum_{i=0}^{k-1}[ y + i - \piso{ (y+i)/(x+i)  }(y+i))
        //  = 
        // sum_{i=0}^{k-1} y + i    // (SUM1)
        // - 
        // sum_{i=0}^{k-1} \piso{ (y+i)/(x+i)  }(y+i) (**)
        lll sum1 = (lll) k*(lll)y + (lll)k*((lll)k-1)/2;



        // sum_{i=0}^{k-1} \piso{ (y+i)/(x+i)  }(y+i) *)
        //  = 
        // sum_{i=0}^{k-1} \piso{ (y+i)/(x+i)  }i (SUM2)
        // sum_{i=0}^{k-1} \piso{ (y+i)/(x+i)  }y (SUM3 sin el y)

        // suma de intervalos pesada
        // sum_{i=0}^{k-1} \piso{ (y+i)/(x+i)  }i
        lll sum2 = 0;  // suma por intervalos pesada

        // suma de intervalos
        // sum_{i=0}^{k-1} \piso{ (y+i)/(x+i)  }
        lll sum3 = 0; //  suma por intervalos

        // suma de intervalos vacia
        // debe dar k
        lll sum4 = 0; 
        

        lll lim = y/x + 5;

        // estamos sumando en el rango
        // tal que  // piso{ (y+i)/(x+i)  } ==c
        for( ll c=1; c <= lim; c++){
            
            // el i mas grande tal que // piso{ (y+i)/(x+i)  } >=c
            lll mayoresIguales =  max_i(c,x,y,k);

            // el i mas grande tal que // piso{ (y+i)/(x+i)  } >= c+1
            lll mayores=  max_i(c+1,x,y,k);

            if( mayoresIguales < 0 ) break;
            if( mayores <= -1 ) mayores = -1;

            // piso{ (y+i)/(x+i)  } == c
            lll iguales = mayoresIguales - mayores;

            sum2 +=  c *  sum_gauss(mayores,mayoresIguales);

            sum3 +=  c * iguales;

            sum4 += iguales;
        }


        // DEBUG{
        //     cout << " sum1 : " << sum1 << " ";
        //     cout << "  sum2 : " << sum2 << " ";
        //     cout << "  sum3 : " << sum3 << " ";
        //     cout << "  sum4 : " << sum4 << " ";
        //     cout << "  k : " << k << " \n";
        // }

    
        lll ans = sum1  - x*sum3 - sum2;
        ll rans = (ll) ans;
        cout <<  rans << "\n";



        // // comparar ocn la repsuesta real
        // DEBUG{
        //     ll sum2_real = 0;
        //     ll sum3_real = 0;
        //     ll sum23_real = 0;
        //     for( int i=0; i<k; i++){
        //         sum23_real += (y+i)/(x+i) * (x+i);
        //         sum2_real += (y+i)/(x+i) * (i);
        //         sum3_real += (y+i)/(x+i) ;
        //     }

        //     ll ansr = sum1 - sum23_real;

        //     cout << " ->" <<  ansr << "\n";
        //     cout << "  sum2 : " << sum2_real << " ";
        //     cout << "  sum3 : " << sum3_real << " \n";


        //     cout << "\n\n";
        // }
        
    }

    
}
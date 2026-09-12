/*  
    * Contest: Codeforces Round 481 (Div. 3)
    * URL: https://codeforces.com/contest/978
    * Problem: D. Almost Arithmetic Progression

    * Topic: brute force | implementation | arithmetic progression | math
    * Rating: 1500 
    * Algorithm: - try all possible values for the arithmetic progessions's common difference
                   (the interval [b2-b1-2, b2-b1+2]) 
                 - try all posibles values for the staring term
                   (b1-1,b1,b1+1)
    * Complexity: O(N)

    * Status: ACCEPTED
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
     
     
    // uso :  g++ -DLOCAL A.cpp
    int main(){
        #ifdef LOCAL
            ifstream cin("in.in");
        #else
            ios_base::sync_with_stdio(0); 
            cin.tie(0);
            cout.tie(0);
        #endif
     
     
        #ifdef LOCAL
        int t; cin >> t;
        while(t--){
        #else
     
        #endif
        
        int n; cin >> n;
        vi a(n); for( int & ai: a) cin >> ai;
     
        if( n==1 ){
            cout << "0\n";
            return 0;
        }
     
     
        int dif = a[1] - a[0];
        // las posibles dif son de dif -2 a dif +2     
        DEBUG{
            cout <<  " " << dif -2 << " " << dif +2 << "\n";
            cout <<   " " << a[0]-1 << " " << a[0]+1 << "\n";
        }
     
        int minimum_change = INT_MAX;
        bool algun_posible = false;
        for( int d = dif-2; d<= dif+2; d++){
     
            for( int ini = a[0]-1; ini <= a[0]+1; ini ++ ){
                
                int this_case_change = (ini == a[0])? 0 : 1;
                int ai = ini;
                bool posible = true;
                for( int i=1; i<n; i++){
                    ai += d;
     
                    if( a[i] == ai ) continue;
                    else if( a[i] -1 == ai ) this_case_change++;
                    else if( a[i] +1 == ai ) this_case_change++;
                    else{
                        posible = false;
                        break;
                    }
                }
     
                if( posible ){
                    algun_posible = true;
                    minimum_change = min(minimum_change, this_case_change);
                }
            }
     
        }
     
        if( algun_posible ){
            cout << minimum_change << "\n";
        }else{
            cout << "-1\n" ;
        }
        
     
     
     
     
        #ifdef LOCAL
        }
        #else
     
        #endif
    }
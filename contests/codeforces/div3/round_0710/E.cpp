/*  
    * Contest: Codeforces Round 710 (Div. 3)
    * URL: https://codeforces.com/contest/1506/countdown
    * Problem: E. Restoring the Permutation
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

    int t; cin >> t;

    while( t-- ){
        int n; cin >> n;
        vi arr(n);
        for( int &x : arr) cin >> x;


        print(n, arr);
        
        vector<bool> used_mini(n+1,false);
        vector<bool> used_maxi(n+1,false);
        vector<bool> caso_maxi(n+1,false);
        vi mini(n,0), maxi(n,0);
        used_mini[ arr[0] ] = true;
        mini[0] = maxi[0] = arr[0];
        for( int i=1; i<n; i++){
            if( arr[i] == arr[i-1] ) continue;
            mini[i] = maxi[i] = arr[i];
            used_mini[ arr[i] ] = true;
            used_maxi[ arr[i] ] = true;
            caso_maxi[ arr[i] ] = true;
        }

        // exicographically minimal permutation
        print( mini );
        print(maxi);
        // para el minimo
        int idx = 1;
        for( int i=0; i<n; i++){
            // si ya esta puesto
            if( mini[i] ) continue;
            // si no esta pouesto aun le ponermos el menor posible
            while( used_mini[idx] ) idx++;
            mini[i] = idx;
            used_mini[idx] = true;
        }

        // lexicographically maximum permutation).
        vi last_aviable(n);
        iota( all(last_aviable), -1);
        print(last_aviable);

        priority_queue<int> q;
        int lastValPut = 0;
        // for( int i=1; i< lastValPut; i++) q.push(i);
        for( int i=0; i<n; i++){
            // si ya esta puesto
            if( maxi[i] ){
                print( lastValPut+1, maxi[i] );
                for( int j= lastValPut+1; j< maxi[i]; j++ ){
                     q.push( j);
                     print("push", j);
                }
                   

                lastValPut =  maxi[i];

                
                print("ya esta", i,maxi);
                continue;
            }
            print("hi");
            int put = q.top(); 
            print(put);
            q.pop();
            maxi[i] = put;

            print(i,maxi);
        }
        

        for( int i=0; i<n; i++)
            cout << mini[i] << " \n"[i==n-1];

        for( int i=0; i<n; i++)
            cout << maxi[i] << " \n"[i==n-1];

        DEBUG cout << "\n";
    }
}
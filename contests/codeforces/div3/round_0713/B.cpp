/*  
    * Contest: Codeforces Round 713 (Div. 3)
    * URL: https://codeforces.com/contest/1512
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

    while(t--){
        int n; cin >> n;
        vector<vector<char>> arr (n+1, vector<char>(n+1));

        int x1=-1, y1=-1, x2,y2; 

        for( int i=1; i<=n; i++){
        for( int j=1; j<=n; j++){
            cin >> arr[i][j];
            if( arr[i][j] =='*'){
                if( x1 == -1) x1=i,y1=j;
                else x2=i,y2=j;
            }
        }
        }
       DEBUG{
            for( int i=1; i<=n; i++){
            for( int j=1; j<=n; j++){
                cout << arr[i][j] << " ";
            } cout << "\n";
            }
            cout << "\n";
       }
        if( y2== y1){
            int other_y = (y1<n)? y1+1: 1;
            arr[x1][other_y] = '*';
            arr[x2][other_y] = '*';
        }
        else if( x1 == x2 ){
             int other_x = (x1<n)? x1+1: 1;
            arr[other_x][y2] = '*';
            arr[other_x][y1] = '*';
        }
        else{
            arr[x1][y2] = '*';
            arr[x2][y1] = '*';
        }
      

        for( int i=1; i<=n; i++){
        for( int j=1; j<=n; j++){
            cout << arr[i][j] ;
        } cout << "\n";
        }
        DEBUG3
    }
}
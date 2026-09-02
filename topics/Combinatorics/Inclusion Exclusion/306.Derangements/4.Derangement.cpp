/*  
    
    Inclusion and Exclusion (PIE) // Derangements
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez
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

bool debug =  true;
#define DEBUG if(debug)
#define NODEBUG if(!debug)

const int MOD = 1e9 + 7;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 



// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ifstream cin("in.txt");
    int n; cin >> n;
    int arr[n+1];
    

    vector<int> fijos;
    for( int i=1; i<=n ; i++ ){
        cin >>  arr[i];
        if( arr[i] == i ) fijos.pb(i);
        // cout << arr[i] << '\n';
    }



    int cnt = fijos.size();
    // cout << "cnt: " << cnt << '\n';


    if( cnt %2 == 0 ){
        cout << cnt/2 << '\n';
        for(  int i=0; i<cnt ; i+=2)
            cout << fijos[i] << ' ' << fijos[i+1] <<  "\n";
        return 0;
    }

    
    /// no olvidar n >= 2
    // si hay una  cantidad impar
    if( cnt == 1 ){
        cout << "1\n";
        // si n== 2 no es posible solo cnt =1
        // si n > 3 // cualqueira
        cout << fijos[0] << " " << (fijos[0]-1+1)%n + 1 << '\n';
        return 0;
    }



    // hay almenos 3
    cout << (cnt+1)/2 << '\n';
    cout << fijos[0] << ' ' << fijos[1] << '\n';
    cout << fijos[1] << ' ' << fijos[2] << '\n';

    for(  int i=3; i<cnt ; i+=2)
        cout << fijos[i] << ' ' << fijos[i+1] <<  "\n";
    return 0;
}
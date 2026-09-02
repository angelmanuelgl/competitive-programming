/*
    https://www.spoj.com/problems/SUMMATION/
    topic-list/contribution_technique   4.SUMMATION
    Angel Manuel Gonzalez Lopez
*/
// // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // 

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

const int MOD = 100000007;

// // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ifstream cin("in.txt");

    int t; cin >> t;
    for( int i=1; i<=t; i++){
        int n; cin >> n;
        ll ans = 0;
        for( int i=0; i<n; i++){
            int x; cin >> x;
            ans = (ans+x) %MOD;
        }



        
        //  2 ^ (n-1)
        ll pow = 1;
        for( int i=1; i<=n-1; i++){
            pow = (pow*2) %MOD;
        }
        
        ll ansf = ans * pow %MOD;
        cout << "Case " << i << ": " << ansf << '\n';

    }

}
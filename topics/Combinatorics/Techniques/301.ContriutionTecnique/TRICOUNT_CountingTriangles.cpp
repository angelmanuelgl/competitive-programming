#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
bool debug =  false;
#define DEBUG if(debug)

const int MOD = 998244353;

const int maxn= 1e6+5;
// const int maxn= 4;
ll ans[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // casos bases
    ll v=0, sum=0, tri=1; 
    ans[1] = 1;


    // rellenar
    for( int i=2; i<maxn; i++ ){
        v+= (i-1);
        sum += v;
        tri += i*2-1;
        ans[i] = sum + tri;

        DEBUG{
            cout << " sum[ " << i << " ] = " << sum << '\n';
            cout << " tri[ " << i << " ] = " << tri << '\n';
            cout << " v[ " << i << " ] = " << v << '\n';
            cout << " v[ " << i << " ] = " << v << '\n';
        }

       
    }

    int t; cin >> t;
    while( t-- ){
        int n; cin >> n;
        cout << ans[n] << '\n';
    }

}
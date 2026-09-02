#include<bits/stdc++.h>
using namespace std;



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t,n; cin >> t;
    for( int i=1; i<=t; i++){
        cin >> n;
        // n = i;
        cout << 1ll + 4*(n-1) + 4*(n-1)*(n-2)/2 + 1ll*2*(n-1)*(n-2)*(n-3)/6 << '\n';
        // cout << "\n\n";
    }
}
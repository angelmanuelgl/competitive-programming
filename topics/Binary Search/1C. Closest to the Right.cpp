#include<bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n,k;
    cin >> n >> k;


    int arr[n];
    for( int i=0; i<n; i++ ) cin >> arr[i];

    /// el minimo que es mayor igual
    int x;
    while(k--){
        cin >> x;
        //l es menor y r es mayor igual
        int l=-1 , r=n;  //arr[-1]=-\infty arr[n]=\infty \c /
        while( l+1<r ){
            int m = (l+r)/2;
            if( arr[m] < x ) l= m;
            else r= m;
        }
        cout << r+1 << '\n';
    }

}

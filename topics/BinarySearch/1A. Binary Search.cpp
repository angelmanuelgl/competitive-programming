#include<bits/stdc++.h>
using namespace std;
//https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/A
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

   int n,k;
   cin >> n >> k;

   int arr[n];
   for( int i=0; i<n; i++ ) cin >> arr[i];

   int x;
   while(k--){
        cin >> x;
        bool esta=false;
        int l=0, r=n;
        while( l<=r ){
            int m = (l+r)/2;

            if( arr[m]== x ){
                esta= true;
                break;
            }else if( arr[m]< x ) l= m+1;
            else if( x < arr[m] ) r= m-1;
        }
        if( esta )cout << "YES\n";
        else cout << "NO\n";

   }

}

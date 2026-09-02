#include<bits/stdc++.h>
using namespace std;


typedef int64_t ll;

const int MOD = 1000000007;
DSDSDSDSDSD

const int MAXN = 1000005; // Ajusta según el límite del problema
ll arr[MAXN];
ll sum[MAXN];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ifstream cin("in.txt");

    int n; cin >> n;
    for( int i=0; i<n; i++){
        cin >> arr[i];

    }

    if( n==1) {
        cout << "0\n";
        return 0;
    }

    sort( arr, arr+n );

    sum[n-1] =  arr[n-1];
    for( int i=n-2; i>=0; i--){
        sum[i] = sum[i+1]  + arr[i];
        sum[i] %= MOD;
    }
    

    ll ans=0;
    for( int i=0; i<n-1; i++){
        ll unaparte = arr[i]*(n-1-i) %MOD;
        
        ans +=   sum[i+1] - unaparte ;
        // OJO: A> B no implica A mod M > B mod M
        ans += MOD; // el +MOD es por si sacando modulos se vuelve negativo// aunque realente no es negativo
        ans %= MOD;
    }

    for( int i=1; i<=n-2; i++){
        ans *= 2;
        ans %= MOD;
    }

    cout << ans  << '\n';
}

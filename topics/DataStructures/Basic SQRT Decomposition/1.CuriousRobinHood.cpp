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

const int MOD = 1e9 + 7;

// codigo en papel
// start programar 3:56
// wrong answer 4:22
// acepted 4:34

const int MAXN = 1e5 + 5;
const int BLOCK_SIZE = 320;// sqrt( 1e5)

int a[MAXN];
int block_sum[MAXN / BLOCK_SIZE + 5];
int n,q;

void construir(){
    memset( block_sum, 0, sizeof(block_sum));
    for( int i=0; i<n; i++){
        block_sum[ i/BLOCK_SIZE  ] +=a[i];
    }
}

void actualizar( int i, int val ){
    block_sum[i/BLOCK_SIZE] -=  a[i];
    a[i] = val;
    block_sum[i/BLOCK_SIZE] +=  a[i];
}

int query_sum( int l, int r){
    int sum = 0;
    int cl = l / BLOCK_SIZE;
    int cr = r / BLOCK_SIZE;
    if( cl == cr ){
        for(  int i=l; i<=r; i++) sum += a[i];
    }else{
        int fin = min( (cl+1)*BLOCK_SIZE - 1, r) ;
        for( int i=l; i<=fin; i++ ) sum+=a[i];
        for( int i=cl+1; i<cr; i++ ) sum+= block_sum[i];
        for( int i=cr*BLOCK_SIZE; i<=r; i++ ) sum+=a[i];
    }

    return sum;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t; cin >> t;

    int tipo,i,v,j;


    int caso=1;
    while( t--){
        cin >> n >> q;

        
        memset( a, 0, sizeof(a));
        for( int i=0; i<n; i++) cin >> a[i];
        construir(); 
        
        cout << "Case " << caso++ << ":\n";
        while(q--){
            cin >> tipo; 

            if( tipo == 1 ){
                cin >> i;
                cout << a[i] <<'\n';
                actualizar( i, 0 );

            }else if( tipo == 2){
                cin >> i >> v;
                actualizar( i, a[i] + v );

            }else if( tipo== 3 ){
                cin >> i >> j;
                cout << query_sum( i , j) << '\n';
            }

        }
        

    }

    

}


/*  
    Inclusion and Exclusion // 307. Inclusion Exclusion on Multiples
    youkn0wwho.academy/topic-list
    Angel Manuel Gonzalez Lopez

    
    contar cantidad de aprjeas primas relatias hasta n

    ! podemos usar lp y funcion phi, 
    ! pero aqu propogno como calcular phi con criba

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



const int MAXN = 1e5 +5;
int phi[MAXN];
void phi_criba(){
    for( int i=0; i<MAXN; i++) phi[i] = i;

    for( int p=2; p<MAXN; p++){
        if( phi[p] == p) { // si p es primo
            for( int j = p; j < MAXN; j += p){
                //  phi(j) = phi(j) * (1 - 1/p)
                //  phi(j) = phi(j) -  phi[j] / p
                phi[j] -= phi[j] / p;
            }
        }
    }
}

ll acum[MAXN];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    // precalcilar la cantidad de primos relativos menores a i
    phi_criba();
    
    for( int i=1; i<MAXN; i++){
        acum[i] = acum[i-1] + phi[i];
    }



    int caso=0,t; cin>> t;

    while( ++caso<=t){
        int n;
        cin >> n;
        ll total = (ll)n * (n - 1) / 2 + n;
        cout << "Case " << caso << ": " << total-acum[n] << '\n';
    }
    
}
    
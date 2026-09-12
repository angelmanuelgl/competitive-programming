/*  
    * Contest: Codeforces Round 481 (Div. 3)
    * URL: https://codeforces.com/contest/978
    * Problem: G. Petya's Exams

    * Topic: greedy | implementation | sortings
    * Rating:  1700
    * Algorithm: Each day, we study for the nearest upcoming exam
                 We iterate through the days from 1 to n, for each day
                  - if an exam question has been released: 
                     we add the days required to study to a priority queue
                     using weight : - (day the of exam )
                  - note that, in the priority queue the next element will be
                    the nearest upcoming examn. And the maximun size is N*M
                    because ci <= N and i<=M
                  - we study for the nearest upcoming exam

                 After all days, we verify if the priority queue is empty
                 and check that for each exam study day, we check is the exam
                 takes place on a later day
    * Complexity: N days
                  M Exams
                  O( M *N log( N*M )  ) time
                  O( NM ) memory
    * ToDo: try on O( N log M ) and O(N+M) memory
    * Status: ACCEPTED
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
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
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
#define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
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


    #ifdef LOCAL
    int t; cin >> t;
    while(t--){
    #else

    #endif

    int n, m; cin >> n >> m;
    

    // day //
    // indice del examen que se hace este dia o 0
    vi examenes(n+3,0);
    // cada dia tiene un vector con los examenes que se publican ese dia
    vi publicacion[n+3];

    // idx //
    vi days_needed(m+3); // idx to days neded for examen idx
    vi day_of_examen(m+3); // idx to day of examen idx

    int si,di,ci;
    for( int i=1; i<=m; i++){
        cin >> si >> di >> ci;
       

        // publican pregutnas
        publicacion[ si ].pb(i);

        // dia de aplicacion
        examenes[ di ] = i;
        day_of_examen[i] = di;


        // cuantos dias necesito
        days_needed[i] = ci;
    }

    vi ans(n+3,0);
    // la cola la ordenaremos segun que examen queda antes
    priority_queue< pii > pending_study_days;
    for( int day=1; day<=n; day++){
        // ver que examenes se publican
        // y poner los dias de estudioa  al cola
        for( int i=0; i< sz(publicacion[day]); i++  ){
            int idx_examen_publicado = publicacion[day][i];
            int necesita_estudiar = days_needed[  idx_examen_publicado ];
            int dia_del_examen = day_of_examen[  idx_examen_publicado ];

            for( int k=1;k<= necesita_estudiar; k++ )
                pending_study_days.push({ -dia_del_examen, idx_examen_publicado});

        } 

        // si es un dia de examen
        if( examenes[day] != 0 ){
            ans[day] = m+1;
            continue;
        }

        // si no hay examen 

        // y no hay estudio pendiente
        if( pending_study_days.empty() ){
            ans[day] = 0;
            continue;
        }

        // entonces hay estudio pendeinte
        pii tmp = pending_study_days.top(); pending_study_days.pop();
        ans[day] = tmp.se;
        
    }

    bool posible = true;
    // si al acabar los dias y examenes me quedaron estuidos pendientes no s epuede
    if( !pending_study_days.empty() ) posible = false;

    // si para algun examen tuve que estudiar depsues del examen
    for( int i=1; i<=n && posible; i++){
        if( ans[i] == m+1 || ans[i] == 0) continue;

        // este dia estudiamos para ans[i]
        if( day_of_examen[ ans[i] ] <= i ){
            posible = false;
            break;
        }

    }

    print(ans);

    if( !posible ) cout  << "-1\n";
    else{
        for( int i=1; i<=n; i++) cout << ans[i] << " \n"[i==n];
    }
    

    DEBUG cout << "\n\n";
    #ifdef LOCAL
    }
    #else

    #endif
    
}
#include<bits/stdc++.h>
using namespace std;

//Grafo de 1 a n
const int N = 2e5 + 9;

vector<int> g[N];
vector<int> t[N], rg[N], bucket[N]; //t = dominator tree of the nodes reachable from root
int tPar[N];
//semidominator, parent in dfs tree, immediate dominator
//parent in dsu, nodo with minimum sdom in the path until current union
int sdom[N], par[N], idom[N], dsu[N], label[N];
int id[N], rev[N], T;

int find_(int u, int x = 0) {
    if(u == dsu[u]) return x ? -1 : u;
    int v = find_(dsu[u], x+1);
    if(v < 0)return u;
    if(sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
}

void dfs(int u) {
  T++; id[u] = T;
  rev[T] = u; label[T] = T;
  sdom[T] = T; dsu[T] = T;
  for(int i = 0; i < g[u].size(); i++) {
      int w = g[u][i];
      if(!id[w]) dfs(w), par[id[w]] = id[u];
      rg[id[w]].push_back(id[u]);
  }
}

void clearStructures(int n){
  for(int i = 0; i <= n; i++) {
    t[i].clear(), g[i].clear(), rg[i].clear(), bucket[i].clear();
    tPar[i] = i;
    sdom[i] = par[i] = idom[i] = dsu[i] = label[i] = id[i] = rev[i] = 0;
  }
}

//raíz, número de nodos
//Esta es la función que hay que llamar
void build(int r, int n) {
  dfs(r);
  n = T;
  for(int i = n; i >= 1; i--) {
    for(int j = 0; j < rg[i].size(); j++) sdom[i] = min(sdom[i], sdom[find_(rg[i][j])]);
    if(i > 1) bucket[sdom[i]].push_back(i);
    for(int j = 0; j < bucket[i].size(); j++) {
      int w = bucket[i][j];
      int v = find_(w);
      if(sdom[v] == sdom[w]) idom[w] = sdom[w];
      else idom[w] = v;
    }
    if(i > 1) dsu[i] = par[i];
  }
  for(int i = 2; i <= n; i++) {
    if(idom[i] != sdom[i]) idom[i]=idom[idom[i]];
    t[rev[i]].push_back(rev[idom[i]]);
    t[rev[idom[i]]].push_back(rev[i]);
    tPar[rev[i]] = rev[idom[i]];
  }
}




int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  while(cin >> n >> m) {
		clearStructures(n);
    T = 0;
		for (int i = 0; i <= n; i++){
			st[i] = en[i] = 0;
		}
    vector<pair<int, int>> ed;
    for(int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      ed.push_back({u, v});
    }
    build(1, n);
    T = 0;
    yo(1);
    vector<int> ans;
    for(int i = 0; i < m; i++) {
      int u = ed[i].first, v = ed[i].second;
      if(st[u] && !(st[v] <= st[u] && en[u] <= en[v])) ans.push_back(i);
    }
    yo(1);
    cout << ans.size() << '\n';
    for(auto x: ans) cout << x + 1 << ' ';
    cout << '\n';
  }
  return 0;
}

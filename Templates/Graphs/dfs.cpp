#include<bits/stdc++.h>
using namespace std;

const int N = 100+20, M = 100+20;
vector<vector<int>> adj[N];
bool vis[N];
int n, m, cnt;

void dfs(int v){
	vis[v] = true;
	++cnt;
	for(auto &u: adj[v])
		if(!vis[u]) dfs(u);

}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	dfs(1);
	if (cnt == n) cout << "connected\n";
	else cout << "NotConnected\n";
}

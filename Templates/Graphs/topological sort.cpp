#include<bits/stdc++.h>
using namespace std;

const int N = 100+20, M = 100+20;
vector<vector<int>> adj(N);
bool vis[N];
int n, m;
vector<int> ans;
void dfs(int v){
	if(!vis[v]){
		vis[v] = true;
		for(auto &u: adj[v])
			if(!vis[u]) dfs(u);
		ans.emplace_back(v);
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
	}
	for(int i = 1; i <= n; ++i)
		dfs(i);
	reverse(ans.begin(),ans.end());
	for(auto &i: ans) cout << i << ' ';
	cout << '\n';
}

class Solution {
public:
    void check(int m, int n, vector<vector<int>>& pref, vector<vector<bool>>& vis){
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(pref[i][j] != 0) vis[i][j] = 1;
            }
        }
    }
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<bool>> vis(m, vector<bool> (n));
        vector<vector<int>>init(m, vector<int>(n));
        for(auto &i: guards){
            init[i[0]][i[1]] =  1;
        }
        for(auto &i: walls){
            init[i[0]][i[1]] =  -2e7;
        }
        // right direction
        vector<vector<int>> pref = init;
        for(int i = 0; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(pref[i][j-1] < 0) continue;
                pref[i][j] += pref[i][j-1];
            }
        }
        check(m, n, pref, vis);
        // left direction
        pref = init;
        for(int i = 0; i < m; ++i){
            for(int j = n-2; j >= 0; --j){
                if(pref[i][j+1] < 0) continue;
                pref[i][j] += pref[i][j+1];
            }
        }
        check(m, n, pref, vis);
        // down direction
        pref = init;
        for(int j = 0; j < n; ++j){
            for(int i = 1; i < m; ++i){
                if(pref[i-1][j] < 0) continue;
                pref[i][j] += pref[i-1][j];
            }
        }
        check(m, n, pref, vis);
        // up direction
        pref = init;
        for(int j = 0; j < n; ++j){
            for(int i = m-2; i >= 0; --i){
                if(pref[i+1][j] < 0) continue;
                pref[i][j] += pref[i+1][j];
            }
        }
        check(m, n, pref, vis);

        int ans = 0;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(vis[i][j] == 0) ++ans;
            }
        }
        return ans;
    }
};

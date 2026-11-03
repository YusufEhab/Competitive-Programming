class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mx = nums[0], ans = 0;
        for(auto &i: nums) mx = max(mx, i);
        for(auto &i: nums) ans += mx-i;
        return ans;
    }
};

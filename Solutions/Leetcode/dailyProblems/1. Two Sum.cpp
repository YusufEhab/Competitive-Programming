class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // this code could be better in linear time using two pointers 
        vector<int> ans(2);
        bool found = false;
        for(int i = 0; i < nums.size()-1; ++i){
            for(int j = i+1; j < nums.size(); ++j){
                if(nums[i]+nums[j] == target){
                    ans[0] = i, ans[1] = j;
                    found = true;
                    break;
                } 
            }
            if(found) break;
        }
        return ans;
    }
};

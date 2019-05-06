// 用于生成所有子序列

#include <vector>
using namespace std;
bool compare(const vector<int> &a, const vector<int> &b){
    return a.size()>b.size();
}
void dfs(int i, vector<int>& nums, vector<int>& cur, vector<vector<int>>& res)
{
    res.emplace_back(cur);
    if(i >= nums.size())
        return;
    for(int j = i; j < nums.size(); ++j)
    {
        cur.push_back(nums[j]);
        dfs(j + 1, nums, cur, res);
        cur.pop_back();
    }
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> cur;
    dfs(0, nums, cur, res);
    return res;
}
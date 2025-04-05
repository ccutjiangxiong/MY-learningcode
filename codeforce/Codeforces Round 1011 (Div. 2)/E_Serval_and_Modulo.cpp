class Solution {
   public:
    long long minTime(vector<int>& skill, vector<int>& mana) {


        int n = skill.size();  
        int m = mana.size();   

        vector<vector<long long>> dp(n, vector<long long>(m, 0));

        dp[0][0] = (long long)skill[0] * mana[0];
        for (int j = 1; j < m; j++) {
            dp[0][j] = dp[0][j - 1] + (long long)skill[0] * mana[j];
        }
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][0] + (long long)skill[i] * mana[0];
            for (int j = 1; j < m; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + (long long)skill[i] * mana[j];
            }
        }
        return dp[n - 1][m - 1];
    }
};
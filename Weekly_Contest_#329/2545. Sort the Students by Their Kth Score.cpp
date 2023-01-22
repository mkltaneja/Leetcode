class Solution {
public:
    
    vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) 
    {
        sort(score.begin(), score.end(), [&](auto const &a, auto const &b){
            return a[k] > b[k];
        });
        
        return score;
    }
};

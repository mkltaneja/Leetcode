
// Time Complexity = O(19*n*m)
// Space Complexity = O(3*n*m)

class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) 
    {
        int n = image.size(), m = image[0].size();
        vector<vector<vector<int>>> average(n, vector<vector<int>>(m, vector<int>(2, 0)));
        vector<vector<int>> result(n, vector<int>(m, 0));
        for(int i = 0; i+2 < n; i++)
        {
            for(int j = 0; j+2 < m; j++)
            {
                int isValid = 1, sum = 0;
                for(int x = i; x < i+3; x++)
                {
                    for(int y = j; y < j+3; y++)
                    {
                        sum += image[x][y];
                        int c = (i+2-x)? abs(image[x][y] - image[x+1][y]) <= threshold : 1;
                        int d = (j+2-y)? abs(image[x][y] - image[x][y+1]) <= threshold : 1;
                        isValid &= (c && d);
                    }
                }
                if(isValid)
                    for(int x = i; x < i+3; x++)
                        for(int y = j; y < j+3; y++)
                            average[x][y][0] += sum / 9, average[x][y][1]++;
            }
        }
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int sum = average[i][j][0], cnt = average[i][j][1];
                result[i][j] = cnt? (sum / cnt) : image[i][j];
            }
        }
        return result;
    }
};

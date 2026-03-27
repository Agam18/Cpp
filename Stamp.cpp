
https://leetcode.com/problems/stamping-the-grid/solutions/7517228/prefix-sum-approach-memory-beats-100-by-8hlfv/
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& g, int h, int w) {
        int m = g.size();
        int n = g[0].size();

        int p[m][n];
        memset(p,0,sizeof(p));

        // prefix sum to compute number of blocked cells in this sub matrix
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                int x = 0;
                int y = 0;
                int z = 0;
                p[i][j] = g[i][j];
                if(i-1 >= 0) p[i][j] += p[i-1][j];
                if(j-1 >= 0) p[i][j] += p[i][j-1];
                if(i-1>=0 && j-1>=0) p[i][j] -= p[i-1][j-1];
            }
        }

        // mark stamp starting points
        int stamp[m][n];
        memset(stamp,0,sizeof(stamp));

        for(int i = 0;i <= m-h;i++){
            for(int j = 0;j <= n-w;j++){
                int cnt = p[i+h-1][j+w-1];
                if(j-1>=0) cnt -= p[i+h-1][j-1];
                if(i-1>=0) cnt -= p[i-1][j+w-1];
                if(i-1>=0 && j-1>=0) cnt += p[i-1][j-1];

                if(cnt == 0) stamp[i][j] = 1;
            }
        }


        memset(p,0,sizeof(p));

        // compute prefix sum for stamp
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                int x = 0;
                int y = 0;
                int z = 0;
//                p[i][j] = stamp[i][j];
                if(i-1 >= 0) stamp[i][j] += stamp[i-1][j];
                if(j-1 >= 0) stamp[i][j] += stamp[i][j-1];
                if(i-1>=0 && j-1>=0) stamp[i][j] -= stamp[i-1][j-1];
            }
        }


        // check if all non-blocked cells are covered by atleast 1 stamp
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(g[i][j] == 1) continue; // skip blocked cells

                int cnt = stamp[i][j];

                if(i-h>=0) cnt -= stamp[i-h][j];
                if(j-w>=0) cnt -= stamp[i][j-w];
                if(i-h>=0 && j-w>=0) cnt += stamp[i-h][j-w];

                if(cnt == 0) return false;
            }
        }

        return true;
    }
};
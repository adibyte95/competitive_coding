/*
  https://leetcode.com/problems/possible-bipartition/
*/
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        // Check for bipartite graph can be done using 2-color graph coloring.
        // Idea is to use two colors and assign colors to each node such that
        // each adjacent node gets a different color, if we this assignment is not
        // possible, then it is not bipartite
        
        // create the graph
        vector<vector<int>> g(N);
        for(auto &edge: dislikes) {
            g[edge[0] - 1].emplace_back(edge[1] - 1);
            g[edge[1] - 1].emplace_back(edge[0] - 1);
        }
        // for keeping track of color of each node
        // -1: unvisited
        // 0: color 1
        // 1: color 2
        vector<int> color(N, -1);
        // in case of disconnected graph
        for(int i = 0; i < N; i++) {
            // take the current as root node
            if(color[i] == -1) {
                // color it 
                color[i] = 1;
                queue<int> q;
                q.emplace(i);
                
                while(!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    
                    // color the adjacent nodes
                    for(int adj = 0; adj < g[curr].size(); adj++) {
                        int adj_idx = g[curr][adj];
                        if(color[adj_idx] == -1) {
                            // color it to mark visited
                            color[adj_idx] = 1 - color[curr];
                            q.emplace(adj_idx);
                        }
                        else if(color[adj_idx] == color[curr])
                            return false;
                    }
                }
            }
        }
        return true;
    }
};

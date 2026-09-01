class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        int litter_idx[20][20];
        memset(litter_idx, -1, sizeof(litter_idx));
        
        int K = 0;
        
        // 1. Locate the Start 'S' and uniquely index all Litters 'L'
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                } else if (classroom[i][j] == 'L') {
                    litter_idx[i][j] = K++;
                }
            }
        }
        
        // If there's no litter in the classroom, 0 moves are required.
        if (K == 0) return 0;
        int target_mask = (1 << K) - 1;
        
        // 2. max_eng[r][c][mask] stores the maximum energy seen at (r, c) holding `mask`
        // Initialized to -1 to represent unvisited states.
        int max_eng[20][20][1024];
        memset(max_eng, -1, sizeof(max_eng));
        
        // 3. Queue configuration: tuple<row, col, bitmask, current_energy, distance_moved>
        queue<tuple<int, int, int, int, int>> q;
        q.push({start_r, start_c, 0, energy, 0});
        max_eng[start_r][start_c][0] = energy;
        
        int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        // 4. Run standard BFS
        while (!q.empty()) {
            auto [r, c, mask, eng, dist] = q.front();
            q.pop();
            
            // Re-prune in case a better energy was pushed & processed to this exact state while this waited in Q
            if (eng < max_eng[r][c][mask]) continue;
            
            for (auto& d : dirs) {
                int nr = r + d[0];
                int nc = c + d[1];
                
                // Bounds and Obstacle checking
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                if (classroom[nr][nc] == 'X') continue;
                
                int n_eng = eng - 1;
                // If it costs more energy than we have just to step in, it's invalid
                if (n_eng < 0) continue;
                
                int n_mask = mask;
                if (classroom[nr][nc] == 'L') {
                    n_mask |= (1 << litter_idx[nr][nc]);
                }
                
                // Found all litters — BFS guarantees it's the minimum moves
                if (n_mask == target_mask) return dist + 1;
                
                // Replenish energy if we step onto a Reset area
                if (classroom[nr][nc] == 'R') {
                    n_eng = energy;
                }
                
                // Only queue if stepping into this state gives us strictly more energy than known before
                if (n_eng > max_eng[nr][nc][n_mask]) {
                    max_eng[nr][nc][n_mask] = n_eng;
                    q.push({nr, nc, n_mask, n_eng, dist + 1});
                }
            }
        }
        
        return -1; // Exhausted all paths without finding the target
    }
};
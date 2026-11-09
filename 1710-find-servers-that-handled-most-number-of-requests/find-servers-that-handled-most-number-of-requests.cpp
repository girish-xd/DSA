class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        
        // Min-heap to keep track of busy servers.
        // Stores pairs of {end_time, server_id}.
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy;
        
        // Array to count the number of requests handled by each server.
        vector<int> count(k, 0);
        
        for (int i = 0; i < arrival.size(); ++i) {
            long long arr_time = arrival[i];
            long long duration = load[i];
            
            // Free up servers that are done with their requests before or at the current arrival time
            while (!busy.empty() && busy.top().first <= arr_time) {
                available.insert(busy.top().second);
                busy.pop();
            }
            
            // If there are no available servers, the request is dropped
            if (available.empty()) {
                continue; 
            }
            
            // Find the next available server starting from index (i % k)
            auto it = available.lower_bound(i % k);
            
            // If no server >= (i % k) is available, wrap around to the first available server
            if (it == available.end()) {
                it = available.begin();
            }
            
            int server_id = *it;
            
            // Assign the request: remove from available, push to busy, increment handle count
            available.erase(it);
            busy.push({arr_time + duration, server_id});
            count[server_id]++;
        }
        
        // Find the maximum number of requests handled
        int max_requests = *max_element(count.begin(), count.end());
        vector<int> result;
        
        // Collect all servers that handled the maximum number of requests
        for (int i = 0; i < k; ++i) {
            if (count[i] == max_requests) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};
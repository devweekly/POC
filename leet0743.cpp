#include <vector>
#include <queue>
#include <climits>
#include <iostream>

/*
有 n 个网络节点，标记为 1 到 n。
给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。
现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
*/
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int nodeSize, int startingPoint) {
        // 建立邻接表表示图
        // source: time[0] 
        // target: time[1]
        // duration: time[2]
        vector<vector<pair<int, int>>> graph(nodeSize + 1);
        for (auto& time : times) {
            // graph index对应source，里面存放的是一个{targe, duration}的pair
            graph[time[0]].push_back({time[1], time[2]});
            cout << "---- " << time[0] << " target: " << time[1] << endl;
        }
        cout << "---- graph vector created, filled with first param. Vector size: " << nodeSize + 1 << endl;

        // 初始化距离数组
        vector<int> distanceToStarting(nodeSize + 1, INT_MAX);
        // 起始点自己的距离是0
        distanceToStarting[startingPoint] = 0;

        cout << "---- distances vector created, distances[" << startingPoint << "] is startingPoint, with value 0" << endl;

        // 使用优先队列优化BFS，每次取出距离最小的节点
        // begin, end, 比较器
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priority_q;
        // {距离, 起始节点}
        priority_q.push({0, startingPoint}); 

        cout << "---- priority_queue created, push {0, " << startingPoint << "} as front" << endl;

        cout << "-----------------------" << endl;

        while (!priority_q.empty()) {
            auto [prevDistance, u] = priority_q.top();
            priority_q.pop();

            cout << "-------- whileloop begin to pop up queue, prevDistance: " << prevDistance << ", starting point: " << u << endl;

            // 剪枝：如果当前距离大于已知距离，则跳过
            // 为什么？
            if (prevDistance > distanceToStarting[u]) {
                cout << "-------------- prevDistance: " << prevDistance << " is larger than distanceToStarting[" << u << "], skip this loop " << endl;
                continue; 
            }

            for (auto& [target, duration] : graph[u]) {
                if (prevDistance +  duration < distanceToStarting[target]) {
                    cout << "-------------- prevDistance: " << prevDistance << ", duration: " << duration << ", distanceToStarting[target]: " << distanceToStarting[target] << ", target: " << target << endl;
                    cout << "-------------- prevDistance+duration: " << prevDistance + duration << " less than value of distanceToStarting[" << target << "], push to queue " << endl;
                    distanceToStarting[target] = prevDistance + duration;
                    priority_q.push({distanceToStarting[target], target});
                } else {
                    cout << "-------------- distanceToStarting[" << target << "] has quicker path already " << endl;
                    // 因为问题要求 “Return the minimum time it takes for all the n nodes to receive the signal. “
                    // 2->3->5->6 （也就是5为source，6为target的时候），distanceToStarting[6]是5，
                    //     也就是6节点到开始节点的时间如果走另一条线 2->1->6需要的时间更短，所以这个else分支(5到6的尝试）没必要再走了
                }
            }

            cout << "---------- forloop end " << endl;
        }

        // 找到所有节点的最大距离
        int ans = 0;
        for (int i = 1; i <= nodeSize; ++i) {
            cout << "-------- startingPoint loop " << i << ", distance is " << distanceToStarting[i] << endl;
            // 如果存在无法到达的节点，返回-1
            if (distanceToStarting[i] == INT_MAX) {
                cout << "-------- startingPoint can NOT reach to the node " << i << endl;
                return -1; 
            }
            ans = max(ans, distanceToStarting[i]);
            cout << "-------- startingPoint could reach to the node " << i << ", ans is " << ans << endl;
        }

        return ans;
    }
};

int main() {
    Solution s {};
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}, {3, 5, 2}, {1, 6, 4}, { 5, 6, 3}};
    int result = s.networkDelayTime(times, 6, 2);
    cout << "The shortest transformation sequence length is: " << result << endl;
    return 0;
}

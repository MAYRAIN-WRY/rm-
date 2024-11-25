#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int x, y;
    double cost;
};//节点的结构

double bfs(const vector<vector<int>>& map, int x1, int y1, int x2, int y2, double t) {
    int n = map.size();
    int m = map[0].size();
    vector<vector<double>> cost_so_far(n, vector<double>(m, -1));
    vector<Node> list;
    int front = 0;

    list.push_back({ x1, y1, 0 });
    cost_so_far[x1][y1] = 0;

    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (front < list.size()) {
        Node current = list[front++];

        if (current.x == x2 && current.y == y2) {
            return current.cost + map[x2][y2];  // 加上终点的代价
        }

        for (auto i : directions) {
            int nx = current.x + i.first;
            int ny = current.y + i.second;

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                double new_cost = current.cost + map[nx][ny] + t * map[current.x][current.y];

                if (cost_so_far[nx][ny] == -1 || new_cost < cost_so_far[nx][ny]) {
                    cost_so_far[nx][ny] = new_cost;
                    list.push_back({ nx, ny, new_cost });
                }
            }
        }
    }

    return -1;  // 如果没有路径到达终点，返回-1
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }
    double t;
    cin >> t;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    double cost_min = bfs(grid, x1, y1, x2, y2, t);
    cout << fixed << cost_min << endl;

    return 0;
}
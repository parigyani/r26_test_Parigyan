#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

struct Node {
    int x, y;
    double cost;
    double heuristic;
    bool operator>(const Node& other) const {
        return cost + heuristic > other.cost + other.heuristic;
    }
};

double heuristic(int x1, int y1, int x2, int y2) {
    return std::hypot(x2 - x1, y2 - y1);
}

std::vector<std::pair<int, int>> aStar(int startX, int startY, int goalX, int goalY, const std::vector<std::vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    open.push({startX, startY, 0, heuristic(startX, startY, goalX, goalY)});

    while (!open.empty()) {
        Node current = open.top(); open.pop();
        if (visited[current.x][current.y]) continue;
        visited[current.x][current.y] = true;

        if (current.x == goalX && current.y == goalY) {
            std::cout << "Path found!" << std::endl;
            break;
        }

        for (auto [dx, dy] : std::vector<std::pair<int, int>>{{1,0},{-1,0},{0,1},{0,-1}}) {
            int nx = current.x + dx, ny = current.y + dy;
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0 && !visited[nx][ny]) {
                open.push({nx, ny, current.cost + 1, heuristic(nx, ny, goalX, goalY)});
            }
        }
    }

    return {}; // You can extend this to return the actual path
}
#include <iostream>
#include <vector>
#include <cmath>

struct Command {
    double time;
    double angle;
};

std::vector<Command> generateOdometry(const std::vector<std::pair<int, int>>& path, double wheelRadius, double wheelBase) {
    std::vector<Command> commands;
    for (size_t i = 1; i < path.size(); ++i) {
        int dx = path[i].first - path[i-1].first;
        int dy = path[i].second - path[i-1].second;
        double distance = std::hypot(dx, dy);
        double angle = std::atan2(dy, dx);
        double time = distance / (wheelRadius * 2 * M_PI); // Simplified
        commands.push_back({time, angle});
    }
    return commands;
}
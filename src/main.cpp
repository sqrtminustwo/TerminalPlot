#include <plot.h>
#include <random>

int genRandom(int lower, int upper) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

int main() {
    std::vector<int> points;
    int max_y = 240;
    int y_split = 10;
    int max_points_in_one_graph = 20;
    int update_time = 200;
    Plot plot(points, max_y, y_split, max_points_in_one_graph, update_time);
    plot.startPlotting();

    int point;
    while (true) {
        point = genRandom(10, 230);
        points.push_back(point);
        std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
    }
}

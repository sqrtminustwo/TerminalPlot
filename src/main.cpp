#include <plot.h>
#include <random>

int genRandom(int lower, int upper) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

int main() {

    int max_fps = 240;
    int y_split = 10;
    int max_points_in_one_graph = 20;
    std::vector<int> fps_history;
    Plot plot(fps_history, max_fps, y_split, max_points_in_one_graph, 1000);
    plot.startPlotting();

    int fps;
    while (true) {
        fps = genRandom(10, 230);
        fps_history.push_back(fps);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

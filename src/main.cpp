#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <plot.h>
#include <random>

int update_time = 500;
// For random points only (not needed for plotting)
std::tuple<int, int> generation_bounds1{1, 99};
std::tuple<int, int> generation_bounds2{10, 230};

std::vector<int> points1;
int max_y0 = 100;
Plot plot_simple(points1, max_y0);

std::vector<int> points2;
int max_y1 = 240;
ftxui::Color color1 = ftxui::Color::White;
int y_split = 20;
int max_points_in_one_graph = 20;
std::vector<ftxui::Color> colors{
    ftxui::Color::Red,
    ftxui::Color::Orange1,
    ftxui::Color::Yellow,
    ftxui::Color::Green,
    ftxui::Color::Blue,
    ftxui::Color::Aquamarine1,
    ftxui::Color::Purple
};
Plot plot_colorized(points2, max_y1, color1, y_split, max_points_in_one_graph, update_time);

std::vector<int> points3;
int max_y2 = 100;
ftxui::Color color2 = ftxui::Color::Yellow;
std::vector<int> y_splits{10, 20, 30};
Plot plot_dynamic_y_split(points3, max_y2, color2);

std::vector<int> points4;
int max_y3 = 100;
ftxui::Color color3 = ftxui::Color::Blue;
std::vector<int> points_in_graph{10, 20, 30};
Plot plot_dynamic_points_in_graph(points4, max_y3, color3);

int genRandom(int lower, int upper) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

void genPoint(std::vector<int> &points, int lb, int ub) {
    int point = genRandom(lb, ub);
    points.push_back(point);
}

void updateSimplePlot() {
    static auto [lb, ub] = generation_bounds1;
    genPoint(points1, lb, ub);
}

template <typename T>
int updateIndex(int i, std::vector<T> &vec) {
    return i >= vec.size() - 1 ? 0 : i + 1;
}
void updateColorizedPlot() {
    static int cur_color = 0;
    static auto [lb, ub] = generation_bounds2;

    genPoint(points2, lb, ub);
    plot_colorized.setColor(colors.at(cur_color));

    cur_color = updateIndex(cur_color, colors);
}
void updateDynamicYSplitPlot() {
    static int cur_split = 0;
    static auto [lb, ub] = generation_bounds1;

    genPoint(points3, lb, ub);
    plot_dynamic_y_split.setYSplit(y_splits.at(cur_split));

    cur_split = updateIndex(cur_split, y_splits);
}
void updateDynamicPointsInGraph() {
    static int cur_points = 0;
    static auto [lb, ub] = generation_bounds1;

    genPoint(points4, lb, ub);
    plot_dynamic_points_in_graph.setMaxPointsInGraph(points_in_graph.at(cur_points));

    cur_points = updateIndex(cur_points, points_in_graph);
}

int main() {
    using namespace ftxui;

    // If you want to plot a single graph uncomment the graph you want and comment 108-124, and unneeded update calls to
    // other graphs in loop

    // plot_simple.startPlotting();
    // plot_colorized.startPlotting();
    // plot_dynamic_y_split.startPlotting();
    // plot_dynamic_points_in_graph.startPlotting();

    // Unrelated to graphing, used to plot multiple graphs at the same time for demo
    // If its not common sense to you, read https://arthursonzogni.github.io/FTXUI/
    // I'm not shure if call to getPlot() is needed for each render but i'm just to lazy to store each component in new
    // variable as i already save it in plot class
    auto graphs = Renderer([&] {
        return hbox(
            {vbox(
                 {vbox(plot_simple.getPlot()->Render()) | flex,
                  separator(),
                  vbox(plot_colorized.getPlot()->Render()) | flex}
             ) | flex,
             separator(),
             vbox(
                 {vbox(plot_dynamic_y_split.getPlot()->Render()) | flex,
                  separator(),
                  vbox(plot_dynamic_points_in_graph.getPlot()->Render()) | flex}
             ) | flex}
        );
    });
    TerminalScreen terminalScreen(graphs, update_time);
    terminalScreen.start();

    while (true) {
        updateSimplePlot();
        updateColorizedPlot();
        updateDynamicYSplitPlot();
        updateDynamicPointsInGraph();
        std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
    }
}

#ifndef PLOT_H
#define PLOT_H

#include <terminal_screen.h>
#include <ftxui/component/component_base.hpp>
#include <vector>
#include <memory>

class Plot {
  public:
    Plot(std::vector<int> &points, int max_y, int y_split, int max_points_in_graph, int update_time);

    void startPlotting();

    void setMaxY(int max_y) { this->max_y = max_y; }
    void setMaxPointInGraph(int max_points_in_graph) {
        this->max_points_in_graph = max_points_in_graph;
        step = getStep();
    };

    ftxui::Component getPlot() { return main_component; };

  private:
    int normalizePoint(int point) { return ((float)(max_y - point) / (float)max_y) * 100; }
    int getStep() { return 100 / max_points_in_graph; }

    std::unique_ptr<TerminalScreen> terminal_screen;
    ftxui::Component main_component;
    int max_y;
    int y_split;
    int max_points_in_graph;
    int step;
    // In ms (value below 50ms will cause high cpu load)
    int update_time;
    std::vector<int> &points;
};

#endif

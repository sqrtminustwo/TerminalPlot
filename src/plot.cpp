#include <plot.h>
#include <ctime>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"      // for Renderer
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/dom/canvas.hpp"               // for Canvas

using namespace ftxui;

Plot::Plot(std::vector<int> &points, int max_y, int y_split, int max_points_in_graph, int update_time)
    : points(points), max_y(max_y), y_split(y_split), max_points_in_graph(max_points_in_graph), step(getStep()),
      update_time(update_time) {
    main_component = Renderer([this] {
        auto c = Canvas(100, 100);

        int size = this->points.size();
        int pos = size > this->max_points_in_graph ? size - this->max_points_in_graph : 0;

        std::vector<int>::const_iterator first = this->points.begin() + pos;
        std::vector<int>::const_iterator last = this->points.begin() + size;
        std::vector<int> points_subset(first, last);

        int coef = 1;
        int x;
        for (pos = 1; pos < points_subset.size(); pos++) {
            x = coef * step;
            coef++;
            auto p1 = normalizePoint(points_subset.at(pos - 1));
            auto p2 = normalizePoint(points_subset.at(pos));
            // c.DrawText(1, 0, " " + std::to_string(p1) + " " + std::to_string(p2));
            c.DrawPointLine(x - step, p1, x, p2);
        }

        std::vector<Element> vec{};

        for (int split = this->max_y; split >= 0; split -= this->y_split) {
            vec.push_back(text(std::to_string(split)));
            vec.push_back(filler());
        }
        auto y_axis_fps = vbox(vec);

        return hbox(y_axis_fps, canvas(std::move(c))) | border;
    });
}

void Plot::startPlotting() {
    moved = true;
    terminal_screen = std::unique_ptr<TerminalScreen>(new TerminalScreen(main_component, update_time));
    terminal_screen->start();
}

ftxui::Component Plot::getPlot() {
    if (moved) throw std::runtime_error("Was used for plotting, can't reuse!");
    return main_component;
}

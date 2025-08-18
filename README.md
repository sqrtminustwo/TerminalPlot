# TerminalPlot

![til](/demo/demo2.gif)

A simple C++ program to make graphs in a terminal.

## Requirements

[FTXUI](https://github.com/ArthurSonzogni/FTXUI) is the library used for plotting, required through [CMakeLists.txt](/CMakeLists.txt):

```CMake
find_package(ftxui REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
```

## Usage

You can see the code used for demo in [main.cpp](/src/main.cpp). All you need to plot:

```C++
std::vector<int> points; // Points of graph (passed by reference, can be updated after passing)
int max_y = 100;         // Max y-coordinate (can be updated during plotting through setMaxY())
int y_split = 10;        // (Optional, default = 10) y-axis will have max_y/y_split segments (can be updated during
                         // plotting through setMaxPointsInGraph())
int max_points_in_one_graph = 20; // (Optional, default = 10) Max amount of points loaded in graph width
int update_time =
    200; // (Optional, default = 1000ms) Update speed of the graph (below 50ms will cause high cpu load)
ftxui::Color color = ftxui::Color::White; // (Optional, default = ftxui::Color::White) Color of the graph
Plot plot(points, max_y, color, y_split, max_points_in_one_graph, update_time);
plot.startPlotting(); // Ended on class destruction (see implementation for details)

// Random point generation (for demo)
int point;
while (true) {
    point = genRandom(1, 99);
    points.push_back(point);
    std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
}
```

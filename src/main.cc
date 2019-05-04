#include "graphics.hh"
#include "map.hh"

#include <QApplication>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ratio>

constexpr int DEFAULT_I = 1000;
constexpr double DEFAULT_DT = 1;

int main(int argc, char **argv) {
    using namespace std::chrono;

    const int iters = (argc == 2) ? std::atoi(argv[1]) : DEFAULT_I;
    const double deltatime = (argc == 3) ? std::atof(argv[2]) : DEFAULT_DT;

    Map map(deltatime);
    std::cin >> map;

    QApplication app(argc, argv);
    Graphics graphics(nullptr, map, iters);
    graphics.show();

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int exec = app.exec();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << " seconds" << std::endl;
    return exec;
}

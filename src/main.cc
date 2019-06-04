#include "graphics.hh"
#include "map.hh"

#include <QApplication>

#include <chrono>
#include <cstdlib>
#include <iostream>

enum Model { BRUTE = 1, BHTREE, PARALLEL };
constexpr int DEFAULT_I = 1000;
constexpr int DEFAULT_TRACE = 1;
constexpr double DEFAULT_DT = 1;

int main(int argc, char **argv) {
    using namespace std::chrono;

    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " model [iterations] [trace]"
                  << std::endl;
        return 1;
    }

    const Model model = static_cast<Model>(std::atoi(argv[1]));
    const int iters = (argc == 3) ? std::atoi(argv[2]) : DEFAULT_I;
    const int trace = (argc == 4) ? std::atoi(argv[3]) : DEFAULT_TRACE;

    std::shared_ptr<Map> map;
    switch (model) {
    case BRUTE:
        map = std::shared_ptr<Map>(new MapBrute(DEFAULT_DT, iters));
        break;
    case BHTREE:
        map = std::shared_ptr<Map>(new MapBHTree(DEFAULT_DT, iters));
        break;
    case PARALLEL:
        map = std::shared_ptr<Map>(new MapParallel(DEFAULT_DT, iters));
        break;
    default:
        return 1;
    }
    std::cin >> map;

    QApplication app(argc, argv);
    Graphics graphics(nullptr, map, iters, trace);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int exec = app.exec();
    /*for (int i = 0; i < iters; i++) {
        map->compute();
        if (i % trace == 0) {
            std::cout << i << std::endl;
            std::cout << map << std::endl;
        }
    }*/
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << " seconds" << std::endl;
    return exec;
}

#ifndef BARRIER_HH
#define BARRIER_HH

#include <condition_variable>
#include <thread>

class Barrier {
  public:
    Barrier(int threads);
    void wait();

  private:
    std::mutex mutex;
    std::condition_variable cv;
    int threads;
    int counter;
    int waiting;
};

#endif
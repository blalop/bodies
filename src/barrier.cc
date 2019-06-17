#include "barrier.hh"

Barrier::Barrier(int threads) : threads(threads), counter(0), waiting(0) {}

void Barrier::wait() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->counter++;
    this->waiting++;
    this->cv.wait(lock, [&] { return counter >= threads; });
    this->cv.notify_one();
    this->waiting--;
    if (this->waiting == 0) {
        this->counter = 0;
    }
    lock.unlock();
}

#ifndef THREADPOOL_H
#define THREADPOOL_H

/*
 * Based off https://stackoverflow.com/a/32593825/6441490
 */

#include <cstdint>
#include <vector>
#include <future>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

template<std::size_t poolSize = 0>
class FuturePool {
private:
    using Task = std::function<void()>;     // Passed to addTask

    std::vector<std::future<void>> futures; // List of poolSize futures
    std::queue<Task> tasksQueue;            // Task to be completed
    std::mutex queueMutex;                  // Mutex to use tasksQueue and shouldStop
    std::condition_variable cv;             // CV to notify changes in tasksQueue and shouldStop
    bool shouldStop, stopped;               // shouldStop=1 -> futures exit while -> stopped=1


public:
    FuturePool() : shouldStop(false), stopped(false) {
        std::size_t numThreads;

        if (poolSize == 0)
            numThreads = std::thread::hardware_concurrency(); // Number of CPU threads
        else
            numThreads = poolSize;

        this->futures.reserve(numThreads);
        for (size_t i = 0; i < numThreads; i++)
            this->futures.push_back(std::async(&FuturePool::futureFn, this));
    }

    void pushTask(const Task &task) {
        std::unique_lock<std::mutex> lock(this->queueMutex); // Acquire taskQueue & shouldStop
        this->tasksQueue.push(task);
        lock.unlock();                                       // Release
        this->cv.notify_one();                               // Only one future have to be notified
    }

    void waitFor() {
        std::unique_lock<std::mutex> lock(this->queueMutex);
        this->shouldStop = true;                             // Ask futures to stop
        lock.unlock();

        cv.notify_all();                                     // Notify every future that should stop

        for (const auto &f:this->futures)
            f.wait();                                        // Sync wait for each future to stop

        this->futures.clear();
        this->stopped = true;
    }

    ~FuturePool() {
        if (!this->stopped)
            this->waitFor();
    }

private:
    void futureFn() {
        //Declare lock, but do NOT lock the queue immediately
        std::unique_lock<std::mutex> lock(this->queueMutex, std::defer_lock);

        while (true) {
            //Acquire the queue
            lock.lock();

            //Wait until the queue won't be empty or stop is signaled
            this->cv.wait(lock, [&inst = this]() {
                return !inst->tasksQueue.empty() || inst->shouldStop;
            });

            //Even if shouldStop=1, first empty the queue
            if (!this->tasksQueue.empty() && this->shouldStop)
                return;

            //Pop one task from the queue
            Task task = std::move(this->tasksQueue.front());
            this->tasksQueue.pop();

            //Release the queue
            lock.unlock();

            //Execute the task
            task();
        }
    }
};


#endif

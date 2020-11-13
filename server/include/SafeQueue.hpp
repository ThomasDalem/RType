/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue {
public:
    SafeQueue(): _stop(false) {};
    ~SafeQueue() {};

    void push(T &value)
    {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push(std::move(value));
        }
        _cv.notify_one();
    };

    bool tryGetPop(T &poppedValue)
    {
        std::lock_guard<std::mutex> _lock(_mutex);

        if (_queue.empty()) {
            return false;
        }
        poppedValue = std::move(_queue.front());
        _queue.pop();
        return true;
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _cv.wait(lock, [this]{ return (!_queue.empty() || _stop); });
        _queue.pop();
    };

    bool empty()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }

    void stop()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _stop = true;
    }

private:
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    bool _stop;
};

#endif /* !SAFEQUEUE_HPP_ */

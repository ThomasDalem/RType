/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** SafeQDeque
*/

#ifndef SAFEDEQUE_HPP_
#define SAFEDEQUE_HPP_

#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeDeque {
public:
    SafeDeque(): _stop(false) {};
    ~SafeDeque() {};

    void push(T &value)
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _deque.push(value);
        lock.unlock();
        _cv.notify_one();
    };

    bool tryGetPop(T &poppedValue)
    {
        std::mutex<std::mutex> _lock(_mutex);

        if (_deque.empty()) {
            return false;
        }
        poppedValue = _deque.front();
        _deque.pop();
        return true;
    }

    void pop()
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this]{ return (!_deque.empty() || _stop); });
        _deque.pop();
    };

    T &at(int pos)
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this]{ return (!_deque.empty() || _stop); });
        return _deque.at(pos);
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return _deque.empty();
    }

private:
    std::deque<T> _deque;
    std::mutex _mutex;
    std::condition_variable _cv;
    bool _stop;
};

#endif /* !SAFEDEQUE_HPP_ */

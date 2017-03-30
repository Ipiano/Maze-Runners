#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <condition_variable>
#include <mutex>

class semaphore
{
private:
    std::mutex _mut;
    std::condition_variable _cv;
    unsigned long _count;
    unsigned long _max;

public:
    semaphore(int count=1) : _count(count), _max(count){}

    void notify()
    {
        std::unique_lock<std::mutex> lock(_mut);
        _count = (_count != _max ? _count+1:_count);
        _cv.notify_one();
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(_mut);
        while(!_count)
            _cv.wait(lock);

        --_count;
    }
};

#endif // SEMAPHORE_H

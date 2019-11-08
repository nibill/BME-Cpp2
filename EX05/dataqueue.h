#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include <iostream>
#include <deque>
#include <condition_variable>

using namespace std;

template <typename T>
class DataQueue
{
public:
    DataQueue(uint16_t size=1000):max_size(size){}

    void add(T elementToAdd)
    {
        if(!isFull())
        {
            lock_guard<mutex> Locker(dequeLocker);
            myDeque.push_front(elementToAdd);
            lock_guard<mutex> full_locker(fullLocker);
            if (myDeque.size() >= max_size)
            {
                full=true;
            }
        }
        else{
            unique_lock<mutex>Locker_get{dequeLocker};
            consumer_notification.wait(Locker_get,[this]{return !isFull();});
            myDeque.push_front(elementToAdd);
            lock_guard<mutex> full_locker(fullLocker);
            if (myDeque.size() >= max_size)
            {
                full=true;
            }
        }
        consumer_notification.notify_one();
    }

    T get()
    {
        T returnValue;
        if(isEmpty())
        {
            unique_lock<mutex>Locker_get{dequeLocker};
            produce_notification.wait(Locker_get,[this]{return !(isEmpty());});
            returnValue = myDeque.back();
            myDeque.pop_back();
            lock_guard<mutex> full_locker(fullLocker);
            if (myDeque.size() < max_size)
            {
                full=false;
            }
        }
        else {
            lock_guard<mutex>Locker(dequeLocker);
            returnValue = myDeque.back();
            myDeque.pop_back();
            lock_guard<mutex> full_locker(fullLocker);
            if ( myDeque.size() < max_size){full=false;}
        }
        consumer_notification.notify_one();
        return returnValue;
    }

    bool isFull(){
        lock_guard<mutex>Locker(fullLocker);
        return full;
    }

    bool isEmpty(){
        lock_guard<mutex>Locker(dequeLocker);
        return myDeque.empty();
    }

private:
    uint16_t max_size;
    bool full = false;
    deque<T> myDeque;
    mutex dequeLocker;
    mutex fullLocker;
    condition_variable produce_notification;
    condition_variable consumer_notification;
};
#endif // DATAQUEUE_H

// File   : transqueue.h
// Author : Silei
// Descr  : Provide thread safe data transfer

#ifndef TRANSQUEUE_H
#define TRANSQUEUE_H

#include <mutex>
#include <list>

template<typename Elem_T , typename Con_T = std::list<Elem_T> >
class TransQueue {
    typedef std::mutex Mutex;
    typedef std::lock_guard<std::mutex> Locker;

public:
    TransQueue(){

    }

    ~TransQueue(){

    }

    bool IsEmpty(){
        Locker enter(quetex);
        return theQueue.empty();
    }

    size_t Size(){
        Locker enter(quetex);
        return theQueue.size();
    }

    void Clear(){
        Locker enter(quetex);
        theQueue.clear();
    }

    void Add(const Elem_T& elem){
        Locker enter(quetex);
        theQueue.push_back(elem);
    }

    TransQueue& operator<<(const Elem_T& elem){
        Add(elem);
        return *this;
    }

    TransQueue& operator>>(Elem_T& elem){
        elem = Get();
        return *this;
    }

    Elem_T Get(){
        Locker enter(quetex);
        Elem_T elem(theQueue.front());
        theQueue.pop_front();
        return elem;
    }



private:
    Mutex quetex;
    Con_T theQueue;
};

#endif // TRANSQUEUE_H

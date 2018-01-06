#ifndef LIST_H
#define LIST_H


#include<iostream>
#include<malloc.h>
using namespace std;
template<class T>
class SqList{
public:
    const static int DefaultLength, Incremental;
    SqList(){
        init(DefaultLength);
    }
    SqList(int size){
        init(size);
    }
    SqList(const SqList<T> &list){
        cap_ = list.cap_;
        last_ = list.last_;
        head_ = new T[cap_];
        for(size_t i = 0; i < list.last_; i++){
            head_[i] = list.head_[i];
        }
    }
    ~SqList(){
        delete[] head_;
    }
    void init(int size){
        if(size <= 0)size = 1;
        last_ = 0, cap_ = size;
        head_ = new T[cap_];
    }
    void push(T x){
        if(last_ >= cap_){
            cap_ += Incremental;
            T *new_head = new T[cap_];
            for(size_t i = 0; i < last_; i++){
                new_head[i] = head_[i];
            }
            delete[] head_;
            head_ = new_head;
        }
        *(head_+last_) = x;
        last_++;
    }
    void pop(){
        erase(0);
    }
    void erase(size_t pos){
        if(pos >= last_){
            throw "list fuck you";
        }

        else{
            for(size_t i = pos + 1; i < last_; i++){
                head_[i-1] = head_[i];
            }
            last_--;
        }
    }
    void print(){
        for(int i = 0; i < last_; i++){
            cout << *(head_+i) << " ";
        }
    }
    int length(){
        return last_;
    }
    void bigger(int size){
        if(size <= 0)return;
        cap_ += size;
        T *new_head = new T[cap_];
        for(size_t i = 0; i < last_; i++){
            new_head[i] = head_[i];
        }
        delete[] head_;
        head_ = new_head;
    }
    void reserve(size_t size){
        bigger(size - last_);
    }
    T& operator [](int i){
        if(i >= last_){
            throw "fuck you";
        }
        else
            return *(head_ + i);
    }

    void operator= (const SqList<T> &list){
        if(cap_ >= list.cap_){
            for(size_t i = 0; i < list.last_; i++)
                head_[i] = list.head_[i];
        }else{
            cap_ = list.cap_;
            last_ = list.last_;
            T *new_head = new T[cap_];
            for(size_t i = 0; i < list.last_; i++)
                new_head[i] = list.head_[i];
            delete head_;
            head_ = new_head;
        }
    }
private:
    T *head_;
    int last_, cap_;

};
template<class T>
const int SqList<T>::DefaultLength = 10;
template<class T>
const int SqList<T>::Incremental = 20;

#endif // LIST_H

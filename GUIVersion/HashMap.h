#ifndef HASH_MAP_H
#define HASH_MAP_H

#include<iostream>
#include<string>
#include "List.h"
//#include "BKDRHash.h"
template<class ValueType>
struct Entry{
    //std::string key;
    size_t hash;
    ValueType value;
    Entry<ValueType> *next;
    Entry(){
        hash = -1;
        next = NULL;
    }
    Entry(size_t h, const ValueType &v, Entry<ValueType> *e){
        hash = h;
        value = v;
        next = e;
    }
    ~Entry(){
        Entry<ValueType> *ptr = next, *next_ptr = NULL;
        for(; ptr != NULL; ptr = next_ptr){
            next_ptr = ptr->next;
            delete ptr;
        }

    }
    Entry(const Entry &e){
        hash = e.hash;
        value = e.value;
        next = e.next;
    }
    void operator = (const Entry &e){
        hash = e.hash;
        value = e.value;
        next = e.next;
    }
};
template<class ValueType>
class StringHashMap{
private:
    SqList<Entry<ValueType>*> list_;
    size_t entry_size_, list_length_;

    void AddEntry(size_t hash, const ValueType &value, size_t list_pos){
        Entry<ValueType> *old_first = list_[list_pos];
        list_[list_pos] = new Entry<ValueType>(hash, value, old_first);
        entry_size_++;
        if(entry_size_ > list_length_*2){
            resize(list_length_*IncRatio);
        }
    }
public:
    StringHashMap():list_(DefaultLength){
        entry_size_ = 0;
        list_length_ = DefaultLength;
        for(int i = 0; i < list_length_; i++){
            list_.push(NULL);
        }
    }
    StringHashMap(size_t len):list_(len){
        entry_size_ = 0;
        list_length_ = len;
        for(int i = 0; i < list_length_; i++){
            list_.push(NULL);
        }
    }
    ~StringHashMap(){
        for(size_t i = 0; i < list_length_; i++){
            delete list_[i];
            //list_[i].~()
        }
    }
    unsigned int StringHashCode(const char* key)
    {
        char* str = const_cast<char*>(key);

        unsigned int seed = 31; // 31 131 1313 13131 131313 etc.. 37
        unsigned int hash = 0;
        while (*str)
        {
            hash = hash*seed + *str;
            str++;
        }
        return hash;
    }
    unsigned int StringHashCode(const std::string &s)
    {
        return StringHashCode(s.c_str());
    }
    void put(std::string key, const ValueType &value){
        size_t hash = StringHashCode(key);
        size_t list_pos = hash % list_length_;
        cout << hash << ":" << list_pos << endl;
        for(Entry<ValueType> *ptr = list_[list_pos]; ptr != NULL; ptr = ptr->next){
            if(hash == ptr->hash){
                ptr->value = value;
                return;
            }
        }
        AddEntry(hash, value, list_pos);
    }
    ValueType get(std::string key){
        size_t hash = StringHashCode(key);
        size_t list_pos = hash % list_length_;
        for(Entry<ValueType> *ptr = list_[list_pos]; ptr != NULL; ptr = ptr->next){
            if(ptr->hash == hash){
                return ptr->value;
            }
        }
        return ValueType();
    }
    void resize(size_t new_len){
    }
    ValueType &operator [] (std::string key){
        size_t hash = StringHashCode(key);
        size_t list_pos = hash % list_length_;
        for(Entry<ValueType> *ptr = list_[list_pos]; ptr != NULL; ptr = ptr->next){
            if(ptr->hash == hash){
                return ptr->value;
            }
        }
        //ц╩сп
        Entry<ValueType> *old_first = list_[list_pos];
        list_[list_pos] = new Entry<ValueType>(hash, ValueType(), old_first);
        entry_size_++;
        if(entry_size_ > list_length_*2){
            resize(list_length_*IncRatio);
        }
        return list_[list_pos]->value;
    }
    bool is_exist(std::string key){
        size_t hash = StringHashCode(key);
        size_t list_pos = hash % list_length_;
        for(Entry<ValueType> *ptr = list_[list_pos]; ptr != NULL; ptr = ptr->next){
            if(ptr->hash == hash){
                return true;
            }
        }
        return false;
    }
    bool erase(std::string key){
        size_t hash = StringHashCode(key);
        size_t list_pos = hash % list_length_;
        Entry<ValueType> *ptr = list_[list_pos], *fro_ptr = NULL;
        if(ptr == NULL)
            return false;
        if(ptr->hash == hash){
            list_[list_pos] = ptr->next;
            delete ptr;
            return true;
        }
        fro_ptr = ptr;
        ptr = ptr->next;
        while(!ptr){
            if(ptr->hash == hash){
                fro_ptr->next = ptr->next;
                delete ptr;
                return true;
            }
            fro_ptr = ptr;
            ptr = ptr->next;
        }
        return false;
    }


    const static int DefaultLength, IncRatio;

};
template<class ValueType>
const int StringHashMap<ValueType>::DefaultLength = 512;
template<class ValueType>
const int StringHashMap<ValueType>::IncRatio = 2;


#endif // HASH_MAP_H

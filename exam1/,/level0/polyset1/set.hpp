#ifndef SET_HPP
#define SET_HPP


#include "array_bag.hpp"
#include "bag.hpp"
#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

class   set{
    private :
        searchable_bag &bag_ptr;
    public :
        set(searchable_bag &other);
        ~set(){
            bag_ptr.clear();
        }

        void insert(int value);
        void insert(int *array , int size);
        void print() const;
        void clear();

        bool has(int value)const;
        searchable_bag&     get_bag()const;      
};

#endif
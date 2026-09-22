#ifndef SET_HPP
#define SET_HPP


#include "array_bag.hpp"
#include "bag.hpp"
#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

// a set owns no storage of its own — it just wraps a searchable_bag&
// and adds a has() check on top of insert()
class   set{
    private :
        searchable_bag &bag_ptr;

    public :
        // ------------------------------------------------------------------
        // CANONICAL FORM
        // ------------------------------------------------------------------
        set(searchable_bag &other);
        ~set(){
            bag_ptr.clear();
        }

        // ------------------------------------------------------------------
        // INSERTION — the has() check before inserting is what makes this
        // a set instead of a plain bag
        // ------------------------------------------------------------------
        void insert(int value);
        void insert(int *array , int size);

        // ------------------------------------------------------------------
        // DELEGATION — everything else just forwards to the wrapped bag
        // ------------------------------------------------------------------
        void print() const;
        void clear();
        bool has(int value)const;
        searchable_bag&     get_bag()const;
};

#endif

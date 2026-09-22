#ifndef SEARCHABLE_TREE_BAG_HPP
#define SEARCHABLE_TREE_BAG_HPP

#include "array_bag.hpp"
#include "bag.hpp"
#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"
#include "tree_bag.hpp"

// declared searchable_bag, tree_bag (in that order) -> ctor init list
// below must initialize them in that same order, or -Werror=reorder fires
class   searchable_tree_bag : public searchable_bag , public tree_bag {
        public :
                // ------------------------------------------------------------------
                // CANONICAL FORM
                // ------------------------------------------------------------------
                searchable_tree_bag();
                searchable_tree_bag(const searchable_tree_bag &other);
                searchable_tree_bag&   operator=(const searchable_tree_bag &other);

                // ------------------------------------------------------------------
                // SEARCH — must walk l/r using the exact same rule tree_bag::insert()
                // used to place the nodes (< goes l, >= goes r)
                // ------------------------------------------------------------------
                bool    has(int value)const;
};

#endif

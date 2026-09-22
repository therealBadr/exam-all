#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "bag.hpp"
#include "searchable_bag.hpp"

// declared searchable_bag, array_bag (in that order) -> ctor init list
// below must initialize them in that same order, or -Werror=reorder fires
class   searchable_array_bag : public searchable_bag , public array_bag {
        public :
                // ------------------------------------------------------------------
                // CANONICAL FORM
                // ------------------------------------------------------------------
                searchable_array_bag();
                searchable_array_bag(const searchable_array_bag &other);
                searchable_array_bag&   operator=(const searchable_array_bag &other);

                // ------------------------------------------------------------------
                // SEARCH — the one method searchable_bag requires
                // ------------------------------------------------------------------
                bool    has(int value)const;
};

#endif

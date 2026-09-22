#include "searchable_array_bag.hpp"

// ============================================================================
// CANONICAL FORM
// ============================================================================

// order here matches the class's base-list order: searchable_bag, array_bag
searchable_array_bag::searchable_array_bag() : searchable_bag(), array_bag() {
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag& other) : array_bag(other) {
}
searchable_array_bag&	searchable_array_bag::operator=(const searchable_array_bag& other) {
	if (this != & other) array_bag::operator=(other);
	return (*this);
}

// ============================================================================
// SEARCH
// ============================================================================

bool    searchable_array_bag::has(int value)const {
    for(int i = 0 ; i < size ; i++)
        if(data[i] == value)
                return true;
    return false;
}

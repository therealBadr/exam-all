#include "set.hpp"

// ============================================================================
// CANONICAL FORM
// ============================================================================

set::set(searchable_bag &other) : bag_ptr(other) {

}
// destructor is defined inline in the header: ~set(){ bag_ptr.clear(); }

// ============================================================================
// INSERTION
// ============================================================================

void    set::insert(int value)
{
    if(!bag_ptr.has(value))    // <- the one line that turns a bag into a set
        bag_ptr.insert(value);
}
void	set::insert(int *array, int size) {
	for (int i = 0; i < size; i++) {
		if (!bag_ptr.has(array[i]))
			bag_ptr.insert(array[i]);
	}
}

// ============================================================================
// DELEGATION
// ============================================================================

void    set::print()const{
    bag_ptr.print();
}
void    set::clear(){
    bag_ptr.clear();
}
bool    set::has(int value)const
{
    return bag_ptr.has(value);
}
searchable_bag& set::get_bag()const{
    return bag_ptr;
}

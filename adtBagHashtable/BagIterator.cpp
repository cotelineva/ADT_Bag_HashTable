#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->index = 0;
}

void BagIterator::first() {
	//complexity: theta(1)

	this->index = 0;
}


void BagIterator::next() {
	//complexity: theta(1);

	this->index++;
}


bool BagIterator::valid() const {
	//complexity: theta(1)

	if (this->index > 0 && this->index < bag.m) {
		return true;
	}
	return false;
}



TElem BagIterator::getCurrent() const
{
	//complexity: theta(1)

	if (valid()) {
		return bag.table[this->index];
	}
	return NULL_TELEM 
}

#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

//first hash function
int Bag::h1(TElem k) const{
	return k % this->m;
}

//second hash function
int Bag::h2(TElem k) const{
	return 1 + (k % (this->m - 1));
}

//main hash function
int Bag::h(TElem k, int i) const{
	return (h1(k) + i * h2(k)) % this->m;
}

Bag::Bag() {

	this->m = 8;
	this->nrElem = 0;
	this->table = new TElem[m];
	for (int i = 0; i < this->m; i++) {
		this->table[i] = -1;
	}
}


void Bag::add(TElem elem) {
	//complexity: 
	//best: O(1);		worst: O(n^2);		average: omega(n);


	//wir uberprufen ob wir genug platz haben
	if (this->nrElem == this->m) {
		this->m *= 2;
		TElem* newTable = new TElem[this->m];

		//wir initialisieren den neuen vektor mit "leeren" Elemente, also -1
		for (int i = 0; i < this->m; i++) {
			newTable[i] = -1;
		}

		for (int i = 0; i < this->m / 2; i++) {

			//hier wollen wir die elemente in den neuen vektor tun, also mit rehashing
			if (this->table[i] != -1) {

				//wir finden die position heraus
				int idx = 0;
				int pos = h(this->table[i], idx);

				//falls diese position besetzt ist, berechnen wir eine neue mit hilfe eines neuen i
				while (idx < this->m / 2 && newTable[pos] != -1) {
					idx++;
					pos = h(this->table[i], idx);
				}

				if (this->m / 2 >= idx) {
					newTable[pos] = elem;
				}
			}
		}
		delete[] this->table;
		this->table = newTable;
	}

	//wir finden die position heraus
	int i = 0;
	int position = h(elem, i);

	//falls diese position besetzt ist, berechnen wir eine neue mit hilfe eines neuen i
	while (i < this->m && this->table[position] != -1) {
		i++;
		position = h(elem, i);
	}
	if (this->m >= i) {
		this->table[position] = elem;
		this->nrElem++;
	}
}


bool Bag::remove(TElem elem) {
	//complexity: O(n)
	
	//falls das Elem nicht existiert
	if (search(elem) == false) {
		return false;
	}

	int i = 0;
	while (i < this->nrElem && this->table[i] != -1) {
		//falls wir das Elem gefunden haben
		if (this->table[i] == elem) {

			//wir stellen das element auf -1 zuruck
			this->table[i] = -1;
			this->nrElem--;
			return true;
		}
		i++;
	}

	return false;
}


bool Bag::search(TElem elem) const {
	//complexity: O(n)

	int i = 0;
	int position = h(elem, i);
	
	//falls das element existier und wir es noch nicht gefunden haben
	while (i < this->m && this->table[position] != -1 && this->table[position] != elem) {
		i++;
		position = h(elem, i);
	}

	//wir haben das elem gefunden
	if (i < this->m && this->table[position] == elem) {
		return true;
	}
	//das elem existiert nicht in bag
	else {
		return false;
	}
}

int Bag::nrOccurrences(TElem elem) const {
	//complexity: theta(n)

	int ct = 0;
	for (int i = 0; i < this->m; i++) {
		if (this->table[i] == elem && this->table[i] != -1) {
			ct++;
		}
	}
	return ct; 
}


int Bag::size() const {
	//complexity: theta(1)

	return this->nrElem;
}


bool Bag::isEmpty() const {
	//complexity: theta(1)

	if (this->nrElem == 0) {
		return true;
	}
	else {
		return false;
	}
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag Bag::difference(Bag b1, Bag b2) {
	//complexity: O(n^2)

	//b3 = b1 - b2
	//b1: 2 9 7 2 5 9
	//b2: 9 7 5 1 3
	//b3: 2 2 9

	int i;
	Bag b3;

	//wir vergleichen die elem aus b2 mit die aus b1
	for (int j = 0; j < b2.nrElem; j++) {
		
		//wir durchgehen den ganzen b1 fur jedes elem aus b2
		i = 0;
		while (i < b1.nrElem) {
			//wenn wir 2 gleiche elem gefunden haben, stellen wir -1 auf diese position in b1
			if (b2.table[j] == b1.table[i]) {
				b1.table[i] = -1;
			}
			else {
				i++;
			}
		}
	}

	//hier tun wir alle verschiedene von -1 elem in einen neuen bag
	i = 0;
	for (int j = 0; j < b1.nrElem; j++) {
		if (b1.table[j] != -1) {
			b3.table[i] = b1.table[j];
			b3.nrElem++;
			i++;
		}
	}

	return b3;
}


Bag::~Bag() {
	//complexity: theta(n)

	delete[] this->table;
}


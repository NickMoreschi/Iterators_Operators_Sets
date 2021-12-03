#include "set.h"
#include <iostream>

using namespace std;

Set::Set() {
    _size = 0;
    _head = new Elem;
    _tail = new Elem;
    _head->next = _tail;
    _head->prev = 0;
    _tail->next = 0;
    _tail->prev = _head;
}

Set::Set(const Set& rhs) {
    _size = rhs._size;
    _head = new Elem;
    _tail = new Elem;

    Elem *temp = _head;
    Elem *copy = rhs._head->next;

    while (copy != rhs._tail) {
        Elem *node = new Elem;
        node->info = copy->info;
        node->prev = temp;
        temp->next = node;
        temp = temp->next;
        copy = copy->next;
    }

    temp->next = _tail;
    _tail->prev = temp;
}

Set::~Set() {
    Elem *temp = _head;
    while (temp != _tail) {
        temp = temp->next;
        delete temp->prev;
    }
    delete temp;
}

Set& Set::operator = (const Set &rhs) {
    if (&rhs == this) {
        return *this;
    }

    _size = rhs._size;
    Elem *temp = _head;

    while (temp != _tail) {
        temp = temp->next;
        delete temp->prev;
    }

    delete temp;
    _head = new Elem;
    _tail = new Elem;
    temp = _head;

    Elem *copy = rhs._head->next;
    while (copy != rhs._tail) {
        Elem *node = new Elem;
        node->info = copy->info;
        node->prev = temp;
        temp->next = node;
        temp = temp->next;
        copy = copy->next;
    }

    temp->next = _tail;
    _tail->prev = temp;

    return *this;
}

void Set::insert(ELEMENT_TYPE num) {
    Elem *temp = _head;    
    Elem *n = new Elem;
    n->info = num;

    Elem *node = _head->next;
    while (node != _tail) {
        if (node->info == num) {
            return;
        }
        node = node->next;
    }

  while (temp) {
    if (temp->info > num || temp == _tail) {
        Elem *cur = temp->prev;
        cur->next = n;
        n->prev = cur;
        n->next = temp;
        temp->prev = n;
        _size++;
        return;
    }
    temp = temp->next;
  }
}

void Set::erase(ELEMENT_TYPE x) {
    Elem *temp = _head->next;

    while (temp != _tail) {
        if (temp->info == x) {
            Elem *n = temp->next;
            Elem *node = temp->prev;

            temp->prev->next = n;
            temp->next->prev = node;
            delete temp;
            _size--;
            return;
        }
    temp = temp->next;
  }
}

void Set::clear() {
    Elem *temp = _head->next;

    while (temp != _tail) {
        temp = temp->next;
        delete temp->prev;
    }

    _head->next = _tail;
    _tail->prev = _head;
    _size = 0;
}

int Set::size() const {
    return _size;
}

bool operator==(const Set& s1, const Set& s2) {
    Set::Iterator t1 = s1.begin();
    Set::Iterator t2 = s2.begin();

    if (s1.size() != s2.size()) {
        return false;
    }

    while (t1 != s1.end()) {
        if (t1 == t2) {
            return false;
        }
        t1++;
        t2++;
    }

    return true;
}

ostream& operator<<(ostream& os, Set& s) {
    Set::Iterator it = s.begin();

    while (it != s.end()) {
        os << *it << " ";
        it++;
    }

    return os;
}

Set::Iterator Set::find(ELEMENT_TYPE x) const {
    Elem *node = _head->next;

    while (node != _tail) {
	    if (node->info == x) {
            return Set::Iterator(node);
        }
        node = node->next;
    }

    return end();
}

Set::Iterator Set::begin() const {
    return Set::Iterator(_head -> next);
}

Set::Iterator Set::end() const {
    return Set::Iterator(_tail);
}

Set::Reverse_Iterator Set::rbegin() const {
    return Set::Reverse_Iterator(_tail -> prev);
}

Set::Reverse_Iterator Set::rend() const {
    return Set::Reverse_Iterator(_head);
}

ostream& Set::dump(ostream& out, const Set &s) {
    Set::Iterator it = s.begin();

    while (it != s.end()) {
        out << *it << " ";
        it++;
    }

    return out;
}

Set operator - (const Set& s1, const Set& s2) {
    Set newSet = s1;
    Set::Iterator it = s2.begin();

    while (it != s2.end()) {
        newSet.erase(*it);
        it++;
    }

    return newSet;
}

Set operator & (const Set& s1, const Set& s2) {
    Set newSet;
    Set::Iterator it1 = s2.begin();
    Set::Iterator it2 = s1.begin();

    while (it1 != s2.end()) {
        while (it2 != s1.end()) {
            if (*it1 == *it2) {
                newSet.insert(*it1);
            }
            it2++;
        }
        it2 = s1.begin();
        it1++;
    }

    return newSet;
}

Set operator | (const Set& s1, const Set& s2) {
    Set newSet = s1;
    Set::Iterator it = s2.begin();

    while (it != s2.end()) {
        newSet.insert(*it);
        it++;
    }

    return newSet;
}

Set::Iterator::Iterator(){
    _cur = nullptr;
}

Set::Iterator::Iterator(Elem *x) {
    _cur = x;
}

ELEMENT_TYPE& Set::Iterator::operator * () {
    return _cur -> info;
}

Set::Iterator Set::Iterator::operator ++ (int x) {
    _cur = _cur -> next;
    return *this;
}

Set::Iterator Set::Iterator::operator -- (int x) {
    _cur = _cur -> prev;
    return *this;
}

bool Set::Iterator::operator == (Iterator it) const {
    return _cur == it._cur;
}

bool Set::Iterator::operator != (Iterator it) const {
    return _cur != it._cur;
}

Set::Reverse_Iterator::Reverse_Iterator(){
    _cur = NULL;
}

Set::Reverse_Iterator::Reverse_Iterator(Elem *x) {
    _cur = x;
}

ELEMENT_TYPE& Set::Reverse_Iterator::operator * () {
    return _cur->info;
}

Set::Reverse_Iterator Set::Reverse_Iterator::operator ++ (int x) {
    _cur = _cur -> prev;
    return *this;
}

Set::Reverse_Iterator Set::Reverse_Iterator::operator -- (int x) {
    _cur = _cur -> next;
    return *this;
}

bool Set::Reverse_Iterator::operator == (Reverse_Iterator it) const {
    return _cur == it._cur;
}

bool Set::Reverse_Iterator::operator != (Reverse_Iterator it) const {
    return _cur != it._cur;
}
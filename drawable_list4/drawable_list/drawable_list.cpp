// drawable_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../drawable_list.h"

void Iterator::decrease_counter() {
	struct Node* temp = this->ptr;
	temp->iterator_counter--;
	if ((temp->iterator_counter == 0) && (temp->valid == false)) {
		this->ptr->item->~Drawable();
		delete this->ptr;
		delete this;
	}
}

void Iterator::increase_counter() {
	this->ptr->iterator_counter++;
}

Iterator::Iterator(Node& n) : ptr(&n) { increase_counter(); }
Iterator::Iterator(const Iterator& other) : ptr(other.ptr) { increase_counter(); }
Iterator::Iterator() : ptr(nullptr) {}

Iterator::~Iterator() {
	decrease_counter();
}

Drawable* Iterator::get_object() {return (this->ptr == nullptr) ? nullptr : this->ptr->item; }

void Iterator::invalidate() { 
	this->ptr->valid = false;
	if (this->ptr->iterator_counter == 1) { decrease_counter(); }
}

Iterator& Iterator::set(const Iterator& other) {
	decrease_counter();
	this->ptr = other.ptr;
	increase_counter();
	return *this ;
}

Iterator& Iterator::next() {
	Node* current = this->ptr->next;
	while ((current != nullptr) && (current->valid != false)) {
		current = current->next;
	}
	if (current == nullptr) {
		ptr = nullptr;
		return *this;
	}
	decrease_counter();
	this->ptr = current;
	increase_counter();
	return *this;
}

Iterator& Iterator::prev() {
	Node* current = this->ptr->prev;
	while ((current != nullptr) && (current->valid != false)) {
		current = current->prev;
	}
	if (current == nullptr) {
		ptr = nullptr;
		return *this;
	}
	decrease_counter();
	this->ptr = current;
	increase_counter();
	return *this;
}

bool Iterator::valid() const { 
	if (ptr == nullptr) { return false; }
	return this->ptr->valid; 
}

DrawableList::DrawableList() : head(nullptr), tail(nullptr), size(0) {}

DrawableList::~DrawableList() {
	Iterator counter = begin();
	while (counter.ptr != nullptr) {
		erase(counter);
		counter = counter.next();
	}
}

void DrawableList::push_front(Drawable& item) {
	Node* node = new Node;
	node->item = &item;
	node->next = this->head;
	node->valid = true;
	this->head = node;
	this->size++;
}

void DrawableList::push_back(Drawable& item) {
	Node* node = new Node;
	node->item = &item;
	node->prev = this->tail;
	node->valid = true;
	this->tail = node;
	this->size++;
}

void DrawableList::erase(Iterator& it) {
	Node* NodeNext = it.ptr->next;
	Node* NodePrev = it.ptr->prev;
	NodeNext->prev = NodePrev;
	NodePrev->next = NodeNext;
	this->size--;
	it.invalidate();
}

int DrawableList::get_size() const {
	return this->size;
}

Iterator DrawableList::begin() {
	if (this->head == nullptr) { return Iterator::Iterator(); }
	Iterator temp = Iterator::Iterator(*this->head);
	if (temp.ptr->valid != true) { temp = temp.next(); }
	return temp;
}

Iterator DrawableList::end() {
	if (this->tail == nullptr) { return Iterator::Iterator(); }
	Iterator a = Iterator::Iterator(*this->tail);
	if (a.ptr->valid != true) { a = a.prev(); }
	return a;
}

Iterator DrawableList::find(Drawable* that) {
	if (size == 0) { return Iterator(); }
	Iterator current = begin();
	while (current.valid()) {
		Drawable* point = current.get_object();
		if (point == that) { return current; }
	}
	return Iterator();
}
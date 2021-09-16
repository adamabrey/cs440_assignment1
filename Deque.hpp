#ifndef _DEQUE_HPP_
#define _DEQUE_HPP_

#define Deque_DEFINE(t)
struct Deque_int_Iterator {
  int* addr;
  void (*inc)(Deque_int_Iterator *);
  void (*dec)(Deque_int_Iterator *);
  int (*deref)(Deque_int_Iterator *);
};

void inc(Deque_int_Iterator *it) {

}

void dec(Deque_int_Iterator* it) {

}

int deref(Deque_int_Iterator *) {

}

struct Deque_int {
  int* data;
  int front;
  int back;
  int (*pop_back)(Deque_int *, int i);
  int (*pop_front)(Deque_int *, int i);
  void (*push_back)(Deque_int *, int val);
  void (*push_front)(Deque_int *, int val);
  void (*dtor)(Deque_int *);
  int (*at)(Deque_int *, int i);
  int (*back)(Deque_int *);
  int (*front)(Deque_int *);
  bool (*empty)(Deque_int *);
  void (*clear)(Deque_int *);
  Deque_int_Iterator (*begin)(Deque_int *);
  Deque_int_Iterator (*end)(Deque_int *);
  int (*size)(Deque_int *);
};

int pop_back(Deque_int *deq, int i) {

}

int pop_front(Deque_int *deq, int i) {

}

void push_back(Deque_int *deq, int val) {

}

void push_front(Deque_int *deq, int val) {

}

void dtor(Deque_int *deq) {

}

int at(Deque_int *deq, int i) {

}

int front(Deque_int *deq) {

}

int back(Deque_int *deq) {

}

bool empty(Deque_int *deq) {

}

void clear(Deque_int *deq) {

}

Deque_int_Iterator begin(Deque_int *deq) {

}

Deque_int_Iterator end(Deque_int *deq) {

}

int size(Deque_int *deq) {

}

bool Deque_int_equal(Deque_int deq1, Deque_int deq2) {

}

bool Deque_int_Iterator_equal(Deque_int_Iterator it1, Deque_int_Iterator it2) {

}

void Deque_int_ctor(Deque_int *, bool (*cmp)(int, int)) {

}

#endif

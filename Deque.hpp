#ifndef _DEQUE_HPP_
#define _DEQUE_HPP_

#define Deque_DEFINE(t)
struct Deque_int_Iterator {
  int* addr;
  int* first_addr;
  int* last_addr;
  void (*inc)(Deque_int_Iterator *);
  void (*dec)(Deque_int_Iterator *);
  int (*deref)(Deque_int_Iterator *);
};

void inc(Deque_int_Iterator *it) {
  if (it->addr == it->last_addr) {
    it->addr = it->first_addr;
  } else {
    it->addr++;
  }
}

void dec(Deque_int_Iterator *it) {
  if (it->addr == it->first_addr) {
    it->addr = it->last_addr;
  } else {
    it->addr--;
  }
}

int deref(Deque_int_Iterator *it) {
  return *(it->addr);
}

struct Deque_int {
  int* data;
  int front_i;
  int back_i;
  int data_size;
  int (*pop_back)(Deque_int *);
  int (*pop_front)(Deque_int *);
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
  size_t (*size)(Deque_int *);
  void (*sort)(Deque_int *, Deque_int_Iterator it1, Deque_int_Iterator it2);
};

int pop_back(Deque_int *deq) {
  if (!deq->empty(deq)) {
    deq->back_i = (deq->back_i - 1) % deq->data_size;
    return deq->data[deq->back_i];
  }
  return 0;
}

int pop_front(Deque_int *deq) {
  if (!deq->empty(deq)) {
    int val = deq->data[deq->front_i];
    deq->front_i = (deq->front_i + 1) % deq->data_size;
    return val;
  }
  return 0;
}

void push_back(Deque_int *deq, int val) {
  if (deq->size(deq) == deq->data_size) {
    int* new_data = (int*)malloc(deq->data_size * 2 * sizeof(int));
    int new_i = 0;
    for (int i=deq->front_i; i != deq->back_i; i = (i+1)%data_size) {
      new_data[new_i] = deq->data[i];
      new_i++;
    }
    deq->front_i = 0;
    deq->back_i = new_i;
    deq->data_size *= 2;
    free(deq->data);
    deq->data = new_data;
  }
  deq->data[deq->back_i] = val;
  deq->back_i = (deq->back_i + 1) % deq->data_size;
}

void push_front(Deque_int *deq, int val) {
  if (deq->size(deq) == deq->data_size) {
    int* new_data = (int*)malloc(deq->data_size * 2 * sizeof(int));
    int new_i = 0;
    for (int i=deq->front_i; i != deq->back_i; i = (i+1)%deq->data_size) {
      new_data[new_i] = deq->data[i];
      new_i++;
    }
    deq->front_i = 0;
    deq->back_i = new_i;
    deq->data_size *= 2;
    free(deq->data);
    deq->data = new_data;
  }
  deq->front_i = (deq->front_i - 1) % deq->data_size;
  deq->data[deq->front_i] = val;
}

void dtor(Deque_int *deq) {
  free(deq->data);
}

int at(Deque_int *deq, int i) {
  return deq->data[(deq->front_i + i) % deq->data_size];
}

int front(Deque_int *deq) {
  return deq->data[deq->front_i];
}

int back(Deque_int *deq) {
  return deq->data[(deq->back_i - 1) % deq->data_size];
}

bool empty(Deque_int *deq) {
  return (deq->size(deq) == 0);
}

void clear(Deque_int *deq) {
  free(deq->data);
  deq->data = (int*)malloc(deq->data_size * sizeof(int));
  deq->front_i = 0;
  deq->back_i = 0;
}

//think this returns an iterator to the front_i location
Deque_int_Iterator begin(Deque_int *deq) {
  Deque_int_Iterator it;
  it.first_addr = &(deq->data[0]);
  it.last_addr = &(deq->data[deq->data_size-1]);
  it.addr = &(deq->data[deq->front_i]);
  it.inc = &inc;
  it.dec = &dec;
  it.deref = &deref;
  return it;
}

//think this returns an iterator to the back_i location
Deque_int_Iterator end(Deque_int *deq) {
  Deque_int_Iterator it;
  it.first_addr = &(deq->data[0]);
  it.last_addr = &(deq->data[deq->data_size-1]);
  it.addr = &(deq->data[deq->back_i]);
  it.inc = &inc;
  it.dec = &dec;
  it.deref = &deref;
  return it;
}

std::size_t size(Deque_int *deq) {
  return (deq->back_i - deq->front_i) % deq->data_size;
}

void sort(Deque_int *deq, Deque_int_Iterator it1, Deque_int_Iterator it2) {

}

bool Deque_int_equal(Deque_int deq1, Deque_int deq2) {
  if (deq1.size(deq1) != deq2.size(deq2)) {
    return false;
  }
  Deque_int_Iterator it2 = deq2.begin(&deq2);
  for (Deque_int_Iterator it1 = deq1.begin(&deq1); !Deque_MyClass_Iterator_equal(it1, deq1.end(&deq1)); it1.inc(&it1)) {
    if (it2.deref(&it2) != it1.deref(&it1)) { //structs cant be == so idk
      return false;
    }
    it2.inc(&it2);
  }
  return true;
}

bool Deque_int_Iterator_equal(Deque_int_Iterator it1, Deque_int_Iterator it2) {
  return (it1->addr == it2->addr);
}

void Deque_int_ctor(Deque_int *deq, bool (*cmp)(int, int)) {

}

#endif

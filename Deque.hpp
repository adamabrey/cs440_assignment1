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

//function set by constructor to use for sorting
bool is_less(int val1, int val2);

//could get better performance with faster sort, but insertion sort is simple
void sort(Deque_int *deq, Deque_int_Iterator start, Deque_int_Iterator end) {
  int current, temp;
  Deque_int_Iterator x = start;
  Deque_int_Iterator y;
  for (x.inc(&x); !Deque_int_Iterator_equal(x, end); x.inc(&x)) {
    current = x.deref(&x);

    x.dec(&x);                //ugly way to put y = x - 1
    y = x;                    //retains all fields
    x.inc(&x);

    //while (y > 0 && current < data[y])
    while (!Deque_int_Iterator_equal(y, it1) && is_less(current, y.deref(&y))) {

      temp = y.deref(&y);   //ugly way to do data[y+1] = data[y];
      y.inc(&y);
      *(y.addr) = temp;
      y.dec(&y);

      y.dec(&y);            //y--
    }

    if (Deque_int_Iterator_equal(y, it1)) {
      temp = y.deref(&y);   //data[y+1] = data[y];
      y.inc(&y);
      *(y.addr) = temp;
      y.dec(&y);
    }

    y.inc(&y);              //data[y+1] = current;
    *(y.addr) = current;
  }
}

bool Deque_int_equal(Deque_int deq1, Deque_int deq2) {
  if (deq1.size(deq1) != deq2.size(deq2)) {
    return false;
  }
  Deque_int_Iterator it2 = deq2.begin(&deq2);
  for (Deque_int_Iterator it1 = deq1.begin(&deq1); !Deque_MyClass_Iterator_equal(it1, deq1.end(&deq1)); it1.inc(&it1)) {
    if (it2.deref(&it2) != it1.deref(&it1)) { //structs cant be == so idk
                                              //change to double less than comparison
                                              //figure out if want to deal with func not set first
      return false;
    }
    it2.inc(&it2);
  }
  return true;
}

bool Deque_int_Iterator_equal(Deque_int_Iterator it1, Deque_int_Iterator it2) {
  return (it1->addr == it2->addr);
}

void Deque_int_ctor(Deque_int *deq, bool (less_than)(int, int)) {
  deq->data_size = 8;   //feel like power of 2 has some benefit?
  deq->data = (int*)malloc(deq->data_size * sizeof(int));
  deq->front_i = 0;
  deq->back_i = 0;
  deq->pop_back = &pop_back;
  deq->pop_front = &pop_front;
  deq->push_back = &push_back;
  deq->push_front = &push_front;
  deq->dtor = &dtor;
  deq->at = &at;
  deq->back = &back;
  deq->front = &front;
  deq->empty = &empty;
  deq->clear = &clear;
  deq->begin = &begin;
  deq->end = &end;
  deq->size = &size;
  deq->sort = &sort;    //init all function pointers in deque

  is_less = less_than;  //set cmp function for sorting;
                        //test to see if need as a deque function instead
}

#endif

#ifndef _DEQUE_HPP_
#define _DEQUE_HPP_

#define Deque_DEFINE(t) \
  struct Deque_##t##_Iterator {\
    t *addr;\
    t *first_addr;\
    t *last_addr;\
    void (*inc)(Deque_##t##_Iterator *);\
    void (*dec)(Deque_##t##_Iterator *);\
    t &(*deref)(Deque_##t##_Iterator *);\
  };\
\
  void inc(Deque_##t##_Iterator *it) {\
    if (it->addr == it->last_addr) {\
      it->addr = it->first_addr;\
    } else {\
      it->addr++;\
    }\
  }\
\
  void dec(Deque_##t##_Iterator *it) {\
    if (it->addr == it->first_addr) {\
      it->addr = it->last_addr;\
    } else {\
      it->addr--;\
    }\
  }\
\
  t &deref(Deque_##t##_Iterator *it) {\
    return *(it->addr);\
  }\
\
  struct Deque_##t {\
    t *data;\
    int front_i;\
    int back_i;\
    int data_size;\
    int num_of_vals;\
    t (*pop_back)(Deque_##t *);\
    t (*pop_front)(Deque_##t *);\
    void (*push_back)(Deque_##t *, t val);\
    void (*push_front)(Deque_##t *, t val);\
    void (*dtor)(Deque_##t *);\
    t &(*at)(Deque_##t *, int i);\
    t &(*back)(Deque_##t *);\
    t &(*front)(Deque_##t *);\
    bool (*empty)(Deque_##t *);\
    void (*clear)(Deque_##t *);\
    Deque_##t##_Iterator (*begin)(Deque_##t *);\
    Deque_##t##_Iterator (*end)(Deque_##t *);\
    size_t (*size)(Deque_##t *);\
    void (*sort)(Deque_##t *, Deque_##t##_Iterator it1, Deque_##t##_Iterator it2);\
    bool (*is_less)(const t &val1, const t &val2);\
    char type_name[sizeof("Deque_" #t)];\
  };\
\
  t pop_back(Deque_##t *deq) {\
    int i = deq->back_i - 1;\
    if (i < 0) i += deq->data_size;\
    deq->back_i = i;\
    deq->num_of_vals--;\
    return deq->data[deq->back_i];\
  }\
\
  t pop_front(Deque_##t *deq) {\
    t val = deq->data[deq->front_i];\
    deq->front_i = (deq->front_i + 1) % deq->data_size;\
    deq->num_of_vals--;\
    return val;\
  }\
\
  void push_back(Deque_##t *deq, t val) {\
    if (deq->size(deq) == deq->data_size) {\
      t *new_data = (t *)malloc(deq->data_size * 2 * sizeof(t));\
      int i = deq->front_i;\
      int new_i;\
      for (new_i = 0; new_i < deq->num_of_vals; new_i++) {\
        new_data[new_i] = deq->data[i];\
        i = (i+1)%deq->data_size;\
      }\
      deq->front_i = 0;\
      deq->back_i = new_i;\
      deq->data_size *= 2;\
      free(deq->data);\
      deq->data = new_data;\
    }\
    deq->data[deq->back_i] = val;\
    deq->back_i = (deq->back_i + 1) % deq->data_size;\
    deq->num_of_vals++;\
  }\
\
  void push_front(Deque_##t *deq, t val) {\
    if (deq->size(deq) == deq->data_size) {\
      t *new_data = (t *)malloc(deq->data_size * 2 * sizeof(t));\
      int i = deq->front_i;\
      int new_i;\
      for (new_i = 0; new_i < deq->num_of_vals; new_i++) {\
        new_data[new_i] = deq->data[i];\
        i = (i+1)%deq->data_size;\
      }\
      deq->front_i = 0;\
      deq->back_i = new_i;\
      deq->data_size *= 2;\
      free(deq->data);\
      deq->data = new_data;\
    }\
    deq->front_i = (deq->front_i - 1);\
    if (deq->front_i < 0) deq->front_i += deq->data_size;\
    deq->data[deq->front_i] = val;\
    deq->num_of_vals++;\
  }\
\
  void dtor(Deque_##t *deq) {\
    free(deq->data);\
  }\
\
  t &at(Deque_##t *deq, int i) {\
    return deq->data[(deq->front_i + i) % deq->data_size];\
  }\
\
  t &front(Deque_##t *deq) {\
    return deq->data[deq->front_i];\
  }\
\
  t &back(Deque_##t *deq) {\
    return deq->data[(deq->back_i - 1) % deq->data_size];\
  }\
\
  bool empty(Deque_##t *deq) {\
    return (deq->size(deq) == 0);\
  }\
\
  void clear(Deque_##t *deq) {\
    /*free(deq->data);*/\
    /*deq->data = (t *)malloc(deq->data_size * sizeof(t));*/\
    deq->front_i = 0;\
    deq->back_i = 0;\
    deq->num_of_vals = 0;\
  }\
\
  /*think this returns an iterator to the front_i location*/\
  Deque_##t##_Iterator begin(Deque_##t *deq) {\
    Deque_##t##_Iterator it;\
    it.first_addr = &(deq->data[0]);\
    it.last_addr = &(deq->data[deq->data_size-1]);\
    it.addr = &(deq->data[deq->front_i]);\
    it.inc = &inc;\
    it.dec = &dec;\
    it.deref = &deref;\
    return it;\
  }\
\
  /*think this returns an iterator to the back_i location*/\
  Deque_##t##_Iterator end(Deque_##t *deq) {\
    Deque_##t##_Iterator it;\
    it.first_addr = &(deq->data[0]);\
    it.last_addr = &(deq->data[deq->data_size-1]);\
    it.addr = &(deq->data[deq->back_i]);\
    it.inc = &inc;\
    it.dec = &dec;\
    it.deref = &deref;\
    return it;\
  }\
\
  std::size_t size(Deque_##t *deq) {\
    return deq->num_of_vals;\
  }\
\
  bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2) {\
    return (it1.addr == it2.addr);\
  }\
\
  /*could get better performance with faster sort, but insertion sort is simple*/\
  void sort(Deque_##t *deq, Deque_##t##_Iterator start, Deque_##t##_Iterator end) {\
    t current, temp;\
    Deque_##t##_Iterator x = start;\
    Deque_##t##_Iterator y;\
    for (x.inc(&x); !Deque_##t##_Iterator_equal(x, end); x.inc(&x)) {\
      current = x.deref(&x);\
\
      x.dec(&x);                /*ugly way to put y = x - 1*/\
      y = x;                    /*retains all fields*/\
      x.inc(&x);\
\
      /*while (y > 0 && current < data[y])*/\
      while (!Deque_##t##_Iterator_equal(y, start) && deq->is_less(current, y.deref(&y))) {\
\
        temp = y.deref(&y);   /*ugly way to do data[y+1] = data[y];*/\
        y.inc(&y);\
        y.deref(&y) = temp;\
        y.dec(&y);\
\
        y.dec(&y);            /*y--*/\
      }\
\
      /*if (y == 0)*/\
      if (Deque_##t##_Iterator_equal(y, start) && deq->is_less(current, y.deref(&y))) {\
        temp = y.deref(&y);   /*data[y+1] = data[y];*/\
        y.inc(&y);\
        y.deref(&y) = temp;\
        y.dec(&y);\
\
      } else {\
        y.inc(&y);            /*needed for y+1*/\
                              /*unless at start, then y was never decremented*/\
      }\
\
      y.deref(&y) = current;    /*data[y+1] = current;*/\
    }\
  }\
\
  bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2) {\
    if (deq1.size(&deq1) != deq2.size(&deq2)) {\
      return false;\
    }\
    Deque_##t##_Iterator it2 = deq2.begin(&deq2);\
    for (Deque_##t##_Iterator it1 = deq1.begin(&deq1); !Deque_##t##_Iterator_equal(it1, deq1.end(&deq1)); it1.inc(&it1)) {\
\
      /*long boolean statement, basically testing if *it1 == *it2 by*/\
      /*doing two less than comparisons, neither should return true if ==*/\
      if (deq1.is_less(it2.deref(&it2), it1.deref(&it1)) || deq1.is_less(it1.deref(&it1), it2.deref(&it2))) {\
        return false;\
      }\
      /*one for each cmp function to be safe*/\
      if (deq2.is_less(it2.deref(&it2), it1.deref(&it1)) || deq2.is_less(it1.deref(&it1), it2.deref(&it2))) {\
        return false;\
      }\
      it2.inc(&it2);\
    }\
    return true;\
  }\
\
  void Deque_##t##_ctor(Deque_##t *deq, bool (less_than)(const t &, const t &)) {\
    deq->data_size = 8;         /*feel like power of 2 has some benefit?*/\
    deq->data = (t *)malloc(deq->data_size * sizeof(t));\
    deq->front_i = 0;\
    deq->back_i = 0;\
    deq->num_of_vals = 0;\
    deq->pop_back = &pop_back;\
    deq->pop_front = &pop_front;\
    deq->push_back = &push_back;\
    deq->push_front = &push_front;\
    deq->dtor = &dtor;\
    deq->at = &at;\
    deq->back = &back;\
    deq->front = &front;\
    deq->empty = &empty;\
    deq->clear = &clear;\
    deq->begin = &begin;\
    deq->end = &end;\
    deq->size = &size;\
    deq->sort = &sort;          /*init all function pointers in deque*/\
    deq->is_less = less_than;   /*set cmp function for sorting*/\
    strcpy(deq->type_name, "Deque_" #t);\
  }\


// struct Deque_int_Iterator {
//   int* addr;
//   int* first_addr;
//   int* last_addr;
//   void (*inc)(Deque_int_Iterator *);
//   void (*dec)(Deque_int_Iterator *);
//   int (*deref)(Deque_int_Iterator *);
// };
//
// void inc(Deque_int_Iterator *it) {
//   if (it->addr == it->last_addr) {
//     it->addr = it->first_addr;
//   } else {
//     it->addr++;
//   }
// }
//
// void dec(Deque_int_Iterator *it) {
//   if (it->addr == it->first_addr) {
//     it->addr = it->last_addr;
//   } else {
//     it->addr--;
//   }
// }
//
// int deref(Deque_int_Iterator *it) {
//   return *(it->addr);
// }
//
// struct Deque_int {
//   int* data;
//   int front_i;
//   int back_i;
//   int data_size;
//   int num_of_vals;
//   int (*pop_back)(Deque_int *);
//   int (*pop_front)(Deque_int *);
//   void (*push_back)(Deque_int *, int val);
//   void (*push_front)(Deque_int *, int val);
//   void (*dtor)(Deque_int *);
//   int (*at)(Deque_int *, int i);
//   int (*back)(Deque_int *);
//   int (*front)(Deque_int *);
//   bool (*empty)(Deque_int *);
//   void (*clear)(Deque_int *);
//   Deque_int_Iterator (*begin)(Deque_int *);
//   Deque_int_Iterator (*end)(Deque_int *);
//   size_t (*size)(Deque_int *);
//   void (*sort)(Deque_int *, Deque_int_Iterator it1, Deque_int_Iterator it2);
//   bool (*is_less)(const int &val1, const int &val2);
//   char type_name[sizeof("Deque_int")];
// };
//
// int pop_back(Deque_int *deq) {
//   if (!deq->empty(deq)) {
//     deq->back_i = (deq->back_i - 1) % deq->data_size;
//     deq->num_of_vals--;
//     return deq->data[deq->back_i];
//   }
//   return 0;
// }
//
// int pop_front(Deque_int *deq) {
//   if (!deq->empty(deq)) {
//     int val = deq->data[deq->front_i];
//     deq->front_i = (deq->front_i + 1) % deq->data_size;
//     deq->num_of_vals--;
//     return val;
//   }
//   return 0;
// }
//
// void push_back(Deque_int *deq, int val) {
//   if (deq->size(deq) == deq->data_size) {
//     int* new_data = (int*)malloc(deq->data_size * 2 * sizeof(int));
//     int i = deq->front_i;
//     int new_i;
//     for (new_i = 0; new_i < deq->num_of_vals; new_i++) {
//       new_data[new_i] = deq->data[i];
//       i = (i+1)%deq->data_size;
//     }
//     deq->front_i = 0;
//     deq->back_i = new_i;
//     deq->data_size *= 2;
//     free(deq->data);
//     deq->data = new_data;
//   }
//   deq->data[deq->back_i] = val;
//   deq->back_i = (deq->back_i + 1) % deq->data_size;
//   deq->num_of_vals++;
// }
//
// void push_front(Deque_int *deq, int val) {
//   if (deq->size(deq) == deq->data_size) {
//     int* new_data = (int*)malloc(deq->data_size * 2 * sizeof(int));
//     int i = deq->front_i;
//     int new_i;
//     for (new_i = 0; new_i < deq->num_of_vals; new_i++) {
//       new_data[new_i] = deq->data[i];
//       i = (i+1)%deq->data_size;
//     }
//     deq->front_i = 0;
//     deq->back_i = new_i;
//     deq->data_size *= 2;
//     free(deq->data);
//     deq->data = new_data;
//   }
//   deq->front_i = (deq->front_i - 1) % deq->data_size;
//   deq->data[deq->front_i] = val;
//   deq->num_of_vals++;
// }
//
// void dtor(Deque_int *deq) {
//   free(deq->data);
// }
//
// int at(Deque_int *deq, int i) {
//   return deq->data[(deq->front_i + i) % deq->data_size];
// }
//
// int front(Deque_int *deq) {
//   return deq->data[deq->front_i];
// }
//
// int back(Deque_int *deq) {
//   return deq->data[(deq->back_i - 1) % deq->data_size];
// }
//
// bool empty(Deque_int *deq) {
//   return (deq->size(deq) == 0);
// }
//
// void clear(Deque_int *deq) {
//   free(deq->data);
//   deq->data = (int*)malloc(deq->data_size * sizeof(int));
//   deq->front_i = 0;
//   deq->back_i = 0;
//   deq->num_of_vals = 0;
// }
//
// //think this returns an iterator to the front_i location
// Deque_int_Iterator begin(Deque_int *deq) {
//   Deque_int_Iterator it;
//   it.first_addr = &(deq->data[0]);
//   it.last_addr = &(deq->data[deq->data_size-1]);
//   it.addr = &(deq->data[deq->front_i]);
//   it.inc = &inc;
//   it.dec = &dec;
//   it.deref = &deref;
//   return it;
// }
//
// //think this returns an iterator to the back_i location
// Deque_int_Iterator end(Deque_int *deq) {
//   Deque_int_Iterator it;
//   it.first_addr = &(deq->data[0]);
//   it.last_addr = &(deq->data[deq->data_size-1]);
//   it.addr = &(deq->data[deq->back_i]);
//   it.inc = &inc;
//   it.dec = &dec;
//   it.deref = &deref;
//   return it;
// }
//
// std::size_t size(Deque_int *deq) {
//   return deq->num_of_vals;
// }
//
// bool Deque_int_Iterator_equal(Deque_int_Iterator it1, Deque_int_Iterator it2) {
//   return (it1.addr == it2.addr);
// }
//
// //could get better performance with faster sort, but insertion sort is simple
// void sort(Deque_int *deq, Deque_int_Iterator start, Deque_int_Iterator end) {
//   int current, temp;
//   Deque_int_Iterator x = start;
//   Deque_int_Iterator y;
//   for (x.inc(&x); !Deque_int_Iterator_equal(x, end); x.inc(&x)) {
//     current = x.deref(&x);
//
//     x.dec(&x);                //ugly way to put y = x - 1
//     y = x;                    //retains all fields
//     x.inc(&x);
//
//     //while (y > 0 && current < data[y])
//     while (!Deque_int_Iterator_equal(y, start) && deq->is_less(current, y.deref(&y))) {
//
//       temp = y.deref(&y);   //ugly way to do data[y+1] = data[y];
//       y.inc(&y);
//       *(y.addr) = temp;
//       y.dec(&y);
//
//       y.dec(&y);            //y--
//     }
//
//     //if (y == 0)
//     if (Deque_int_Iterator_equal(y, start)) {
//       temp = y.deref(&y);   //data[y+1] = data[y];
//       y.inc(&y);
//       *(y.addr) = temp;
//       y.dec(&y);
//
//     } else {
//       y.inc(&y);            //needed for y+1
//                             //unless at start, then y was never decremented
//     }
//
//     *(y.addr) = current;    //data[y+1] = current;
//   }
// }
//
// bool Deque_int_equal(Deque_int deq1, Deque_int deq2) {
//   if (deq1.size(&deq1) != deq2.size(&deq2)) {
//     return false;
//   }
//   Deque_int_Iterator it2 = deq2.begin(&deq2);
//   for (Deque_int_Iterator it1 = deq1.begin(&deq1); !Deque_int_Iterator_equal(it1, deq1.end(&deq1)); it1.inc(&it1)) {
//
//     //long boolean statement, basically testing if *it1 == *it2 by
//     //doing two less than comparisons, neither should return true if ==
//     if (deq1.is_less(it2.deref(&it2), it1.deref(&it1)) || deq1.is_less(it1.deref(&it1), it2.deref(&it2))) {
//       return false;
//     }
//     //one for each cmp function to be safe
//     if (deq2.is_less(it2.deref(&it2), it1.deref(&it1)) || deq2.is_less(it1.deref(&it1), it2.deref(&it2))) {
//       return false;
//     }
//     it2.inc(&it2);
//   }
//   return true;
// }
//
// void Deque_int_ctor(Deque_int *deq, bool (less_than)(const int &, const int &)) {
//   deq->data_size = 8;         //feel like power of 2 has some benefit?
//   deq->data = (int*)malloc(deq->data_size * sizeof(int));
//   deq->front_i = 0;
//   deq->back_i = 0;
//   deq->num_of_vals = 0;
//   deq->pop_back = &pop_back;
//   deq->pop_front = &pop_front;
//   deq->push_back = &push_back;
//   deq->push_front = &push_front;
//   deq->dtor = &dtor;
//   deq->at = &at;
//   deq->back = &back;
//   deq->front = &front;
//   deq->empty = &empty;
//   deq->clear = &clear;
//   deq->begin = &begin;
//   deq->end = &end;
//   deq->size = &size;
//   deq->sort = &sort;          //init all function pointers in deque
//   deq->is_less = less_than;   //set cmp function for sorting
//   strcpy(deq->type_name, "Deque_int");
// }

#endif

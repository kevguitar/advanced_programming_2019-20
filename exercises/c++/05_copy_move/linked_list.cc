#include <algorithm>
#include <iostream>
#include <memory>


#include "ap_error.h"
// -I ../../../06_error_handling.cc in building

enum class Insertion_method { push_back, push_front };

template <class value_type>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method should be used to fill the list
  void insert(const value_type& v, const Insertion_method m);
  void insert(value_type&& v, const Insertion_method m);

  template <class T>
  friend std::ostream& operator<<(std::ostream&, const List<T>&);

/*  // return the size of the list
  std::size_t size() const { return size; }  without const declaration here, 
                                               error in main when calling 
                                               "const l.size();" */

  // delete all the nodes of the list (decl only)
  void reset();


  // default ctor
  List() noexcept = default; // No exceptions to be thrown.

  // decl only
  List(const List& l);

  // move ctor: Nothing can go wrong; move ctor just swaps objects already 
  //            implemented. "List&& l" could be replaced by "list&&"; the name 
  //            is not needed if the body is not precised.
  List(List&& l) noexcept = default;
  
  // copy assignment (decl only)
  List& operator=(const List& l);

  // move assignment (decl only)
  List& operator=(List&& l);
  
  // default destructor
  ~List() = default;

 private:
  // private struct node with the proper value_type
  struct node {
    value_type value;
    std::unique_ptr<node> next;

    // custom ctor
    node(const value_type& v, node * p): value{v}, next{p} {}
    node(value_type&& v, node * p): value{std::move(v)}, next{p} {}

    // Recursive copy ctor of the 
    node(const std::unique_ptr<node>& p) : value{p->value}{
      if(p->next)
        next = std::make_unique<node>(p->next);
    }
 

/*    // default ctor
    node() == default;

    // copy ctor
    node(const node& n) : value{n.value}, next{n.next} {}

    // move ctor
    node(node&& n) : value{std::move(n.value)}, next{std::move(n.next)} {}

    // copy assignment
    node& operator=(const node& n) {
      if (&n == this) return *this;
      next.reset();              // first of all clean my memory
      auto tmp = n;              // then use copy ctor
      (*this) = std::move(tmp);  // finally move assignment

      return *this;
    }

    // move assignment
    node& operator=(node&& n) {
      if (&n == this) return *this;
      value = std::move(n.value);
      next = std::move(n.next);

      return this;
    }
    
    // default destructor
    ~node() = default;*/

/*    node* tail() {
      auto tmp = head.get();
      while(tmp->next)
        tmp = tmp->next.get();

      return tmp;
    }*/
  };

  // append the newly created node at the end of the list (decls only)
  void push_back(const value_type& v);
  void push_back(value_type&& v);

  // insert the newly created node in front of the list (decls only)
  void push_front(const value_type& v);
  void push_front(value_type&& v);

  std::unique_ptr<node> head;
  std::size_t size;
};


// insert for lvalue
template <class value_type>
void List<value_type>::insert(const value_type& v, const Insertion_method m) {
  if (!head) { // It inserting first node...
    //head.reset(new node{v, nullptr});
    head = std::make_unique<node>(v, nullptr); // move assignment, create new 
                                               // object in heap
    return;
  }
  switch (m){
    case Insertion_method::push_back:
      push_back(v);
      break;
    case Insertion_method::push_front:
      push_front(v);
      break;
    default:
      AP_ERROR(false)<<"unknown insertion method";
      break;
  }
}

// insert for rvalue
template <class value_type>
void List<value_type>::insert(value_type&& v, const Insertion_method m) {
  if (!head) { // It inserting first node...
    //head.reset(new node{v, nullptr});
    head = std::make_unique<node>(std::move(v), nullptr); // move assignment, create new 
                                               // object in heap
    return;
  }
  switch (m){
    case Insertion_method::push_back:
      push_back(std::move(v));
      break;
    case Insertion_method::push_front:
      push_front(std::move(v));
      break;
    default:
      AP_ERROR(false)<<"unknown insertion method";
      break;
  }
}


// insert for universal references; do this to combine lvalue and rvalue in one 
// function.
template <class value_type>
template <class OT>
void List<value_type>::insert(OT&& v, const Insertion_method m) {
  if (!head) { // It inserting first node...
    //head.reset(new node{v, nullptr});
    head = std::make_unique<node>(v, nullptr); // move assignment, create new 
                                               // object in heap
    return;
  }
  switch (m){
    case Insertion_method::push_back:
      push_back(v);
      break;
    case Insertion_method::push_front:
      push_front(v);
      break;
    default:
      AP_ERROR(false)<<"unknown insertion method";
      break;
  }
}

/*
// deletes all the nodes of the list
template <class value_type>
void List::reset() {
  // TODO:
  // Sufficient to delete only the pointers (without invoking memory leask)? 
  auto foot = head;
  if (head) { head = (*foot).next; }  // if head!=nullptr push head to next node
  while (head) {                       // check if head==nullptr;
    head = (*head).next;              // push head to next node
    ((*foot).next).reset(nullptr);    // delete old head
  }
  size = 0;
}*/



/*// DON'T DO THIS!!! USE HEADER FILE!
// A range-for is not needed, since linked list can be trivially looped 
// through by a succesive sequence of pointers connecting each node, ending at
// a null pointer. Instead, we need a display function 
template <class value_type>
std::ostream& List::operator<<(std::ostream& os, const List<T>& l) {
    auto temp = head;
    while (temp) { // while temp is not nullptr
      os<<(*temp).value<<" ";
      temp = (*temp).next;
    }
    os<<std::endl;
    return os;
} */



// NEW

template<class value_type>
List<value_type>::List(const List& l) {
  /*auto tmp = l.head.get(); // raw pointer
    while(tmp) {
    insert(tmp->value, Insertion_method::push_back);
    tmp = tmp->next.get();
  }*/
  head = std::make_unique<node>(l.head);

}



template <class T>
void List<T>::push_back(const T& v) {
  node* last = tail();
  //last->next.reset(new node{v, nullptr});
  last->next = std::make_unique<node>(v, nullptr);
}

template <class T>
void List<T>::push_front(const T& v) {
  // auto h = head.release();
  // auto new_node = new node {v, h};
  // head.reset(new_node);

  // head.reset(new node{v, head.release()});

  head = std::make_unique<node>(v, head.release());
}


template<class value_type>
std::ostream& operator<<(std::ostream& os, const List<value_type>& l) {
  auto tmp = l.head.get();
  while (tmp) {
    os<<tmp->value<<" ";
    tmp = tmp->l.next.get();
  }
  return os;
}



// Tell the compiler that List<T>::node* is actually a type by putting typename.
template<class value_type>
typename List<T>::node* List<T>::tail() {
  auto tmp = head.get();
  while(tmp->next)
    tmp = tmp->next.get();

  return tmp;
}

int main() {
  try{

    List<int> l{};

    l.insert(4, Insertion_method::push_back);
    l.insert(5, Insertion_method::push_back);
    l.insert(3, Insertion_method::push_front);

    std::cout<<l<<std::endl;

    auto ol = l;

    l.insert(14, Insertion_method::push_front);

    std::cout<<l<<std::endl; // check deep copy
    std::cout<<ol<<std::endl;

  } catch(std::exception& e) {
    std::cerr<<e.what()<<std::endl;
  } catch(...) {
    std::cerr<<"Unknown exception"<<std::endl;
  }

  return 0;
}
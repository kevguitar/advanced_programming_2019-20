#include <iostream>
#include <memory>  //unique_ptr

#include "ap_error.h"

enum class method { push_back, push_front };

template <class T>
class List {
  struct node {
    std::unique_ptr<node> next;
    T value;
    /* Note that node* implicitly converts to unique_ptr<node> */ 
    node(const T& v, node* p) : next{p}, value{v} {/* copy ctor from args */
      std::cout << "copy ctor" << std::endl;
    }
    node(T&& v, node* p) : next{p}, value{std::move(v)} {/*move ctor from args*/
      std::cout << "move ctor" << std::endl;
    }
    /* This ctor creates a copy of a given node, and inherits next only if it is
       not a nullptr. */
    explicit node(const std::unique_ptr<node>& p) : value{p->value} {
      if (p->next)
        next = std::make_unique<node>(p->next);
    }
  };

  std::unique_ptr<node> head;

  /* OT&& is called universal reference. It behaves like an lvalue or an rvalue
     reference, depending on of what type is the argument. */ 
  template <class OT>
  void push_back(OT&& v);

  template <class OT>
  void push_front(OT&& v) {
    // auto h = head.release();
        /* new node {v,h}; direct-list-initialization (both explicit and 
           non-explicit constructors are considered) */
    // auto new_node = new node {v,h}; 
    // head.reset(new_node);

    /* Here, the move (copy) ctor is used if v is an rvalue (lvalue). */
    // head.reset(new node{v, head.release()});

    /* std::forward<OT> forwards v as an rvalue (lvalue) if v is an 
       rvalue(lvalue). */
    head = std::make_unique<node>(std::forward<OT>(v), head.release());
  }

  node* tail() noexcept;

 public:
  /* These functions all just move objects in memory, hence they don't need 
     exceptions. */
  List() noexcept = default;
  List(List&& l) noexcept = default;
  List& operator=(List&& l) noexcept = default;

  List(const List& l);
  List& operator=(const List& l);

  /* Universal reference; accept v as lvalue and rvalue. */
  template <class OT>
  void insert(OT&& v, const method m);

  /* A non-member function can access the private and protected members of a 
     class if it is declared a friend of that class. */
  template <class O> /* class O must not equal class T. */
  friend std::ostream& operator<<(std::ostream&, const List<O>&);
};

/* Member function List<T>::tail() returns pointer to last node of the list. 
   Inside a declaration or a definition of a template, "typename" can be used to
   declare that a dependent qualified name is a type. */ 
template <class T>
typename List<T>::node* List<T>::tail() noexcept {
  auto tmp = head.get(); /* Returns a pointer to head. */

  while (tmp->next)
    tmp = tmp->next.get();

  return tmp;
}

template <class T>
template <class OT>
void List<T>::insert(OT&& v, const method m) {
  if (!head) { // If List is empty, define *head as the only node.
    // head.reset(new node{v,nullptr});
    head = std::make_unique<node>(std::forward<OT>(v), nullptr);
    return;
  }
  switch (m) {
    case method::push_back:
      push_back(std::forward<OT>(v));
      break;

    case method::push_front:
      push_front(std::forward<OT>(v));
      break;
    default:

      /* TODO: Review AP_ERROR */
      AP_ERROR(false) << "Unknown insertion method";
      break;
  };
}

template <class T>
template <class OT>
void List<T>::push_back(OT&& v) {
  node* last = tail();
  // last->next.reset(new node{v, nullptr});
  last->next = std::make_unique<node>(std::forward<OT>(v), nullptr);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
  auto tmp = l.head.get();
  while (tmp) {
    os << tmp->value << " ";
    tmp = tmp->next.get();
  }
  return os;
}

/* copy ctor */
template <class T>
List<T>::List(const List& l) {
  /* Raw pointer: all list elements have to be inserted manually */
  // auto tmp = l.head.get();
  // while(tmp){
  //   insert(tmp->value,method::push_back);
  //   tmp=tmp->next.get();
  // }
  /* unique_ptr: new List takes l.head as new head using custom copy ctor of
     class "node" */
  head = std::make_unique<node>(l.head);
}

int main() {
  try {
    List<int> l{};

    l.insert(4, method::push_back);
    l.insert(5, method::push_back);
    l.insert(3, method::push_front);

    std::cout << l << std::endl;

    auto ol = l;
    int a = 9;
    l.insert(14, method::push_front);
    l.insert(a, method::push_front);

    std::cout << l << std::endl;
    std::cout << ol << std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}

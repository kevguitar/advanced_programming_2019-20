#include <algorithm>
#include <iostream>
#include <memory>

enum class Insertion_method { push_back, push_front };

template <class value_type>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method should be used to fill the list
  void insert(const value_type& v, const Insertion_method m);
  void insert(value_type&& v, const Insertion_method m);

  // return the size of the list
  std::size_t size() const { return size; } /* without const declaration here, 
                                               error in main when calling 
                                               "const l.size();" */

  // delete all the nodes of the list (decl only)
  void reset();

  // display function: forwards the pointers to all nodes to ostream
  std::ostream& operator<<(std::ostream& os, const List<T>& l);

  // default ctor
  List() : node{}, head{}, size{} { std::cout << "custom ctor\n"; }

  // custom ctor
  explicit List(const std::size_t length)
      : node{/* node ctor */}, head{new node{/* node ctor */}}, size{length} {
    std::cout << "custom ctor\n";
  }

  // TODO: copy ctor (decl only)
  List(const List& l);

  // move ctor
  List(List&& l) {}
  
  // TODO: copy assignment (decl only)
  List& operator=(const List& l);

  // TODO: move assignment (decl only)
  List& operator=(List&& l);
  
  // default destructor
  ~List() = default;

 private:
  // private struct node with the proper value_type
  struct node {
    value_type value;
    std::unique_ptr<node> next;

    // custom ctor
    explicit node(const value_type& v) 
        : value{v}, next{new std::unique_ptr<node>} {}

    // default ctor
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
    ~node() = default;
  };

  // append the newly created node at the end of the list (decls only)
  // TODO
  void push_back(const value_type& v);
  void push_back(value_type&& v);

  // insert the newly created node in front of the list (decls only)
  // TODO
  void push_front(const value_type& v);
  void push_front(value_type&& v);

  std::unique_ptr<node> head;
  std::size_t size;
};


template <class value_type>
void List::insert(const value_type& v, const Insertion_method m) {
  if (m==Insertion_method::push_front) {
    auto first{new node};
    auto tmp = head; 
    first->next = tmp;  // could I use {} initializers here?    
    first->value = v;   // ... and here?            
    head = &first;  
  } else {
    auto last{new node};
    auto tmp = head;
    while ((*tmp)->next) { tmp = (*tmp)->next; } // while not null, redirect tmp
    last->value = v;                // for last element, set value to v,
    (last->next).reset(nullptr);    // point last node to nullptr,
    (*tmp)->next = &last;           // point penultimate node to last node                
  }
}


template <class value_type>
void List::insert(value_type&& v, const Insertion_method m) {
  if (m==Insertion_method::push_front) {
    auto first{new node};
    auto tmp = head; 
    first->next{tmp};
    first->value{std::move(v)};             
    head = &first;  
  } else {
    auto last{new node};
    auto tmp = head;
    while ((*tmp)->next) { tmp = (*tmp)->next; } // while not null, redirect tmp
    last->value{std::move(v)};                // for last element, set value to v,
    (last->next).reset(nullptr);    // point last node to nullptr,
    (*tmp)->next = &last;           // point penultimate node to last node                
  }
}


// deletes all the nodes of the list
template <class value_type>
void List::reset() {
  // TODO:
  // Sufficient to delete only the pointers (without invoking memory leask)? 
  auto foot = head;
  if (head) { head = (*foot)->next; }  // if head!=nullptr push head to next node
  while (head) {                       // check if head==nullptr;
    head = (*head)->next;              // push head to next node
    ((*foot)->next).reset(nullptr);    // delete old head
  }
  size = 0;
}

// A range-for is not needed, since linked list can be trivially looped 
// through by a succesive sequence of pointers connecting each node, ending at
// a null pointer. Instead, we need a display function 
template <class value_type>
std::ostream& List::operator<<(std::ostream& os, const List<T>& l) {
    auto temp = head;
    while (temp) { // while temp is not nullptr
      os<<(*temp)->value<<" ";
      temp = (*temp)->next;
    }
    os<<std::endl;
    return os;
} 
#include <algorithm>  // std::copy
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


// TODO
template <class value_type>
void List::insert(const value_type& v, const Insertion_method m) {
  if (m==Insertion_method::push_front) {
    // create node first;
    // copy address of pointer head to tmp_pointer;
    // first.next = tmp_pointer;    // Do I need to invoke std::copy here?
    // first.value = v;             
    // head = &v;  
  } else {
    // create node last;
    // loop through nodes (pointer by pointer) until node.pointer==nullptr
    // last.value = v;          // Do I need to invoke std::copy here?
    // set node.pointer = &last.value;
    // last.next = nullptr;
  }
}

// TODO
template <class value_type>
void List::insert(value_type&& v, const Insertion_method m) {
  if (m==Insertion_method::push_front) {
    // node first{std::move()};
    // copy address of pointer head to tmp_pointer;
    // first.next = tmp_pointer;    // Do I need to invoke std::copy here?
    // first.value = v;             
    // head = &v;  
  } else {
    // create node last;
    // loop through nodes (pointer by pointer) until node.pointer==nullptr
    // last.value = v;          // Do I need to invoke std::copy here?
    // set node.pointer = &last.value;
    // last.next = nullptr;
  }
}


// deletes all the nodes of the list
template <class value_type>
void List::reset() {
  // deletes node pointers
  unique_ptr<node> foot{head};
  if (head) { head = (*foot).next; }  // if head!=nullptr push head to next node
  while(head) {                       // check if head==nullptr;
    head = (*head).next;              // push head to next node
    (*foot).next.reset(nullptr);      // delete old head
  }
  // set size to 0;
  size = 0;

}

// TODO
template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
}

/*template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}*/
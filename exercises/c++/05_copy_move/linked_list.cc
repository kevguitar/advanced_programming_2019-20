enum class Insertion_method { push_back, push_front };

template <class value_type>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method should be used to fill the list
  /* It uses the std::copy semantics. Here, std::move is not suitable. */
  void insert(const value_type& v, const Insertion_method m);

  // && denotes "arg-value reference" What is it??
  /* It is not an lvalue, or an object that is not given a name (i.e. it cannot 
     be assigned to the lhs of an equation). Here, std::move is suitable.
     Example application where argvalue is needed:
     std::vector<Vector<int>> vv;
     vv.push_back(Vector<int(78)); 
     The last expression takes an argument that is not needed after constructing
     the vector. */  
  void insert(value_type&& v, const Insertion_method m);

  // return the size of the list
  std::size_t size() const;

  // delete all the nodes of the list
  void reset();

  // constructor(s) for List
  
  // copy semantics // TODO: like for vector
  // move semantics // TODO: like for vector
  
  // destructor     // TODO: like for vector

 private:
 
  // private struct node with the proper value_type
  struct node {
    value_type value;
    std::unique_ptr<node> next;

    // implement suitable constructor(s) for node
    // TODO!!
    
    // copy and move semantics if needed
    // Could be useful; observe vector class and judge afterwards.
    
    // destructor // Why would it be needed here?
  };

  // append the newly created node at the end of the list
  void push_back(const value_type& v);
  void push_back(value_type&& v);  /* argvalue overload */

  // insert the newly created node in front of the list
  void push_front(const value_type& v);
  void push_front(value_type&& v);  /* argvalue overload */

  std::unique_ptr<node> head;
  std::size_t size;
};

// TODO: Understand hierarchy of member functions (which are fundamental,
// which are secondary? Which are private, which are public?)

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

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
}
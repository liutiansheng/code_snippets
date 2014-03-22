/// @file create own-defined list which support multiple data types
///       just like Python data structures
/// @note actually in c++, can use boost::any to do the same thing
/// @author Chinson Liu

#include <iostream>

using namespace std;

class List;

class NodeBase {
  friend class List;
  friend ostream& operator<<(ostream &out, const List &list);
public:
  NodeBase() : next(NULL) {}
  virtual ~NodeBase() {}

  virtual void operator<<(ostream &out) = 0;

private:
  NodeBase *next; 
};

///
///template class to create Node type based on data type
///
template<typename DataType>
class Node: public NodeBase {
  friend class List;
public:
  Node(const DataType &idata): data(idata){}

  virtual void operator<<(ostream &out)
  {
    out<<data;
  }

private:
  DataType data;
};

class List
{
  friend ostream& operator<<(ostream &out, const List &list);
public:
  List()
  {
    head = tail = NULL;
  }
  ~List()
  {
    for (; head;) {
      NodeBase *next = head->next;
      delete head;
      head = next;
    }
    tail = NULL;
  }

  ///
  ///template function to add a new node
  ///based on the input data type, to determine
  ///the node type
  ///
  template <typename DataType>
  void add(const DataType &data)
  {
    NodeBase *node = new Node<DataType>(data);
    if (!tail) {
      head = node;
    }
    else {
      tail->next = node;
    }
    tail = node;
  }

private:
  NodeBase *head, *tail;
};

///
///test to output all datas in the input @a list 
///
ostream& operator<<(ostream &out, const List &list)
{
  for (NodeBase *node = list.head; node; node = node->next)
  {
    node->operator<<(out);
    out<<' ';
  }
  return out;
}

///
///test a list support multiple data types just like Python
///
int main()
{

  List *list = new List;

  list->add(1);
  list->add(2.5);
  list->add(string("hello world"));

  cout<<*list<<endl;
  
  delete list; list = NULL;
  return 0;
}

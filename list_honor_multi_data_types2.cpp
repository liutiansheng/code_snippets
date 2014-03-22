/// @file create own-defined list which support multiple data types
///       just like Python data structures
/// @note actually in c++, can use boost::any to do the same thing
/// @author Chinson Liu

#include <iostream>

using namespace std;

class List;

class DataBase {
public:
  virtual ~DataBase() {}

  virtual void operator<<(ostream &out) = 0;
};

template <typename InnerType>
class Data : public DataBase {
public:
  Data(const InnerType &idata) : innerData(idata)  {}

  virtual void operator<<(ostream &out)
  {
    out<<innerData;
  }
private:
    InnerType innerData;
};

///
///template class to create Node type based on data type
///
class Node {
  friend class List;
  friend ostream& operator<<(ostream &out, const List &list);
public:
  template <typename InnerType>
  Node(const InnerType &idata)
    : data(new Data<InnerType>(idata)), next(NULL) {}
  ~Node()
  {
    delete data; data = NULL;
  }

private:
  DataBase *data;
  Node     *next;
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
      Node *next = head->next;
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
  template <typename InnerType>
  void add(const InnerType &data)
  {
    Node *node = new Node(data);
    if (!tail) {
      head = node;
    }
    else {
      tail->next = node;
    }
    tail = node;
  }

private:
  Node *head, *tail;
};

///
///test to output all datas in the input @a list 
///
ostream& operator<<(ostream &out, const List &list)
{
  for (Node *node = list.head; node; node = node->next)
  {
    if (node->data) {
      node->data->operator<<(out);
      out<<' ';
    }
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

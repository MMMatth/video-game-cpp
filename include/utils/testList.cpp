#include "list.hpp"

int main(int argc, char const *argv[]) {
  LinkedList<int> list = LinkedList<int>();
  list.addLink(1);
  list.addLink(2);
  list.addLink(2);
  list.addLink(3);
  list.removeLink(2);

  cout << list.toString() << endl;
  return 0;
}
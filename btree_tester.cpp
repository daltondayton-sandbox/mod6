#include "btree.h"
#include <iostream>
bool checkTest(std::string testName, int whatItShouldBe, int whatItIs);
BTree<int> populateTree();
int main() {
  BTree<int> myTree = populateTree();
  myTree.preOrder();
  std::cout << std::endl << std::endl;
  myTree.postOrder();
  std::cout << std::endl << std::endl;
  myTree.inOrder();
  std::cout << std::endl << std::endl;
  checkTest("Test #1, number of nodes", 35, myTree.nodeCount());
  return 0;
}
BTree<int> populateTree() {
  BTree<int> myTree;
  int values[] = {37, 32, 73, 95, 42, 12, 0,  49, 98, 7,  27, 17,
                  47, 87, 77, 97, 67, 85, 15, 5,  35, 55, 65, 75,
                  25, 45, 3,  93, 83, 53, 63, 23, 13, 43, 33};
  int size = (sizeof(values) / sizeof(*values));
  for (int i = 0; i < size; i++) {
    myTree.insert(values[i]);
  }
  return myTree;
}
// Helps with Testing
bool checkTest(std::string testName, int whatItShouldBe, int whatItIs) {
  if (whatItShouldBe == whatItIs) {
    std::cout << "Passed " << testName << std::endl;
    return true;
  } else {
    std::cout << "***Failed test " << testName << " *** " << std::endl
              << " Output was " << whatItIs << std::endl
              << " Output should have been " << whatItShouldBe << std::endl;
    return false;
  }
}

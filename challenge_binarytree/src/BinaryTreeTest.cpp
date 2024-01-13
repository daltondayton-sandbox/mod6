#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <memory>
#include "BinaryTree.hpp"

using std::cout;
using std::endl;
using std::string;
using std::stoi;
using std::ostringstream;

bool checkTest(string testName, bool condition);
bool checkTest(string testName, int whatItShouldBe, int whatItIs);
bool checkString(string testName, const char* whatItIs, const char* whatItShouldBe);
bool testFindMethod();
bool testOutput();
bool testRightMostNodeSearch();
bool deleteTest();
bool testHeight();
bool testLeavesCount();

void populateTree(BinaryTree<int>& testTree);

int main(int argc, char** argv){

   int test = 0;
   int count = 0;

   if(argc > 1){
      test = stoi(argv[1]);
   }
   switch(test){
      case 0:
         if (testFindMethod()) count++;
         if (testOutput()) count++;
         if (testRightMostNodeSearch()) count++;
         if (deleteTest()) count++;
         if (testHeight()) count++;
         if (testLeavesCount()) count++;
         cout << "Passed " << count << " out of 6 tests";
         return count != 6;
      case 1:
         return !testFindMethod();
      case 2:
         return !testOutput();
      case 3:
         return !testRightMostNodeSearch();
      case 4:
         return !deleteTest();
      case 5:
         return !testHeight();
      case 6:
         return !testLeavesCount();
   }

}

void populateTree(BinaryTree<int>& testTree){

  int values[] = {37, 32, 73, 95, 42, 12, 0, 49, 98, 7, 27, 17, 47, 87, 77, 97, 67, 85, 15, 5, 35, 55, 65, 75, 25, 45, 3, 93, 83, 53, 63, 23, 13, 43, 33};
  int size = (sizeof(values)/sizeof(*values));

  for(int i = 0; i < size; i++){
      testTree.insert(values[i]);
  }

}

bool testFindMethod(){
    bool passed = true;
    BinaryTree<int> myTree;
    populateTree(myTree);

    auto ptr = myTree.find(49);
    passed &= checkTest("Test Find(49)", 49, ptr->item);
    ptr = myTree.find(5);
    passed &= checkTest("Test Find(5)", 5, ptr->item);
    ptr = myTree.find(95);
    passed &= checkTest("Test Find(95)", 95, ptr->item);
    ptr = myTree.find(37);
    passed &= checkTest("Test Find(37)", 37, ptr->item);
    ptr = myTree.find(200);
    passed &= checkTest("Test Find(200)", ptr == nullptr);
    return passed;
}

bool testOutput(){
  bool passed = true;
  BinaryTree<int> myTree;
  populateTree(myTree);
  ostringstream output;
  myTree.inOrder(output);
  passed &= checkString("Test Output 1", output.str().c_str(), "0 3 5 7 12 13 15 17 23 25 27 32 33 35 37 42 43 45 47 49 53 55 63 65 67 73 75 77 83 85 87 93 95 97 98");
  output.str("");
  output.clear();
  BinaryTree<int> simpleTree;
  simpleTree.insert(8);
  simpleTree.inOrder(output);
  passed &= checkString("Test Output 2", output.str().c_str(), "8");
  output.str("");
  output.clear();
  simpleTree.insert(12);
  simpleTree.inOrder(output);
  passed &= checkString("Test Output 3", output.str().c_str(), "8 12");
  output.str("");
  output.clear();
  simpleTree.insert(7);
  simpleTree.inOrder(output);
  passed &= checkString("Test Output 4", output.str().c_str(), "7 8 12");
  output.str("");
  output.clear();
  return passed;
}

bool testRightMostNodeSearch(){
    bool passed = true;
    BinaryTree<int> myTree;
    populateTree(myTree);
    auto ptr = myTree.find(49);
    auto ptrchild = myTree.findRightMostNode(ptr);
    passed &= checkTest("Test RightNodeTest(49)", 67, ptrchild->item);
    return passed;
}

bool deleteTest(){
  bool passed = true;
  BinaryTree<int> myTree;
  populateTree(myTree);
  myTree.remove(33);
  auto ptr = myTree.find(33);
  passed &= checkTest("Test Delete Leaf: 33", ptr == nullptr);
  ostringstream output;
  myTree.inOrder(output);
  passed &= checkString("Test Output After Delete: 33", output.str().c_str(), "0 3 5 7 12 13 15 17 23 25 27 32 35 37 42 43 45 47 49 53 55 63 65 67 73 75 77 83 85 87 93 95 97 98");
  output.str("");
  output.clear();

  myTree.remove(67);
  ptr = myTree.find(67);
  passed &= checkTest("Test Delete Node with Left Child: 67", ptr == nullptr);
  myTree.inOrder(output);
  passed &= checkString("Test Output After Delete: 67", output.str().c_str(), "0 3 5 7 12 13 15 17 23 25 27 32 35 37 42 43 45 47 49 53 55 63 65 73 75 77 83 85 87 93 95 97 98");
  output.str("");
  output.clear();

  myTree.remove(42);
  ptr = myTree.find(42);
  passed &= checkTest("Test Delete Node with Right Child: 42", ptr == nullptr);
  myTree.inOrder(output);
  passed &= checkString("Test Output After Delete: 42", output.str().c_str(), "0 3 5 7 12 13 15 17 23 25 27 32 35 37 43 45 47 49 53 55 63 65 73 75 77 83 85 87 93 95 97 98");
  output.str("");
  output.clear();

  myTree.remove(73);
  ptr = myTree.find(73);
  passed &= checkTest("Test Delete Node with two children: 73", ptr == nullptr);
  myTree.inOrder(output);
  passed &= checkString("Test Output After Delete: 73", output.str().c_str(), "0 3 5 7 12 13 15 17 23 25 27 32 35 37 43 45 47 49 53 55 63 65 75 77 83 85 87 93 95 97 98");
  output.str("");
  output.clear();

  myTree.remove(37);
  ptr = myTree.find(37);
  passed &= checkTest("Test Delete root: 37", ptr == nullptr);
  myTree.inOrder(output);
  passed &= checkString("Test Output After Delete: 37", output.str().c_str(), "0 3 5 7 12 13 15 17 23 25 27 32 35 43 45 47 49 53 55 63 65 75 77 83 85 87 93 95 97 98");
  output.str("");
  output.clear();

  return passed;
}

bool testHeight(){
  BinaryTree<int> myTree;
  populateTree(myTree);
  return checkTest("Test height()", 7, myTree.height());
}

bool testLeavesCount(){
    BinaryTree<int> myTree;
    populateTree(myTree);
    return checkTest("Test leavesCount()", 11, myTree.leavesCount());
}

//Helps with Testing
bool checkString(string testName, const char* whatItIs, const char* whatItShouldBe){

  if(whatItIs && whatItShouldBe && strcmp(whatItIs, whatItShouldBe) == 0){
    cout << "Passed Test " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    return false;
  }
}
//Helps with Testing
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    return false;
  }
}
//Helps with Testing
 bool checkTest(string testName, bool condition) {

  if (condition) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl;
    return false;
  }

}

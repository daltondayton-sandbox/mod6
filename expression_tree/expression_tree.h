#pragma once

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

struct Node {
  std::string data{""};
  Node *left{nullptr};
  Node *right{nullptr};
};

class ExpressionTree {
public:
  // default constructor creates an empty expression tree
  ExpressionTree();

  // Creates an expression tree from the given string expression
  ExpressionTree(std::string expr);

  // copy constructor
  ExpressionTree(const ExpressionTree &other);

  // destructor deallocates all nodes in the tree void
  ~ExpressionTree();

  // Clears the expression tree, stores the given expression in a new tree int
  void setExpression(std::string expr);

  // return the results of evaluating the expression tree void
  int getResult();

  // outputs the tree to the ostream &using an in - order traversal
  void printParseTreeInOrder(std::ostream &os);

  // outputs the tree to the ostream &using post - order traversal
  void printParseTreePostOrder(std::ostream &os);

protected:
  Node *root;

private:
  void setExpressionHelper(std::string &expr, int &position, Node *curr);
  void printParseTreeInOrderHelper(std::ostream &os, Node *curr);
  void printParseTreePostOrderHelper(std::ostream &os, Node *curr,
                                     bool &isFirst);
  int getResultHelper(Node *curr);
  void clearTree(Node *curr);
  Node *copyNodes(const Node *originalNode);
};

ExpressionTree::ExpressionTree() {
  //
  root = nullptr;
}

ExpressionTree::ExpressionTree(std::string expr) {
  //
  setExpression(expr);
}

ExpressionTree::ExpressionTree(const ExpressionTree &other) {
  //
  root = copyNodes(other.root);
}

Node *ExpressionTree::copyNodes(const Node *originalNode) {
  if (originalNode == nullptr) {
    return nullptr;
  }
  Node *newNode = new Node();
  newNode->data = originalNode->data;
  newNode->left = copyNodes(originalNode->left);
  newNode->right = copyNodes(originalNode->right);
  return newNode;
}

ExpressionTree::~ExpressionTree() {
  //
  clearTree(root);
}

void ExpressionTree::clearTree(Node *curr) {
  if (curr == nullptr) {
    return;
  }
  clearTree(curr->left);
  clearTree(curr->right);
  delete curr;
}

void ExpressionTree::setExpression(std::string expr) {
  clearTree(root);
  root = nullptr;
  int position = 0;
  root = new Node();
  setExpressionHelper(expr, position, root);
}

void ExpressionTree::setExpressionHelper(std::string &expr, int &position,
                                         Node *curr) {
  if (root == nullptr)
    root = new Node();
  if (position >= expr.length())
    return;
  if (expr[position] == '(') {
    curr->left = new Node();
    setExpressionHelper(expr, ++position, curr->left);
  }
  if (isdigit(expr[position])) {
    std::string num = "";
    while (isdigit(expr[position])) {
      num += expr[position];
      ++position;
    }
    curr->data = num;
    return;
  }
  if (expr[position] == '+' || expr[position] == '-' || expr[position] == '*' ||
      expr[position] == '/' || expr[position] == '^') {
    curr->data = expr[position];
    curr->right = new Node();
    setExpressionHelper(expr, ++position, curr->right);
  }
  if (expr[position] == ')') {
    ++position;
    return;
  }
}

int ExpressionTree::getResult() {
  //
  return getResultHelper(root);
}

int ExpressionTree::getResultHelper(Node *curr) {
  if (curr == nullptr) {
    return 0;
  }
  if (isdigit(curr->data[0])) {
    return std::stoi(curr->data);
  }
  int left = getResultHelper(curr->left);
  int right = getResultHelper(curr->right);
  if (curr->data == "+") {
    return left + right;
  } else if (curr->data == "-") {
    return left - right;
  } else if (curr->data == "*") {
    return left * right;
  } else if (curr->data == "/") {
    return left / right;
  } else if (curr->data == "^") {
    return pow(left, right);
  }
  return 0;
}

void ExpressionTree::printParseTreeInOrder(std::ostream &os) {
  printParseTreeInOrderHelper(os, root);
}

void ExpressionTree::printParseTreeInOrderHelper(std::ostream &os, Node *curr) {
  if (curr == nullptr) {
    return;
  }
  printParseTreeInOrderHelper(os, curr->left);
  os << curr->data;
  printParseTreeInOrderHelper(os, curr->right);
}

void ExpressionTree::printParseTreePostOrder(std::ostream &os) {
  bool isFirst = true;
  printParseTreePostOrderHelper(os, root, isFirst);
}

void ExpressionTree::printParseTreePostOrderHelper(std::ostream &os, Node *curr,
                                                   bool &isFirst) {
  if (curr == nullptr) {
    return;
  }
  printParseTreePostOrderHelper(os, curr->left, isFirst);
  printParseTreePostOrderHelper(os, curr->right, isFirst);
  if (!isFirst) {
    os << " ";
  }
  os << curr->data;
  isFirst = false;
}

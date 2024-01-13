#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>

template <class Type>
struct Node
{
    Type item{};
    Node<Type> *left{nullptr};
    Node<Type> *right{nullptr};
};

template <class Type>
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void insert(Type item);
    void preOrder(std::ostringstream &out);
    void inOrder(std::ostringstream &out);
    void postOrder(std::ostringstream &out);
    int nodeCount();
    Node<Type> *find(Type item);
    Node<Type> *findRightMostNode(Node<Type> *find);
    void remove(Type item);
    int height();
    int leavesCount();

protected:
    Node<Type> *root{nullptr};

private:
    void destroy(Node<Type> *curr);
    void insert(Type item, Node<Type> *curr);
    void preOrder(std::ostringstream &out, Node<Type> *curr);
    void postOrder(std::ostringstream &out, Node<Type> *curr);
    void inOrder(std::ostringstream &out, Node<Type> *curr, bool &firstNode);
    int nodeCount(Node<Type> *curr);
    int leavesCount(Node<Type> *curr);
    Node<Type> *find(Type item, Node<Type> *curr);
    Node<Type> *remove(Type item, Node<Type> *curr);
    int height(int level, Node<Type> *curr);
};

template <class Type>
BinaryTree<Type>::BinaryTree()
{
    root = nullptr;
}

template <class Type>
BinaryTree<Type>::~BinaryTree()
{
    destroy(root);
}

template <class Type>
void BinaryTree<Type>::destroy(Node<Type> *curr)
{
    if (curr != nullptr)
    {
        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }
}

template <class Type>
void BinaryTree<Type>::insert(Type item)
{
    if (root == nullptr)
    {
        root = new Node<Type>;
        root->item = item;
        root->left = nullptr;
        root->right = nullptr;
    }
    else
    {
        insert(item, root);
    }
}

template <class Type>
void BinaryTree<Type>::insert(Type item, Node<Type> *curr)
{
    if (item < curr->item)
    {
        if (curr->left == nullptr)
        {
            curr->left = new Node<Type>;
            curr->left->item = item;
            curr->left->left = nullptr;
            curr->left->right = nullptr;
        }
        else
        {
            insert(item, curr->left);
        }
    }
    else
    {
        if (curr->right == nullptr)
        {
            curr->right = new Node<Type>;
            curr->right->item = item;
            curr->right->left = nullptr;
            curr->right->right = nullptr;
        }
        else
        {
            insert(item, curr->right);
        }
    }
}

template <class Type>
void BinaryTree<Type>::preOrder(std::ostringstream &out)
{
    preOrder(out, root);
}

template <class Type>
void BinaryTree<Type>::preOrder(std::ostringstream &out, Node<Type> *curr)
{
    if (curr)
    {
        out << curr->item << " ";
        preOrder(out, curr->left);
        preOrder(out, curr->right);
    }
}

template <class Type>
void BinaryTree<Type>::inOrder(std::ostringstream &out)
{
    bool firstNode = true;
    inOrder(out, root, firstNode);
}

template <class Type>
void BinaryTree<Type>::inOrder(std::ostringstream &out, Node<Type> *curr, bool &firstNode)
{
    if (curr)
    {
        inOrder(out, curr->left, firstNode);

        if (!firstNode)
            out << " ";
        else
            firstNode = false;

        out << curr->item;

        inOrder(out, curr->right, firstNode);
    }
}

template <class Type>
void BinaryTree<Type>::postOrder(std::ostringstream &out)
{
    postOrder(out, root);
}

template <class Type>
void BinaryTree<Type>::postOrder(std::ostringstream &out, Node<Type> *curr)
{
    if (curr)
    {
        postOrder(out, curr->left);
        postOrder(out, curr->right);
        out << curr->item << " ";
    }
}

template <class Type>
int BinaryTree<Type>::nodeCount()
{
    return nodeCount(root);
}

template <class Type>
int BinaryTree<Type>::nodeCount(Node<Type> *curr)
{
    if (curr)
    {
        return 1 + nodeCount(curr->left) + nodeCount(curr->right);
    }
}

template <class Type>
int BinaryTree<Type>::leavesCount()
{
    return leavesCount(root);
}

template <class Type>
int BinaryTree<Type>::leavesCount(Node<Type> *curr)
{
    if (curr == nullptr)
    {
        return 0;
    }
    else if (curr->left == nullptr && curr->right == nullptr)
    {
        return 1;
    }
    else
    {
        return leavesCount(curr->left) + leavesCount(curr->right);
    }
}

template <class Type>
Node<Type> *BinaryTree<Type>::find(Type item)
{
    return find(item, root);
}

template <class Type>
Node<Type> *BinaryTree<Type>::find(Type item, Node<Type> *curr)
{
    if (curr == nullptr)
    {
        return nullptr;
    }
    else if (curr->item == item)
    {
        return curr;
    }
    else if (item < curr->item)
    {
        return find(item, curr->left);
    }
    else
    {
        return find(item, curr->right);
    }
}

template <class Type>
Node<Type> *BinaryTree<Type>::findRightMostNode(Node<Type> *curr)
{
    if (curr == nullptr)
    {
        return nullptr;
    }

    while (curr != nullptr)
    {
        if (curr->right == nullptr)
        {
            return curr;
        }
        curr = curr->right;
    }

    return nullptr;
}

template <class Type>
void BinaryTree<Type>::remove(Type item)
{
    root = remove(item, root);
}

template <class Type>
Node<Type> *BinaryTree<Type>::remove(Type item, Node<Type> *curr)
{
    // At a leaf
    if (curr == nullptr)
    {
        return nullptr;
    }
    // search left and right
    else if (item < curr->item)
    {
        curr->left = remove(item, curr->left);
    }
    else if (item > curr->item)
    {
        curr->right = remove(item, curr->right);
    }
    // Item found
    else
    {
        // Node has no children
        if (curr->left == nullptr && curr->right == nullptr)
        {
            delete curr;
            curr = nullptr;
        }
        // Left point is null, replace with right branch
        else if (curr->left == nullptr)
        {
            Node<Type> *temp = curr;
            curr = curr->right;
            delete temp;
        }
        // Right point is null, replace with left branch
        else if (curr->right == nullptr)
        {
            Node<Type> *temp = curr;
            curr = curr->left;
            delete temp;
        }
        // Else replace with rightmode node of left branch
        else
        {
            Node<Type> *temp = findRightMostNode(curr->left);
            curr->item = temp->item;
            curr->left = remove(temp->item, curr->left);
        }
    }

    return curr;
}

template <class Type>
int BinaryTree<Type>::height()
{
    return height(-1, root);
}

template <class Type>
int BinaryTree<Type>::height(int level, Node<Type> *curr)
{
    if (curr == nullptr)
    {
        return level;
    }

    int left = height(level + 1, curr->left);
    int right = height(level + 1, curr->right);

    if (left > right)
    {
        return left;
    }
    else
    {
        return right;
    }
}

#endif // BINARY_TREE_HPP

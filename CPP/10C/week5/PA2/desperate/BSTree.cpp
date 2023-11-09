#include "BSTree.h"
#include "iostream"
using namespace std;

BSTree::BSTree() { root = nullptr; }
BSTree::~BSTree() { delete root; }

// void BSTree::remove(const string &key){              //used the remove
// function given on Zybooks.
//     Node* par = nullptr;
//     Node* cur = root;
//     while(cur != nullptr){
//         if(cur->getData() == key){      //to check if cur is the correct node
//             if(cur->getCount() > 1){
//                 cur->setCount((cur->getCount()-1));
//                 return;
//             }
//             if(cur->getLeft() == nullptr && cur->getRight() == nullptr){
//             //removing leaf node
//                 if (par == nullptr) { // Node is root
//                     root = nullptr;
//                 }else if (par->getLeft() == cur){
//                     par->setLeft(nullptr);
//                 }else {
//                     par->setRight(nullptr);
//                 }
//             } else if(cur->getRight() == nullptr){
//                 if(par == nullptr){
//                     root = cur->getLeft();
//                 } else if (par->getLeft() == cur){
//                     par->setLeft(cur->getLeft());
//                 } else {
//                     par->setRight(cur->getLeft());
//                 }
//             } else if(cur->getLeft() == nullptr){
//                 if(par == nullptr){
//                     root = cur->getRight();
//                 } else if(par->getLeft() == cur){
//                     par->setLeft(cur->getRight());
//                 } else {
//                     par->setRight(cur->getRight());
//                 }
//             } else{                                 //Remove node with two
//             children
//                 Node* suc = cur->getRight();
//                 while(suc->getLeft() != nullptr){
//                     suc = suc->getLeft();
//                 }
//                 string successorData = suc->getData();
//                 remove(successorData);
//                 cur->setData(successorData);
//             }
//             return;                                //node found and removed.
//         } else if(cur->getData() < key) {
//             par = cur;
//             cur = cur->getRight();
//         } else {
//             par = cur;
//             cur = cur->getLeft();
//         }
//     }
// }

bool BSTree::search(const string &node) const {
  Node *n = root;
  while (n != nullptr && !(n->getData() == node)) {
    if (n->getData() < node) {
      n = n->getRight();
    } else if (n->getData() > node) {
      n = n->getLeft();
    }
  }
  if (n != nullptr)
    return true;
  else
    return false;
}

string BSTree::smallest() const {
  Node *n = root;

  if (n != nullptr) {
    while (n->getLeft() != nullptr) { // furthest left is the smallest value
      n = n->getLeft();
    }
    return n->getData();
  } else
    return ""; // return empty string if empty
}

string BSTree::largest() const {
  Node *n = root;

  if (n != nullptr) {
    while (n->getRight() != nullptr) { // furthest right is the largest value
      n = n->getRight();
    }
    return n->getData();
  } else
    return ""; // return empty string if empty
}

void BSTree::preOrder() const { preOrder(root); }

void BSTree::preOrder(Node *n) const {
  if (n != nullptr) {
    cout << n->getData() << "(" << n->getCount() << "), ";
    preOrder(n->getLeft());
    preOrder(n->getRight());
  }
}

void BSTree::postOrder() const { postOrder(root); }

void BSTree::postOrder(Node *n) const {
  if (n != nullptr) {
    postOrder(n->getLeft());
    postOrder(n->getRight());
    cout << n->getData() << "(" << n->getCount() << "), ";
  }
}

void BSTree::inOrder() const { inOrder(root); }

void BSTree::inOrder(Node *n) const {
  if (n != nullptr) {
    inOrder(n->getLeft());
    cout << n->getData() << "(" << n->getCount() << "), ";
    inOrder(n->getRight());
  }
}

int BSTree::height(const string &data) const {
  if (!search(data)) {
    return -1;
  }
  Node *curr = root;
  while (curr != nullptr && !(curr->getData() == data)) {
    if (curr->getData() < data) {
      curr = curr->getRight();
    } else if (curr->getData() > data) {
      curr = curr->getLeft();
    }
  }

  Node *currLeft = curr;
  Node *currRight = curr;
  int leftCnt = 0;
  int rightCnt = 0;

  if (curr->getLeft() != nullptr) {
    currLeft = currLeft->getLeft();
    leftCnt++;
    leftCnt = leftCnt + height(currLeft->getData());
  }
  if (curr->getRight() != nullptr) {
    currRight = currRight->getRight();
    rightCnt++;
    rightCnt = rightCnt + height(currRight->getData());
  }
  if (leftCnt >= rightCnt) {
    return leftCnt;
  } else {
    return rightCnt;
  }
}

void BSTree::insert(const string &newString) {
  Node *insertNode = new Node(newString);
  if (root == nullptr) {
    root = insertNode;
    root->setLeft(nullptr);
    root->setRight(nullptr);
  } else {
    Node *curr = root;

    while (curr != nullptr) {
      if (insertNode->getData() == curr->getData()) {
        curr->setCount(curr->getCount() + 1);
        return;
      }

      if (insertNode->getData() < curr->getData()) { // going to be left of head
        if (!curr->getLeft()) {
          curr->setLeft(insertNode);
          break;
        } else {
          curr = curr->getLeft();
        }
      } else {
        if (insertNode->getData() > curr->getData()) { // right of head
          if (!curr->getRight()) { // if empty space for insertion
            curr->setRight(insertNode);
            break;
          } else {
            curr = curr->getRight(); // move over to the right
          }
        }
      }
    }
  }
}

void BSTree::remove(const string &data) {

  if (root == nullptr) {
    return;
  } else if ((!root->getRight() && !root->getLeft()) &&
             (root->getData() == data)) {
    delete root;
    root = nullptr;
    return;
  }
  remove(root, root, data);
}

void BSTree::remove(Node *prev, Node *curr, string data) { // recursive helper

  if (curr == nullptr) { // empty tree
    return;
  } else if (curr->getData() == data) { // found node we want to remove
    if (curr->getCount() > 1 && curr->getData() != prev->getData()) {
      curr->setCount(curr->getCount() -
                     1); // removing element that's count is >1
      return;
    }
    if (curr == root &&
        curr->getCount() > 1) { // if node that's found is root and has count >1
      curr->setCount(curr->getCount() - 1);
      return;
    } else if (!curr->getRight() &&
               !curr->getLeft()) { // if node to be removed was a leaf

      if (curr->getData() > prev->getData()) { // if it was on the right of prev
        prev->setRight(nullptr);
        delete curr;
        return;
      } else if (curr->getData() < prev->getData()) { // if on left of prev
        prev->setLeft(nullptr);
        delete curr;
        return;
      } else if (curr->getData() == prev->getData()) { // if equal to prev
        if (prev->getRight() == nullptr) { // if right is already nptr
          prev->setLeft(nullptr);          // delete left
          delete curr;
        } else if (prev->getLeft() == nullptr) { // vice versa ^
          prev->setRight(nullptr);
          delete curr;
        } else if (prev->getRight() &&
                   prev->getLeft()) { // if both right and left aren't null
          if (curr->getData() ==
              prev->getLeft()->getData()) { // if equal to left
            prev->setLeft(nullptr);
            delete curr;
          } else if (curr->getData() ==
                     prev->getRight()->getData()) { // vice versa
            prev->setRight(nullptr);
            delete curr;
          }
        }
      }
    } else if ((curr->getLeft() != nullptr && curr->getRight() != nullptr) ||
               (curr->getLeft() != nullptr &&
                curr->getRight() == nullptr)) { // if not a leaf node
      Node *temp = max(
          curr->getLeft()); // calls max to find largest from that point forward
      curr->setData(temp->getData());
      curr->setCount(temp->getCount());
      remove(curr, curr->getLeft(), curr->getData());
    } else if (!curr->getLeft() &&
               curr->getRight()) { // if left u want to find min
      Node *temp = min(curr->getRight());
      curr->setData(temp->getData());
      curr->setCount(temp->getCount());
      remove(curr, curr->getRight(), curr->getData());
    }
  } else if (curr->getData() < data) { // if node is less than root
    remove(curr, curr->getRight(), data);
  } else if (curr->getData() > data) { // greater than root
    remove(curr, curr->getLeft(), data);
  }
}
Node *BSTree::min(Node *curr) const { // smallest within the subtree
  Node *temp = curr;

  while (curr != nullptr) {
    temp = curr;
    curr = curr->getLeft();
  }

  return temp;
}

Node *BSTree::max(Node *curr) const { // largest within subtree
  Node *temp = curr;

  while (curr != nullptr) {
    temp = curr;
    curr = curr->getRight();
  }
  return temp;
}

#include <iostream>
#include<bits/stdc++.h>

using namespace std;

// Red Black tree->type of self balancing Binary Search trees
// O(log(n)) ->insert, delete, search

//properities
//(1) Root -> always black
//(2)Red nodes can't have Red Childrens
//(3)every path from a node to
// null node must have the same number of black nodes
//(4) All Leaves (NIL nodes) are black

//💡Ensuring that
//The longest path is at most twice the shortest path

// Why Red-Black tree
//Over BST
//BST operations (e.g., search, max, min, insert, delete.. etc) take O(h)
// where h is the height of the BST.
// The cost of these operations
// may become O(n) for a skewed Binary tree.
// If we make sure that the height of the tree
// remains O(log n)
// after every insertion and deletion,
// guarantee upper bound of O(log n) for all operations.

//Over AVL
//The AVL trees are more balanced compared to
// Red-Black Trees, but they may cause more
// rotations during insertion and deletion.
// So if your application involves frequent
// insertions and deletions,
// then Red-Black trees should be preferred.
// And if the insertions and deletions are less
// frequent and search is a more frequent operation,
// then AVL tree should be preferred over the Red-Black Tree


// INSERTION
//(1)performing a standard binary search tree (BST) insertion
//(2)fixing any violations of Red-Black properties.
//a- If the parent of the new node is black, no properties are violated.
//b-If the parent is red, the tree might violate the Red Property, requiring fixes.
struct Node{
    int data;
    string color ;
    Node *l , *r, *p;
    Node(int data){
      this->data=data;
      this->color ="r";
      l = r = p = nullptr;
    }
};

class RedBlackTree{
    Node *root;
    //Left Rotate
    //function take a pointer to the node around
    //which the left rotation will occur
    void leftRotation(Node *x){
      //handle Two Cases
      //1 - if x is null there is nothing to rotate
      //2 - x must have a right child to make the left rotation
      if (x==nullptr|| x->r==nullptr) return;
      //Define y as the right child of x
      Node *y = x->r;
      // make y's left subtree to be
      //x's right subtree
      x->r = y->l;
      //if y's left subtree is not null
      //set y's left child's parent to x
      if (y->l != nullptr){
        y->l->p = x;
      }
      //set y's paret to x's paret
      y->p = x->p;
      //if x's parent is null
      // make y is the root of the tree
      if (x->p ==nullptr){
        root = y;
      }
      else if (x == x->p->l){
        x->p->l = y;
      }
      else{
        x->p->r = y;
      }
      //make y->r to point to x
      y->l = x;
      //make x's parent to y
      x->p = y;
    }
    //Right Rotate
    void rightRotation(Node *y){
      if (y == nullptr || y->l==nullptr) return;
      Node *x =y->l;
      //make x's right subtree to be y's left subtree
      y->l = x->r;
      // if x->r is not null
      if (x->r != nullptr){
        x->r->p = y;
      }
      //set x's parent to y's parent
      x->p = y->p;
      //if y's parent is null(y is root)
      if (y->p ==nullptr){
        root = x;
      }
        // if y is the right child of its parent
        //make x to be the right child of y's parent
      else if (y->p->r ==y){
        y->p->r =x;
      }
      else {
        y->p->l=x;
      }
      //make y to be the right child of x
      x->r= y;
      y->p =x;
    }
public:
    //Fix Insertion
    void FixRBT_insert(Node *z){
      //z is the new_n
      //y is the uncle
      //case1:
      //z->p is black then no violations
      //case2:
      //z->p is red check the uncle
      //[1] if uncle is red
      //steps:
      //a-reclor z->p and y to balck
      //b-recolor z->p->p to red
      //c-continue the loop with z->p->p
      //[2] if uncle is black or null
      // case of the triangle(Zigzag shape)
      //steps:
      //if z is the right child of z->p and z->p is the left child of z->p->p
      //or if z is the left child of z->p and z->p is the right child of z->p->p
      // rotate the tree around z->p to the opposite direction
      // to make the triangle to be a straight line
      //case of the line
      //steps:
      //if z is a left child of a left parent or
      // z is a right child of a right parent
      // recolor z->p and z->p->p
      // rotate the tree around z->p->p
      // to the opposite direction
      while(z !=root && z->p&&z->p->p&& z->p->color=="r"){
        //if parent is a left child
        //then the uncle is the right child
        if (z->p==z->p->p->l){
          Node *y = z->p->p->r;
          //case2.1
          if (y !=nullptr && y->color=="r"){
            z->p->color="b";
            y->color="b";
            z->p->p->color="r";
            z= z->p->p;//move z to the grandparent
            //why? because the grandparent may violate the RBT properties
          }else{
            //case2.2
            //triangle shape
            if (z == z->p->r){
              z = z->p;
              leftRotation(z);//maka it line
            }
            z->p->color ="b";
            z->p->p->color ="r";
            rightRotation(z->p->p);
          }
        }else{
          Node *y = z->p->p->l;
          if (y!= nullptr && y->color=="r"){
            z->p->color="b";
            y->color="b";
            z->p->p->color="r";
            z=z->p->p;
          }else{
            if(z == z->p->l){
              z = z->p;
              rightRotation(z);
            }
            z->p->color="b";
            z->p->p->color="r";
            leftRotation(z->p->p);
          }

        }
      }
      //ensure the root color is black
      root->color = "b";
    }
    //Insert
    void  insert(int val){
      Node* new_n = new Node(val);
      // make pointer to track the parent
      Node *y = nullptr;
      //start from root
      Node *x =root;
      //traverse the tree to find the correct position
      while(x!=nullptr){
        y=x;
        if (new_n->data<x->data){
          x =x->l;
        }
        else {
          x =x->r;
        }
      }
      //set the parent of the new node
      new_n->p = y;
      //if the tree is empty
      // y is nullptr
      if (y ==nullptr){
        root =new_n;
      }else if (new_n->data>y->data){
        y->r =new_n;
      }else {
        y->l =new_n;
      }
      // fix any violations of RBT properties
      FixRBT_insert(new_n);
    }
    //Deletion
    //steps
    //search for the node
    //Replace it
    //cases
    //[1] No children: It is simply removed.
    //[2] one child: replace it with its child
    //[3] two childrens Replace it with in-order successor
    //(smallest node in the right subtree)
    // or predecessor , then delete that successor
    //then fix any violation

    //Replace
    //replace to replace one pNode with another
    //replace a pNode with its in-order successor.
    void replace(Node *old, Node *New){
//      old: The Node to be replaced.
//      New: The Node that will replace old
      if (old->p == nullptr){
        root = New;//if old is the root
        //make New the new root
      }else if (old == old->p->l){
        old->p->l =New;
      }else{
        old->p->r =New;
      }
      if (New != nullptr){
        New->p=old->p;
      }
    }
    //Smallest
    //function to find in-order successor
    //the smallest node in its right subtree
    Node *right_smallest(Node *x){
      while (x->l!=nullptr){
        x=x->l;//keep moving to the left
        //until we reach the smallest node
      }
      return x;
    }

    void remove(int val) {
      Node *z = root;
      //traverse to find the node
      while (z != nullptr) {
        if (val > z->data) {
          z = z->r;
        } else if (val < z->data) {
          z = z->l;
        } else {
          Delete(z);
          return;
        }
      }
      cout << "Node with value " << val << " not found" << endl;
    }
    //the logic of deletion
    void Delete(Node *z){
      if (z==nullptr){
        return;
      }
      Node *y = z; //pointer to the node to be deleted
      Node *x = nullptr; //the node that will replace it
      string y_original_color =y->color;
      //case1: one child
      if (z->l == nullptr){
        x = z->r;
        replace(z,z->r);
      }else if (z->r == nullptr){
        x = z->l;
        replace(z,z->l);
      }
        //case2:two children
      else{
        y = right_smallest(z->r);
        y_original_color = y->color;
        x = y->r;

        if (y->p == z) {
          if (x != nullptr)
            x->p = y; // Check if x is not nullptr before assigning parent
        } else {
          if (x != nullptr)
            x->p = y->p; // Check if x and y->parent are not nullptr before assigning parent
          replace(y, y->r);
          if (y->r != nullptr)
            y->r->p = y; // Check if y->right is not nullptr before assigning parent
          y->r = z->r;
          if (y->r != nullptr)
            y->r->p = y; // Check if y->right is not nullptr before assigning parent
        }
        replace(z, y);
        y->l = z->l;
        if (y->l!= nullptr)
          y->l->p = y; // Check if y->left is not nullptr before assigning parent
        y->color = z->color;
      }

      if (y_original_color == "b" && x != nullptr) // Check if x is not nullptr
        FixRBT_delete(x);

      delete z;
      }

    //Fix the RBT properties after deletion
    //The deletion of a black node may cause a violation of the RBT properties.
    void FixRBT_delete(Node *x){
      //x is the double-black node.
      //w (sibling of x).
      while (x!=root && x!=nullptr && x->color=="b"){
        if (x==x->p->l){
          Node *w = x->p->r;
          //case1: Sibling is red
          if (w->color =="r"){
            //Recolor w (black) and x->parent (red).
            //Perform a left rotation on x->parent.
            //Update w to x->parent->right after the rotation.
            //the rotation is in the direction of x
            w->color="b";
            x->p->color="r";
            //rotate the tree around x->p
            //to the direction of x
            leftRotation(x->p);
            //update w after rotation
            w = x->p->r;
          }
          //case2: Sibling and its children are black
          if ((w->l ==nullptr||w->l->color =="b") && (w->r ==nullptr||w->r->color=="b")){
            w->color="r";//recolor the sibling
            x = x->p;//Move the double black up to the parent
          }
            //case3:Sibling’s Right Child Is Black, Left Child Is Red
          else{
//            w (sibling) is black.
//            w->right (sibling's right child) is black or nullptr.
//            w->left (sibling's left child) is red.
            //Recolor the sibling's left child to black and the sibling (w) to red.
            //Perform a right rotation on the sibling (w).
            //Update w to be the new sibling of x.
            if (w->r==nullptr || w->r->color=="b"){
              if (w->l !=nullptr){
                w->l->color = "b";
              }
              w->color ="r";
              rightRotation(w);
              //why right rotation?
              //away from the double black node

              w = x->p->r; //update w after rotation
            }
            //case4:Sibling’s Right Child Is Red
            //Recolor w to match x->parent.
            //Recolor x->parent and w->right to black.
            //Perform a left rotation on x->parent.
            //the direction of the rotation is x
            //Set x = root to end the loop.
            w->color=x->p->color;
            x->p->color="b";
            if (w->r !=nullptr){
              w->r->color="b";
            }
            leftRotation(x->p);
            x = root; //end the loop
          }
        }else{
          Node *w = x->p->l;
          if (w->color == "r") {
            w->color = "b";
            x->p->color = "r";
            rightRotation(x->p);
            w = x->p->l;
          }
          if ((w->r == nullptr || w->r->color =="b") &&
              (w->l == nullptr || w->l->color == "b")) {
            w->color = "r";
            x = x->p;
          }
          else {
            if (w->l == nullptr || w->l->color == "b") {
              if (w->r!= nullptr)
                w->r->color = "b";
              w->color = "r";
              leftRotation(w);
              w = x->p->l;
            }
            w->color = x->p->color;
            x->p->color = "b";
            if (w->l != nullptr)
              w->l->color = "b";
            rightRotation(x->p);
            x = root;
          }

        }
      }
      if (x != nullptr)
        x->color = "b";
      //The double black node is now at the root.
      //Set it to be black to satisfy the RBT properties.

    }
    void printHelper(Node* root, string indent, bool last){
      //bool last: Indicates whether the current node is the last child
      if (root != nullptr) {
        cout << indent;
        if (last) {
          cout << "R----";
          indent += "   ";
          //If last is true, the node is a right
          // child, and the output starts with
          // "R----". The indent is updated with
          // " " to create space for further levels.
        }
        else {
          //If last is false,
          // the node is a left child,
          // and the output starts with "L----".
          // The indent is updated with "| " to
          // indicate there’s a connection
          // to another sibling.
          cout << "L----";
          indent += "|  ";
        }
        string Color= (root->color == "r") ? "RED" : "BLACK";
        cout << root->data << "(" << Color << ")"<< endl;
        printHelper(root->l, indent, false);
        printHelper(root->r, indent, true);
      }
    }
    void printTree()
    {
      if (root == nullptr)
        cout << "Tree is empty." << endl;
      else {
        cout << "Red-Black Tree:" << endl;
        printHelper(root, "", true);
      }
    }
};
int main() {
// Inserting values into Red-Black Tree
  RedBlackTree rbtree;
  rbtree.insert(7);
  rbtree.insert(3);
  rbtree.insert(18);
  rbtree.insert(10);
  rbtree.insert(22);
  rbtree.insert(8);
  rbtree.insert(11);
  rbtree.insert(26);
  rbtree.insert(2);
  rbtree.insert(6);

  // Printing Red-Black Tree
  rbtree.printTree();

  // Deleting nodes from Red-Black Tree
  cout << "After deleting 18:" << endl;
  rbtree.remove(18);
  rbtree.printTree();

  cout << "After deleting 11:" << endl;
  rbtree.remove(11);
  rbtree.printTree();

  cout << "After deleting 3:" << endl;
  rbtree.remove(3);
  rbtree.printTree();



}

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
   int value, height;
   Node* left, * right;
   Node(int value) : value(value), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* root) {
   if (root == nullptr) {
      return 0;
   }
   return root->height;
}

void updateHeight(Node* root) {
   if (root != nullptr) {
      root->height = max(height(root->left), height(root->right)) + 1;
   }
}

int getBalance(Node* root) {
   if (root == nullptr) {
      return 0;
   }

   return height(root->left) - height(root->right);
}

Node* minValueNode(Node* root) {
   Node* current = root;
   while (current->left) {
      current = current->left;
   }
   return current;
}

Node* rightRotate(Node* root) {
   Node* newRoot = root->left;
   Node* toMove = newRoot->right;

   newRoot->right = root;
   root->left = toMove;

   updateHeight(root);
   updateHeight(newRoot);

   return newRoot;
}

Node* leftRotate(Node* root) {
   Node* newRoot = root->right;
   Node* toMove = newRoot->left;

   newRoot->left = root;
   root->right = toMove;

   updateHeight(root);
   updateHeight(newRoot);

   return newRoot;
}

Node* maintainBalance(Node* root) {
   if (root == nullptr) {
      return root;
   }

   updateHeight(root);
   int balance = getBalance(root);

   if (balance > 1 && getBalance(root->left) >= 0) {
      return rightRotate(root);
   }
   if (balance > 1 && getBalance(root->left) < 0) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
   }
   if (balance < -1 && getBalance(root->right) <= 0) {
      return leftRotate(root);
   }
   if (balance < -1 && getBalance(root->right) > 0) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
   }

   return root;
}

Node* insert(Node* root, int value) {
   if (root == nullptr) {
      return new Node(value);
   }
   if (value < root->value) {
      root->left = insert(root->left, value);
   }
   if (value > root->value) {
      root->right = insert(root->right, value);
   }
   else {
      return root;
   }

   return maintainBalance(root);
}

Node* remove(Node* root, int value) {
   if (root == nullptr) {
      return root;
   }
   if (value < root->value) {
      root->left = remove(root->left, value);
   }
   else if (value > root->value) {
      root->right = remove(root->right, value);
   }
   else {
      if (root->left == nullptr) {
         Node* temp = root->right;
         free(root);
         root = temp;
      }
      else if (root->right == nullptr) {
         Node* temp = root->left;
         free(root);
         root = temp;
      }
      else {
         Node* minVal = minValueNode(root->right);
         root->value = minVal->value;
         root->right = remove(root->right, minVal->value);
      }
   }
   return maintainBalance(root);
}

void inorderPrint(Node* root) {
   if (root != nullptr) {
      inorderPrint(root->left);
      cout << root->value << " ";
      inorderPrint(root->right);
   }
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int N; cin >> N;

   Node* root = nullptr;

   int value;
   string input;
   for (int i = 0; i < N; i++) {
      cin >> input;
      if (input == "add") {
         cin >> value;
         root = insert(root, value);
      }
      else if (input == "del") {
         cin >> value;
         root = remove(root, value);
      }
      else if (input == "inorder") {
         inorderPrint(root);
         cout << "\n";
      }
   }

   return 0;
}
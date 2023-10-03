//
// Created by msgab on 9/15/2023.
//
#pragma once
#include <sstream>
#include <vector>
using namespace std;

struct Node{
    string name;
    string ufid;
    Node* left;
    Node* right;
    int level;
    int height;
    Node() : name(""), ufid(""), left(nullptr), right(nullptr), level(0), height(0){}
};


class AVLTree{
private:
    Node* root;
    void inorderHelp(Node *root, string &order);
    Node* InsertHelper(string name, string ufid, Node* root);
    int height(Node *node);
    int balanceFactor(Node *node);
    Node* rotateLeft(Node* first);
    Node* rotateRight(Node* first);
    void preorderHelp(Node *root, string &order);
    void postorderHelp(Node *root, string &order);
    void searchNumHelper(string ufid, Node* root);
    void searchNameHelper(string name, Node *root, string &output);
    Node* removeHelp(string ufid, Node *root);
    void removeInorderHelper(vector<Node*> &inorder, int num, Node* root);
    //int updateLevel(Node *node);
    Node* s(Node* parent, Node *lchild);

public:

    //insert is where we perform rotations and use recursion
    //unsuccessful happens when the value is already in the tree
    //check recursivly while coming back up

    //ask about insert
    void Insert(AVLTree &t, string name, string ufid);
    void preorder(AVLTree &t);
    string inorder(AVLTree &t);
    void postorder(AVLTree &t);
    void printLevelCount(AVLTree &t);
    void searchID(string ufid, AVLTree &t);
    string searchName(string name, AVLTree &t);
    void remove(string ufid, AVLTree &t);
    void removeInorder(int num, AVLTree &t);
    AVLTree();
};

AVLTree::AVLTree() {
    root = nullptr;
}

int AVLTree::height(Node *node){
    if(node == nullptr){
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

int AVLTree::balanceFactor(Node *node) {
    if(node == nullptr){
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node *AVLTree::rotateLeft(Node *first) {
    //first it take the node to the right of the first node in the rotation
    Node* rightchild = first->right;
    //then we place a node at the open space to the left of the middle node
    first->right = rightchild->left;
    rightchild->left = first;
    if(first == root){
        root = rightchild;
    }
    return rightchild;
}

Node *AVLTree::rotateRight(Node *first) {
    //first we take the node to the left of the first node for the middle in the rotation
    Node* middle = first->left;
    //then we place a node in the open space to the right of the middle node
    Node* open_space = middle->right;
    //then we put the first node to the right of the middle node
    middle->right = first;
    //after that we fill in the children of the middle node on the right side to the new node
    first->left = open_space;
    first->height = height(first);
    middle->height = height(middle);
    if(first == root){
        root = middle;
    }
    return middle;
}




Node* AVLTree::InsertHelper(string name, string ufid, Node *root) {
    if(root == nullptr){
        Node *node = new Node;
        node->name = name;

        node->ufid = ufid;
        node->level = 0;
        node->height = 1;
        return node;
    }
    else if(ufid > root->ufid){
        root->right = InsertHelper(name, ufid, root->right);
    }
    else if(ufid < root->ufid){
        root->left = InsertHelper(name, ufid, root->left);
    }

    //update heights
    root->height = 1 + max(root->left ? root->left->height : 0 , root->right ? root->right->height: 0);
    //cout << root->height << " that is height and this is value " << root->ufid << endl;

    int balance_value = balanceFactor(root);
    //cout << balance_value << endl;
    if(balance_value == -2){
        //this is a right node rotate right then left rotation
        if(balanceFactor(root->right) > 0){
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);


    }
        //left heavy tree
    else if(balance_value == 2){
        //rotate the left node left before rotating right
        if(balanceFactor(root->left) < 0){
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }
    //update level
    //root->level = updateLevel(root);
    return root;

}


void AVLTree::Insert(AVLTree &t, string name, string ufid) {

    if(t.root == nullptr){
        Node *node = new Node;
        node = InsertHelper(name, ufid, nullptr);
        t.root = node;
    }
    else{
        InsertHelper(name, ufid, t.root);


    }

}

void AVLTree::preorderHelp(Node *root, string &order) {
    if(root == nullptr){
        return;
    }
    else{
        order += root->name + ", ";
        preorderHelp(root->left, order);
        preorderHelp(root->right, order);
    }
}

void AVLTree::preorder(AVLTree &t) {
    Node *node = t.root;
    //node->visted = true;
    string traversal = "";
    preorderHelp(node, traversal);
    int leng = traversal.length();
    string final = traversal.substr(0,leng -2);
    cout << final << endl;
    final = "";
    traversal = "";
    return ;
}


void AVLTree::inorderHelp(Node *root, string &order) {

    if(root == nullptr){
        return ;
    }
    else{

        inorderHelp(root->left, order);
        order += root->name + ", ";
        inorderHelp(root->right, order);
    }
}

string AVLTree::inorder(AVLTree &t) {
    Node *node = t.root;
    //node->visted = true;
    string traversal = "";
    inorderHelp(node, traversal);
    int leng = traversal.length();
    string final = traversal.substr(0,leng -2);
    if(final == ""){
        final = "unsuccessful";
    }
    //cout << final << endl;
    return final;
}

void AVLTree::postorderHelp(Node *root, string &order) {
    if(root == nullptr){
        return;
    }
    else{
        postorderHelp(root->left, order);
        postorderHelp(root->right, order);
        //cout<< "this root is visited " << root->ufid << endl;
        order += root->name + ", ";
    }
}

void AVLTree::postorder(AVLTree &t) {
    Node *node = t.root;
    //node->visted = true;
    string traversal = "";
    postorderHelp(node, traversal);
    int leng = traversal.length();
    string final = traversal.substr(0,leng -2);
    cout << final << endl;
    final = "";
    traversal = "";
    return ;
}



void AVLTree::printLevelCount(AVLTree &t) {
    Node *node = t.root;
    t.root->height = height(t.root);
    int final = root->height;
    //I have it set to O Level for the first one
    cout << final << endl;
}

void AVLTree::searchNumHelper(string ufid, Node *root) {

    if(root == nullptr){
        cout << "unsuccessful" << endl;
        return ;
    }
    else if (ufid == root->ufid){
        cout << root->name << endl;

    }
    else{
        if(ufid < root->ufid){
            searchNumHelper(ufid, root->left);
        }
        else{
            searchNumHelper(ufid, root->right);
        }
    }
}


void AVLTree::searchID(string ufid, AVLTree &t) {
    Node *node = t.root;
    searchNumHelper(ufid, node);

}

void AVLTree::searchNameHelper(string name, Node *root, string &output) {
    string first = name;
    if(root == nullptr){
        return ;
    }
    else if(name == root->name){
        output += root->ufid + "\n";
    }
    else{
        searchNameHelper(first, root->left, output);
        searchNameHelper(first, root->right, output);

    }
    //return "";
}

string AVLTree::searchName(string name, AVLTree &t) {
    string first = name;
    Node *node = t.root;
    string final = "";
    searchNameHelper(first, t.root, final);
    if (final == ""){
        final = "unsuccessful";
    }
    return final;
}

Node *AVLTree::s(Node* parent, Node *lchild){
    //first go to the left child node of the given node
    //it has to have a left child because we only call this if it has two children
    if(lchild->left == nullptr && parent == nullptr){
        //this is the in-order sucsessor and is the right node
        return lchild;
    }
    else if(lchild->left == nullptr){
        parent->left = lchild->right;
        lchild->right = nullptr;
        return lchild;
    }
    else{
        s(lchild, lchild->left);

    }
}
//redo this
Node* AVLTree::removeHelp(string ufid, Node *root) {
    if(root == nullptr){
        cout <<"unsuccessful" << endl;
        return nullptr;
    }
    //trying to find the node to delete
    if(ufid < root->ufid){
        root->left = removeHelp(ufid, root->left);
    }
    //trying to find the node to delete
    else if(ufid > root->ufid){
        root->right = removeHelp(ufid, root->right);
    }
    else{
        //if it has no children
        if(root->left == nullptr && root->right == nullptr){
            /*root = nullptr;
            delete root;*/
            return nullptr;
        }
        // if it has one child
        else if(root->left != nullptr && root->right == nullptr){
            //cout<< "this will remove the node and replace it with its left child" << endl;
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else if(root->right != nullptr && root->left == nullptr){
            //cout<< "this will remove the node and replace it with its right child" << endl;
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else{
            //this is where we find the inorder predecessor
            //cout << "we find inorder predecessor and replace it with that" << endl;
            Node* successor = s(nullptr, root->right);
            Node* left = root->left;
            Node* right = root->right;
            if(successor != right){
                successor->right = right;
            }
            successor->left = left;
            root = nullptr;
            delete root;
            return successor;

        }
    }
    return root;
}

void AVLTree::remove(string ufid, AVLTree &t) {

    Node* node = t.root;
    t.root = removeHelp(ufid, t.root);
    cout << "successful" << endl;
}

void AVLTree::removeInorderHelper(vector<Node *> &inorder, int num, Node *root) {
    if(root == nullptr){
        return ;
    }
    else{

        removeInorderHelper(inorder,num,root->left);
        inorder.push_back(root);
        removeInorderHelper(inorder, num, root->right);
    }
}

void AVLTree::removeInorder(int num, AVLTree &t){
    //will have it's own inorder traversal that counts through each node
    //if there is no node to that number, return is unsuccsessful
    vector<Node*> nodes;
    removeInorderHelper(nodes, num, t.root);
    int len = nodes.size();
    if(num > len){
        cout << "unsuccessful" << endl;
    }
    else{
        Node* remove_node = nodes[num];
        t.root = removeHelp(remove_node->ufid, t.root);
        cout << "successful" << endl;
    }
}

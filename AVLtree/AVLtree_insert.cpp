#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    void insert(const T &value)
    {
        //TODO
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

//Helping functions
void rotateRight(Node* &root) {
    //TODO: Rotate and return new root after rotate
    Node* tmp = root->pLeft;
    root->pLeft = tmp->pRight;
    tmp->pRight = root;
    root = tmp;
}

void rotateLeft(Node* &root) {
    //TODO: Rotate and return new root after rotate
    Node* tmp = root->pRight;
    root->pRight = tmp->pLeft;
    tmp->pLeft = root;
    root = tmp;
}

void insertRec(const T &value, Node* &node) {
    Node* tmp = NULL;
    if(!node) node = new Node(value);
    else if(value < node->data) {
        if(node->pLeft) insertRec(value, node->pLeft);
        else {
            tmp = new Node(value);
            node->pLeft = tmp;
            // cout << "insert " << value << " into left of " << node->data << endl;
        }
    }
    else if(value > node->data) {
        if(node->pRight) insertRec(value, node->pRight);
        else {
            Node* tmp = new Node(value);
            node->pRight = tmp;
            // cout << "insert " << value << " into right of " << node->data << endl;
        }
    }
    else {
        tmp = new Node(value);
        tmp->pRight = node->pRight;
        node->pRight = tmp;
    }
    int i = getHeightRec(node->pLeft) - getHeightRec(node -> pRight);
    // cout << "Node = " << node->data << " i = " << i << endl;
    if(i > 1) {
        if(node->pLeft->balance == RH) {
            // cout << "Rotate left at subnode " << node->pLeft->data << endl;
            rotateLeft(node->pLeft);
        }
        
        // cout << "Rotate right at node " << node->data << endl;
        rotateRight(node);
    }
    else if(i < -1) {
        if(node->pRight->balance == LH) {
            // cout << "Rotate right at subnode " << node->pRight->data << endl;
            rotateRight(node->pRight);
        }
        // cout << "Rotate left at node " << node->data << endl;
        rotateLeft(node);
    }
    else if(i == 1) {
        node->balance = LH;
        // cout << "Node " << node->data << "'s BalanceValue is " << node->balance << endl;
    }
    else if(i == -1) {
        node->balance = RH;
        // cout << "Node " << node->data << "'s BalanceValue is " << node->balance << endl;
    }
    // cout << LH << " " << EH << " " << RH << endl;
}


void insert(const T &value){
    //TODO
    insertRec(value, root);
}


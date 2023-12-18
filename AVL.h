#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//AVL TREE
class AVL{
private:
    struct node{
        node(){ 
            left  = nullptr; 
            right = nullptr; 
        }
        
        int key;
        int height;
        
        node* left;
        node* right;
    };
    
    //PRIVATE MEMBER VARIABLES
    node* m_root;
    
    //PRIVATE MEMBER FUNCTIONS
    node* ReturnNode(int key);
    node* CreateLeaf(int key);
    node* ReturnNode(int key, node* ptr);
    node* RightRotate(node* y);
    node* LeftRotate(node* x);
    node* RecursiveSearch(node* ptr, int key);
    node* AddLeaf(node* ptr, int key);
    node* BalanceTree(int balance_factor, node* unbalanced_node , node* latest_inserted_node);
    
    void PrintInOrder(node* ptr);
    void PrintScores(node* ptr);
    void RemoveSubtree(node* ptr);
    void RemoveNode(int key, node* parent);
    void RemoveMatch(node* parent, node* match, bool isLeft);
    void RemoveRootMatch();
    void PrintTree2D(node* ptr, int space);
    void PreOrder(node* ptr);
    
    int addBT(node* ptr);
    int Height(node* ptr);
    int FindSmallest(node* ptr);
    int GetBalanceFactor(node* ptr);
    inline int Max(int a, int b) { return (a > b) ? a : b; }
    
    int m_collisions = 0;
    int m_maxCollisions = 0;
    int m_nodeCount  = 0;
    int m_space = 10;
    int m_defaultErrorValue = -40404;
    
    string m_username{};
    
    vector<int> m_data;
    vector<int> m_nodeCollisions;
    
public:
    AVL() : m_root(nullptr) { m_nodeCollisions.resize(512); }
    ~AVL();
    
    void  BalanceTree();
    void  AddLeaf(int key);
    void  RemoveNode(int key);
    void  PrintChildren(int key);
    void  PrintInOrder();
    void  PrintScores();
    void  PrintTreeData();
    void  PrintTree2D(int space);
    void  PreOrder();
    void  PrintCollisions(int indexes);
    
    int FindSmallest();
    int ReturnRootKey();
    
    inline vector<int> GetData() { return m_data; }
    inline int GetBalanceFactor() { return GetBalanceFactor(m_root); }
    inline int Height() { return Height(m_root); } 
    inline int collisions(){ return m_collisions; }
    inline int errorValue(){ return m_defaultErrorValue; }
    inline string UserName(){ return m_username; }
    inline void SetUserName(string name) { m_username = name; }
    
};


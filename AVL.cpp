#include "AVL.h"

//DESTRUCTOR
AVL::~AVL(){
    RemoveSubtree(m_root);
    
    //cout << "\nAVL Tree succesfully deconstructed.\n";
}

int AVL::ReturnRootKey() {
    if(m_root)
        return m_root->key;
    
    cout << "\nTree currently does not have a root node.\n";
    return m_defaultErrorValue; //ERROR VALUE;
}

AVL::node* AVL::CreateLeaf(int key){
    node* newNode = new node;
    newNode->key = key;
    newNode->height = 1;
    
    return newNode;
}

//FALSE = COLLISION, TRUE = NO COLLISION
AVL::node* AVL::AddLeaf(node* ptr, int key){
    if(!m_root){
        m_root = CreateLeaf(key);
        return m_root;
    }
    
    //REMEMBER, IN BINARY TREES, THE LEFT NODE IS ALWAYS SMALLER THAN THE NODE
    //THE RIGHT NODE IS ALWAYS GREATER THAN THE NODE
    
    //IF THE KEY IS LESS THAN THAN THE KEY WE'RE POINTING TO,
    if(key < ptr->key){
        if(ptr->left){ //CHECK IF THE POINTER HAS A LEFT NODE
            AddLeaf(ptr->left, key); //RECURSIVELY CALL THIS UNTIL YOU CAN ADD A KEY
        }
        else{ //IF THE NODE DOES NOT HAVE A LEFT NODE
            ptr->left = CreateLeaf(key); //THE NODE'S LEFT NODE IS NOW THIS LEAF
        }
    }
    //IF THE KEY IS GREATER THAN THAN THE KEY WE'RE POINTING TO,
    else if(key > ptr->key){
        if(ptr->right){ //CHECK IF THE POINTER HAS A RIGHT NODE
            AddLeaf(ptr->right, key); //RECURSIVELY CALL THIS UNTIL YOU CAN ADD A KEY
        }
        else{ //IF THE NODE DOES NOT HAVE A RIGHT NODE
            ptr->right = CreateLeaf(key); //THE NODE'S RIGHT NODE IS NOW THIS LEAF
        }
    }
    //KEY THAT WE WANT TO ADD IS THE SAME AS THE CURRENT NODE WE'RE LOOKING AT
    else{
        m_collisions++;
        return ptr;
        //cout << "The key " << key << " has already been added to the tree.\n";
    }  
}

void AVL::AddLeaf(int key){
    //ENSURE NO DUPLICATE VALUES
    if(find(m_data.begin(), m_data.end(), key) != m_data.end() == false)
        m_data.push_back(key);
    
    AddLeaf(m_root, key);
}

AVL::node* AVL::ReturnNode(int key, node* ptr){
    if(!ptr) return nullptr; //NULL CHECK
    
    //FOUND THE NODE WE WANT, CAN IMMEDIATELY RETURN
    if(ptr->key == key) return ptr;
    
    //RECURSIVELY CALL UNTIL WE FIND THE NODE WE ARE LOOKING FOR
    else if(key < ptr->key) return ReturnNode(key, ptr->left); 
    else return ReturnNode(key, ptr->right);
}

AVL::node* AVL::ReturnNode(int key){
    return ReturnNode(key, m_root);
}

//RECURSIVELY TRAVERSE THE TREE IN ORDER FROM LOWEST VALUE TO HIGHEST VALUE
//IN-ORDER TRAVERSAL
void AVL::PrintInOrder(node* ptr){
    if(!m_root) {
        cout << "\nThe tree is currently empty.\n";
        return;
    }
    
    //LOWER VALUE FIRST
    if(ptr->left){
        PrintInOrder(ptr->left); //RECURSIVELY CALL TO TRAVERSE ALL BRANCHES
    }
    
    //OUTPUT
    cout << ptr->key << " ";
    
    //GREATER VALUE SECOND
    if(ptr->right){
        PrintInOrder(ptr->right);
    }
}

void AVL::PrintInOrder(){
    PrintInOrder(m_root);
}

void AVL::PrintChildren(int key){
    node* on = ReturnNode(key); //WHERE TO START
    
    //IF THE KEY IS NOT FOUND IN THE TREE
    if(!on) 
        cout << "\nKey " << key << " currently does not exist in the tree.\n";
    else{ //IF IT IS
        cout << "\nParent Node = " << on->key << "\n";
        
        //IF THE PARENT NODE HAS OR DOESNT HAVE A LEFT NODE
        on->left == NULL ?
            cout << "Left Child = NULL\n" :
            cout << "Left Child = " << on->left->key << "\n";
        
        //IF THE PARENT NODE HAS OR DOESNT HAVE A RIGHT NODE
        on->right == NULL ?
            cout << "Right Child = NULL\n" :
            cout << "Right Child = " << on->right->key << "\n";
    }
}

void AVL::PrintTree2D(node* ptr, int space){
    if(!ptr)
        return;
    
    //SPACING FOR TREE
    space += m_space;
    
    PrintTree2D(ptr->right, space); //PROCESS RIGHT SUB TREE FIRST
    
    cout << "\n";
    for(int i = m_space; i < space; i++)
        cout << " ";
    cout << ptr->key << "\n";
    
    PrintTree2D(ptr->left, space);
}

void AVL::PrintTree2D(int space){
    PrintTree2D(m_root, space);
}

void AVL::PrintTreeData(){
    if(!m_root) return;
    
    cout << "\nRoot Node: " << m_root->key << "\n";
    for(const auto& node : m_data){
        PrintChildren(node);
        cout << "\n";
    }
    
    cout << "Total count of nodes in tree: " << m_data.size() << ".\n";
}

int AVL::FindSmallest(node* ptr){
    //CHECK IF THE TREE IS EMPTY
    if(!m_root){
        cout << "The tree is currently empty.\n";
        return m_defaultErrorValue; //ERROR VALUE
    }
    
    //ONLY HAVE TO CHECK LEFT CHILD BECAUSE IT WILL ALWAYS BE SMALLER
    if(ptr->left) return FindSmallest(ptr->left); //RECURSIVELY CALL UNTIL YOU ARE AS FAR LEFT AS POSSIBLE
    else return ptr->key; //FINALLY RETURN THE SMALLEST VALUE
}

int AVL::FindSmallest(){
    return FindSmallest(m_root);
}

void AVL::RemoveNode(int key, node* parent){
    if(!m_root) {
        cout << "The tree is currently empty.\n";
        return;
    }
    
    //IF THE KEY WE WANT TO DELETE IS THE ROOT, DELETE THE ROOT AND RESTRUCTURE THE TREE
    //BINARY SEARCH
    if(m_root->key == key) RemoveRootMatch();
    else{
        //IF THE KEY IS LESS THAN THE CURRENT NODES' VALUE, THEN IT MUST BE IN A LEFT CHILD NODE
        if(key < parent->key && parent->left){
            //IF THE PARENT'S LEFT CHILD HAS THE DESIRED VALUE, 
            parent->left->key == key ? 
                RemoveMatch(parent, parent->left, true) : //DELETE IT
                RemoveNode(key, parent->left); //ELSE, RECURSIVELY CALL
        }
        //IF THE KEY IS GREATER THAN THE CURRENT NODES' VALUE, THEN IT MUST BE IN A RIGHT CHILD NODE
        else if(key > parent->key && parent->right){
            //IF THE PARENT'S LEFT CHILD HAS THE DESIRED VALUE, 
            parent->right->key == key ? 
                RemoveMatch(parent, parent->right, false) : //DELETE IT
                RemoveNode(key, parent->right); //ELSE, RECURSIVELY CALL
        }
        //KEY NOT FOUND
        else{
            cout << "The key " << key << " was not found in the tree.\n";
        }
    }
}

void AVL::RemoveNode(int key){
    RemoveNode(key, m_root); //ALWAYS PLUG IN ROOT IF YOU WANT THE RECURSIVE PROGRESS TO START AT THE ROOT
}

void AVL::RemoveRootMatch(){
    if(!m_root) {
        cout << "Cannot remove root. The tree is currently empty.\n";
        return;
    }
    
    node* delPtr = m_root;
    int rootKey  = m_root->key;
    int smallestInRightSubtree;
    
    //CASE 0 (ROOT NODE HAS 0 CHILDREN)
    if(!m_root->left && !m_root->right){
        m_root = NULL;
        delete delPtr;
    }
    
    //CASE 1 (ROOT NODE HAS 1 CHILD)
    //IF ROOT NODE ONLY HAS RIGHT CHILD
    else if(!m_root->left && m_root->right){
        m_root = m_root->right;
        delPtr->right = NULL;
        
        delete delPtr;
        
        cout << "The root node with key " << rootKey << " was deleted successfully.\n" <<
                "The new root contains key " << m_root->key << "\n.";
    }
    //IF ROOT NODE ONLY HAS LEFT CHILD
    else if(m_root->left && !m_root->right){
        m_root = m_root->left;
        delPtr->left = NULL;
        
        delete delPtr;
        
        cout << "The root node with key " << rootKey << " was deleted successfully.\n" <<
                "The new root contains key " << m_root->key << "\n.";
    }
    
    //CASE 2 (ROOT NODE HAS 2 CHILDREN)
    else{
        smallestInRightSubtree = FindSmallest(m_root->right); //FIND THE SMALLEST NUMBER IN THE RIGHT SUBTREE ONLY
        
        //REPLACING THE ROOT WITH THE SMALLEST NUMBER IN THE RIGHT SUB TREE.
        //THIS ENSURES BINARY TREE STRUCTURE BECAUSE EVERY NUMBER ON THE RIGHT OF THE TREE AND LEFT OF THE TREE WILL ALIGN
        RemoveNode(smallestInRightSubtree, m_root);
        m_root->key = smallestInRightSubtree;
        
        cout << "The root key containing key " << rootKey << 
                " was overwritten with key " << m_root->key << ".\n";
    }
}

//PARENT, THE MATCH, AND THE RELATIONSHIP BETWEEN THE MATCH AND THE PARENT
void AVL::RemoveMatch(node* parent, node* match, bool isLeft){
    if(!m_root) {
        cout << "Cannot remove match. The tree is currently empty.\n";
        return;
    }
    
    node* delPtr;
    int matchKey = match->key;
    int smallestInRightSubtree;
    
    
    //CASE 0 (MATCHING NODE HAS 0 CHILDREN)
    if(!match->left && !match->right){
        delPtr = match;
        
        //CHECK IF LEFT OR RIGHT CHILD OF PARENT NODE
        isLeft ? 
            parent->left = NULL :
            parent->right = NULL;
        
        delete delPtr;
        
        cout << "The node containing key " << matchKey << " was successfully removed.\n";
    }
    
    //CASE 1 (MATCHING NODE HAS 1 CHILD)
    //ONLY HAS A RIGHT CHILD
    else if(!match->left && match->right){
        
        //IF THE MATCH IS A LEFT CHILD OF ITS PARENT, THEN SHIFT THE PARENT'S CHILDREN ACCORDINGLY
        //SHIFT ACCORDING TO WHAT HAS A NODE
        //IN THIS CASE, THE LEFT CHILD OF MATCH IS NOT NULL, SO WE MUST ASSIGN IT
        isLeft ?
            parent->left  = match->right:
            parent->right = match->right;
        
        //DISCONNECT FROM TREE
        match->right = NULL;
        
        cout << "The node containing key " << matchKey << " was successfully removed.\n";
        
        delPtr = match;
        delete delPtr;
    }
    //ONLY HAS A LEFT CHILD
    else if(match->left && !match->right){
        
        //IF THE MATCH IS A LEFT CHILD OF ITS PARENT, THEN SHIFT THE PARENT'S CHILDREN ACCORDINGLY
        isLeft ?
            parent->left  = match->left:
            parent->right = match->left;
        
        //DISCONNECT FROM TREE
        match->left = NULL;
        
        cout << "The node containing key " << matchKey << " was successfully removed.\n";
        
        delPtr = match;
        delete delPtr;
    }
    //CASE 3 (MATCHING HAS 2 CHILDREN)
    else{
        smallestInRightSubtree = FindSmallest(match->right);
        RemoveNode(smallestInRightSubtree, match); //START SEARCH AT MATCH NODE
        
        //OVERWRITE THE KEY WITH THE SMALLEST KEY IN IT'S RIGHT SUB TREE
        //IN ORDER TO KEEP BINARY TREE STRUCTURE
        match->key = smallestInRightSubtree;
    }
}

void AVL::RemoveSubtree(node* ptr){
    if(!ptr) return;
    
    //THIS FUNCTION DELETES THE BINARY TREE IN POST-ORDER TRAVERSAL
    //DELETE THE LEFT SUBTREE
    if(ptr->left){
        RemoveSubtree(ptr->left); //RECURSIVELY DELETE SUBTREES
    }
    
    //DELETE THE RIGHT SUBTREE
    if(ptr->right){
        RemoveSubtree(ptr->right); //RECURSIVELY DELETE SUBTREES
    }
    
    //cout << "Deleting the node containing key " << ptr->key << ".\n";
    delete ptr;
}

int AVL::GetBalanceFactor(node* ptr){
    if (ptr == NULL)  
        return 0;  
    return Height(ptr->left) - Height(ptr->right);  
}

int AVL::Height(node* ptr){
    if(!ptr) return 0;

    int left_subtree_height = Height(ptr->left);
      int right_subtree_height = Height(ptr->right);

      if (left_subtree_height > right_subtree_height)
      {
        return (left_subtree_height + 1);
      }
      else 
      {
        return (right_subtree_height + 1);
      }
}

AVL::node* AVL::RightRotate(node *x)  
{  
    node * y  = x->left;
    node * T2 = y->right;

    // Perform rotation  
    y->right = x;
    x->left = T2;

    return y;
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
AVL::node* AVL::LeftRotate(node *x)  
{  
    node * y  = x->right;
    node * T2 = y->left;

    // Perform rotation  
    y->left = x;
    x->right = T2;
    
    return y;
}

AVL::node* AVL::RecursiveSearch(node* ptr, int key){
    if(!ptr || ptr->key == key)
        return ptr;
    
    else if(key < ptr->key)
        return RecursiveSearch(ptr->left, key);
    else
        return RecursiveSearch(ptr->right, key);
}

void AVL::PreOrder(node* ptr)  
{  
    if(!ptr) return;
    cout << ptr->key << " ";  
    PreOrder(ptr->left);  
    PreOrder(ptr->right);  

}

void AVL::PreOrder(){
    PreOrder(m_root);
}

AVL::node* AVL::BalanceTree(int balance_factor, node* unbalanced_node , node* latest_inserted_node){
    if (balance_factor > 1) 
    {
      // left-left imbalance
      if(GetBalanceFactor(unbalanced_node->left) >= 0)
      {
        unbalanced_node = RightRotate(unbalanced_node);
        return unbalanced_node;
      }

      // left-right imbalance
      else if(GetBalanceFactor(unbalanced_node->left) == -1)
      {
        unbalanced_node->left = LeftRotate(unbalanced_node->left);
        unbalanced_node = RightRotate(unbalanced_node);
        return unbalanced_node;
      }
    }

    if (balance_factor < -1) 
    {
      // right-right imbalance  
      if(GetBalanceFactor(unbalanced_node->right) <= -0)
      {
        unbalanced_node = LeftRotate(unbalanced_node);
        return unbalanced_node;
      }

      // right-left imbalance 
      else if(GetBalanceFactor(unbalanced_node->left) == 1)
      {
        unbalanced_node->right = RightRotate(unbalanced_node->right);
        unbalanced_node = LeftRotate(unbalanced_node);
        return unbalanced_node;
      }
    }
    
    return m_root;
}

void AVL::BalanceTree(){
    BalanceTree(GetBalanceFactor(), m_root, ReturnNode(m_data.back()));
}

void AVL::PrintCollisions(int indexes){
    //POPULATE THE NODE COLLISION LIST
    for(const auto& link : m_data) {
        m_nodeCollisions[link]++;
    }
    
    //std::sort(m_nodeCollisions.begin(), m_nodeCollisions.end(), greater<int>());
    
    bool streak = true;
    int indx = 0;
    for(int i = 0; i < indexes; i++){
        cout << "Linked List size: " << indx << ": "<< m_nodeCollisions[i] << "\n";
        if(m_nodeCollisions[i] != 0){
            streak = true;
        }else
            streak = false;
        
        if(streak)
            m_maxCollisions++;
        
        indx++;
        }
    cout << "Maximum number of collisions: " << m_maxCollisions << "\n";
}

void AVL::PrintScores(node* ptr){
    cout << "\n----" << m_username << "----\n";   
    
    //GATHER SUM OF POINTS
    if(!m_root) {
        cout << "\nThe tree is currently empty.\n";
        return;
    }
    
    int sum = addBT(ptr);
    
    cout << "POINTS: " << sum << "\n";
}

int AVL::addBT(node* ptr)
{
    if (!ptr) return 0;
    
    return (ptr->key + addBT(ptr->left) + addBT(ptr->right));
}

void AVL::PrintScores(){
    PrintScores(m_root);
}
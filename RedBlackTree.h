#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

#include <iostream>


/**
 * Container for a single node containing a parent, colour, key, and two siblings.
 */
template<class Type>
struct Node
{
    enum NodeColour { Red, Black };

    Node()
    {
        Parent = RChild = LChild = nullptr;
    }

    Node(Type NodeKey)
    {
        Key = NodeKey;
        Parent = RChild = LChild = nullptr;
    }

    /*
    ~Node()
    {
        delete RChild;
        delete LChild;
    }
     */

    bool IsLeaf() const
    {
        return !RChild && !LChild;
    }

    static void ReplaceNode(Node<Type>* ParentNode, Node<Type>* ChildNode)
    {
        ChildNode->Parent = ParentNode->Parent;
        if((ParentNode->Parent->LChild) && *(ParentNode->Parent->LChild) == *ParentNode)
        {
            ParentNode->Parent->LChild = ChildNode;
        }
        else
        {
            ParentNode->Parent->RChild = ChildNode;
        }
    }

    bool operator==(const Node Right) const
    {
        return this->Key == Right.Key;
    }

    Node* Parent;
    Node* RChild;
    Node* LChild;
    Type Key;
    NodeColour Colour;

};  //end Node definition


/**
 * The Red Black Tree data structure
 * Obeys the following five properties:
 * 1. All nodes are either red or black
 * 2. The root is always black
 * 3. Every leaf is black
 * 4. If a node is red, then both of its children are black
 * 5. For all nodes, the number of black nodes to a leaf node is the same
 *
 * Assumes that any templated type has valid comparison operators for find, insert, and delete to work
 */
template<class Type>
class RedBlackTree
{
public:
    RedBlackTree();
    RedBlackTree(Type RootKey);
    ~RedBlackTree();

    /***
     * Inserts the given key into the tree, if it is not already in the tree
     * @param NewKey The new key to insert into the tree
     */
    void Insert(const Type NewKey);

    /**
     * Removes the given key from the tree, if it exists in the tree
     * @param KeyToDelete The key to delete from the tree
     */
    void Delete(const Type KeyToDelete);

    /**
     * Finds the key passed as parameter in the tree, if it exists
     * @param KeyToFind The key to search for in the tree
     * @return true if key is in the tree, false otherwise
     */
    bool Find(const Type KeyToFind) const;

    /**
     * Finds the node containing the minimum key in the tree
     * @return The node containing the minimum key in the tree
     */
    Node<Type>* FindMin() const;

    /**
     * Finds the node containing the maximum key in the tree
     * @return The node containing the maximum key in the tree
     */
    Node<Type>* FindMax() const;

    /***
     * Makes and returns a sorted array of all elements in the tree
     * @return A pointer to the first element of the newly created array
     */
    Type* MakeArray() const;

    /** Getter function to retrieve size of the tree */
    int GetSize() const;


    void InOrder() const;
    void PreOrder() const;

private:
    /**
     * Returns a pointer to the node with a key matching the key passed as parameter
     * If no node in the tree has a matching key, then the parent of where the key should be is returned
     * @param KeyToFind The key to search for
     * @return The node matching the key, or the parent of the node where the key should go
     */
    Node<Type>* FindIntl(const Type KeyToFind) const;

    void TreeFixInsertion(Node<Type>* X);

    /**
     * Performs a left rotation in the tree at node X
     * Assumes that X has a right child which is not null
     * @param X Node to perform the left rotation on
     */
    void LeftRotation(Node<Type>* X);

    /**
     * Performs a right rotation in the tree at node X
     * Assumes that X has a left child which is not null
     * @param X Node to perform the right rotation on
     */
    void RightRotation(Node<Type>* X);

    /**
     * Finds the min key of a tree starting at the node passed as parameter
     * @param StartNode The node to start the min key search at
     * @return The node with the minimum key
     */
    Node<Type>* FindMinIntl(Node<Type>* StartNode) const;

    /**
     * Finds the max key of a tree starting at the node passed as parameter
     * @param StartNode The node to start the max key search at
     * @return The node with the maximum key
     */
    Node<Type>* FindMaxIntl(Node<Type>* StartNode) const;

    /**
     * Performs an in order traversal of the tree, filling an array with each element as needed
     * @param A Current node for recursive fill
     * @param Arr Array containing the sorted keys; is assumed to be of size at least equal to the tree size
     * @param CurrElement Counter for which position we are currently filling in the array
     */
    void InOrderFill(Node<Type>* A, Type* Arr, int& CurrElement) const;

    void InOrderItl(Node<Type>* a) const;
    void PreOrderItl(Node<Type>* a) const;

    /** Root node in the tree */
    Node<Type>* Root;

    /** The current number of nodes stored in the tree */
    int Size;


};  //end RedBlackTree definition



template<class Type>
RedBlackTree<Type>::RedBlackTree()
{
    Root = nullptr;
    Size = 0;
}

template<class Type>
RedBlackTree<Type>::RedBlackTree(Type RootKey)
{
    Root = new Node<Type>(RootKey);
    Root->Colour = Node<Type>::NodeColour::Black;

    Size = 1;
}

template<class Type>
RedBlackTree<Type>::~RedBlackTree()
{
    delete Root;
}


template<class Type>
void RedBlackTree<Type>::Insert(const Type NewKey)
{
    std::cout << "Inserting key " << NewKey << std::endl;
    //if the root node is null, then insert the key into the root and colour it black
    if(!Root)
    {
        Root = new Node<Type>(NewKey);
        Root->Colour = Node<Type>::NodeColour::Black;
        Size++;
        return;
    }

    Node<Type>* Par = FindIntl(NewKey);

    //If find returns a node that does not match the new key, then we need to insert that key
    if(Par->Key != NewKey)
    {
        Node<Type>* CurrNode;
        if (NewKey < Par->Key)
        {
            Par->LChild = new Node<Type>(NewKey);
            CurrNode = Par->LChild;
        }
        else
        {
            Par->RChild = new Node<Type>(NewKey);
            CurrNode = Par->RChild;
        }

        CurrNode->Colour = Node<Type>::NodeColour::Red;
        CurrNode->Parent = Par;
        CurrNode->RChild = nullptr;
        CurrNode->LChild = nullptr;
        Size++;

        TreeFixInsertion(CurrNode);
    }
}

template<class Type>
void RedBlackTree<Type>::Delete(const Type KeyToDelete)
{
    Node<Type>* NodeToDelete = FindIntl(KeyToDelete);

    //if the key doesn't exist in our tree, then just return
    if(NodeToDelete->Key != KeyToDelete)
    {
        return;
    }

    typename Node<Type>::NodeColour OriginalColour = NodeToDelete->Colour;

    //case 1: the node to delete is a leaf
    if(NodeToDelete->IsLeaf())
    {
        if((NodeToDelete->Parent->LChild) && *(NodeToDelete->Parent->LChild) == *NodeToDelete)
        {
            NodeToDelete->Parent->LChild = nullptr;
        }
        else
        {
            NodeToDelete->Parent->RChild = nullptr;
        }
        delete NodeToDelete;
        NodeToDelete = nullptr;
    }
    //case 2: the node to delete has one child
    else if(!NodeToDelete->LChild || !NodeToDelete->RChild)
    {
        if(NodeToDelete->LChild)
        {
            Node<Type>::ReplaceNode(NodeToDelete, NodeToDelete->LChild);

            delete NodeToDelete;
            NodeToDelete = nullptr;
        }
        else
        {
            Node<Type>::ReplaceNode(NodeToDelete, NodeToDelete->RChild);

            delete NodeToDelete;
            NodeToDelete = nullptr;
        }
    }
    //case 3: the node to delete is an internal node with two children
    else
    {
        Node<Type>* MinNode = FindMinIntl(NodeToDelete->RChild);

    }

    Size--;
}

template<class Type>
bool RedBlackTree<Type>::Find(const Type KeyToFind) const
{
    Node<Type>* FoundNode = FindIntl(KeyToFind);
    return FoundNode->Key == KeyToFind;
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindMin() const
{
    return FindMinIntl(this->Root);
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindMax() const
{
    return FindMaxIntl(this->Root);
}

template<class Type>
Type* RedBlackTree<Type>::MakeArray() const
{
    Type* Arr = new Type[this->Size];
    int x = 0;
    InOrderFill(this->Root, Arr, x);
    return Arr;
}

template<class Type>
int RedBlackTree<Type>::GetSize() const
{
    return Size;
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindIntl(const Type KeyToFind) const
{
    Node<Type>* Par = nullptr;
    Node<Type>* CurrNode = this->Root;
    while(CurrNode)
    {
        if(KeyToFind == CurrNode->Key)
        {
            return CurrNode;
        }

        Par = CurrNode;
        if(KeyToFind < CurrNode->Key)
        {
            CurrNode = CurrNode->LChild;
        }
        else
        {
            CurrNode = CurrNode->RChild;
        }
    }

    return Par;
}

template<class Type>
void RedBlackTree<Type>::TreeFixInsertion(Node<Type>* X)
{
    Node<Type>* CurrNode = X;
    while((CurrNode->Parent) && CurrNode->Parent->Colour == Node<Type>::NodeColour::Red)
    {
        Node<Type>* Par = CurrNode->Parent;

        //Is Par a left child of its parent?
        if((Par->Parent->LChild) && *Par == *(Par->Parent->LChild))
        {
            std::cout << "Performing fix-up on left child" << std::endl;
            Node<Type>* Y = Par->Parent->RChild;
            if(!Y || Y->Colour == Node<Type>::NodeColour::Black)
            {
                if((Par->RChild) && *(Par->RChild) == *X)
                {
                    CurrNode = Par;
                    LeftRotation(CurrNode);
                }

                CurrNode->Parent->Colour = Node<Type>::NodeColour::Black;
                CurrNode->Parent->Parent->Colour = Node<Type>::NodeColour::Red;
                RightRotation(CurrNode->Parent->Parent);
            }
            else
            {
                Par->Colour = Node<Type>::NodeColour::Black;
                Y->Colour = Node<Type>::NodeColour::Black;
                Y->Parent->Colour = Node<Type>::NodeColour::Red;
                CurrNode = Y->Parent;
            }

            Y = nullptr;
        }
        else  //We know Par is a right child of its parent
        {
            std::cout << "Performing fix-up on right child" << std::endl;
            Node<Type>* Y = Par->Parent->LChild;
            if(!Y || Y->Colour == Node<Type>::NodeColour::Black)
            {
                if((Par->LChild) && *(Par->LChild) == *X)
                {
                    CurrNode = Par;
                    RightRotation(CurrNode);
                }

                CurrNode->Parent->Colour = Node<Type>::NodeColour::Black;
                CurrNode->Parent->Parent->Colour = Node<Type>::NodeColour::Red;
                LeftRotation(CurrNode->Parent->Parent);
            }
            else
            {
                Par->Colour = Node<Type>::NodeColour::Black;
                Y->Colour = Node<Type>::NodeColour::Black;
                Y->Parent->Colour = Node<Type>::NodeColour::Red;
                CurrNode = Y->Parent;
            }

            Y = nullptr;
        }

        Par = nullptr;
    }
    this->Root->Colour = Node<Type>::NodeColour::Black;
    CurrNode = nullptr;
}

template<class Type>
void RedBlackTree<Type>::LeftRotation(Node<Type>* X)
{
    std::cout << "Performing left rotation" << std::endl;
    Node<Type>* Y = X->RChild;

    //move Y's left child to the right child of X and modify the child's parent if necessary
    X->RChild = Y->LChild;
    if(Y->LChild != nullptr)
    {
        X->RChild->Parent = X;
    }

    Node<Type>* Par = X->Parent;
    if(!Par)
    {
        this->Root = Y;
        Y->Parent = nullptr;
    }
    else if((Par->LChild) && *(Par->LChild) == *X)
    {
        Par->LChild = Y;
        Y->Parent = Par;
    }
    else
    {
        Par->RChild = Y;
        Y->Parent = Par;
    }

    Y->LChild = X;
    X->Parent = Y;

    Y = nullptr;
    Par = nullptr;
}

template<class Type>
void RedBlackTree<Type>::RightRotation(Node<Type>* X)
{
    std::cout << "Performing right rotation" << std::endl;
    Node<Type>* Y = X->LChild;

    X->LChild = Y->RChild;
    if(Y->RChild != nullptr)
    {
        Y->RChild->Parent = X;
    }

    Node<Type>* Par = X->Parent;
    if(!Par)
    {
        this->Root = Y;
        Y->Parent = nullptr;
    }
    else if((Par->LChild) && *(Par->LChild) == *X)
    {
        Par->LChild = Y;
        Y->Parent = Par;
    }
    else
    {
        Par->RChild = Y;
        Y->Parent = Par;
    }

    Y->RChild = X;
    X->Parent = Y;

    Y = nullptr;
    Par = nullptr;
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindMinIntl(Node<Type>* StartNode) const
{
    Node<Type>* MinNode = nullptr;
    Node<Type>* CurrNode = StartNode;

    while(CurrNode)
    {
        MinNode = CurrNode;
        CurrNode = CurrNode->LChild;
    }

    return MinNode;
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindMaxIntl(Node<Type>* StartNode) const
{
    Node<Type>* MaxNode = nullptr;
    Node<Type>* CurrNode = StartNode;

    while(CurrNode)
    {
        MaxNode = CurrNode;
        CurrNode = CurrNode->RChild;
    }

    return MaxNode;
}

template<class Type>
void RedBlackTree<Type>::InOrderFill(Node<Type>* A, Type* Arr, int& CurrElement) const
{
    if(!A)
        return;

    InOrderFill(A->LChild, Arr, CurrElement);
    Arr[CurrElement] = A->Key;
    CurrElement++;
    InOrderFill(A->RChild, Arr, CurrElement);
}

template<class Type>
void RedBlackTree<Type>::InOrderItl(Node<Type>* a) const
{
    if(!a)
        return;

    InOrderItl(a->LChild);
    std::cout << a->Key << " ";
    InOrderItl(a->RChild);
}

template<class Type>
void RedBlackTree<Type>::InOrder() const
{
    InOrderItl(Root);
}


template<class Type>
void RedBlackTree<Type>::PreOrderItl(Node<Type>* a) const
{
    if(!a)
        return;

    std::cout << a->Key << " and is colour " << (a->Colour == Node<Type>::NodeColour::Black ? "black" : "red") << " and has parent ";
    ((a->Parent) ? std::cout << a->Parent->Key : std::cout << "null");
    std::cout << std::endl;
    PreOrderItl(a->LChild);
    PreOrderItl(a->RChild);
}

template<class Type>
void RedBlackTree<Type>::PreOrder() const
{
    PreOrderItl(Root);
}
#endif //REDBLACKTREE_REDBLACKTREE_H

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

#include <iostream>
#include <memory>
#include <algorithm>

/**
 * Container for a single node containing a key, its colour, its parent, and two siblings.
 */
template<class Type>
struct Node
{
    enum NodeColour
    {
        Red, Black
    };

    Node()
    {
        Parent = RChild = LChild = nullptr;
    }

    Node(Type NodeKey)
    {
        Key = NodeKey;
        Parent = RChild = LChild = nullptr;
    }


    ~Node()
    {
        delete RChild;
        delete LChild;
    }

    /** Is this node a leaf? */
    bool IsLeaf() const
    {
        return !RChild && !LChild;
    }

    /** Tests to see if this node is black */
    static bool TestColourBlack(const Node<Type>* TestNode)
    {
        return !TestNode || TestNode->Colour == NodeColour::Black;
    }

    /** Tests to see if this node is red */
    static bool TestColourRed(const Node<Type>* TestNode)
    {
        return TestNode && TestNode->Colour == NodeColour::Red;
    }

    bool operator==(const Node &Right) const
    {
        return this->Key == Right.Key;
    }

    bool operator!=(const Node &Right) const
    {
        return !(*this == Right);
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
 * 3. Every leaf node (null node) is black
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

    /**
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
     * Finds the smallest key in the tree
     * @return The smallest key in the tree
     */
    Type FindMin() const;

    /**
     * Finds the largest key in the tree
     * @return The largest key in the tree
     */
    Type FindMax() const;

    /***
     * Makes and returns a sorted array of all elements in the tree
     * @return A pointer to the first element of the newly created array
     */
    Type* MakeArray() const;

    /** Getter function to retrieve size of the tree */
    int GetSize() const;

    int GetHeight() const;
    int GetBlackHeight() const;

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

    /**
     * Fixes the tree after an insertion so that the red-black properties are obeyed
     * @param X Node that was inserted
     */
    void TreeFixInsertion(Node<Type>* X);

    /**
     * Fixes tree after deletion so that the red-black properties are obeyed
     * @param X Node that replaced the deleted node
     * @param Y Parent of X; needed only in the case when X is null
     * @param DeletedKey Key that was removed from tree; used to initialize X, should X be null
     */
    void TreeFixDeletion(Node<Type>* X, Node<Type>* Y, Type DeletedKey);

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
     * Helper function to delete a leaf node from the tree
     * Assumes that the node is a leaf (does not internal checks to see if this assumption is true)
     * @param NodeToDelete Pointer to the node that is to be deleted
     */
    void DeleteLeaf(Node<Type>* NodeToDelete);

    /**
     * Helper function to delete a node with one child from the tree
     * Assumes that the node has at most one child (does no internal checks to see if this assumption is true)
     * @param NodeToDelete Pointer to the node that is to be deleted
     */
    void DeleteNodeOneChild(Node<Type>* NodeToDelete);

    /**
     * Replaces a child node with that of its parent
     * @param ParentNode Parent node of child
     * @param ChildNode Child node of parent
     */
    void ReplaceNode(Node<Type>* ParentNode, Node<Type>* ChildNode);

    /**
     * Finds the min key of a tree starting at the node passed as parameter
     * Assumes that StartNode is not null, otherwise nullptr will be returned
     * @param StartNode The node to start the min key search at
     * @return The node with the minimum key
     */
    Node<Type>* FindMinIntl(Node<Type>* StartNode) const;

    /**
     * Finds the max key of a tree starting at the node passed as parameterAssumes that StartNode is not null, otherwise nullptr will be returned
     * Assumes that StartNode is not null, otherwise nullptr will be returned
     * @param StartNode The node to start the max key search at
     * @return The node with the maximum key
     */
    Node<Type>* FindMaxIntl(Node<Type>* StartNode) const;

    int GetHeightIntl(Node<Type>* Curr) const;
    int GetBlackHeightIntl(Node<Type>* Curr) const;

    /**
     * Performs an in order traversal of the tree, filling an array with each element as needed
     * @param A Current node for recursive fill
     * @param Arr Array containing the sorted keys; is assumed to be of size at least equal to the tree size
     * @param CurrElement Counter for which position we are currently filling in the array
     */
    void InOrderFill(Node<Type>* A, Type* Arr, int &CurrElement) const;

    /**
     * Performs an in order traversal of the current node
     * @param a Current node to perform an in order traversal on
     */
    void InOrderItl(Node<Type>* a) const;

    /**
     * Performs a pre order traversal of the current node
     * @param a Current node to perform a pre order traversal on
     */
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
    //if the root node is null, then insert the key into the root and colour it black
    if (!Root)
    {
        Root = new Node<Type>(NewKey);
        Root->Colour = Node<Type>::NodeColour::Black;
        Size++;
        return;
    }

    Node<Type>* Par = FindIntl(NewKey);

    //If find returns a node that does not match the new key, then we need to insert that key
    if (Par->Key != NewKey)
    {
        Node<Type>* InsertedNode;
        if (NewKey < Par->Key)
        {
            Par->LChild = new Node<Type>(NewKey);
            InsertedNode = Par->LChild;
        }
        else
        {
            Par->RChild = new Node<Type>(NewKey);
            InsertedNode = Par->RChild;
        }

        InsertedNode->Colour = Node<Type>::NodeColour::Red;
        InsertedNode->Parent = Par;
        InsertedNode->RChild = nullptr;
        InsertedNode->LChild = nullptr;
        Size++;

        TreeFixInsertion(InsertedNode);
    }

    Par = nullptr;
}

template<class Type>
void RedBlackTree<Type>::Delete(const Type KeyToDelete)
{
    if (Size == 0)
    {
        return;
    }

    Node<Type>* NodeToDelete = FindIntl(KeyToDelete);

    //if the key doesn't exist in our tree, then just return
    if (NodeToDelete->Key != KeyToDelete)
    {
        NodeToDelete = nullptr;
        return;
    }

    typename Node<Type>::NodeColour OriginalColour = NodeToDelete->Colour;

    Node<Type>* ReplacementNode = nullptr;
    Node<Type>* ReplacementNodeParent = nullptr;

    //special case: if the root is the only node left, then just delete the root
    if (Size == 1)
    {
        delete Root;
        Root = nullptr;
        OriginalColour = Node<Type>::NodeColour::Red;
    }
        //case 1: the node to delete is a leaf
    else if (NodeToDelete->IsLeaf())
    {
        ReplacementNodeParent = NodeToDelete->Parent;
        DeleteLeaf(NodeToDelete);
    }
        //case 2: the node to delete has one child
    else if (!NodeToDelete->LChild || !NodeToDelete->RChild)
    {
        if (NodeToDelete->LChild)
        {
            ReplacementNode = NodeToDelete->LChild;
        }
        else
        {
            ReplacementNode = NodeToDelete->RChild;
        }

        ReplacementNodeParent = NodeToDelete->Parent;
        DeleteNodeOneChild(NodeToDelete);
    }
        //case 3: the node to delete is an internal node with two children
    else
    {
        Node<Type>* MinNode = FindMinIntl(NodeToDelete->RChild);
        OriginalColour = MinNode->Colour;

        NodeToDelete->Key = MinNode->Key;

        if (MinNode->IsLeaf())
        {
            ReplacementNodeParent = MinNode->Parent;
            DeleteLeaf(MinNode);
        }
        else
        {
            if (MinNode->LChild)
            {
                ReplacementNode = MinNode->LChild;
            }
            else
            {
                ReplacementNode = MinNode->RChild;
            }

            ReplacementNodeParent = MinNode->Parent;
            DeleteNodeOneChild(MinNode);
        }
    }

    Size--;

    if (OriginalColour == Node<Type>::NodeColour::Black && Size != 0)
    {
        TreeFixDeletion(ReplacementNode, ReplacementNodeParent, KeyToDelete);
    }

    NodeToDelete = nullptr;
    ReplacementNode = nullptr;
    ReplacementNodeParent = nullptr;
}

template<class Type>
bool RedBlackTree<Type>::Find(const Type KeyToFind) const
{
    if (Size == 0)
    {
        return false;
    }

    Node<Type>* FoundNode = FindIntl(KeyToFind);
    Type NodeKey = FoundNode->Key;
    FoundNode = nullptr;
    return NodeKey == KeyToFind;
}

template<class Type>
Type RedBlackTree<Type>::FindMin() const
{
    Node<Type>* Min = FindMinIntl(this->Root);
    Type MinKey = Min->Key;
    Min = nullptr;
    return MinKey;
}

template<class Type>
Type RedBlackTree<Type>::FindMax() const
{
    Node<Type>* Max = FindMaxIntl(this->Root);
    Type MaxKey = Max->Key;
    Max = nullptr;
    return MaxKey;
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
int RedBlackTree<Type>::GetHeight() const
{
    return GetHeightIntl(Root);
}

template<class Type>
int RedBlackTree<Type>::GetBlackHeight() const
{
    return GetBlackHeightIntl(Root);
}

template<class Type>
int RedBlackTree<Type>::GetSize() const
{
    return Size;
}

template<class Type>
void RedBlackTree<Type>::InOrder() const
{
    InOrderItl(Root);
}

template<class Type>
void RedBlackTree<Type>::PreOrder() const
{
    PreOrderItl(Root);
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindIntl(const Type KeyToFind) const
{
    Node<Type>* Par = nullptr;
    Node<Type>* CurrNode = this->Root;
    while (CurrNode)
    {
        if (KeyToFind == CurrNode->Key)
        {
            return CurrNode;
        }

        Par = CurrNode;
        if (KeyToFind < CurrNode->Key)
        {
            CurrNode = CurrNode->LChild;
        }
        else
        {
            CurrNode = CurrNode->RChild;
        }
    }

    CurrNode = nullptr;

    return Par;
}

template<class Type>
void RedBlackTree<Type>::TreeFixInsertion(Node<Type>* X)
{
    Node<Type>* CurrNode = X;

//we assume the current node is coloured red; only do this loop while our parent is also coloured red
    while ((CurrNode->Parent) && CurrNode->Parent->Colour == Node<Type>::NodeColour::Red)
    {
        Node<Type>* Par = CurrNode->Parent;

//Is Par a left child of its parent?
        if ((Par->Parent->LChild) && *Par == *(Par->Parent->LChild))
        {
            Node<Type>* Y = Par->Parent->RChild;
            if (Node<Type>::TestColourBlack(Y))
            {
                if ((Par->RChild) && *(Par->RChild) == *CurrNode)
                {
                    CurrNode = Par;
                    LeftRotation(CurrNode);
                }

                CurrNode->Parent->Colour = Node<Type>::NodeColour::Black;
                CurrNode->Parent->Parent->Colour = Node<Type>::NodeColour::Red;
                RightRotation(CurrNode->Parent->Parent);
            }
            else //we are going to recolour the nodes
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
            Node<Type>* Y = Par->Parent->LChild;
            if (Node<Type>::TestColourBlack(Y))
            {
                if ((Par->LChild) && *(Par->LChild) == *CurrNode)
                {
                    CurrNode = Par;
                    RightRotation(CurrNode);
                }

                CurrNode->Parent->Colour = Node<Type>::NodeColour::Black;
                CurrNode->Parent->Parent->Colour = Node<Type>::NodeColour::Red;
                LeftRotation(CurrNode->Parent->Parent);
            }
            else //we are going to recolour the nodes
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
void RedBlackTree<Type>::TreeFixDeletion(Node<Type>* X, Node<Type>* Y, Type DeletedKey)
{
    Node<Type>* TempNode = nullptr;

//If node x is null, then we create a new temp node that takes its place, with parent Y
    if (!X)
    {
        X = new Node<Type>();
        X->Parent = Y;
        X->Colour = Node<Type>::NodeColour::Black;
        X->Key = DeletedKey;

        TempNode = X;

        if (!Y->LChild)
        {
            Y->LChild = X;
        }
        else
        {
            Y->RChild = X;
        }
    }

    while (*X != *Root && X->Colour == Node<Type>::NodeColour::Black)
    {
        Node<Type>* Sibling;

        if ((X->Parent->LChild) && *(X->Parent->LChild) == *X)
        {
            Sibling = X->Parent->RChild;

            //case 1: our sibling is red
            if (Node<Type>::TestColourRed(Sibling))
            {
                Sibling->Colour = Node<Type>::NodeColour::Black;
                X->Parent->Colour = Node<Type>::NodeColour::Red;
                LeftRotation(X->Parent);

                Sibling = X->Parent->RChild;
            }

            //case 2: Our sibling is black, with two blackk children
            if (Node<Type>::TestColourBlack(Sibling->LChild) && Node<Type>::TestColourBlack(Sibling->RChild))
            {
                Sibling->Colour = Node<Type>::NodeColour::Red;

                X = X->Parent;
            }
            else
            {
                //case 3: our sibling is black, and its right child is black as well
                if (Node<Type>::TestColourBlack(Sibling->RChild))
                {
                    Sibling->Colour = Node<Type>::NodeColour::Red;
                    Sibling->LChild->Colour = Node<Type>::NodeColour::Black;
                    RightRotation(Sibling);
                    Sibling = X->Parent->RChild;
                }

                //case 4: our sibling is black and its right child is red
                Sibling->Colour = X->Parent->Colour;
                X->Parent->Colour = Node<Type>::NodeColour::Black;
                Sibling->RChild->Colour = Node<Type>::NodeColour::Black;
                LeftRotation(X->Parent);

                X = this->Root;
            }
        }
        else
        {
            Sibling = X->Parent->LChild;

            //case 1: our sibling is red
            if (Node<Type>::TestColourRed(Sibling))
            {
                Sibling->Colour = Node<Type>::NodeColour::Black;
                X->Parent->Colour = Node<Type>::NodeColour::Red;
                RightRotation(X->Parent);

                Sibling = X->Parent->LChild;
            }

            //case 2: Our sibling is black, with two blackk children
            if (Node<Type>::TestColourBlack(Sibling->LChild) && Node<Type>::TestColourBlack(Sibling->RChild))
            {
                Sibling->Colour = Node<Type>::NodeColour::Red;

                X = X->Parent;
            }
            else
            {
                //case 3: our sibling is black, and its left child is black as well
                if (Node<Type>::TestColourBlack(Sibling->LChild))
                {
                    Sibling->Colour = Node<Type>::NodeColour::Red;
                    Sibling->RChild->Colour = Node<Type>::NodeColour::Black;
                    LeftRotation(Sibling);
                    Sibling = X->Parent->LChild;
                }

                //case 4: our sibling is black and its left child is red
                Sibling->Colour = X->Parent->Colour;
                X->Parent->Colour = Node<Type>::NodeColour::Black;
                Sibling->LChild->Colour = Node<Type>::NodeColour::Black;
                RightRotation(X->Parent);

                X = Root;
            }
        }

        Sibling = nullptr;
    }
    X->Colour = Node<Type>::NodeColour::Black;

//delete the temp node if we created it at the beginning of the function
    if (TempNode)
    {
        if ((Y->LChild) && *Y->LChild == *TempNode)
        {
            Y->LChild = nullptr;
        }
        else
        {
            Y->RChild = nullptr;
        }

        delete TempNode;
        TempNode = nullptr;
    }
}

template<class Type>
void RedBlackTree<Type>::LeftRotation(Node<Type>* X)
{
    Node<Type>* Y = X->RChild;

//move Y's left child to the right child of X and modify the child's parent if necessary
    X->RChild = Y->LChild;
    if (Y->LChild != nullptr)
    {
        X->RChild->Parent = X;
    }

    Node<Type>* Par = X->Parent;
    if (!Par)
    {
        this->Root = Y;
        Y->Parent = nullptr;
    }
    else if ((Par->LChild) && *(Par->LChild) == *X)
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
    Node<Type>* Y = X->LChild;

    X->LChild = Y->RChild;
    if (Y->RChild != nullptr)
    {
        Y->RChild->Parent = X;
    }

    Node<Type>* Par = X->Parent;
    if (!Par)
    {
        this->Root = Y;
        Y->Parent = nullptr;
    }
    else if ((Par->LChild) && *(Par->LChild) == *X)
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
void RedBlackTree<Type>::DeleteLeaf(Node<Type>* NodeToDelete)
{
    if ((NodeToDelete->Parent->LChild) && *(NodeToDelete->Parent->LChild) == *NodeToDelete)
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

template<class Type>
void RedBlackTree<Type>::DeleteNodeOneChild(Node<Type>* NodeToDelete)
{
    if (NodeToDelete->LChild)
    {
        ReplaceNode(NodeToDelete, NodeToDelete->LChild);
        NodeToDelete->LChild = nullptr;
    }
    else
    {
        ReplaceNode(NodeToDelete, NodeToDelete->RChild);
        NodeToDelete->RChild = nullptr;
    }

    delete NodeToDelete;
    NodeToDelete = nullptr;
}

template<class Type>
void RedBlackTree<Type>::ReplaceNode(Node<Type>* ParentNode, Node<Type>* ChildNode)
{
    ChildNode->Parent = ParentNode->Parent;
    if (!(ParentNode->Parent))
    {
        this->Root = ChildNode;
    }
    else if ((ParentNode->Parent->LChild) && *(ParentNode->Parent->LChild) == *ParentNode)
    {
        ParentNode->Parent->LChild = ChildNode;
    }
    else
    {
        ParentNode->Parent->RChild = ChildNode;
    }
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindMinIntl(Node<Type>* StartNode) const
{
    Node<Type>* MinNode = nullptr;
    Node<Type>* CurrNode = StartNode;

    while (CurrNode)
    {
        MinNode = CurrNode;
        CurrNode = CurrNode->LChild;
    }
    CurrNode = nullptr;
    return MinNode;
}

template<class Type>
Node<Type>* RedBlackTree<Type>::FindMaxIntl(Node<Type>* StartNode) const
{
    Node<Type>* MaxNode = nullptr;
    Node<Type>* CurrNode = StartNode;

    while (CurrNode)
    {
        MaxNode = CurrNode;
        CurrNode = CurrNode->RChild;
    }
    CurrNode = nullptr;
    return MaxNode;
}

template<class Type>
int RedBlackTree<Type>::GetHeightIntl(Node<Type>* Curr) const
{
    if (!Curr)
    {
        return -1;
    }

    return std::max(GetHeightIntl(Curr->LChild), GetHeightIntl(Curr->RChild)) + 1;
}

template<class Type>
int RedBlackTree<Type>::GetBlackHeightIntl(Node<Type>* Curr) const
{
    if (!Curr)
    {
        return 0;
    }

    if (Curr->Colour == Node<Type>::NodeColour::Black)
    {
        return GetHeightIntl(Curr->LChild) + 1;
    }
    else
    {
        return GetHeightIntl(Curr->LChild);
    }
}

template<class Type>
void RedBlackTree<Type>::InOrderFill(Node<Type>* A, Type* Arr, int &CurrElement) const
{
    if (!A)
    {
        return;
    }

    InOrderFill(A->LChild, Arr, CurrElement);
    Arr[CurrElement] = A->Key;
    CurrElement++;
    InOrderFill(A->RChild, Arr, CurrElement);
}

template<class Type>
void RedBlackTree<Type>::InOrderItl(Node<Type>* a) const
{
    if (!a)
    {
        return;
    }

    InOrderItl(a->LChild);
    std::cout << a->Key << " ";
    InOrderItl(a->RChild);
}

template<class Type>
void RedBlackTree<Type>::PreOrderItl(Node<Type>* a) const
{
    if (!a)
    {
        return;
    }

    std::cout << a->Key << " and is colour " << (a->Colour == Node<Type>::NodeColour::Black ? "black" : "red")
              << " and has parent ";
    ((a->Parent) ? std::cout << a->Parent->Key : std::cout << "null");
    std::cout << std::endl;
    PreOrderItl(a->LChild);
    PreOrderItl(a->RChild);
}

#endif //REDBLACKTREE_REDBLACKTREE_H

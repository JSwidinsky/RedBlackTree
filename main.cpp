#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "RedBlackTree.h"
using namespace std;

/**
 * Function that inserts a series of random numbers into a red black tree
 * @param Tree The tree to insert the elements into
 * @param NumEntriesToAdd How many entries should we add to the tree?
 * @param RandRange The interval for which the numbers will be added; interval is [0, RandRange)
 * */
void InsertIntoTree(RedBlackTree<int>& Tree, int NumEntriesToAdd, int RandRange)
{
    float start = clock();
    for (int i = 0; i < NumEntriesToAdd; i++)
    {
        int a = rand() % RandRange;

        Tree.Insert(a);
    }

    cout << "Time for insertion to finish: " << (clock() - start) / CLOCKS_PER_SEC << endl;
}


int main()
{
    srand(time(0));

    cout << fixed << setprecision(10);

    RedBlackTree<int> RBTree;

    for(int i = 0; i < 5; i++)
        InsertIntoTree(RBTree, 1000000, 10000000 * (i + 1));

    cout << "Minimum element: " << RBTree.FindMin() << endl;
    cout << "Maximum element: " << RBTree.FindMax() << endl;

    cout << RBTree.GetSize() << endl;
    cout << RBTree.GetHeight() << " " << RBTree.GetBlackHeight() << endl;

    return 0;
}
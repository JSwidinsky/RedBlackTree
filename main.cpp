#include <iostream>
#include <ctime>
#include <cstdlib>
#include "RedBlackTree.h"
using namespace std;
int main()
{
    srand(time(0));

    RedBlackTree<int>* RBT = new RedBlackTree<int>();

    for(int i = 1; i <= 10; i++)
       RBT->Insert(i);

    //RBT->PreOrder();

    //RBT->PreOrder();

    RBT->Delete(9);

    RBT->PreOrder();

    delete RBT;

    return 0;
}
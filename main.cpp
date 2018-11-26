#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "RedBlackTree.h"
using namespace std;
int main()
{
    srand(time(0));

    RedBlackTree<int>* RBT = new RedBlackTree<int>();

    ifstream Input("./RandNums.dat");

    vector<int> randNums;

    bool FillFromFile = true;
    if(FillFromFile)
    {
        for (int i = 0; i < 10000; i++)
        {
            int a;
            Input >> a;
            RBT->Insert(a);

            if(i % 2 == 0)
                randNums.push_back(a);
        }
    }
    else
    {
        for (int i = 1; i <= 10; i++)
        {
            RBT->Insert(i);
        }
    }

    for(int i : randNums)
    {
        RBT->Delete(i);
    }

    //RBT->PreOrder();
    cout << RBT->GetSize() << endl;
    //RBT->InOrder();

    delete RBT;

    return 0;
}
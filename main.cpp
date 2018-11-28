#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "RedBlackTree.h"
using namespace std;
int main()
{
    srand(time(0));

    cout << fixed << setprecision(10);

    float start = clock();

    RedBlackTree<int>* RBT = new RedBlackTree<int>();

    vector<int> randNums;

    bool FillFromFile = true;
    if(FillFromFile)
    {
        for (int i = 0; i < 2000000; i++)
        {
            int a;
            do
            {
                a = rand() % 10000000;
            }
            while(RBT->Find(a));

            RBT->Insert(a);

            if(i % 1 == 0)
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

    cout << "Minimum element: " << RBT->FindMin() << endl;
    cout << "Maximum element: " << RBT->FindMax() << endl;

    cout << "Time to finish insertions: " << (clock() - start)/CLOCKS_PER_SEC << endl;

    start = clock();

    for(int i : randNums)
    //for(int i = 1; i <= 10; i++)
    {
        RBT->Delete(i);
    }

    cout << "Time to finish deletions: " << (clock() - start)/CLOCKS_PER_SEC << endl;

    //RBT->PreOrder();
    cout << RBT->GetSize() << endl;
    //RBT->InOrder();

    delete RBT;

    return 0;
}
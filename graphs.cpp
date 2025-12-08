#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
    int maxv = 15;
    GR Gr(maxv);
    srand(time(nullptr));
    Gr.Create_auto();
    Gr.CheckDistance();

    cout << "\n ===== End =====\n";
}
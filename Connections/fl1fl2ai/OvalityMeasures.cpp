#include "OvalityMeasures.h"
#include <iostream>
using namespace std;

OvalityMeasures::OvalityMeasures() : radius(0), score(0), innerRadius(0), diameters(nullptr), diam_num(0), circleCenter(0, 0)
{
}

void OvalityMeasures::print() const
{
    cout << "Radius: " << radius << " ";
    circleCenter.print();

    cout << "Score: " << score << endl;
    cout << "InnerRadius: " << innerRadius << endl;
    cout << "Diam. Num.: " << diam_num << endl;
    cout << "Diameters: ";
    for (int i = 0; i < diam_num; i++)
        cout << diameters[i] << " ";
    cout << endl;
}

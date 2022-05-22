#include <iostream>
#include "OrgChart.hpp"

using namespace std;
using namespace ariel;

int main(int argc, char const *argv[])
{
    OrgChart chart;
    chart.add_root("Eyal")
        .add_sub("Eyal", "Tal")
        .add_sub("Eyal", "Itai");

    for (auto it = chart.begin_reverse_order(); it != chart.reverse_order(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}

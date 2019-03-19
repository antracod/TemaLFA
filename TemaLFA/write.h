#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <list>

using namespace std;


ofstream out("raspuns.txt");

void display(list<string> v)
{
    for (list<string>::iterator it = v.begin(); it != v.end(); it++)
    {
        out << *it << " ";
    }
    out << "\n";
}

void final_write(int x)
{
    if(x == 1)
    {
        out << "Cuvantul valid\n";
    }
    else
    {
        out << "Cuvant invalid\n";
    }
}

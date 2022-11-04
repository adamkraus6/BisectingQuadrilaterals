// Mathew Clutter
// Adam Kraus

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

double bisect();

struct Point
{
    double x, y;
} points[4];

int main(int argc, char **argv)
{
    ifstream fin("quad.in");
    ofstream fout("quad.out");
    int caseNum = 1;

    if(!fin)
    {
        cout << "Bad quad.in" << endl;
        fin.close();
        return -1;
    }

    if(!fout)
    {
        cout << "Bad quad.out" << endl;
        fout.close();
        return -1;
    }

    while(true)
    {
        fin >> points[0].x >> points[0].y;

        if(points[0].x == -1 && points[0].y == -1)
        {
            break;
        }

        for(int i = 1; i < 4; i++)
        {
            fin >> points[i].x >> points[i].y;
        }

        double bi = bisect();
        fout << "Case " << caseNum << ": " << bi << endl;
        cout << "Case " << caseNum << ": " << bi << endl;
        caseNum++;
    }

    fin.close();
    fout.close();
}

double bisect()
{
    return 0;
}
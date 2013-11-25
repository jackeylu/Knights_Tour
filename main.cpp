#include <iostream>
#include <cstdlib>
#include "Knights.h"

using namespace std;

void help(const char* filename)
{
    cout << "print a Hamilton tour for a m * n board" << endl;
    cout << filename << "\t<m> <n>" << endl;
    cout << "\t m \t the rows" << endl;
    cout << "\t n \t the columns" << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        help(argv[0]);
        return 1;
    }

    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    Knight knight(row, col);
    knight.output();
    return 0;
}

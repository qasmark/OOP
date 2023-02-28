#include <iostream>
#include "Tests.cpp"
#include <vector>
#include <sstream>
#include <iterator>
#include <string>

using list = std::vector <double>;

int main()
{
    
}

list InitializeVector(std::istream& input)
{
    list values((std::istream_iterator<double>(input)),
                 std::istream_iterator<double>());
    //for (list::iterator num = values.begin(); num != values.end(); num++)
    //{

    //}
    return values;
}
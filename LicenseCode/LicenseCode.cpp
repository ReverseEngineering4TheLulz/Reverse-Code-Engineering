#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int input;

    cout<<"Enter your activation code: ";
    cin>>input;

    if (input == 34561)
    {
        MessageBox(0, "Congratulations your license is valid", "License check", 0);
    }

    else
    {
     	MessageBox(0, "Your license is invalid", "License check", 0);
    }

    return 0;
}

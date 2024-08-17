#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int string_to_int(string str)
{
    int num = 0;
    stringstream ss(str);
    ss >> num;
    return num;
}

bool is_number(string &str)
{
    for (char const &chr : str)
    {
       if (isdigit(chr) == false)
       {
            return false;
       }
    }

    return true;
}

bool check_serial_number(string &serial_num_str)
{
    int counter = 0;
    for (const char &chr : serial_num_str)
    {
        if (chr % 2 == 0)
        {
            counter++;
        }
    }

    if (counter == 3)
    {
        return true;
    }

    return false;

}

int main()
{
    string serial_number = "";

    cout<<"Enter serial number: ";
    getline(cin, serial_number);

    if (is_number(serial_number) == false)
    {
        cout<<"Invalid input"<<endl;
    }

    else
    {
		if (check_serial_number(serial_number) == true)
        {
            cout<<"The serial number is correct."<<endl;
        }

        else
        {
            cout<<"Invalid serial number."<<endl;
        }
    }

	system("PAUSE");
}


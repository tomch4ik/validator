#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int main()
{
    ofstream out;
    out.open("Newfiles.html", ios::out | ios::trunc);

    ifstream in;
    in.open("files.html", ios::in);
    if (in)
    {
        const int size = 300;
        do
        {
            char buffer[size] = {};
            in.getline(buffer, size);
            cout << buffer << endl;
            out << buffer << endl;
            Sleep(50);
        } while (in);
        string line;
        int open_tag = 0;
        int close_tag = 0;
        string last_open;
        while (getline(in, line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '<')
                {
                    if (i + 1 < line.length() && line[i + 1] == '/')
                    {
                        close_tag++;
                        string close_tag;
                        i += 2;
                        while (i < line.length() && line[i] != '>')
                        {
                            close_tag += line[i];
                            i++;
                        }
                        if (last_open != close_tag)
                        {
                            cout << "tag </" << close_tag << "> is no correspond open tag <" << last_open << ">" << endl;
                            return 1;
                        }
                        last_open = " ";
                    }
                    else
                    {
                        open_tag++;
                        string open_tag;
                        i++;
                        while (i < line.length() && line[i] != '>')
                        {
                            open_tag += line[i];
                            i++;
                        }
                        last_open = open_tag;
                    }
                }
            }
        }
        if (open_tag == close_tag)
        {
            cout << "File is valid" << endl;
        }
        else if (open_tag > close_tag)
        {
            cout << "Missing tag >" << endl;
        }
        else
        {
            cout << "Missing tag <" << endl;
        }
        out.close();
        in.close();
    }
    else
    {
        cout << "Could not open the file" << endl;
    }
    return 0;
}


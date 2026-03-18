#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

string applyMapping(string text, map<char, char> mapping)
{
    string result = "";

    for (char c : text)
    {
        if (mapping.count(c))
            result += mapping[c];
        else if (mapping.count(toupper(c)))
        {
            char mapped = mapping[toupper(c)];
            if (islower(c))
                result += tolower(mapped);
            else
                result += mapped;
        }
        else
            result += c;
    }

    return result;
}

void inputMapping(map<char, char> &mapping)
{
    char cipher, plain;
    cout << "Nhap mapping (vi du: G T), nhap 0 de dung:\n";

    while (true)
    {
        cout << "Cipher: ";
        cin >> cipher;
        if (cipher == '0') break;

        cout << "Plain: ";
        cin >> plain;

        mapping[cipher] = plain;
    }
}

void showMapping(map<char, char> mapping)
{
    cout << "\nMapping hien tai:\n";
    for (auto p : mapping)
    {
        cout << p.first << " -> " << p.second << endl;
    }
}
int main()
{
    string ciphertext;
    map<char, char> mapping;
    int choice;

    cout << "Nhap ciphertext:\n";
    getline(cin, ciphertext);

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Nhap mapping\n";
        cout << "2. Hien thi mapping\n";
        cout << "3. Ap dung mapping\n";
        cout << "4. Xoa mapping\n";
        cout << "5. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            inputMapping(mapping);
            break;

        case 2:
            showMapping(mapping);
            break;

        case 3:
            cout << "\nKet qua:\n";
            cout << applyMapping(ciphertext, mapping) << endl;
            break;

        case 4:
            mapping.clear();
            cout << "Da xoa mapping!\n";
            break;

        case 5:
            cout << "Thoat chuong trinh.\n";
            break;

        default:
            cout << "Chon sai!\n";
        }

    } while (choice != 5);

    return 0;
}
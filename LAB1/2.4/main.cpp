#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

char matrix[5][5];

void TaoMaTran(string key)
{
    bool used[26] = {false};
    string newKey = "";

    for (char c : key)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (c == 'J') c = 'I';

            if (!used[c - 'A'])
            {
                used[c - 'A'] = true;
                newKey += c;
            }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J') continue;

        if (!used[c - 'A'])
        {
            used[c - 'A'] = true;
            newKey += c;
        }
    }

    int k = 0;
    for (char c : newKey)
    {
        matrix[k / 5][k % 5] = c;
        k++;
    }
}

void printMatrix()
{
    cout << "\nMa tran Playfair:\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void findPos(char c, int &r, int &c2)
{
    if (c == 'J') c = 'I';

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c)
            {
                r = i;
                c2 = j;
                return;
            }
}

string prepare(string text)
{
    string temp = "";

    for (char c : text)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (c == 'J') c = 'I';
            temp += c;
        }
    }

    string res = "";

    for (size_t i = 0; i < temp.length(); i++)
    {
        res += temp[i];

        if (i + 1 < temp.length() && temp[i] == temp[i + 1])
        {
            res += 'X';
        }
    }

    if (res.length() % 2 != 0)
        res += 'X';

    return res;
}

string cleanCipher(string text)
{
    string res = "";

    for (char c : text)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (c == 'J') c = 'I';
            res += c;
        }
    }

    return res;
}

string encrypt(string text)
{
    string res = "";

    for (size_t i = 0; i + 1 < text.length(); i += 2)
    {
        char a = text[i], b = text[i + 1];
        int r1, c1, r2, c2;

        findPos(a, r1, c1);
        findPos(b, r2, c2);

        if (r1 == r2)
        {
            res += matrix[r1][(c1 + 1) % 5];
            res += matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            res += matrix[(r1 + 1) % 5][c1];
            res += matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            res += matrix[r1][c2];
            res += matrix[r2][c1];
        }
    }

    return res;
}

string decrypt(string text)
{
    text = cleanCipher(text);

    string res = "";

    for (size_t i = 0; i + 1 < text.length(); i += 2)
    {
        char a = text[i], b = text[i + 1];
        int r1, c1, r2, c2;

        findPos(a, r1, c1);
        findPos(b, r2, c2);

        if (r1 == r2)
        {
            res += matrix[r1][(c1 + 4) % 5];
            res += matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            res += matrix[(r1 + 4) % 5][c1];
            res += matrix[(r2 + 4) % 5][c2];
        }
        else
        {
            res += matrix[r1][c2];
            res += matrix[r2][c1];
        }
    }

    return res;
}

void printPairs(string text)
{
    cout << "Cac cap ky tu: ";
    for (size_t i = 0; i + 1 < text.length(); i += 2)
    {
        cout << text[i] << text[i + 1] << " ";
    }
    cout << endl;
}

int main()
{
    string key, text;
    int choice;

    cout << "Nhap khoa: ";
    getline(cin, key);

    TaoMaTran(key);
    printMatrix();

    do
    {
        cout << "\n1. Ma hoa\n2. Giai ma\n3. Thoat\nChon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            cout << "Nhap plaintext: ";
            getline(cin, text);

            string prepared = prepare(text);
            cout << "Sau chuan hoa: " << prepared << endl;
            printPairs(prepared);

            cout << "Ciphertext: " << encrypt(prepared) << endl;
        }
        else if (choice == 2)
        {
            cout << "Nhap ciphertext: ";
            getline(cin, text);

            cout << "Plaintext: " << decrypt(text) << endl;
        }

    } while (choice != 3);

    return 0;
}

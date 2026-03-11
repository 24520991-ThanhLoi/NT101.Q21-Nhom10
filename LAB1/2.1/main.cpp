#include <iostream>
#include <string>

using namespace std;

string encrypt(string text,int key)
{
    key=key%26;
    string result ="";
    for(char c:text)
    {
        if(isalpha(c))
        {
            char base;
            if(isupper(c))
                base ='A';
            else
                base ='a';
            result +=(c-base+key)%26+base;
        }
        else result +=c;
    }
    return result;
}

string decrypt(string text,int key)
{
    return encrypt(text,26-key);
    
}

int tinhdiem(string text)
{
    string a="ETAOINSRHLDCU";
    int diem=0;
    for(char c:text)
    {
        c=toupper(c);
        size_t pos=a.find(c);
        if(pos != string::npos)
        {
            diem +=(a.length()-pos);
        }
        
    }
    return diem;
}

void bruteForce(string ciphertext)
{
    int maxDiem=-1;
    int bestKey=0;
    string bestText="";
    for(int key=0;key<26;key++)
    {
        string decrypted =decrypt(ciphertext,key);
        int diem =tinhdiem(decrypted);
        if(diem >maxDiem)
        {
            maxDiem=diem;
            bestKey=key;
            bestText=decrypted;
        }
    }
    cout<<"\nPlaintext: "<<bestText<<endl;
    cout<<"Key: "<<bestKey<<endl;
}

int main()
{
    string text;
    int key;
    int choice;
    do
    {
        cout<<"\nChon chuc nang:"<<endl;
        cout<<"1. Ma hoa"<<endl;
        cout<<"2. Giai Ma"<<endl;
        cout<<"3. Brute Force"<<endl;
        cout<<"4. Exit"<<endl;
        cin>>choice;
        cin.ignore();

        switch(choice)
        {
            case 1:
                cout<<"Plaitext: ";
                getline(cin,text);
                cout<<"Key: ";
                cin>>key;
                cout<<"Ciphertext: "<<encrypt(text,key)<<endl;
                break;
            case 2:
                cout<<"Ciphertext: ";
                getline(cin,text);
                cout<<"Key: ";
                cin>>key;
                cout<<"Plaintext: "<<decrypt(text,key);
                break;
            case 3:
                cout<<"Ciphertext: ";
                getline(cin,text);
                bruteForce(text);
                break;
            case 4:
                cout<<"Thoai khoi chuong trinh";
                break;
            default:
                cout<<"Chon lai chuc nang"<<endl;
        }
    } while (choice !=4 );
    





    return 0;
}
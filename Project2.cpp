#include <iostream>
#include<string>
#include <fstream>
#include <vector>
#define SIZE 26
using namespace std;

struct NODE
{
    NODE* next[SIZE];
    bool end;
};

int char_to_int(char c)
{
    return c - 'a';
}

char int_to_char(int i)
{
    return i + 'a';
}

NODE* createNode()
{
    NODE* p = new NODE;
    for (int i = 0; i < SIZE; i++)
    {
        p->next[i] = NULL;
    }
    p->end = false;
    return p;
}

void Insertion(NODE* pRoot, string key)
{
    for (int i = 0; i < key.length(); i++)
    {
        int c = char_to_int(key[i]);
        if (pRoot->next[c] == NULL)
        {
            pRoot->next[c] = createNode();
        }
        pRoot = pRoot->next[c];
    }
    pRoot->end = true;
}

void readInput(int& n, string& s)
{
    getline(cin, s);
    int dem = s.length();
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            dem--;
            s[i] = s[i + 1];
            for (int j = i + 1; j < s.length(); j++)
            {
                s[j] = s[j + 1];
            }
        }
    }
    n = dem;
}

vector<string> readDict(NODE*& pRoot, const char *fileName)
{
    ifstream fi(fileName);
    string s;
    vector<string> V;
    if (fi.is_open() == false)
    {
        cout << "Can't read the file" << endl;
        return V;
    }
    while (!fi.eof())
    {
        getline(fi, s);
        Insertion(pRoot, s);
        V.push_back(s);
    }
    fi.close();
    return V;
}

bool checkDuplicate(string s, string str, int n)
{
    int a[SIZE] = { 0 };
    int b[SIZE] = { 0 };
    for (int i = 0; i < n; i++)
    {
        int c = char_to_int(s[i]);
        a[c]++;
    }
    for (int i = 0; i < str.length(); i++)
    {
        int c = char_to_int(str[i]);
        b[c]++;
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (b[i] > a[i])
            return false;
    }
    return true;
}

void searchWord(NODE* pRoot, bool HASH[], string str, vector<string>& V, string s, int n)
{
    if (pRoot->end == true && str.size() >= 3 && checkDuplicate(s, str, n))
    {
        V.push_back(str);
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (HASH[i] && pRoot->next[i])
        {
            char c = int_to_char(i);
            searchWord(pRoot->next[i], HASH, str + c, V, s, n);
        }
    }
}

void printValidWord(vector<string>& V, string s , NODE *pRoot, int n)
{
    bool HASH[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        HASH[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        HASH[char_to_int(s[i])] = true;
    }
    NODE* temp = pRoot;
    string str = "";
    for (int i = 0; i < SIZE; i++)
    {
        if (HASH[i] && temp->next[i])
        {
            str = str + int_to_char(i);
            searchWord(pRoot->next[i], HASH, str, V, s, n);
            str = "";
        }
    }
    cout << V.size() << endl;
    for (string i : V) {
        cout << i << endl;
    }
}

int main()
{
    string s;
    vector<string> V;
    int n = 0;
    NODE* pRoot = createNode();
    const char* fileName = "Dic.txt";
    vector<string> Vi=readDict(pRoot,fileName);

    if (Vi.empty())
        return 0;

    readInput(n, s);
    printValidWord(V, s, pRoot, n);
    return 0;
}
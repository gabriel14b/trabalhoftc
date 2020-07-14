#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include <vector>
#include <stdio.h>

using namespace std;

class afd
{
    char lr[100];
    int i = 0, est = 0, tran = 0, fecha = 0, ponto = 0;

    std::vector<int>* final = new std::vector<int>();
    std::vector<int>* from = new std::vector<int>();
    std::vector<int>* to = new std::vector<int>();
    std::vector<char>* input = new std::vector<char>();

    std::vector<char>* entre = new std::vector<char>();
    std::vector<int>* par = new std::vector<int>();
    std::vector<int>* ver = new std::vector<int>();

    std::vector<char>* dir = new std::vector<char>();
    std::vector<char>* esq = new std::vector<char>();

public:
    afd(char a, int k) { lr[k] = a; }
    void lerAfd(char a, int k);
    void autom();
    void zer();
    void um();
    void apar();
    void uni(int k);
    void inter();
    void sub();
    void verSenten();
};

void afd::lerAfd(char a, int k)
{
    lr[k] = a;
    if (a == '+' || a == '-' || a == '.')
    {
        ver->push_back(2);
    }
    else
    {
        ver->push_back(1);
    }
}

void afd::autom()
{
    est = 1;
    final->push_back(false);
    tran = 0;

    for  (i = 1; i < 100; i++)
    {
        if (lr[i] == '1')
            um();
        if (lr[i] == '0')
            zer();
        if (lr[i] == '(')
            apar();
    }

    ofstream myfile;
    myfile.open("AFD.txt");
    myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><!--Created with JFLAP 6.4.--><structure>&#13;\n";
    myfile << "\t<type>fa</type>&#13;\n";
    myfile << "\t<automaton>&#13;\n";
    myfile << "\t\t<!--The list of states.-->&#13;\n";

    for (i = 0; i < est; i++)
    {
        myfile << "\t\t<state id=\"" << i << "\" name=\"q" << i << "\">&#13;\n";
        myfile << "\t\t\t<x>0.0</x>&#13;\n";
        myfile << "\t\t\t<y>0.0</y>&#13;\n";
        if (i == 0)
        {
            myfile << "\t\t\t<initial/>&#13;\n";
        }
        if (final->at(i))
        {
            myfile << "\t\t\t<final/>&#13;\n";
        }
        myfile << "\t\t</state>&#13;\n";
    }

    myfile << "\t\t<!--The list of transitions.-->&#13;\n";

    for (i = 0; i < tran; ++i)
    {
        myfile << "\t\t<transition>&#13;";
        myfile << "\n\t\t\t<from>" << from->at(i) << "</from>&#13;";
        myfile << "\n\t\t\t<to>" << to->at(i) <<"</to>&#13;";
        myfile << "\n\t\t\t<read>" << input->at(i) <<"</read>&#13;";
        myfile << "\n\t\t</transition>&#13;\n";
    }

    myfile << "\t</automaton>&#13;\n";
    myfile << "</structure>\n";

    myfile.close();


}

void afd::zer()
{
    int k = 0;
    if (lr[i - 1] == '(' || lr[i - 1] == '+' || lr[i - 1] == '.' || lr[i - 1] == '-');
    else if (lr[i + 1] == '*')
    {
        tran++;
        if (lr[i + 2] == '/')
        {
            final->push_back(true);
        }
        final->push_back(false);
        from->push_back(est - 1);
        to->push_back(est - 1);
        input->push_back('0');
    }
    else
    {
        tran++;
        if (lr[i + 1] == '/')
        {
            final->push_back(true);
        }
        final->push_back(false);
        from->push_back(est - 1);
        to->push_back(est);
        input->push_back('0');
        est++;
    }
    i++;

    if (lr[i] == '1')
        um();
    if (lr[i] == '0')
        zer();
    if (lr[i] == '(')
        apar();
    if (lr[i] == '+')
        uni(k);
    if (lr[i] == '.')
        inter();
    if (lr[i] == '-')
        sub();
}

void afd::um()
{
    int k = 0;
    if (lr[i - 1] == '(' || lr[i - 1] == '+' || lr[i - 1] == '.' || lr[i - 1] == '-');
    else if (lr[i + 1] == '*')
    {
        tran++;
        if (lr[i + 2] == '/')
        {
            final->push_back(true);
        }
        final->push_back(false);
        from->push_back(est - 1);
        to->push_back(est - 1);
        input->push_back('1');
    }
    else
    {
        tran++;
        if (lr[i + 1] == '/')
        {
            final->push_back(true);
        }
        final->push_back(false);
        from->push_back(est - 1);
        to->push_back(est);
        input->push_back('1');
        est++;
    }
    i++;

    if (lr[i] == '1')
        um();
    if (lr[i] == '0')
        zer();
    if (lr[i] == '(')
        apar();
    if (lr[i] == '+')
        uni(k);
    if (lr[i] == '.')
        inter();
    if (lr[i] == '-')
        sub();
}

void afd::apar()
{
    int j = 0, k = 0;

    par->push_back(i);
    ver->at(i - 1) = 0;
    i++;
    j = i;

    while (lr[i] != ')')
    {
        if (lr[i] == '(')
        {
            apar();
        }
        entre->push_back(lr[i]);
        i++;
    }

    ver->at(i - 1) = 0;

    if (lr[i+1] == '*')
    {
        fecha = 1;
        ver->at(i) = 0;
    }
    if (lr[i + 2] == '/')
    {
        ponto = 1;
        ver->at(i) = 0;
    }


    for (k = par->back(); k < i; k++)
    {
        if (ver->at(k - 1) == 2)
        {
            uni(k);
        }
    }
    for (k = par->back(); k < i; k++)
    {
        if (ver->at(k - 1) == 1)
        {
            if (lr[i] == '1')
                um();
            if (lr[i] == '0')
                zer();
        }
    }
    
    par->pop_back();
    i++;
    fecha = 0;
}

void afd::uni(int k)
{
    int ini, fin, k1, feste, festd, festef, festdf;
    char ftrane = 'a', ftrand;

    ini = est;
    k1 = k;
    ver->at(k - 1) = 0;

    for (k; ver->at(k) == 1; k++)
    {
        tran++;
        if (ponto == 1 && ver->at(k+1) == 0)
        {
            final->push_back(true);
        }
        else
            final->push_back(false);
        dir->push_back(lr[k + 1]);
        from->push_back(est - 1);
        to->push_back(est);
        festdf = est;
        if (k == k1)
        {
            festd = est;
            ftrand = lr[k + 1];
        }
        input->push_back(lr[k + 1]);
        est++;
        ver->at(k) = 0;
    }
    fin = est;
    k = k1;
  
    for (k; ver->at(k - 2) == 1; k--)
    {
        tran++;
        esq->push_back(lr[k - 1]);
        if (k == k1)
        {
            feste = est;
            from->push_back(ini - 1);
        }
        else
            from->push_back(est - 1);
        to->push_back(est);
        if (ponto == 1 && ver->at(k - 3) == 0)
        {
            final->push_back(true);
        }
        else
            final->push_back(false);
        festef = est;
        est++;
        ver->at(k) = 0;
    }
    for (k; k < k1; k++)
    {
        input->push_back(esq->at(k1-k-1));
        if (ftrane == 'a')
        {
            ftrane = esq->at(k1 - k - 1);
        }
    }

    if (fecha == 1)
    {
        tran++;
        tran++;
        tran++;
        tran++;

        from->push_back(festef);
        to->push_back(feste);
        input->push_back(ftrane);

        from->push_back(festdf);
        to->push_back(festd);
        input->push_back(ftrand);

        from->push_back(festef);
        to->push_back(festd);
        input->push_back(ftrand);

        from->push_back(festdf);
        to->push_back(feste);
        input->push_back(ftrane);
    }

    i++;

    if (lr[i] == '1')
        um();
    if (lr[i] == '0')
        zer();
    if (lr[i] == '(')
        apar();
    if (lr[i] == '+')
        uni(k);
    if (lr[i] == '.')
        inter();
    if (lr[i] == '-')
        sub();
}

void afd::inter()
{
    int k = 0;
    cout << "inter";
    i++;

    if (lr[i] == '1')
        um();
    if (lr[i] == '0')
        zer();
    if (lr[i] == '(')
        apar();
    if (lr[i] == '+')
        uni(k);
    if (lr[i] == '.')
        inter();
    if (lr[i] == '-')
        sub();
}

void afd::sub()
{
    int k = 0;
    cout << "sub";
    i++;

    if (lr[i] == '1')
        um();
    if (lr[i] == '0')
        zer();
    if (lr[i] == '(')
        apar();
    if (lr[i] == '+')
        uni(k);
    if (lr[i] == '.')
        inter();
    if (lr[i] == '-')
        sub();
}

void afd::verSenten()
{
    int j =0, atual, sent = 1;
    char ch, op;
    bool ver = true;

    atual = from->at(0);

    cout << "\n\n\n";
    fstream sen("sentencas.txt", fstream::in);
    while (sen >> noskipws >> ch)
    {
        cout << ch;
        if (ver == true && ch != '\n')
        {
            for (j = 0; j < tran; j++)
            {
                ver = false;
                if (from->at(j) == atual && input->at(j) == ch)
                {
                    atual = to->at(j);
                    j = tran;
                    ver = true;
                }
            }
        }
        else if (ver == true && ch == '\n' && final->at(atual) == 1)
        {
            cout << "Sentenca numero " << sent << " pertence a linguagem!\n\n";
            sent++;
            atual = from->at(0);
        }
        else if (ver == false && ch == '\n' || ch == '\n' && final->at(atual) == 0)
        {
            cout << "Sentenca numero " << sent << " nao pertence a linguagem!\n\n";
            sent++;
            atual = from->at(0);
            ver = true;
        }
    }
    if (ver == true)
    {
        cout << "\nSentenca numero " << sent << " pertence a linguagem!\n\n";
    }
    else if (ver == false)
    {
        cout << "\nSentenca numero " << sent << " nao pertence a linguagem!\n\n";
    }

}

int main() {


    char ch = ' ';
    char lr[100];
    int i = 1, ver = 0;
    fstream fin("Read.jff", fstream::in);

    afd ling(ch, i);
    while (fin >> noskipws >> ch) {

        if (ver == 3 && ch == '<')
            ver = 4;

        if (ver == 0 && ch == 'o')
            ver++;
        else if (ver == 1 && ch == 'n')
            ver++;
        else if (ver == 2 && ch == '>')
            ver++;
        else if (ver == 3)
        {
            cout << ch;
            ling.lerAfd(ch, i);
            i++;
        }
        else if (ver == 4);
        else
            ver = 0;
    }

    ling.lerAfd('/', i);

    ling.autom();

    ling.verSenten();
    
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;


#define CDFT "\033[0m"  //default
#define CBLD "\033[1m"  //bold
#define CBLK "\033[30m" //black
#define CRED "\033[31m" //red
#define CGRN "\033[32m" //green
#define CYLW "\033[33m" //yellow
#define CBLU "\033[34m" //blue

#define C_NB_CHAR_MAX_PER_LINE 32

void fnPrintHelp(int argc, char* argv[])
{
    cout << "Utilisation de \'Cowsays\':" << endl;
    cout << "  " << argv[0] << " \"<string>\" ( rien de plus, rien de moins ;D )" << endl;
}

string fnSlurp(ifstream& in) {
    stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}


void fnDrawAnimal(string const str)
{
    if(str == "dog")
    {

    }
    else
    {
        cout << "           ^__^                " << endl;
        cout << "           (oo)\\_______       " << endl;
        cout << "           (__)\\       )\\/\\ " << endl;
        cout << "               ||----w |       " << endl;
        cout << "       _v_v____||_____||__v_   " << endl;
        cout << endl;
    }
}

vector<string> fnSplitString(string str)
{
    vector<string> words;

    std::string delimiter = " ";

    size_t last = 0;
    size_t next = 0;
    while ((next = str.find(delimiter, last)) != string::npos)
    {
        //cout << str.substr(last, next-last) << endl;
        words.push_back(str.substr(last, next-last));
        last = next + 1;
    }
    words.push_back(str.substr(last, next-last));
    //cout << str.substr(last) << endl;

    return words;
}

void fnBuildString(string &strLine)
{
    bool bFlag = false;
    while( C_NB_CHAR_MAX_PER_LINE != strLine.length())
    {
        if(bFlag)
        {
            strLine.insert(0, " ");
            bFlag = false;
        }
        else
        {
            strLine += " ";
            bFlag = true;
        }
    }

    cout << "||";
    cout << strLine.c_str();
    cout << "||" << endl;
}

void fnDrawBubble(string str)
{
    vector<string> tokens = fnSplitString(str);

    cout << endl;

    if(str.length() < C_NB_CHAR_MAX_PER_LINE)
    {
        cout << " /";
        for(unsigned int i = 0; i < str.length()+2; i++)
        {
            cout << "=";
        }
        cout << "\\" << endl;
        cout << "|| " << str.c_str() << " ||" << endl;
        cout << " \\";
        for(unsigned int i = 0; i < str.length()+2; i++)
        {
            cout << "=";
        }
        cout << "/" << endl;
    }
    else
    {
        cout << " /";
        for(unsigned int i = 0; i < C_NB_CHAR_MAX_PER_LINE; i++)
        {
            cout << "=";
        }
        cout << "\\" << endl;

        vector<string> lines;
        string strLine = "";

        //Ecriture du texte
        for(string &word : tokens)
        {
            if(strLine.length() + word.length() < C_NB_CHAR_MAX_PER_LINE)
            {
                strLine += " ";
                strLine += word;
            }
            else
            {
                fnBuildString(strLine);
                strLine.clear();
                strLine += " ";
                strLine +=word;
            }
        }

        fnBuildString(strLine);

        cout << " \\";
        for(unsigned int i = 0; i < C_NB_CHAR_MAX_PER_LINE; i++)
        {
            cout << "=";
        }
        cout << "/" << endl;
    }

    cout << "        \\/" << endl;
    cout << "         \\" << endl;
    fnDrawAnimal("cow");

}

int main(int argc, char* argv[])
{
    string strSentence = "";
    if(argc == 2)
    {
        strSentence = string(argv[1]);
    }
    else if( strcmp(argv[1], "-f") == 0 )
    {
        if(argc == 3)
        {
            std::ifstream ifs(argv[2]);
            strSentence = fnSlurp(ifs);
            if(strSentence[strSentence.length()-1] == '\n')
            {
                strSentence.pop_back();
            }
        }
        else
        {
            cout << CRED << "ERREUR: Argument manquant avec '-f'" << CDFT << endl;
            fnPrintHelp(argc, argv);
            exit(1);
        }
    }
    else
    {
        cout << CRED << "ERREUR: Nombre d'arguments inattendu !" << CDFT << endl;
        fnPrintHelp(argc, argv);
        exit(1);
    }

    fnDrawBubble(strSentence);

    return 0;
}

#include "../demos/demo2.cpp"



using namespace std;

int main()
{
    ofstream l;
    cls
    string outputfile = "logs.out";
    setLogFile(outputfile);
    
    cout << MAGENTA << "\n[*]WILKOMMEN ZUM" << BOLDCYAN << " ANDREINET"
    << MAGENTA << "\n[+]Letztes Update:" <<BOLDWHITE << " 02.06.2024"
    << MAGENTA << "\n[+]Version:" << BOLDWHITE << " 1.0.0"
    << MAGENTA << "\n[+]Siehe Github fur mehrere Informationen:" << BOLDWHITE << " https://github.com/Shurkel/PrjSclNN"
    << YELLOW << "\n[ENTER]" << RESET << " um fortzufahren";
    cin.get();
    cls
    runDemo2(outputfile); 

    
}
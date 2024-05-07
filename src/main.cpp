#include "../demos/demo2.cpp"


using namespace std;
int main()
{
    cls
    string outputfile = "demo2_log.out";
    setLogFile(outputfile);
    l<<"[+] Starting demo1\n";
    l.flush();
    runDemo2(outputfile); 

    
}
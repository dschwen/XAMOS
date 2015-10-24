#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

std::istream & getline(std::istream & in, std::string & out)
{
char c;
while(in.get(c).good()) {
if(c == '\n') {
c = in.peek();
if(in.good()) {
if(c == '\r') {
in.ignore();
}
}
break;
}
out.append(1,c);
}
return in;
}

int correct(string fn)
{
ifstream myReadFile;
myReadFile.open(fn.c_str());


string output((std::istreambuf_iterator<char>(myReadFile)),
                 std::istreambuf_iterator<char>());


ofstream outfile;
outfile.open(("corrected/"+fn).c_str());

std::istringstream strm(output);
//std::istringstream strm("alpha\nbeta\n\r...\n\romega\n\n");
for(int i = 0; strm.good(); ++i)
{
std::string line;
getline(strm,line);
//std::cout<<i<<"\t"<<line<<std::endl;

if (line.length() > 0)
{
    std::string::iterator it = line.end() - 1;
    if (*it == '\r')
    {
         line.erase(it);
    }
}

//std::cout<<line<<std::endl;
outfile<<line<<std::endl;
}
outfile.close();
myReadFile.close();
return 0;
}

int main()
{
   correct("ActiveObject.h");
   correct("CommandWrapper.h");
   correct("Dumper.h");
   correct("ExpressionReturn.h");
   correct("Game.h");
   correct("Interpreter.h");
   correct("main.h");
   correct("MequaScript.h");
   correct("MultiExpressionReturn.h");
   correct("Mytype.h");
   correct("Mytypearray.h");
   correct("Parser.h");
   correct("TheTokens.h");
   correct("TokeniserReturn.h");
   correct("ActiveObject.cpp");
   correct("CommandWrapper.cpp");
   correct("Dumper.cpp");
   correct("Interpreter.cpp");
   correct("main.cpp");
   correct("MequaScript.cpp");
   correct("Mytype.cpp");
   correct("Mytypearray.cpp");
   correct("Parser.cpp");
   correct("TheTokens.cpp");

   return 0;
}

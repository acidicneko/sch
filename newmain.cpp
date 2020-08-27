#include <iostream>
#include <fstream>
using namespace std;

//global variables used by functions
string token, ctl, globalvar;
string vartoken;

//tokenizing the recived string
void tokenize(string line)
{
	string tok, str, temp, cmd, vname, value;
	int bracket = 0;
	int pair = 0;
	int set = 0;
	for (int i = 0; i < line.length(); i++)
	{
		tok += line[i];
		if (tok == "<")
		{
			pair = 1;
			bracket = 1;
			tok = "";
		}
		else if (tok == ">")
		{
			if (bracket == 1)
			{
				bracket = 0;
				tok = "";
				if (set == 0)
				{
					temp = str;
					str = "";
					set = 1;
				}
				else if (set == 1)
				{
					pair = 0;
					set = 0;
					if (str == temp)
					{
						token.append(str + ":" + cmd + "#");
						
						str = "";
						cmd = "";
					}
					str = "";
				}
			}
		}
		else if (tok == "(")
		{
			pair = 1;
			bracket = 1;
			tok = "";
		}
		else if (tok == ")")
		{
			if (bracket == 1)
			{
				bracket = 0;
				tok = "";
				if (set == 0)
				{
					temp = str;
					str = "";
					set = 1;
				}
				else if (set == 1)
				{
					pair = 0;
					set = 0;
					if (str == temp)
					{
						vartoken.append(str + ":" + cmd + "#");
						
						str = "";
						cmd = "";
					}
					str = "";
				}
			}
		}
		else if (bracket == 1)
		{
			str += tok;
			tok = "";
		}
		else if (tok == " ")
		{
			if (pair == 0)
			{
				tok = "";
			}
			else if (pair == 1)
			{
				tok = " ";
			}
		}
		else if (set == 1)
		{
			cmd += tok;
			tok = "";
		}
	}
}

//find variables
void finder(string line)
{
	string func, tok, cmd;
	int count = 0;
	for (int i = 0; i < vartoken.length(); i++)
	{
		tok += vartoken[i];
		if ( line + ":"== tok)
		{
			count = 1;
			tok = "";
		}
		else if (tok == "#")
		{
			if (count == 1)
			{
				count = 0;
				globalvar = cmd;
				cmd = "";
				tok = "";
			}
			else
			{
				tok = "";
			}
		}
		else if (count == 1)
		{
			cmd += tok;
			tok = "";
		}
		else if(vartoken[i] == '#'){
			tok = "";
		}
	}
}

//the simple command executer^_^
void exec(string cmdl){
	int end = 0;
	int is_var = 0;
	string tok, cmd, var;
	for(int i = 0; i<cmdl.length(); i++){
		tok+=cmdl[i];
		if(tok == ";"){
			end = 1;
            const char *c = cmd.c_str();
            system(c);
			tok = "";
			cmd = "";
			end = 0;
		}
		else if(cmdl[i] == '$'){
			if(is_var == 0){
				is_var = 1;
				tok = "";
			}
			else if(is_var == 1){
				is_var = 0;
				finder(var);
				cmd.append(globalvar);
				globalvar = "";
				var = "";
				tok = "";
			}
		}
		else if(is_var == 1){
			var+=tok;
			tok = "";
		}
		else if(end == 0){
			cmd+=tok;
			tok="";
		}
	}
}

//parser for tokens
void parser(string line)
{
	string tok, cmd;
	int count = 0;
	for (int i = 0; i < token.length(); i++)//reading char by char in a string
	{
		tok += token[i];
		if ( line + ":"== tok)
		{
			count = 1;
			tok = "";
		}
		else if (tok == "#")
		{
			if (count == 1)
			{
				count = 0;
				exec(cmd);
				cmd = "";
				tok = "";
			}
			else
			{
				tok = "";
			}
		}
		else if (count == 1)
		{
			cmd += tok;
			tok = "";
		}
		else if(token[i] == '#'){
			tok = "";
		}
	}
}


//the main function
int main(int argc, char **argv){
    ifstream file;
    string line, ver, to_tokenize;
	if(argc == 2){
		ver = argv[1];
	}
    file.open("codefile");
	if(ver == "--version"){
        cout << "Simple Command Helper\nBuilt by Ayush Yadav\nsch 2.0 (formerly slch)\n";
    }
    else if(!file){
        cout << "no codefile found\nerror:1\n";
    }
    else{
        while(getline(file, line)){//read from file
            to_tokenize.append(line);
        }
        tokenize(to_tokenize);//make tokens
        if(argc == 1){
            cout << "sch requires an argument\n";
            return 1;
        }
        else if(argc == 2){
            cout << "func: " << argv[1] << endl;
            parser(argv[1]);//parse the function name we recieved
        }
        else if(argc >= 3){
            cout << "too many arguments\n";
            return 1;
        }  
    }
    return 0;
}
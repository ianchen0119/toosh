#include "toosh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <sstream>

void toosh::meow(){
	std::cout <<" 　　　　　 ＿＿  "<< std::endl;
	std::cout <<"　　　　／＞　　フ"<< std::endl;
	std::cout <<"　　　　| 　_  _ l"<< std::endl;
	std::cout <<" 　　　／` ミ＿xノ"<< std::endl;
	std::cout <<"　 　 /　　　 　 |"<< std::endl;
	std::cout <<"　　 /　 ヽ　　 ﾉ "<< std::endl;
	std::cout <<" 　 │　　|　|　|  "<< std::endl;
	std::cout <<"／￣|　　 |　|　| "<< std::endl;
	std::cout <<"| (￣ヽ＿_ヽ_)__) "<< std::endl;
	std::cout <<"＼二つ		   "<< std::endl;

}

toosh::toosh(){
    this->meow();
}

void toosh::prompt(){
  write(2, "$ ", 2);
}

void toosh::splitBySpace(std::string source, int p){
	std::string temp = "";
    int n = (p)?(p):(source.length());
	for(int i = 0; i < n; ++i){
	    if(source[i]==' '){
		this->parse.push_back(temp);
		temp = "";
	    }
	    else{
		temp.push_back(source[i]);
	    }
		
	}
	this->parse.push_back(temp);	
}

int toosh::hasPipe(std::string input){

    int returnVal = input.find("|");

    return returnVal;
}

int toosh::execCmd(std::string input, int t){
    int pipefds[2] = {0, 0};
    int outfd = 0;
    std::string childCmd;
    while (true)
    {
        if(input == ""){
            std::cout << std::endl;
            continue;
        }

        // this->hasInderect();

        // int p = this->hasPipe(input, pipefds, outfd);

        // if(p != std::npos){
            // has pipe
            // pipe(pipefds);
            // outfd = pipefds[1];
        //     this->splitBySpace(input, p);
        // }else{
        //     this->splitBySpace(input, 0);
        // }
        
        this->splitBySpace(input, 0);

        int i = 0;
        for(auto val: this->parse){
            this->execArg[i++] = strdup(val.c_str());
        }
        pid_t pid = fork();
        if(pid){
            int status;
            waitpid(pid, &status, 0 );
            return 0;
        }else{
            execvp(execArg[0], execArg);
            exit(123);
        }
    }  
}

void toosh::run(){
  
  std::string input;
  while (true)
  {
    this->parse.clear();
    
    this->prompt();

    getline(std::cin, input);

    this->execCmd(input, 0);

  }
}
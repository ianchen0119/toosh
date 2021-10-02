#include "toosh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <sstream>

void toosh::meow(){
	std::cout <<" 　　　　　 ＿＿  "<< std::endl;
	std::cout <<"　　　　 ／＞　　フ"<< std::endl;
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
    this->currentCmd = 0;
    this->lastCmd = 0;
    write(2, "$ ", 2);
}

void toosh::parser(std::string source){
	std::string temp = "";
    // std::cout << source.length() << std::endl;

	for(int i = 0; i < source.length(); ++i){
	    if(source[i]==' '){
            if(temp != ""){
                this->parse[this->lastCmd].push_back(temp);
		        temp = "";
            }
            continue;
	    }
        if(source[i]=='|'){
            this->lastCmd++;
            continue;
        }
        // std::cout << temp << std::endl;
		temp.push_back(source[i]);
		
	}
	this->parse[this->lastCmd].push_back(temp);	
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
        
        this->parser(input);

        while(this->currentCmd <= this->lastCmd){
            int i = 0;
            
            for(auto val: this->parse[this->currentCmd]){
                this->execArg[i++] = strdup(val.c_str());
            }

            this->execArg[i] = NULL;

            this->parse[this->currentCmd].clear();

            this->currentCmd++;

            pid_t pid = fork();

            if(pid){
                wait(0);
                // return 0;
            }else{
                if(this->lastCmd > 0 && this->currentCmd == 1){
                    // change output
                    pipe(pipefds);
                    std::cout << "a" << pipefds[1]<< std::endl;
                    dup2(pipefds[1], 1); /* dup write fd to stdout */
                    // close(pipefds[1]);   /* close write fd */
                }
                if(this->lastCmd > 0 && this->currentCmd > 1){
                    std::cout << "b" << pipefds[0] << std::endl;
                    dup2(pipefds[0], 0);
                    // close(pipefds[0]);
                }
                execvp(execArg[0], execArg);
                // todo: clear execArg
                exit(123);
            }
        }
        return 0;
    }  
}

void toosh::run(){
  
  std::string input;
  while (true)
  {
    this->prompt();

    getline(std::cin, input);

    this->execCmd(input, 0);

  }
}
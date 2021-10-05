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

		temp.push_back(source[i]);
		
	}
	this->parse[this->lastCmd].push_back(temp);	
}

int toosh::execCmd(std::string input){
    int pipefds[2] = {0, 0};
    int outfd = 0;
    pid_t pid;
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

            this->parse[this->currentCmd++].clear();

            if(this->currentCmd <= this->lastCmd){
                /* Not a last command (if has a pipe) */
                pipe(pipefds);
            }

            pid = fork();

            if(pid){
                std::cout << "[init] child pid:" << pid << std::endl;
                // waitpid(pid, NULL, 0);
                wait(0);

                if(this->currentCmd <= this->lastCmd){
                    outfd = pipefds[0];
                }
                std::cout << "[finished] child pid:" << pid << std::endl;
            }else{

                if(this->lastCmd > 0 && this->currentCmd == 1){
                    /* first command (if has a pipe) */
                    dup2(pipefds[1] ,1);
                    close(pipefds[1]);
                }

                if(this->currentCmd <= this->lastCmd){
                    dup2(outfd ,0);
                    close(outfd);
                    dup2(pipefds[1] ,1);
                    close(pipefds[1]);       
                }

                if(outfd && this->currentCmd > this->lastCmd){
                    /* The last command (if has a pipe) */
                    dup2(outfd, 0); // stdin
                    close(outfd);
                }

                execvp(this->execArg[0], this->execArg);
                exit(0);
            }
        }
        break;
    }  
    return 0;
}

void toosh::run(){
  
  std::string input;
  while (true)
  {
    this->prompt();

    getline(std::cin, input);

    this->execCmd(input);

  }
}
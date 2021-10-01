#include "toosh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <sstream>

void toosh::splitBySpace(std::string source){
	std::string temp = "";
	for(int i = 0; i < source.length(); ++i){
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


void toosh::prompt(){
  write(2, "$ ", 2);
}

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

void toosh::run(){
  this->meow();
  while (true)
  {
    this->parse.clear();
    
    this->prompt();

    getline(std::cin, this->cmd[0]);

    if(this->cmd[0] == ""){
	std::cout << std::endl;
    	continue;
    }

    this->splitBySpace(this->cmd[0]);
    
    int i = 0;
    
    for(auto val: this->parse){
      std::cout << val << std::endl;
      this->execArg[i++] = strdup(val.c_str());
    }
    
    pid_t pid = fork();
    
    if(pid){
      int status;
      waitpid(pid, &status, 0 );
    }else{
      execvp(execArg[0], execArg);
      exit(123);
    }
  }  
}

int main(){
  toosh instance;
  instance.run();
  return 0;
}


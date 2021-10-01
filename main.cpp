#include "toosh.h"

#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <sstream>

// gcc info.C -lstdc++

// static inline int is_delim(int c)
// {
//     return c == 0 || c == '|';
// }

// static inline int is_redir(int c)
// {
//     return c == '>' || c == '<';
// }

// static inline int is_blank(int c)
// {
//     return c == ' ' || c == '\t' || c == '\n';
// }

// static int is_special(int c)
// {
//     return is_delim(c) || is_redir(c) || is_blank(c);
// }

void toosh::splitBySpace(std::string source){
  std::istringstream in(this->cmd[0]);
  std::string t;
  while (in >> t)
  {
    this->parse.push_back(t);
    std::cout << t << std::endl;
  }
  
}

void toosh::prompt(){
  write(2, "$ ", 2);
}

void toosh::run(){
  while (true)
  {
    this->prompt();
    std::cin >> this->cmd[0];
    this->splitBySpace(this->cmd[0]);
    int i = 0;
    for(auto val: this->parse){
      this->execArg[i] = strdup(val.c_str());
      i++;
    }
    pid_t pid = fork();
    if(pid){
      int status;
      waitpid(pid, &status, 0 );
      return;
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


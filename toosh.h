#ifndef TOOSH_H
#define TOOSH_H
#include <iostream>
#include <vector>
#include <string>

class toosh
{
private:
  std::string cmd[10];
  std::vector<std::string> parse[10];
  char* execArg[50] = {NULL};
  int lastCmd = 0;
  int currentCmd = 0;
  void prompt();
  void parser(std::string source);
  int hasInderect();
  void meow();
  int execCmd(std::string input);
public:
  toosh();
  ~toosh() = default;
  void run();
};


#endif

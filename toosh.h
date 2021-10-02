#ifndef TOOSH_H
#define TOOSH_H
#include <iostream>
#include <vector>
#include <string>

class toosh
{
private:
  std::string cmd[10];
  std::vector<std::string> parse;
  char* execArg[10] = {NULL};
  int lastCmd = 0;
  int currentCmd = 0;
  void prompt();
  void splitBySpace(std::string source, int p);
  int hasInderect();
  int hasPipe(std::string input);
  void meow();
  int execCmd(std::string input, int t);
public:
  toosh();
  ~toosh() = default;
  void run();
};


#endif

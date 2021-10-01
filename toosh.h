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
  int pipefds[2] = {0, 0};
  int outfd = 0;
  int lastCmd = 0;
  int currentCmd = 0;
  void prompt();
  void splitBySpace(std::string source);
  void meow();
public:
  toosh() = default;
  ~toosh() = default;
  void run();
};


#endif

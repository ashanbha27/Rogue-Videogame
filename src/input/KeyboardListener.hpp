#pragma once

#include <vector>

typedef int Key;

class KeyboardListener
{
private:
  std::vector<void (*)(KeyboardListener*, Key)> callbacks;
  bool active;
  bool running;

public:
  KeyboardListener();
  void listen();
  void start();
  void stop();
  void endGame();
  void addCallback(void (* callback)(KeyboardListener*, Key));
};

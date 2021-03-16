#include <ncurses.h>
#include "KeyboardListener.hpp"

KeyboardListener::KeyboardListener()
{
  active = false;
  running = true;
}

void KeyboardListener::start()
{
  active = true;
}

void KeyboardListener::stop()
{
  active = false;
}

void KeyboardListener::endGame()
{
  running = false;
}

void KeyboardListener::listen()
{
  while (active)
  {
    for (void (* callback)(KeyboardListener*, Key) : callbacks)
    {
      if (!running)
      {
        if (getch() == 'x') callback(this, 'x');
      }
      else
      {
        callback(this, getch());
      }
    }
  }
}

void KeyboardListener::addCallback(void (* callback)(KeyboardListener*, Key))
{
  callbacks.push_back(callback);
}

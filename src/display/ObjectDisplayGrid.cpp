#include <string>
#include <panel.h>
#include "ObjectDisplayGrid.hpp"

ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _topHeight, int _gameHeight, int _bottomHeight)
    : width(_width), topHeight(_topHeight), gameHeight(_gameHeight), bottomHeight(_bottomHeight)
{
  initscr(); // initializes ncurses
  cbreak(); // makes characters typed immediately available, instead of waiting for enter to be pressed
  noecho(); // stops typed characters from being shown, makes it easier to get keypresses
  clear(); // clears the screen to start
  curs_set(0); // hide cursor
  refresh();

  topWindow = newwin(topHeight, width, 0, 0);
  gameWindow = newwin(gameHeight, width, topHeight, 0);
  bottomWindow = newwin(bottomHeight, width, topHeight + gameHeight, 0);
}

void ObjectDisplayGrid::addObjectToGameMap(char ch, int x, int y)
{
  gameMap[std::make_tuple(x, y)] = ch;
  mvwaddch(gameWindow, y, x, ch);
  wrefresh(gameWindow);
}

void ObjectDisplayGrid::restoreObjectFromGameMap(int x, int y)
{
  mvwaddch(gameWindow, y, x, gameMap[std::make_tuple(x, y)]);
  wrefresh(gameWindow);
}

void ObjectDisplayGrid::addObjectToGameDisplay(char ch, int x, int y)
{
  mvwaddch(gameWindow, y, x, ch);
  wrefresh(gameWindow);
}

void ObjectDisplayGrid::writeTopMessage(int posX, int posY, const std::string& message)
{
  mvwprintw(topWindow, posY, posX, message.c_str());
  wrefresh(topWindow);
}

void ObjectDisplayGrid::writeBottomMessage(int posX, int posY, const std::string& message)
{
  mvwprintw(bottomWindow, posY, posX, message.c_str());
  wrefresh(bottomWindow);
}

int ObjectDisplayGrid::getWidth() const
{
  return width;
}

int ObjectDisplayGrid::getTopHeight() const
{
  return topHeight;
}

int ObjectDisplayGrid::getGameHeight() const
{
  return gameHeight;
}

int ObjectDisplayGrid::getBottomHeight() const
{
  return bottomHeight;
}

ObjectDisplayGrid::~ObjectDisplayGrid()
{
  delwin(topWindow);
  delwin(gameWindow);
  delwin(bottomWindow);
  endwin(); // free ncurses data
}

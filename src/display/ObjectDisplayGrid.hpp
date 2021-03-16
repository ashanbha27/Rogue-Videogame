#pragma once

#include <string>
#include <ncurses.h>
#include <panel.h>
#include <unordered_map>

typedef std::tuple<int, int> Position;

struct PositionHash : public std::unary_function<Position, std::size_t>
{
  std::size_t operator()(const Position& p) const
  {
    return std::get<0>(p) ^ std::get<1>(p);
  }
};

struct PositionEqual : public std::binary_function<Position, Position, bool>
{
  bool operator()(const Position& p1, const Position& p2) const
  {
    return std::get<0>(p1) == std::get<0>(p2) && std::get<1>(p1) == std::get<1>(p2);
  }
};

typedef std::unordered_map<Position, char, PositionHash, PositionEqual> PositionMap;

class ObjectDisplayGrid
{
private:
  int width, topHeight, gameHeight, bottomHeight;
  WINDOW* topWindow, * gameWindow, * bottomWindow;
  PositionMap gameMap;

public:
  ObjectDisplayGrid(int _width, int _topHeight, int _gameHeight, int _bottomHeight);
  ~ObjectDisplayGrid();
  void addObjectToGameMap(char ch, int x, int y);
  void restoreObjectFromGameMap(int x, int y);
  void addObjectToGameDisplay(char ch, int x, int y);
  void writeTopMessage(int posX, int posY, const std::string& message);
  void writeBottomMessage(int posX, int posY, const std::string& message);
  int getWidth() const;
  int getTopHeight() const;
  int getGameHeight() const;
  int getBottomHeight() const;
};

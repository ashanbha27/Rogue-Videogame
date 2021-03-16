#include "KeyboardListener.hpp"
#include "XmlGameHandler.hpp"
#include "XmlParser.hpp"

Dungeon* dungeon;

void InputHandler(KeyboardListener* keyboardListener, Key key)
{
  dungeon->clearInfoDisplay();
  switch (key)
  {
    case 'x':
    {
      keyboardListener->stop();
      break;
    }
    case 'h':
    {
      dungeon->getPlayer()->updateMoves();
      dungeon->movePlayer(-1, 0);
      break;
    }
    case 'j':
    {
      dungeon->getPlayer()->updateMoves();
      dungeon->movePlayer(0, -1);
      break;
    }
    case 'k':
    {
      dungeon->getPlayer()->updateMoves();
      dungeon->movePlayer(0, 1);
      break;
    }
    case 'l':
    {
      dungeon->getPlayer()->updateMoves();
      dungeon->movePlayer(1, 0);
      break;
    }
    case 'i':
    {
      if (dungeon->getPlayer()->getInventory()->inventoryHidden())
      {
        dungeon->getPlayer()->getInventory()->openInventory();
      }
      else
      {
        dungeon->getPlayer()->getInventory()->closeInventory();
      }
      break;
    }
    case 'p':
    {
      dungeon->clearInfoDisplay();
      dungeon->pickUpItem();
      break;
    }
    case 'E':
    {
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Are you sure (y/n) ?");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (ch == 'Y' || ch == 'y')
      {
        dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "You have abandoned the dungeon, coward! Be gone!");
        keyboardListener->endGame();
      }
      else if (ch == 'n')
      {
        dungeon->getDisplayGrid()
               ->writeBottomMessage(6, 2, "You have chosen to fight onwards! You will be rewarded for your bravery!");
      }
      break;
    }
    case 'H':
    {
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Press a command to learn more");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (ch == 'c') dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Use this to take off armor");
      else if (ch == 'd')
        dungeon->getDisplayGrid()
               ->writeBottomMessage(
                   6,
                   2,
                   "Use this + item number to drop an item from your inventory");
      else if (ch == 'E') dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Use this to end the game");
      else if (ch == 'i') dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Use this to look to look at inventory");
      else if (ch == 'p')
        dungeon->getDisplayGrid()
               ->writeBottomMessage(6, 2, "Use this to pick up an item from the dungeon floor");
      else if (ch == 'w')
        dungeon->getDisplayGrid()
               ->writeBottomMessage(
                   6,
                   2,
                   "Type the index of the armor in the pack to wear it instead of using 'w'");
      else if (ch == 'r')
        dungeon->getDisplayGrid()
               ->writeBottomMessage(
                   6,
                   2,
                   "Type the index of the scroll in the pack to read it instead of using 'r'");
      else if (ch == 'T')
        dungeon->getDisplayGrid()
               ->writeBottomMessage(
                   6,
                   2,
                   "Type the index of the sword in the pack to wield it instead of using 'T'");
      break;
    }
    case '?':
    {
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()
             ->writeBottomMessage(6, 2, "1. 'c' 2. 'd' 3. 'E' 4. 'i' 5. 'p' 6. 'w' 7. 'r' 8. 'T' 9. 'H'+'command'");
      break;
    }
    case 'T':
    {
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Select armor");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (isdigit(ch)) dungeon->wieldSword(ch - '0');
      break;
    }
    case 'w':
    {
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Select armor");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (isdigit(ch)) dungeon->wearArmor(ch - '0');
      break;
    }
    case 'r':
    {
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Select a scroll");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (isdigit(ch)) dungeon->runItemActions(ch - '0');
      break;
    }
    case 'c':
    {
      dungeon->getPlayer()->getInventory()->openInventory();
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Select weapon or armor to unwield");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (isdigit(ch)) dungeon->takeOffArmor(ch - '0');
      break;
    }
    case 'd':
    {
      dungeon->getPlayer()->getInventory()->openInventory();
      dungeon->clearInfoDisplay();
      dungeon->getDisplayGrid()->writeBottomMessage(6, 2, "Select item to drop");
      char ch = getch();
      dungeon->clearInfoDisplay();
      if (isdigit(ch)) dungeon->dropItem(ch - '0');
      break;
    }
    default: break;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2) return -1;

  XmlGameHandler xmlHandler;
  XmlParser xmlParser(xmlHandler);
  xmlParser.parse(argv[1]);

  dungeon = xmlHandler.getDungeon();
  dungeon->getPlayer()->getInventory()->closeInventory();
  dungeon->display();
  dungeon->topDisplay();
  dungeon->clearInfoDisplay();
  dungeon->infoDisplay();

  KeyboardListener keyboardListener;
  keyboardListener.addCallback(&InputHandler);
  keyboardListener.start();
  keyboardListener.listen();

  return 0;
}

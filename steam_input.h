#pragma once

#include "util.h"

enum ControllerKey {
  C_MENU_UP = (1 << 20),
  C_MENU_DOWN,
  C_MENU_SELECT,
  C_MENU_CANCEL,
  C_ZLEVEL_UP,
  C_ZLEVEL_DOWN,
  C_OPEN_MENU,
  C_SCROLL_NORTH,
  C_SCROLL_SOUTH,
  C_SCROLL_EAST,
  C_SCROLL_WEST,
  C_EXIT_CONTROL_MODE,
  C_TOGGLE_CONTROL_MODE,
  C_CHAT,
  C_FIRE_PROJECTILE,
  C_WAIT,
  C_WALK,
  C_COMMANDS,
  C_CHANGE_Z_LEVEL,
  C_DIRECTION_CONFIRM,
  C_DIRECTION_CANCEL,
};

enum class ControllerJoy {
  WALKING,
  SCROLLING,
  DIRECTION
};

class MySteamInput {
  public:
  using Handle = unsigned long long;
  enum class ActionSet {
    MENU,
    GAME,
    DIRECTION
  };
  enum class GameActionLayer {
    TURNED_BASED,
    REAL_TIME
  };
  struct ActionInfo {
    Handle handle;
    string name;
    ActionSet actionSet;
  };
  map<ActionSet, Handle> actionSets;
  map<GameActionLayer, Handle> gameActionLayers;
  map<ControllerKey, ActionInfo> actionHandles;
  vector<Handle> controllers;
  map<ControllerJoy, Handle> joyHandles;
  void init();
  void setMenuActionSet();
  void setGameActionSet();
  optional<ControllerKey> getEvent();
  bool pressed = false;
  vector<ActionSet> actionSetStack;
  void pushActionSet(ActionSet);
  void popActionSet();
  void setGameActionLayer(GameActionLayer);
  pair<double, double> getJoyPos(ControllerJoy);
  void runFrame();
  queue<ControllerKey> actionQueue;
  bool actionLayerPresent = false;
};

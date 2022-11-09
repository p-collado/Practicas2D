#pragma once
#include"Vec2.h"
class cFont;


class InstanceWord
{
public:
  Vec2 pos;
  float speed;
  cFont* font;
  bool active;
  InstanceWord(cFont* _font);
  InstanceWord();
  ~InstanceWord();
};


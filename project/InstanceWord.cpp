#include "InstanceWord.h"

InstanceWord::InstanceWord(cFont* _font)
{
  font = _font;
  speed = 0.f;
  active = false;
}

InstanceWord::InstanceWord()
{
  font = nullptr;
  speed = 0.f;
  active = false;
}

InstanceWord::~InstanceWord()
{
  delete font;
}

#pragma once
#include "../project/CSprite.h"
#include <array>
#include <vector>

class World
{

private:

   std::array<const ltex_t*, 4> background{};
   std::array<float, 4> backgroundRatio{};
   std::array<Vec2, 4> backgroundSpeed{};
   float clearRed;
   float clearGreen;
   float clearBlue;
   Vec2 cameraPos;
   std::vector<CSprite*> Sprites;


    
public:
    World(
        float clearRed = 0.15f,
        float clearGreen = 0.15,
        float clearBlue = 0.15,
        
        const ltex_t* back0 = nullptr,
        const ltex_t* back1 = nullptr,
        const ltex_t* back2 = nullptr,
        const ltex_t* back3 = nullptr);

    float getClearedRed() const;
    float getClearedGreen() const;
    float getClearedBlue() const;

    float x, y;

    const ltex_t* getBackground(size_t layer) const;
    float getScrollRatio(size_t layer) const;
    void setScrollRatio(size_t layer, float ratio);
    const Vec2& getScrollSpeed(size_t layer) const;
    void setScrollSpeed(size_t layer, Vec2& speed);
    const Vec2& getCameraPosition() const;
    void setCameraPosition( Vec2& pos);

    void addSprite(CSprite& sprite);
    void removeSprite(CSprite& sprite);

    void update(float deltatime);
    void draw(const Vec2& screenSize);
    
};

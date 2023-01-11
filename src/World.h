#pragma once
#include "litegfx.h"
#include "../project/CSprite.h"
#include "../project/Vec2.h"
#include <array>

class World
{

private:
   std::array<const ltex_t*, 4> background{};
   std::array<const float, 4> backgroundSpeed{};
    
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

    const ltex_t* getBackground(size_t layer) const;
    float getScrollRatio(size_t layer) const;
    void setScrollRatio(size_t layer, float ratio);
    const Vec2& getScrollSpeed(size_t layer) const;
    void setScrollSpeed(size_t layer, const Vec2& speed);
    const Vec2& getCameraPosition() const;
    void setCameraPosition(const Vec2& pos);

    void addSprite(CSprite& sprite);
    void removeSprite(CSprite& sprite);

    void update(float deltatime);
    void draw(const Vec2& screenSize);
    
};

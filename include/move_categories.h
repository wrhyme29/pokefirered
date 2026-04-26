#ifndef GUARD_MOVE_CATAGORIES_H
#define GUARD_MOVE_CATAGORIES_H

#include "global.h"

enum
{
    MOVE_CATEGORY_PHYSICAL,
    MOVE_CATEGORY_SPECIAL,
    MOVE_CATEGORY_STATUS,
    MOVE_CATEGORY_COUNT
};

extern const struct SpriteSheet gMoveCategorySpriteSheet;
extern const struct SpritePalette gMoveCategorySpritePalette;
extern const struct SpriteTemplate gMoveCategorySpriteTemplates[];

u8 CreateMoveCategorySprite(u16 categoryId, s16 x, s16 y);
u8 ChangeMoveCategorySprite(u16 categoryId, u8 spriteId);
u16 GetOffset(u16 categoryId);

#endif // GUARD_MOVE_CATAGORIES_H

#include "global.h"
#include "gflib.h"
#include "decompress.h"
#include "graphics.h"
#include "move_categories.h"

#define GFX_TAG_MOVE_CATEGORY    55050
#define GFX_OFFSET(offset) (offset * TILE_SIZE_4BPP)

const struct SpriteSheet gMoveCategorySpriteSheet =
{
    .data = gMoveCategories_Gfx,
    .size = 16*16*3/2,
    .tag = GFX_TAG_MOVE_CATEGORY,
};

const struct SpritePalette gMoveCategorySpritePalette =
{
   .data = gMoveCategories_Pal,
   .tag = GFX_TAG_MOVE_CATEGORY,
};

static const struct OamData sMoveCategoryOamData =
{
    .size = SPRITE_SIZE(16x16),
    .shape = SPRITE_SHAPE(16x16),
    .bpp = ST_OAM_4BPP,
    .priority = 0,
};

const struct SpriteTemplate gMoveCategorySpriteTemplate =
{

    .tileTag = GFX_TAG_MOVE_CATEGORY,
    .paletteTag = GFX_TAG_MOVE_CATEGORY,
    .oam = &sMoveCategoryOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

u16 GetOffset(u16 categoryId)
{
    return (categoryId - 1) * 4;
}

u8 CreateMoveCategorySprite(u16 categoryId, s16 x, s16 y)
{
    u8 spriteId;

    spriteId = CreateSprite(&gMoveCategorySpriteTemplate, x, y, 0);
    
    gSprites[spriteId].oam.tileNum = gSprites[spriteId].sheetTileStart + GetOffset(categoryId);
    gSprites[spriteId].invisible = TRUE;

    return spriteId;
}

u8 ChangeMoveCategorySprite(u16 categoryId, u8 spriteId)
{
    gSprites[spriteId].oam.tileNum = gSprites[spriteId].sheetTileStart + GetOffset(categoryId);
}
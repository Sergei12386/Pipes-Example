#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>

#include <mcpe/item/Item.h>
#include <mcpe/tile/Tile.h>
#include <mcpe/client/renderer/TileTessellator.h>

bool (*_TileTessellator$tessellateInWorld)(TileTessellator*, Tile*, const TilePos&, bool);
bool TileTessellator$tessellateInWorld(TileTessellator* self, Tile* tile, const TilePos& pos, bool b) {
	switch(tile->id) {
		case 240:
			return self->tessellatePipeInWorld(tile, pos);
			break;
		default:
			return _TileTessellator$tessellateInWorld(self, tile, pos, b);
			break;
	}
}


void (*_Tile$initTiles)();
void Tile$initTiles() {
	_Tile$initTiles();
	Tile* pipe = new Tile(240, "stone", &Material::stone);
	pipe->setNameId("pipe");
	Tile::tiles[240] = pipe;
	Tile::solid[240] = false;
	Tile::lightBlock[240] = 0;
	new TileItem(240 - 0x100);
}


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*) &Tile::initTiles, 					(void*) &Tile$initTiles, 						(void**) &_Tile$initTiles);
	MSHookFunction((void*) &TileTessellator::tessellateInWorld, (void*) &TileTessellator$tessellateInWorld, 	(void**) &_TileTessellator$tessellateInWorld);
	return JNI_VERSION_1_2;
}

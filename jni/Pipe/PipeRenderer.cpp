#include "mcpe/client/renderer/TileTessellator.h"

bool TileTessellator::tessellatePipeInWorld(Tile* tile, TilePos const& pos){
	useForcedUV = true;
	int x = pos.x, y = pos.y, z = pos.z;
	
	forcedUV = tile->getTexture(0,0); // bottom texture
	
	setRenderBounds(0.35, 0.35, 0.35, 0.65, 0.65, 0.65);
	tessellateBlockInWorld(tile, pos);
	
	forcedUV = tile->getTexture(1,0); //top texture, just in case you want something different
	
	if(tileSource->getTilePtr(x,y+1,z) == tile){
		setRenderBounds(0.40, 0.60, 0.40, 0.60, 1.0, 0.60);
		tessellateBlockInWorld(tile, pos);
	}
	
	if(tileSource->getTilePtr(x,y-1,z) == tile){
		setRenderBounds(0.40, 0.0, 0.40, 0.60, 0.40, 0.60);
		tessellateBlockInWorld(tile, pos);
	}
	
	if(tileSource->getTilePtr(x+1,y,z) == tile){
		setRenderBounds(0.60, 0.40, 0.40, 1.0, 0.60, 0.60);
		tessellateBlockInWorld(tile, pos);
	}
	
	if(tileSource->getTilePtr(x-1,y,z) == tile){
		setRenderBounds(0.0, 0.40, 0.40, 0.40, 0.60, 0.60);
		tessellateBlockInWorld(tile, pos);
	}
	
	if(tileSource->getTilePtr(x,y,z+1) == tile){
		setRenderBounds(0.40, 0.40, 0.40, 0.60, 0.60, 1.0);
		tessellateBlockInWorld(tile, pos);
	}
	
	if(tileSource->getTilePtr(x,y,z-1) == tile){
		setRenderBounds(0.40, 0.40, 0.0, 0.60, 0.60, 0.40);
		tessellateBlockInWorld(tile, pos);
	}
	
	useForcedUV = false;
}

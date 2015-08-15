#pragma once

#include "texture/TextureUVCoordinateSet.h"
#include "../../util/AABB.h"
#include "../../tile/Tile.h"
#include <cmath>

class TileSource;
#include "Tessellator.h"
class TilePos;

const float PI = 3.14159;

// Size : 72740
class TileTessellator
{
public:
	static TileTessellator *instance;

public:
	char filler1[4];				// 0
	TileSource *tileSource;			// 4
	TextureUVCoordinateSet forcedUV;// 8
	bool useForcedUV;				// 40
	char filler2[623];				// 41
	Tessellator* tess;				// 664
	AABB bounds;					// 668

public:
	bool tessellateInWorld(Tile *, const TilePos &, bool);
	void tessellateBlockInWorld(Tile *, const TilePos &);
	bool tessellateCrossInWorld(Tile*, const TilePos&, bool);
	bool tessellateCrossTexture(Tile*, unsigned char, float, float, float, bool);
	uint getLightColor(const TilePos &);
	void tex1(uint);
	bool canRender(int);
	
	void setRenderBounds(float x1, float y1, float z1, float x2, float y2, float z2) {
		bounds = AABB(x1, y1, z1, x2, y2, z2);
	}
	
	bool isOn(TileSource* ts, Tile* tile, int x, int y, int z) {
		if(ts->getTilePtr(x, y, z) == tile) return true;
	}
	
	bool tessellatePipeInWorld(Tile* tile, TilePos const& pos){
		useForcedUV = true;
		int x = pos.x, y = pos.y, z = pos.z;
		
		forcedUV = tile->getTextureUVCoordinateSet("stone",0);
		
		setRenderBounds(0.35, 0.35, 0.35, 0.65, 0.65, 0.65);
		tessellateBlockInWorld(tile, pos);
		
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
};

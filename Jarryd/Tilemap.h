/*
* Author: Jarryd Hall
* Purpose: Tilemap representation header file
*/

#ifndef TILEMAP_H
#define TILEMAP_H

typedef struct
{
    // Height for the room is 3m 
    
	short mapWidth; // number of tiles | note: not number of pixels
	short mapHeight; // number of tiles | note: not number of pixels
	short tileWidth; // size in pixels
	short tileHeight; // size in pixels
	short numberOfTilesInMap; // number of tiles in tile-map
	short worldHeight; // height for the room
	
	// short margin; // pixels to skip for current tile before looking for pixels
	// short spacing; // pixels to advance to the next tile data
} 
ThreeDWorld;

typedef struct
{
	int xPosition;
	int yPosition;
	
} 
CGPoint;

CGPoint* tileForCoordinates (CGPoint position, short width, short height);

#endif /* TILEMAP_H */
#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>

namespace units {
    typedef double Game; // intrinsic units of position
    typedef int Pixel;
    typedef unsigned int Tile;

    typedef unsigned int FPS;
    typedef double Velocity;
    typedef double Acceleration;

    namespace {
        const Game kTileSize{32.0};
    }

    inline Pixel gameToPixel(Game game) {
        // TODO: quit assuming 16x16
        return Pixel(round(game / 2));
    }
    inline Tile gameToTile(Game game) {
        return Tile(game / kTileSize);
    }
    inline Game tileToGame(Tile tile) {
        return tile * kTileSize;
    }
    inline Pixel tileToPixel(Tile tile) {
        return gameToPixel(tileToGame(tile));
    }
} // units

#endif /* UNITS_H_ */

#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>

namespace units {
    typedef int HP;

    typedef double Game; // intrinsic units of position
    typedef int Pixel;
    typedef unsigned int Tile;
    typedef double Degrees;

    typedef unsigned int Frame;

    typedef unsigned int FPS;
    typedef double Velocity;
    typedef double Acceleration;
    typedef double AngularVelocity; // Degrees / milliseconds

    namespace {
        const Game kTileSize{32.0};
        const double kPi{atan(1) * 4};
    }

    inline double degreesToRadians(Degrees degrees) {
        return degrees * kPi / 180.0;
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

    const Game kHalfTile{tileToGame(1) / 2.0};
} // units

#endif /* UNITS_H_ */

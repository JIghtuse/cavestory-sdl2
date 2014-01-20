#ifndef GAME_H
#define GAME_H

struct Game {
    Game();
    ~Game();
private:
    void runEventLoop();
    int fpsDelay;
};

#endif /* GAME_H */

#ifndef GAME_H
#define GAME_H

struct Game {
    Game();
    ~Game();
private:
    void runEventLoop();
    void update();
    void draw();
};

#endif /* GAME_H */

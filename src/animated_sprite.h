#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"

struct AnimatedSprite : public Sprite {
    AnimatedSprite(const std::string& file_path,
            int source_x, int source_y,
            int width, int height,
            SDL_Renderer* ren,
            int fps, int num_frames);

    ~AnimatedSprite();

    virtual void update(std::chrono::duration<double,std::milli> elapsed_time);

private:
    std::chrono::duration<double,std::milli> frame_time_;
    const int num_frames_;
    int current_frame_;
    std::chrono::duration<double,std::milli> elapsed_time_; // since the last
                                                            // frame change
};

#endif /*  ANIMATED_SPRITE_H */

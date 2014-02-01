#ifndef BACKDROP_H_
#define BACKDROP_H_

#include <string>
#include "graphics.h"

struct Backdrop {
    virtual void draw(Graphics& graphics) const = 0;
};

struct FixedBackdrop : public Backdrop {
    FixedBackdrop(const std::string& path, Graphics& graphics);
    void draw(Graphics& graphics) const;
private:
    SDL_Texture* texture_id_;
};

#endif /* BACKDROP_H_ */

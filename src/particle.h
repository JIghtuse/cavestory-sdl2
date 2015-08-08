#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <chrono>

struct Graphics;

struct Particle {
    virtual bool update(std::chrono::milliseconds elapsed_time) = 0;
    virtual void draw(Graphics& graphics) const = 0;
    virtual ~Particle() = 0;
};

inline Particle::~Particle() {}

#endif /* PARTICLE_H_ */

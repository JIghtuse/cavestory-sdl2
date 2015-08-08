#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <chrono>
#include <memory>
#include <set>

#include "units.h"

struct Graphics;
struct Particle;

struct ParticleSystem {
    ParticleSystem() :
        particles_{}
    {}
    void addNewParticle(std::shared_ptr<Particle> particle);
    bool update(const std::chrono::milliseconds elapsed_time);
    void draw(Graphics& graphics) const;

private:
    typedef std::set<std::shared_ptr<Particle> > ParticleSet;
    ParticleSet particles_;
};

#endif /* PARTICLE_SYSTEM_H_ */

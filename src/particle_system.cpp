#include "particle_system.h"
#include "particle.h"

void ParticleSystem::addNewParticle(std::shared_ptr<Particle> particle) {
    particles_.insert(particle);
}

bool ParticleSystem::update(const std::chrono::milliseconds elapsed_time) {
    for (auto it = particles_.begin(); it != particles_.end(); ) {
        if ((*it)->update(elapsed_time)) {
            ++it;
        } else {
            particles_.erase(it++);
        }

    }
    return true;
}

void ParticleSystem::draw(Graphics& graphics) const {
    for (auto& particle: particles_) {
        particle->draw(graphics);
    }
}

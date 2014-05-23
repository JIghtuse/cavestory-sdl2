#include "head_bump_particle.h"
#include "rand.h"
#include <iostream>

const units::Game kSourceX{116};
const units::Game kSourceY{54};
const units::Game kSourceWidth{6};
const units::Game kSourceHeight{6};

const std::chrono::milliseconds kLifeTime{600};
const std::chrono::milliseconds kFlashPeriod{25};
const bool kTimerStartActive{true};
const units::Velocity kSpeed{0.12};

HeadBumpParticle::HeadBumpParticle(Graphics& graphics,
        Vector<units::Game> center_pos) :
    sprite_(graphics, "Caret",
            units::gameToPixel(kSourceX),
            units::gameToPixel(kSourceY),
            units::gameToPixel(kSourceWidth),
            units::gameToPixel(kSourceHeight)),
    live_timer_(kLifeTime, kTimerStartActive),
    center_pos_(center_pos),
    particle_a_(0, rand_angle()),
    particle_b_(0, rand_angle()),
    game_max_offset_a_{static_cast<units::Game>(rand_double(4.0, 20.0))},
    game_max_offset_b_{static_cast<units::Game>(rand_double(4.0, 20.0))}
{}

void HeadBumpParticle::draw(Graphics& graphics) const
{
    if (live_timer_.current_time() / kFlashPeriod % 2 == 0) {
        sprite_.draw(graphics, center_pos_ + particle_a_.getPos());
        sprite_.draw(graphics, center_pos_ + particle_b_.getPos());
    }
}

bool HeadBumpParticle::update(const std::chrono::milliseconds elapsed_time)
{
    const auto magn_diff = kSpeed * elapsed_time.count();
    particle_a_.setMagnitude(std::min(
                particle_a_.getMagnitude() + magn_diff,
                game_max_offset_a_));

    particle_b_.setMagnitude(std::min(
                particle_b_.getMagnitude() + magn_diff,
                game_max_offset_b_));

    return live_timer_.is_active();
}

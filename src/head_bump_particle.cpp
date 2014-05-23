#include "head_bump_particle.h"

const units::Game kSourceX{116};
const units::Game kSourceY{54};
const units::Game kSourceWidth{6};
const units::Game kSourceHeight{6};

const std::chrono::milliseconds kLifeTime{600};
const std::chrono::milliseconds kFlashPeriod{25};
const bool kTimerStartActive{true};
const units::Degrees kDegreesPerMilliSecond{60.0 / 1000.0};

HeadBumpParticle::HeadBumpParticle(Graphics& graphics,
        Vector<units::Game> center_pos) :
    sprite_(graphics, "Caret",
            units::gameToPixel(kSourceX),
            units::gameToPixel(kSourceY),
            units::gameToPixel(kSourceWidth),
            units::gameToPixel(kSourceHeight)),
    live_timer_(kLifeTime, kTimerStartActive),
    center_pos_(center_pos),
    particle_a_(32, 0)
{}

void HeadBumpParticle::draw(Graphics& graphics) const
{
    sprite_.draw(graphics,center_pos_);

    if (live_timer_.current_time() / kFlashPeriod % 2 == 0) {
        sprite_.draw(graphics, center_pos_ + particle_a_.getPos());
    }
}

bool HeadBumpParticle::update(const std::chrono::milliseconds elapsed_time)
{
    const auto angle_diff = kDegreesPerMilliSecond * elapsed_time.count();
    particle_a_.setAngle(particle_a_.getAngle() + angle_diff);

    return live_timer_.is_active();
}

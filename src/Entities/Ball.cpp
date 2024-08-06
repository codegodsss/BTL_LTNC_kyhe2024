#include "Ball.hpp"
#include "Brick.hpp"
#include "Context.hpp"

#include "Core/Effect.hpp"
#include "Core/SoundSystem.hpp"
#include "Utils/Math.hpp"

// When hitting the pad, the ball bounces from PADDLE_ANGLE to 90 + PADDLE_ANGLE
#define PADDLE_ANGLE 30 // degrees
// The ball velocity starts at BALL_SPEED_STEP, and is increased by BALL_SPEED_STEP
// every time a brick is hit, until BALL_MAX_SPEED is reached
#define BALL_START_SPEED 150 // pixels/second
#define BALL_MAX_SPEED   300 // pixels/second
#define BALL_SPEED_STEP  3   // pixels/second
// Number of bricks when Power Ball power-up is activated
#define POWER_BALL_COUNT 10

int Ball::s_instance_count = 0;

Ball::Ball():
    m_angle(math::to_radians(math::rand(PADDLE_ANGLE, 90 + PADDLE_ANGLE))),
    m_velocity(BALL_START_SPEED),
    m_powerHits(0),
    m_gluedTo(nullptr)
{
    setTexture(Resources::getTexture("balls.png"));
    setTextureRect({0, 0, 8, 8});
    ++s_instance_count;
}


Ball::~Ball()
{
    --s_instance_count;
}


Ball* Ball::toBall()
{
    return this;
}


void Ball::unstick()
{
    m_gluedTo = nullptr;
}


void Ball::enablePowerBall()
{
    m_powerHits = POWER_BALL_COUNT;
    setTextureRect({8, 0, 8, 8});
    m_emitter.setParticleColor(sf::Color::Cyan, sf::Color(0, 0, 255, 0));
}


void Ball::resetSpeed()
{
    m_velocity = BALL_START_SPEED;
}


void Ball::createParticles()
{
    m_emitter.setSpawnPosition(getCenter());
    m_emitter.createParticles();
}


void Ball::onUpdate(float frametime)
{
    if (m_gluedTo == nullptr)
    {
        float delta = m_velocity * frametime;
        move(delta * std::cos(m_angle), -delta * std::sin(m_angle));
    }
    else
    {
        // Stick to the paddle
        setX(m_gluedTo->getX() - m_gluedAt);
    }
    m_emitter.setSpawnPosition(getCenter());
}
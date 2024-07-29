#include "Ball.hpp"
#include "Brick.hpp"


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

    m_emitter.setParticleCount(100);
    m_emitter.setParticleColor(sf::Color::Red, sf::Color(255, 255, 0, 0));
    m_emitter.setSpeed(10, 5);
    m_emitter.setAngle(0, math::PI * 2);
    m_emitter.setTimeToLive(1.f);
    m_emitter.setLooping(true);
    m_emitter.setParticleSystem(*Context::get().particles);
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



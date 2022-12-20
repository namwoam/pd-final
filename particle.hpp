#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count) : m_particles(count),
                                         m_vertices(sf::Points, count),
                                         m_lifetime(sf::seconds(3.f)),
                                         m_emitter(0.f, 0.f)
    {
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }
    void setEmission(int direction, sf::Vector2f _sourceSpeed)
    {
        if (direction != -1)
        {
            emissionDuration = 0.1;
            emissionDirection = direction;
        }
        sourceSpeed = _sourceSpeed;
    }
    void update(sf::Time elapsed)
    {
        if (emissionDuration > 0)
        {
            emissionDuration -= elapsed.asSeconds();
        }
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle &p = m_particles[i];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero && emissionDuration > 0)
                resetParticle(i);

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            if (p.lifetime.asSeconds()< 0)
            {
                m_vertices[i].color.a = 0;
            }
            else
            {
                float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
                m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
            }
        }
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

private:
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (emissionDirection + ((std::rand() % (emissionSpan * 2)) - emissionSpan)) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed) + sourceSpeed;
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    sf::Vector2f sourceSpeed;
    int emissionDirection = 0;
    float emissionDuration;
    int emissionSpan = 20;
};
#ifndef RENDERPLANE_HPP
#define RENDERPLANE_HPP 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "util.hpp"

namespace cf
{
    typedef std::vector<std::unique_ptr<sf::RenderTexture> > TextureVec;
    typedef std::vector<std::unique_ptr<sf::Sprite> > SpriteVec;

    class RenderPlane : sf::NonCopyable, public sf::Drawable
    {
    private:
        const unsigned int _MaxTextureSize;
        const sf::Vector2u _Size;

        std::vector<TextureVec> _Textures;
        std::vector<SpriteVec> _Sprites;

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        RenderPlane(sf::Vector2u size);
        sf::Vector2u Size() const { return _Size; }
        void Size(sf::Vector2u v);

        virtual ~RenderPlane();
    };
}

#endif

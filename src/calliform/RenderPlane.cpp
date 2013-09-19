#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <memory>
#include "RenderPlane.hpp"
#include "SFMLError.hpp"
#include "util.hpp"

namespace cf
{

    RenderPlane::RenderPlane(sf::Vector2u size)
        : _maxTextureSize(sf::Texture::getMaximumSize()), _size(size)
    {
        assert(_maxTextureSize > 0);

        unsigned int countX = icdiv(_size.x, _maxTextureSize);
        unsigned int countY = icdiv(_size.y, _maxTextureSize);

        unsigned int remainingX = _size.x;
        for (unsigned int xx = 0; xx < countX; xx++)
        {
            float pX = (float)xx * _maxTextureSize;
            unsigned int width = std::min(_maxTextureSize, remainingX);
            remainingX -= width;

            _textures.emplace_back();
            _sprites.emplace_back();

            unsigned int remainingY = _size.y;
            for (unsigned int yy = 0; yy < countY; yy++)
            {
                float pY = (float)yy * _maxTextureSize;
                unsigned int height = std::min(_maxTextureSize, remainingY);
                remainingY -= height;

                // Create the new texture
                std::unique_ptr<sf::RenderTexture> tex = make_unique<sf::RenderTexture>();
                if (!tex->create(width, height))
                {
                    std::ostringstream os;
                    os << "unable to create texture of size ("
                        << width << ", " << height << ") at ("
                        << xx << ", " << yy << ")";
                    throw SFMLError(os.str());
                }

                // Adjust the view so that drawing works as expected
                sf::View view;
                view.reset(sf::FloatRect(-pX, -pY, width, height));
                tex->setView(view);

                // Create a sprite and attach the texture to it
                std::unique_ptr<sf::Sprite> sprite = make_unique<sf::Sprite>();
                sprite->setTexture(tex->getTexture(), true);
                sprite->setPosition(pX, pY);
                _sprites[xx].push_back(std::move(sprite));

                _textures[xx].push_back(std::move(tex));
            }
            assert(remainingY == 0);
        }
        assert(remainingX == 0);
    }

    RenderPlane::~RenderPlane()
    {
        _sprites.clear();
        _textures.clear();
    }

    void RenderPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const SpriteVec& vec : _sprites)
        {
            for (const std::unique_ptr<sf::Sprite>& sprite : vec)
            {
                target.draw(*sprite, states);
            }
        }
    }
}

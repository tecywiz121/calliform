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
        : _MaxTextureSize(sf::Texture::getMaximumSize()), _Size(size)
    {
        assert(_MaxTextureSize > 0);

        unsigned int countX = icdiv(_Size.x, _MaxTextureSize);
        unsigned int countY = icdiv(_Size.y, _MaxTextureSize);

        unsigned int remainingX = _Size.x;
        for (unsigned int xx = 0; xx < countX; xx++)
        {
            unsigned int width = std::min(_MaxTextureSize, remainingX);
            remainingX -= width;

            _Textures.emplace_back();

            unsigned int remainingY = _Size.y;
            for (unsigned int yy = 0; yy < countY; yy++)
            {
                unsigned int height = std::min(_MaxTextureSize, remainingY);
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
                view.reset(sf::FloatRect(-((float)xx * _MaxTextureSize),
                                         -((float)yy * _MaxTextureSize),
                                         width, height));
                tex->setView(view);

                _Textures[xx].push_back(std::move(tex));
            }
            assert(remainingY == 0);
        }
        assert(remainingX == 0);
    }

    RenderPlane::~RenderPlane()
    {
        _Textures.clear();
    }

}

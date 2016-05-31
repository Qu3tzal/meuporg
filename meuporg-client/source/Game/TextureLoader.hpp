#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        enum TextureId {SAITAMA, SPARTIATE};

        sf::Texture get(TextureId id) const;

        sf::Texture load(std::string path);

    protected:

        // Map who associate Texture id and texture
        std::map <TextureId, sf::Texture> textures;


    private:
};

#endif // TEXTURELOADER_HPP

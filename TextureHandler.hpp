#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <chrono>

namespace TextureHandler{

    sf::Sprite loadImage(const char* path);
    sf::Sprite loadImage(const char* path, sf::IntRect rect);




    class Animation : public sf::Drawable {

        private:
            sf::Sprite drawer;
            std::shared_ptr<sf::RenderTexture> body;
            std::chrono::milliseconds delay;
            std::chrono::milliseconds last;

            void baseConstructor(std::vector<std::string> paths, std::chrono::milliseconds delay);

        public:
            
            Animation(std::vector<std::string> paths, std::chrono::milliseconds delay);
            Animation(std::string* paths, size_t amount, std::chrono::milliseconds delay);
            Animation(std::initializer_list<std::string> paths, std::chrono::milliseconds delay);
            Animation(std::string folder, std::chrono::milliseconds delay);
            Animation(Animation& other);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            void tick();
            void reset();
            
    };


}
#   include "TextureHandler.cpp"
#   include "Animation.cpp"
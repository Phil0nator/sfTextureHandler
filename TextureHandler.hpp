#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <chrono>

namespace TextureHandler{

    /**
     * Load an image into a sprite using the TextureHandler system.
     * @param path the path to the image
     * @returns a sprite set up with the image
     */
    sf::Sprite loadImage(const char* path);

    /**
     * Load a rect of an image into a sprite using the TextureHandler system.
     * @param path the path to the image
     * @returns a sprite set up with the image
     */
    sf::Sprite loadImage(const char* path, sf::IntRect rect);



    /**
     * The Animation class functions as a 'drawable' object that will
     * flip through frames every given number of milliseconds, as long as the 'tick'
     * function is being called.
     */
    class Animation : public sf::Drawable {

        private:
            sf::Sprite drawer;
            std::shared_ptr<sf::RenderTexture> body;
            std::chrono::milliseconds delay;
            std::chrono::milliseconds last;

            void baseConstructor(std::vector<std::string> paths, std::chrono::milliseconds delay);

        public:
            /**
             * Construct an animation from a series of paths, and a delay.
             * @param paths an array of paths to load in order of frames
             * @param delay the minimum number of milliseconds to wait between frames
             */
            Animation(std::vector<std::string> paths, std::chrono::milliseconds delay);
            
            /**
             * Construct an animation from a series of paths, and a delay.
             * @param paths an array of paths to load in order of frames
             * @param amount the number of paths provided
             * @param delay the minimum number of milliseconds to wait between frames
             */
            Animation(std::string* paths, size_t amount, std::chrono::milliseconds delay);
            
            /**
             * Construct an animation from a series of paths, and a delay.
             * @param paths an array of paths to load in order of frames
             * @param delay the minimum number of milliseconds to wait between frames
             */
            Animation(std::initializer_list<std::string> paths, std::chrono::milliseconds delay);
            
            /**
             * Construct an animation from a series of paths, and a delay.
             * @param folder a path to a folder filled with images to load, in order of frames
             * @param delay the minimum number of milliseconds to wait between frames
             */
            Animation(std::string folder, std::chrono::milliseconds delay);
            
            /**
             * Copy constructor
             */
            Animation(Animation& other);

            /**
             * @overload
             * (used internally)
             * use sf::RenderTarget::draw(TextureHandler::Animation&) in order to display
             * the animation in its current state.
             * 
             */
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            
            /**
             * Update the animation.
             * Call this function whenever you are drawing it, and you need it to update.
             * The delay is handled internally, so it must be ran every relevant frame.
             */
            void tick();
            
            /**
             * Reset back to frame zero, and time zero.
             */
            void reset();
            
    };


}
#   include "TextureHandler.cpp"
#   include "Animation.cpp"
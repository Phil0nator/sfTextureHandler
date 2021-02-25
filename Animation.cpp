namespace TextureHandler{


    std::chrono::milliseconds now(){
        return std::chrono::duration_cast< std::chrono::milliseconds >(
                std::chrono::system_clock::now().time_since_epoch() );
    }


    void Animation::baseConstructor(std::vector<std::string> paths, std::chrono::milliseconds delay){
        
        body = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture());
        
        this->delay = delay;
        sf::Texture loader;
        loader.loadFromFile(paths[0]);
        auto size = loader.getSize();
        this->body->create(size.x*paths.size(),size.y);
        this->body->setRepeated(true);


        std::for_each(paths.begin()++,paths.end(), [&](const auto& val){
            drawer.setTexture(loader);
            auto position = drawer.getPosition();
            position.x += size.x;
            drawer.setPosition(position);
            body->draw(drawer);
            loader.loadFromFile(val);
        });
        body->display();
        drawer.setTexture(body->getTexture());
        drawer.setTextureRect(sf::IntRect(0,0,size.x,size.y));

    }


    Animation::Animation(std::vector<std::string> paths, std::chrono::milliseconds delay){
        baseConstructor(paths, delay);
    }
    Animation::Animation(std::string* paths, size_t amount, std::chrono::milliseconds delay){
        std::vector<std::string> newpaths(amount);
        for (size_t i = 0; i < amount; i++)
        {
            newpaths.assign(i, paths[i]);
        }
        baseConstructor(newpaths, delay);
        
    }
    Animation::Animation(std::initializer_list<std::string> paths, std::chrono::milliseconds delay){
        std::vector<std::string> newpaths = std::vector<std::string>(paths);
        baseConstructor(newpaths, delay);
    }
    Animation::Animation(Animation& other){
        drawer=other.drawer;
        body = other.body;
        delay = other.delay;
        last = other.last;

    }

    void Animation::tick(){
        if (now()-last>delay){
            auto rect = drawer.getTextureRect();
            rect.left = drawer.getTexture()->getSize().x;
            drawer.setTextureRect(rect);
            last = now();
        }
    }

    void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const{

        target.draw(drawer);

    }

    void Animation::reset(){
        drawer.setTextureRect(sf::IntRect(   sf::Vector2i(0,0), (sf::Vector2i) drawer.getTexture()->getSize()   ));
    }

};
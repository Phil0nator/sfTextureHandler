#define TEXTURE_CONTAINER_DIMENSION 8000
#include <algorithm>
#include <iostream>
#include <memory>
#include <list>

namespace TextureHandler{
    
    class TallocNode{
        public:
            std::shared_ptr<sf::RenderTexture> body;
            unsigned int x = 0, y = 0;
            unsigned int w = TEXTURE_CONTAINER_DIMENSION, h = TEXTURE_CONTAINER_DIMENSION;
            
            TallocNode(){
                body = std::shared_ptr<sf::RenderTexture>( new sf::RenderTexture() );
                body->create(TEXTURE_CONTAINER_DIMENSION, TEXTURE_CONTAINER_DIMENSION);
            }


            TallocNode(const TallocNode& other, int x, int y, int w, int h){
                body=other.body;
                this->x=x;
                this->y=y;
                this->w=w;
                this->h=h;
            }

            bool operator <(int area) const {
                return (w*h)<area;
            }

            bool operator >(int area) const {
                return (w*h)<area;
            }

    };



    std::list<TallocNode> talloc_head;

    auto checkExisting(int width, int height){
        return std::find_if(
            talloc_head.begin(), 
            talloc_head.end(), 
            [&](const auto& val){ 
                return val.w > width and val.h > height; 
                
                });
    }

    sf::Sprite finalizeTexture(TallocNode& node, sf::Texture request, int width, int height){
        sf::Sprite tmp(request);
        tmp.setPosition(node.x, node.y);
        node.body->draw(tmp);
        node.body->display();
        sf::Sprite out(node.body->getTexture(), sf::IntRect(node.x,node.y, width, height));

        if (node > 50){
            talloc_head.emplace_front(
                TallocNode(
                    node,
                    node.x+width,
                    node.y,
                    node.w-width,
                    node.h
                )
            );

            talloc_head.emplace_front(
                TallocNode(
                    node,
                    node.x,
                    node.y+height,
                    node.w,
                    node.h-height
                )
            );
        }


        node.x+=width;
        node.y+=height;
        node.w -= width;
        node.h -= height;
        
        
        return out;
    }

    sf::Sprite talloc(sf::Texture request){
        
        auto dims = request.getSize();
        tryAgain:

        auto existing = checkExisting(dims.x, dims.y);
        if (existing != talloc_head.end()){
            auto out = finalizeTexture(*existing, request, dims.x, dims.y);
            if (*existing < 50){
                talloc_head.erase(existing);
            }
            return out;
        }

        talloc_head.emplace_front(
            TallocNode()
        );

        goto tryAgain;

    }




    sf::Sprite loadImage(const char* path){
        sf::Texture text;
        text.loadFromFile(path);
        return talloc(text);
    }
    sf::Sprite loadImage(const char* path, sf::IntRect rect){
        sf::Texture text;
        text.loadFromFile(path, rect);
        return talloc(text);
    }


    void flushTextureAllocator(){
        talloc_head.clear();
    }







    




};
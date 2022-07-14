#include "Animation.hpp"

Animation::Animation(int len)
{
    length = len;
    index = 0;
    currLength = 0;
    isPlaying = false;
};

Animation::~Animation(){};

void Animation::load(std::string name, std::string path, double width)
{

    if(animations[name].size() > 0) return;

    std::vector<sf::Sprite> animation;

    sf::Texture* spriteSheet = new sf::Texture();
    spriteSheet->loadFromFile("Art/"+path+".png");

    for(int i = 0; i < spriteSheet->getSize().x; i+=width)
    {
        sf::IntRect area;
        area.left = i;
        area.height = spriteSheet->getSize().y;
        area.width = width;
        area.top = 0;
        sf::Sprite frame;
        frame.setTexture(*spriteSheet);
        frame.setTextureRect(area);
        animation.push_back(frame);
    }

    animations[name] = animation;

};

void Animation::play(sf::RenderWindow* g, double x, double y)
{

    

    if(currLength >= length) 
    {
        index++;
        currLength = 0;
    }

    std::vector<sf::Sprite> current = animations[currentAnimation];

    if(index >= current.size()) index = 0;
    
    if(isPlaying)
        currLength += DeltaTime::get();

    sf::Sprite s = current[index];
    s.setPosition(x, y);

    g->draw(s);

};

void Animation::pause()
{
    isPlaying = false;
    currLength = 0;
};

void Animation::resume()
{
    isPlaying = true;
};

void Animation::select(std::string name)
{
    currentAnimation = name;
};

void Animation::stop()
{
    isPlaying = false;
    index = 0;
    currLength = 0;
};

void Animation::setLength(float l)
{
    length = l;
};

void Animation::flip(std::string name, std::string newname, bool x, bool y)
{
    std::vector<sf::Sprite> another;
    
    for(sf::Sprite sprite: animations[name])
    {   
        if(x)
        {
            sf::IntRect r(sprite.getTextureRect().width + sprite.getTextureRect().left, 0, -sprite.getLocalBounds().width, sprite.getLocalBounds().height);
            sprite.setTextureRect(r);
        }
        
        if(y)
        {
            sf::IntRect r(sprite.getTextureRect().left + sprite.getTextureRect().width, sprite.getTextureRect().height, sprite.getLocalBounds().width, -sprite.getLocalBounds().height);
            sprite.setTextureRect(r);
        }
        another.push_back(sprite);
    }

    animations[newname] = another;

};

void Animation::scale(std::string name, double x, double y)
{
    std::vector<sf::Sprite>& animation = animations[name];

    for(sf::Sprite& sprite: animation)
    {
        sprite.scale(x, y);
    }

}

sf::Vector2f Animation::getSize()
{
    sf::FloatRect size = animations[currentAnimation][0].getGlobalBounds();
    return sf::Vector2f(size.width, size.height);
}
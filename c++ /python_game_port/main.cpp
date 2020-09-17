#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

//global variables, as shown on python project
std::string SCREEN_TITTLE = "Crossy RPG";
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;
sf::Color WHITE_COLOR = sf::Color(255,255,255);
float level_speed = 0;

class Entity{

private:

    sf::RectangleShape BODY;

public:
    //public variables
    sf::Vector2f BODY_POSITION;
    int SPEED = 10;
    //constructor
    Entity(sf::Texture* texture, int x, int y, int width, int height);
    //self movement and control fucntions
    void movement(int max_height);
    void self_movement(int max_width);
    // colition detection fucntion conditions
    bool detect_collition_x(sf::Vector2f other_body, int difference);
    bool detect_collition_y(sf::Vector2f other_body, int difference);
    // capturing the actual position of the entity
    void position_update();
    //draw fucntion for render
    void draw(sf::RenderWindow& window);
    //deconstructor
    ~Entity();
};

Entity::Entity(sf::Texture* texture, int x, int y, int width, int height)
{   //setting texture and position of the the sprite
    BODY.setSize(sf::Vector2f(width,height));
    BODY.setTexture(texture);
    BODY.setPosition(x, y);
    printf("%s\n", "object created");
}


void Entity::movement(int max_height)
{   //controls
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))BODY.move(0, 8);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))BODY.move(0, -8);
    //preventing out of bounds
    if(BODY.getPosition().y >= max_height - 40) BODY.setPosition(BODY.getPosition().x, max_height - 40);
}

void Entity::self_movement(int max_width)
{
    if(BODY_POSITION.x <= 20) SPEED = std::abs(SPEED);
    else if(BODY_POSITION.x >= max_width - 70) SPEED = -std::abs(SPEED);

    BODY.move(SPEED,0);
}

bool Entity::detect_collition_x(sf::Vector2f other_body, int difference)
{

    // x detection
    if(other_body.x  > (BODY_POSITION.x + difference)) return false;
    else if ((other_body.x + difference) < BODY_POSITION.x) return false;
    // y detection
    if((BODY_POSITION.y + difference) < other_body.y) return false;
    else if (BODY_POSITION.y > (other_body.y + difference)) return false;
    //cancelling between x detection
    if((BODY_POSITION.x > other_body.x) & ((BODY_POSITION.x + difference) < (other_body.x + difference))) return false;

    return true;
    printf("%s\n", "collition x");
}

bool Entity::detect_collition_y(sf::Vector2f other_body, int difference)
{   // x detection
    if(other_body.x  > (BODY_POSITION.x + difference)) return false;
    else if ((other_body.x + difference) < BODY_POSITION.x) return false;
    // y detection
    if((BODY_POSITION.y + difference) < other_body.y) return false;
    else if (BODY_POSITION.y > (other_body.y + difference)) return false;
    //cancelling between y detection
    if((BODY_POSITION.y > other_body.y) & ((BODY_POSITION.y + difference) < (other_body.y + difference))) return false;

    return true;
}


void Entity::position_update()
{
    BODY_POSITION = BODY.getPosition();
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(BODY);
}

Entity::~Entity(){printf("%s\n", "object destroyed");}



int main()
{
    bool WIN = false;

    // text used in the game
    sf::Font FONT1;
    FONT1.loadFromFile("Arial.ttf");
    sf::Text TEXT1("OK...INCREASING DIFICULTY", FONT1);
    TEXT1.setCharacterSize(30);
    TEXT1.setFillColor(sf::Color::Magenta);
    TEXT1.setPosition(200, 300);
    sf::Text TEXT2("NICE!!!", FONT1);
    TEXT2.setCharacterSize(80);
    TEXT2.setFillColor(sf::Color::Magenta);
    TEXT2.setPosition(245, 300);
    sf::Text TEXT3("OOF!!!", FONT1);
    TEXT3.setCharacterSize(80);
    TEXT3.setFillColor(sf::Color::Magenta);
    TEXT3.setPosition(245, 300);


    // Create the main window and limit the frames to 60 fps
    sf::RenderWindow app(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITTLE);
    app.setFramerateLimit(60);

    // CREATING TEXTURES FOR OBJECTS
    sf::Texture player_texture;
    if (!player_texture.loadFromFile("sprites/player.png"))return EXIT_FAILURE;
    sf::Texture chest_texture;
    if (!chest_texture.loadFromFile("sprites/treasure.png"))return EXIT_FAILURE;
    sf::Texture enemy_texture;
    if (!enemy_texture.loadFromFile("sprites/enemy.png"))return EXIT_FAILURE;
    sf::Texture ghost_texture;
    if (!ghost_texture.loadFromFile("sprites/GHOST.png"))return EXIT_FAILURE;


    // CREATING OBJECTS FROM ENTITY CLASS
    Entity PLAYER(&player_texture, 375, 650, 50, 50);
    Entity TREASURE(&chest_texture, 375, 50, 50, 50);
    Entity ENEMY(&enemy_texture, 20, 500, 50, 50);
    Entity ENEMY2(&enemy_texture, SCREEN_WIDTH - 20, 370, 50, 50);
    Entity ENEMY3(&enemy_texture, 75, 145, 100, 100);
    Entity ENEMY4(&enemy_texture, SCREEN_WIDTH - 75, 145, 100, 100);
    Entity ENEMY5(&ghost_texture,SCREEN_WIDTH - 75, 435, 25, 25);

    //ASIGNING THE MOVEMENT SPEED FOR THE ENEMIES.
    ENEMY.SPEED *= 1;
    ENEMY2.SPEED *= 1;
    ENEMY3.SPEED *= level_speed + 0.4;
    ENEMY4.SPEED = 10;
    ENEMY5.SPEED = 12;

    //ENNDING SCREEN TEXTURE
    sf::Texture ENDING_TEXTURE;
    if(!ENDING_TEXTURE.loadFromFile("ENDING.png")) return 0;
    sf::Sprite ENDING_SCREEN;
    ENDING_SCREEN.setTexture(ENDING_TEXTURE);

    //BACKGROUND
    sf::Texture background_texture;
    if (!background_texture.loadFromFile("sprites/background.png"))return EXIT_FAILURE;
    sf::Sprite BACKGROUND_SPRITE;
    BACKGROUND_SPRITE.setTexture(background_texture);
    BACKGROUND_SPRITE.setPosition(0,0);
    BACKGROUND_SPRITE.scale(3.1,3.1);




	// Start the game loop
    while (app.isOpen())
    {

        //UPDATING position of the objects before the conditions
        PLAYER.position_update();
        TREASURE.position_update();
        ENEMY.position_update();

        //creating event and second while loop
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit and if esc press, exit
            if (event.type == sf::Event::Closed) app.close();

        }

        //activates the movement and prevents out of bounds
        PLAYER.movement(SCREEN_HEIGHT);
        ENEMY.self_movement(SCREEN_WIDTH);
        ENEMY2.self_movement(SCREEN_WIDTH);
        ENEMY3.self_movement(SCREEN_WIDTH);
        ENEMY4.self_movement(SCREEN_WIDTH);
        ENEMY5.self_movement(SCREEN_WIDTH);

        //COLLITION DETECTION for entities
/*******************************************************************************************/
        if(PLAYER.detect_collition_x(TREASURE.BODY_POSITION, 64))
        {
            WIN = true;
            app.clear();
            if(level_speed < 1.5)app.draw(TEXT1);
            if(level_speed == 1.5)app.draw(TEXT2);
            app.display();
        }
        else if(PLAYER.detect_collition_y(TREASURE.BODY_POSITION, 64))
        {
            WIN = true;
            app.clear();
            if(level_speed < 1.5)app.draw(TEXT1);
            if(level_speed == 1.5)app.draw(TEXT2);
            app.display();
        }



        if(PLAYER.detect_collition_x(ENEMY.BODY_POSITION, 64))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();

        }
        else if(PLAYER.detect_collition_y(ENEMY.BODY_POSITION, 64))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();
        }

        if(PLAYER.detect_collition_x(ENEMY2.BODY_POSITION, 64))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();

        }
        else if(PLAYER.detect_collition_y(ENEMY2.BODY_POSITION, 64))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();
        }

         if(PLAYER.detect_collition_x(ENEMY3.BODY_POSITION, 100))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();

        }
        else if(PLAYER.detect_collition_y(ENEMY3.BODY_POSITION, 100))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();
        }

        if(PLAYER.detect_collition_x(ENEMY4.BODY_POSITION, 100))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();

        }
        else if(PLAYER.detect_collition_y(ENEMY4.BODY_POSITION, 100))
        {
            app.clear();
            app.draw(TEXT3);
            app.display();
            system("sleep 2s");
            level_speed = 2.0;
            app.close();
            main();
        }
/************************************************************************/





//#########################################################################################

        //grabing chest conditions
        if(WIN)
        {
            system("sleep 2s");
            app.close();
            level_speed += 0.5;
            main();
        }


        //beating the game
        if(level_speed > 1.9)
        {
            while(app.isOpen())
            {
            sf::Event ENDING_EVENT;
            while(app.pollEvent(ENDING_EVENT))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) app.close();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                app.close();
                level_speed = 0;
                main();
                }
            }

            app.clear(sf::Color::Black);
            app.draw(ENDING_SCREEN);
            app.display();

            }
            return 0;
        }
//###############################################################################################3



//$$$$$$$$$ render  $$$$$$$$$$$
        app.clear(WHITE_COLOR);
        app.draw(BACKGROUND_SPRITE);
        PLAYER.draw(app);
        TREASURE.draw(app);
        ENEMY.draw(app);

        if(level_speed > 0)
        {
        ENEMY2.draw(app);
        ENEMY2.position_update();
        }
        if(level_speed > 0.9)
        {
        ENEMY3.draw(app);
        ENEMY3.position_update();
        }
        if(level_speed > 1.4)
        {
        ENEMY4.draw(app);
        ENEMY4.position_update();
        ENEMY5.draw(app);
        ENEMY5.position_update();
        }

        app.display();
    }
    //ends while and main
    return 0;
}

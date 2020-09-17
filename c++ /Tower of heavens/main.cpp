#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>


//class for the rain
class Drop : public sf::RectangleShape{
private:

    float x;
    float y;
    float z;
    float yspeed;

public:
    Drop();

    void fall();

};

//scales the VALUE from START TO STOP
float map(float VALUE, float START1, float STOP1, float START2, float STOP2)
{
    return START2 + (STOP2 - START2) * (VALUE - START1) / (STOP1 - START1);

}

//constructor fisrt drop
Drop::Drop()
{   //private variables, x variable must have same value as window width
    this->x = rand() % 1280;
    //this makes the random value to be -100, givin the ilusion the rain is coming from avove the window
    this->y = rand() % 100 - 1000;
    //this value is used for the formula on map and witht he speed of rectangle falling
    this->z = rand() % 20 + 1;
    //speed variable
    this->yspeed = map(this->z, 1, 10, 3, 7);
    //public rectangle values
    this->setSize(sf::Vector2f(5.0, 22.25));
    this->setPosition(this->x, this->y);
    this->setFillColor(sf::Color(130,190,255));
    this->setScale(sf::Vector2f( map(this->z, 1, 15, .03, 0.7), map(this->z, 1, 10, 0.3, 0.7 )));
}



void Drop::fall()
{
    this-> move(sf::Vector2f(0.0, this->yspeed));

    //size of window height  if the rain goes out of bounds "600" repeat
    if(this->getPosition().y > 1280 )
    {
        this->x = rand() % 1280;
        this->y = rand() % 100 - 1200;
        this->z = rand() % 20 + 1;
        this->yspeed = map(this->z, 1, 10, 3, 7);
        this->setScale(sf::Vector2f( map(this->z, 1, 15, .03, 0.7), map(this->z, 1, 15, 0.3, 0.7 )));
        this->setPosition(this->x, this->y);
    }


}



 class Animation{

private:

    sf::Vector2u IMGCOUNT;
    sf::Vector2u CURRENT_IMAGE;

    float TOTAL_TIME;
    float SWITCH_TIME;

public:

    //rectangle used for the texture movement
    sf::IntRect RECTANGULO;


    // constructor
    Animation(sf::Texture* TEXTURE, sf::Vector2u imgcount, float switchtime);
    //deconstructor
    ~Animation();


    void UPDATE(int ROW, float DELTA_TIME, bool FACE_RIGHT);

};




// constructor body
Animation::Animation(sf::Texture* TEXTURE, sf::Vector2u imgcount, float switchtime){

    this->IMGCOUNT = imgcount;

    this->SWITCH_TIME = switchtime;

    //private float
    TOTAL_TIME = 0.0;

    //private vector2u
    CURRENT_IMAGE.x = 0;

    // assigning width and height of public rectangle
    RECTANGULO.width = TEXTURE->getSize().x / float(imgcount.x);
    RECTANGULO.height = TEXTURE->getSize().y / float(imgcount.y);
}



// this update fucntion allow us to move the recangle and it's called on the render part of the code.
void Animation::UPDATE(int ROW, float DELTA_TIME, bool FACE_RIGHT)
{
    //private vector
    CURRENT_IMAGE.y = ROW;
    //private float
    TOTAL_TIME = TOTAL_TIME + DELTA_TIME;


    if (TOTAL_TIME >= SWITCH_TIME)
    {
        TOTAL_TIME = TOTAL_TIME - SWITCH_TIME;

        CURRENT_IMAGE.x++;

        if(CURRENT_IMAGE.x >= IMGCOUNT.x)
        {
            CURRENT_IMAGE.x = 0;
        }

    }
    //top of int rect assignation
    RECTANGULO.top = CURRENT_IMAGE.y * RECTANGULO.height;


    if(FACE_RIGHT)
    {
        RECTANGULO.left = CURRENT_IMAGE.x * RECTANGULO.width;

        RECTANGULO.width = abs(RECTANGULO.width);
    }

    else
    {
        RECTANGULO.left = (CURRENT_IMAGE.x + 1) * abs(RECTANGULO.width);

        RECTANGULO.width = -abs(RECTANGULO.width);
    }

}

// deconstructor
Animation::~Animation(){}





//player class

class Player{

private:
    //creating animation object with no parameters yet.
    Animation animation;

    //private vareables
    sf::RectangleShape body;

    //the row will not be less than 0
    unsigned int ROW;

    float SPEED;

    bool FACE_RIGHT;



public:
    //for colition and object coordinates
    sf::Vector2f PLAYER_COORDINATES;

    sf::FloatRect PLAYER_BOUNDS;



    //contructor
    Player(sf::Texture* textura, sf::Vector2u img_count, float switch_time, float VELOCIDAD);

    //deconstructor
    ~Player();

    void Update(float delta_time);

    void Draw(sf::RenderWindow& window);

    void SET_PLAYER_DATA()
    {
        PLAYER_COORDINATES = body.getPosition();
        PLAYER_BOUNDS = body.getGlobalBounds();

    }



    void SET_POS(float pos_x, float pos_y);

};



Player::Player(sf::Texture* textura, sf::Vector2u img_count, float switch_time, float VELOCIDAD) : animation(textura, img_count, switch_time)
{
    this->SPEED = VELOCIDAD;
    ROW = 0;
    FACE_RIGHT = true;

    body.setSize(sf::Vector2f(64, 84));
    body.setTexture(textura);
    body.setPosition(80,650);
}

Player::~Player(){}




//update fucntion for controls and sprite animation
void Player::Update(float delta_time)
{
    sf::Vector2f MOVEMENT(0.0f,0.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))MOVEMENT.x += SPEED * delta_time;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))MOVEMENT.x -= SPEED * delta_time;

    if(MOVEMENT.x == 0.0f)
    {
        //IDLE ANIMATION ASIGNATION
        ROW = 3;
    }


    else
    {
        ROW = 0;

        if(MOVEMENT.x > 0.0f) FACE_RIGHT = true;

        else FACE_RIGHT = false;
    }

    //CALLING UPDATE FUCNTION FROM ANIMNATION CLASS
    animation.UPDATE(ROW, delta_time, FACE_RIGHT);

    body.setTextureRect(animation.RECTANGULO);

}



void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}



void Player::SET_POS(float pos_x, float pos_y)
{
    body.setPosition(pos_x, pos_y);
}


//i know its a global variable, i cuted corners
int LIVES = 3;
bool ENDING = false;

void PLAYER_LIVES()
{

    LIVES--;

}

int main()
{



    //main window and view
    sf::RenderWindow app(sf::VideoMode(1280, 720), "Tower Of Heavens");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);
    sf::View CAMERA(sf::FloatRect(0.0, 200.0, 1280.0, 600.0));
    //original center
    CAMERA.setCenter(640.0, 980.0);

    //game over condition
    if(LIVES == 0)
    {


        sf::Font FONT2;
        FONT2.loadFromFile("Arial.ttf");
        sf::Text TEXT2(" GAME OVER, PRESS ESC KEY TO EXIT ",FONT2);
        TEXT2.setCharacterSize(35);
        TEXT2.setFillColor(sf::Color::Magenta);

        sf::Text TEXT3(" OR PRESS SPACE BAR TO PLAY AGAINN ",FONT2);
        TEXT3.setCharacterSize(35);
        TEXT3.setFillColor(sf::Color::Magenta);
        TEXT2.setPosition(0,300);
        TEXT3.setPosition(0, 400);

        sf::Text FINAL_TEXT("WELL DONE, U DID IT!!!", FONT2);
        FINAL_TEXT.setCharacterSize(50);
        FINAL_TEXT.setFillColor(sf::Color::Magenta);
        FINAL_TEXT.setPosition(300, 0);

        while(app.isOpen())
        {
            sf::Event event2;
            while(app.pollEvent(event2))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) app.close();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    LIVES = 3;
                    main();
                }


            }
            app.clear();
            app.draw(TEXT2);
            app.draw(TEXT3);
            if(ENDING) app.draw(FINAL_TEXT);
            app.display();
        }


        return 0;
    }

    //*********************  SPRITES  *******************//

    //HEART SPRITES
    sf::Texture HEART_TEXTURE;
    if(!HEART_TEXTURE.loadFromFile("HEART.png"))return 0;
    sf::Sprite HEART;
    HEART.setTexture(HEART_TEXTURE);
    HEART.scale(5,5);
    HEART.setPosition(0, 700);

    sf::Sprite HEART2;
    HEART2.setTexture(HEART_TEXTURE);
    HEART2.scale(5,5);
    HEART2.setPosition(100, 700);

    sf::Sprite HEART3;
    HEART3.setTexture(HEART_TEXTURE);
    HEART3.scale(5,5);
    HEART3.setPosition(200, 700);



    //EMPTY HEART SPRITES
    sf::Texture EMPTY_HEART_TEXTURE;
    if(!EMPTY_HEART_TEXTURE.loadFromFile("HEARTEMPTY.png"))return 0;
    sf::Sprite EMPTY_HEART;
    EMPTY_HEART.setTexture(EMPTY_HEART_TEXTURE);
    EMPTY_HEART.scale(5,5);
    EMPTY_HEART.setPosition(0, 700);

    sf::Sprite EMPTY_HEART2;
    EMPTY_HEART2.setTexture(EMPTY_HEART_TEXTURE);
    EMPTY_HEART2.scale(5,5);
    EMPTY_HEART2.setPosition(100, 700);


    //ANIMATION PROPIETIES ASSIGN
    sf::Texture PLAYER_TEXTURE;
    if(!PLAYER_TEXTURE.loadFromFile("sprite2.png"))return 0;
    Player MAIN_PLAYER(&PLAYER_TEXTURE, sf::Vector2u(6,4), 0.060f, 100.0f);
    float DELTA_TIME;
    sf::Clock RELOJ;


    // PLAYER TEXTURE AND SPRITE 502 for enemy
    sf::Texture texture;
    if (!texture.loadFromFile("player.png"))return EXIT_FAILURE;
    sf::Sprite PLAYER(texture);
    PLAYER.scale(3,3);
    PLAYER.setPosition(200, 1200);


    //enemy sprite
    sf::Texture ENEMY_TEXTURE;
    if (!ENEMY_TEXTURE.loadFromFile("SKULL.png"))return EXIT_FAILURE;
    sf::Sprite ENEMY_SPRITE(ENEMY_TEXTURE);
    ENEMY_SPRITE.scale(5,5);
                            //ORIGINAL SCALE 3,3 ORIGINAL Y 502
    ENEMY_SPRITE.setPosition(20,-540);


    // PLATAFORM
    sf::Texture TEXTURE2;
    if (!TEXTURE2.loadFromFile("PLATAFORM.png"))return EXIT_FAILURE;
    sf::Sprite PLATAFORM1(TEXTURE2);
    PLATAFORM1.setPosition(1047, 314);

    //LEFT WALL SPRITE this help us give the illusion of hitting the wall,
    sf::Texture TEXTURE3;
    if (!TEXTURE3.loadFromFile("WALL.png"))return EXIT_FAILURE;
    sf::Sprite PLATAFORM2(TEXTURE3);
    PLATAFORM2.setPosition(0,0);
    PLATAFORM2.scale(1,12);


    //BACKGROUND 1
    sf::Texture TEXTURE4;
    if (!TEXTURE4.loadFromFile("FLOOR1.png"))return EXIT_FAILURE;
    sf::Sprite FLOOR1(TEXTURE4);

    //background 2
    sf::Texture TEXTURE5;
    if (!TEXTURE5.loadFromFile("FLOOR2.png"))return EXIT_FAILURE;
    sf::Sprite FLOOR2(TEXTURE5);
    FLOOR2.setPosition(FLOOR2.getPosition().x, -1270);



    //CREATING ICE BLOCKS
    sf::Texture ICE_PLATAFORM;
    if (!ICE_PLATAFORM.loadFromFile("PLATAFORM2.png"))return EXIT_FAILURE;

    sf::Sprite BLOCKS[10];
    for(int x = 0; x < 5; x++) BLOCKS[x].setTexture(TEXTURE2);

    //initial position of the blocks
    BLOCKS[0].setPosition(800, 1040);
    BLOCKS[1].setPosition(480,905);
    BLOCKS[2].setPosition(130, 810);
    BLOCKS[3].setPosition(450, 590);
    BLOCKS[4].setPosition(230, 350);

    //MOVING BLOCKS
    BLOCKS[5].setPosition(1047, 314);
    BLOCKS[6].setPosition(1047, 314);
    BLOCKS[7].setPosition(680, -140);
    BLOCKS[8].setPosition(400, -140);
    BLOCKS[9].setPosition(150, -140);
    BLOCKS[5].setTexture(ICE_PLATAFORM);
    BLOCKS[6].setTexture(ICE_PLATAFORM);
    BLOCKS[7].setTexture(ICE_PLATAFORM);
    BLOCKS[8].setTexture(ICE_PLATAFORM);
    BLOCKS[9].setTexture(ICE_PLATAFORM);

    //movement speed of the moving blocks
    int BLOCK_SPEED = 4;
    int BLOCK_SPEED2 = 3;
    int BLOCK_SPEED3 = -3;


    //CREATING SPRITE BAR FOR TESTING PORPUSES
    sf::Texture LONG_BAR;
    if(!LONG_BAR.loadFromFile("BAR.png")) return 0;
    sf::Sprite GREEN_BAR;
    GREEN_BAR.setTexture(LONG_BAR);
    GREEN_BAR.setPosition(0,775);

    sf::Texture LONG_BAR_2;
    if(!LONG_BAR_2.loadFromFile("SPIKES.png")) return 0;
    sf::Sprite RED_BAR;
    RED_BAR.setTexture(LONG_BAR_2);
    RED_BAR.setPosition(0.0, 1250);

    sf::Texture GROUND_TEXTURE;
    if(!GROUND_TEXTURE.loadFromFile("TILEFLOOR.png")) return 0;
    sf::Sprite GROUND;
    GROUND.setTexture(GROUND_TEXTURE);
    GROUND.setPosition(272, -366);

    sf::Sprite GROUND2;
    GROUND2.setTexture(GROUND_TEXTURE);
    GROUND2.setPosition(-200, -470);

    sf::Sprite EXIT;
    EXIT.setTexture(texture);
    EXIT.setPosition(20, -502);
    EXIT.scale(3,3);

    //creating font and text
    sf::Font FONT;
    FONT.loadFromFile("Arial.ttf");
    sf::Text TEXT("LIFE",FONT);
    TEXT.setCharacterSize(30);
    TEXT.setFillColor(sf::Color::Magenta);



    //ENEMY LIFE
    int ENEMY_LIFE = 1;


    //variables for gravity and collition.
    float VELOCITY = 0;
    float GRAVITY = 2.0;
    bool COLLITION = false;
    bool COLLITION2 = false;
    bool COLLITION3 = false;
    bool COLLITION4 = false;
    bool COMPLETE = false;



    //RAINDROPS OBJECT ARRAY
    Drop DROPS[400];


	// MAIN WHILE LOOP
    while (app.isOpen())
    {
        //variables for player conditions and jumping.
        float FLOOR = 1200;
        bool JUMPING = false;
        bool GROUNDED = false;

        //retarting the clock for animation
        DELTA_TIME = RELOJ.restart().asSeconds();
        //animated body is gonna move along player sprite
        MAIN_PLAYER.SET_POS(PLAYER.getPosition().x, PLAYER.getPosition().y -24);

        // events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // X CLOSING WINDOW
            if (event.type == sf::Event::Closed)
                app.close();

            //COLSING WINDOW WITH ESCAPE KEY
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) app.close();


        }

        //PLAYER CONTROLS
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) PLAYER.move(10,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) PLAYER.move(-10,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))JUMPING = true;
        //maual camera controls
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) CAMERA.move(0,-10);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) CAMERA.move(0,10);
/*      PLATAFORM CONTROLS FOR TESTING PORPUSES
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) PLATAFORM1.move(0,-5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) PLATAFORM1.move(0,5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) PLATAFORM1.move(-5,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) PLATAFORM1.move(5,0);
*/



        //activating the gravity.
        VELOCITY += GRAVITY;
        PLAYER.move(0,VELOCITY);


        //OUT OF BOUNDS PREVENTIONS PLAYER, AND VIEW.
        if(PLAYER.getPosition().x > 1130) PLAYER.setPosition(1130, PLAYER.getPosition().y);
        else if(PLAYER.getPosition().x < 0) PLAYER.setPosition(0, PLAYER.getPosition().y);

        if(PLAYER.getPosition().y >= FLOOR)
        {
            PLAYER.setPosition(PLAYER.getPosition().x ,FLOOR);
            GROUNDED = true;
            //prevents velocity from increasing further.
            VELOCITY = 48;
        }
        //preventing camera from going ovet the floor
        if(CAMERA.getCenter().y > 980) CAMERA.setCenter(CAMERA.getCenter().x , 980);


        //jumping from the floor
        if( (JUMPING) & (GROUNDED) ) VELOCITY = -32;





        //ICED BLOCKS movement
        if(BLOCKS[5].getPosition().x <= 449) BLOCK_SPEED = std::abs(BLOCK_SPEED);
        if(BLOCKS[5].getPosition().x >= 930) BLOCK_SPEED = -std::abs(BLOCK_SPEED);
        BLOCKS[5].move(BLOCK_SPEED, 0);

        if(BLOCKS[6].getPosition().y <= -200) BLOCK_SPEED2 = std::abs(BLOCK_SPEED2);
        if(BLOCKS[6].getPosition().y >= 313) BLOCK_SPEED2 = -std::abs(BLOCK_SPEED2);
        BLOCKS[6].move(0, BLOCK_SPEED2);

        if(BLOCKS[7].getPosition().y < -170) BLOCK_SPEED3 = std::abs(BLOCK_SPEED3);
        if(BLOCKS[7].getPosition().y >= -98) BLOCK_SPEED3 = -std::abs(BLOCK_SPEED3);

        BLOCKS[7].move(0,BLOCK_SPEED3);
        BLOCKS[8].move(0,BLOCK_SPEED3);
        BLOCKS[9].move(0,BLOCK_SPEED3);


        //COLITIN DETECTION FOR BLOCKS
        sf::FloatRect PLAYER_BOUNDS = PLAYER.getGlobalBounds();
        for(int x = 0; x < 10; x++)
        {
            if(PLAYER_BOUNDS.intersects(BLOCKS[x].getGlobalBounds())) COLLITION = true;
            else{COLLITION = false;}
            if(COLLITION)
            {
                if(PLAYER.getPosition().y > BLOCKS[x].getPosition().y) PLAYER.setPosition(PLAYER.getPosition().x, BLOCKS[x].getPosition().y + 96);

                if(PLAYER.getPosition().y  < BLOCKS[x].getPosition().y)
                {
                    VELOCITY = 0;

                    PLAYER.setPosition(PLAYER.getPosition().x, BLOCKS[x].getPosition().y - 32);

                    GROUNDED = true;
                    //allows jumping while standing on plataform.
                    if(JUMPING & GROUNDED) VELOCITY = -32;


                }
            }
        }

        //collition for ground and ground2 sprites
        sf::FloatRect GROUND_BOUNDS = GROUND.getGlobalBounds();
        if(PLAYER_BOUNDS.intersects(GROUND_BOUNDS)) COLLITION3 = true;
        else{COLLITION3 = false;}
        if(COLLITION3)
        {
            if(PLAYER.getPosition().y > GROUND.getPosition().y) PLAYER.setPosition(PLAYER.getPosition().x, GROUND.getPosition().y + 50);
            if(PLAYER.getPosition().y < GROUND.getPosition().y)
            {
                VELOCITY = 0;
                PLAYER.setPosition(PLAYER.getPosition().x, GROUND.getPosition().y -32);
                GROUNDED = true;
                if(JUMPING & GROUNDED) VELOCITY = -32;
            }

        }

        sf::FloatRect GROUND_BOUNDS2 = GROUND2.getGlobalBounds();
        if(PLAYER_BOUNDS.intersects(GROUND_BOUNDS2)) COLLITION4 = true;
        else{COLLITION4 = false;}
        if(COLLITION4)
        {
            if(PLAYER.getPosition().y > GROUND2.getPosition().y) PLAYER.setPosition(PLAYER.getPosition().x, GROUND2.getPosition().y + 50);
            if(PLAYER.getPosition().y < GROUND2.getPosition().y)
            {
                VELOCITY = 0;
                PLAYER.setPosition(PLAYER.getPosition().x, GROUND2.getPosition().y -32);
                GROUNDED = true;
                if(JUMPING & GROUNDED) VELOCITY = -32;
            }

        }


        //COLLITION CONDITIONS FOR LEFT wall
        sf::FloatRect PLATAFORM2_BOUNDS = PLATAFORM2.getGlobalBounds();
        if(PLAYER_BOUNDS.intersects(PLATAFORM2_BOUNDS)) COLLITION2 = true;
        else{COLLITION2 = false;}
        if(COLLITION2)
        {
            if(PLAYER.getPosition().x > PLATAFORM2.getPosition().x)PLAYER.setPosition(PLAYER.getPosition().x + 10, PLAYER.getPosition().y);

            if(PLAYER.getPosition().x < PLATAFORM2.getPosition().x)PLAYER.setPosition(PLAYER.getPosition().x -10, PLAYER.getPosition().y);
        }



        //COLLITION DETECTION FOR BARS
        if(PLAYER.getPosition().y <= (GREEN_BAR.getPosition().y + 40))
        {
            GREEN_BAR.move(0.0, -6.0);
            RED_BAR.move(0.0, -6.0);
            CAMERA.move(0.0, -6.0);
        }

        //positioning of hearts and text using the green bar movement
        HEART.setPosition(GREEN_BAR.getPosition().x, GREEN_BAR.getPosition().y - 100);
        HEART2.setPosition(GREEN_BAR.getPosition().x + 100, GREEN_BAR.getPosition().y - 100);
        HEART3.setPosition(GREEN_BAR.getPosition().x + 200, GREEN_BAR.getPosition().y - 100);

        EMPTY_HEART.setPosition(GREEN_BAR.getPosition().x + 100, GREEN_BAR.getPosition().y - 100);
        EMPTY_HEART2.setPosition(GREEN_BAR.getPosition().x + 200, GREEN_BAR.getPosition().y - 100);
        TEXT.setPosition(HEART.getPosition().x, HEART.getPosition().y + 80);



        //LOOSING CONDITION EVENT WHEN FALLING TOO HIGH
        if(PLAYER.getPosition().y  >= RED_BAR.getPosition().y + 18)
        {
            PLAYER_LIVES();
            sf::Time t1 = sf::seconds(1);
            sf::sleep(t1);
            app.close();
            main();

        }


        //ENEMY MOVEMENT
        if(PLAYER.getPosition().y <= ENEMY_SPRITE.getPosition().y + 38)
        {
            if(ENEMY_SPRITE.getPosition().x < PLAYER.getPosition().x) ENEMY_SPRITE.move(7,0);

            if(ENEMY_SPRITE.getPosition().x > PLAYER.getPosition().x) ENEMY_SPRITE.move(-7,0);

        }

        //enemy damage
        sf::FloatRect ENEMY_BOUNDS = ENEMY_SPRITE.getGlobalBounds();
        if(ENEMY_BOUNDS.intersects(PLAYER_BOUNDS))
        {
            if(PLAYER.getPosition().y < ENEMY_SPRITE.getPosition().y)
            {
                ENEMY_LIFE--;
                VELOCITY = -32;
            }

            if(ENEMY_LIFE == 0) ENEMY_SPRITE.setPosition(1400, -50);


            if(PLAYER.getPosition().y > ENEMY_SPRITE.getPosition().y )
            {
                LIVES--;
                app.close();
                main();
                if(LIVES == 0)
                {
                    app.close();
                    main();
                }
            }

        }

        //LEVEL COMPLETE

        //BEATING THE GAME
        sf::FloatRect EXIT_BOUNDS = EXIT.getGlobalBounds();
        if(PLAYER_BOUNDS.intersects(EXIT_BOUNDS)) COMPLETE = true;
        if(COMPLETE)
        {
            ENDING = true;
            app.close();
            LIVES = 0;
            main();
        }


        // RENDER

        app.clear();
        //VIEW SET
        app.setView(CAMERA);
        //for loop to draw the rain
        for(int i = 0; i < 400; i++)
        {
            DROPS[i].fall();
            app.draw(DROPS[i]);
        }

        //BACKGROUND
        app.draw(FLOOR1);
        app.draw(FLOOR2);

        //TESTING SPRITES
        //app.draw(PLAYER);
        //app.draw(PLATAFORM1);
        //app.draw(PLATAFORM2);
        //app.draw(GREEN_BAR);

        //DRAWING THE BLOCKS ARRAY
        for(int i = 0; i < 10; i++) app.draw(BLOCKS[i]);

        app.draw(GROUND);

        //ANIMATION DRAWING AND RENDER
        MAIN_PLAYER.Update(DELTA_TIME);
        MAIN_PLAYER.Draw(app);

        app.draw(ENEMY_SPRITE);
        app.draw(TEXT);
        app.draw(HEART);
        if(LIVES == 3 || LIVES == 2)app.draw(HEART2);
        if(LIVES == 3) app.draw(HEART3);
        app.draw(EMPTY_HEART);
        app.draw(EMPTY_HEART2);
        //original sprite was red bar
        app.draw(RED_BAR);

        app.display();

    }


    return 0;
}

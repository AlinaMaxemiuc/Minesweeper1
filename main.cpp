#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<SFML/Window.hpp>
#include <time.h>
#include<iostream>
#include <sstream>

using namespace sf;

int main()
{
    int nr_click=0;

    //define clock-
    sf::Clock clock;
    sf::Time micro = sf::microseconds( 10000 );
    sf::Time milli = sf::milliseconds( 10 );
    sf::Time second = sf::seconds( 0.01f );
    srand(time(0));

    //define font
    sf::Font font;
    font.loadFromFile("font/font.ttf");

    //define text
    sf::Text text;
    text.setCharacterSize(25);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(350,350);

    //crete grid and graphic program
    RenderWindow app(VideoMode(500, 500), "Minesweeper!");

    int w=32;
    int grid[15][15];
    int sgrid[12][12]; //for showing

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    for (int i=1; i<=10; i++)
        for (int j=1; j<=10; j++)
        {
            sgrid[i][j]=10;
            if (rand()%5==0)  grid[i][j]=9;
            else grid[i][j]=0;
        }

    for (int i=1; i<=10; i++)
        for (int j=1; j<=10; j++)
        {
            int n=0;
            if (grid[i][j]==9) continue;
            if (grid[i+1][j]==9) n++;
            if (grid[i][j+1]==9) n++;
            if (grid[i-1][j]==9) n++;
            if (grid[i][j-1]==9) n++;
            if (grid[i+1][j+1]==9) n++;
            if (grid[i-1][j-1]==9) n++;
            if (grid[i-1][j+1]==9) n++;
            if (grid[i+1][j-1]==9) n++;
            grid[i][j]=n;
        }
    while (app.isOpen())
    {
        //elapsed time
        sf::Time elapsed = clock.getElapsedTime( );

        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;

        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) sgrid[x][y]=grid[x][y],nr_click++;
                else if (e.key.code == Mouse::Right) sgrid[x][y]=11;
        }
        app.clear(Color::White);

        for (int i=1; i<=10; i++)
            for (int j=1; j<=10; j++)
            {
                if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
                s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));
                s.setPosition(i*w, j*w);


                app.draw(s);
            }
        //print time and click
        std::stringstream ss;
        ss << "Time "<<elapsed.asSeconds( )<<"\n"
           <<"Click "<<nr_click;
        text.setString(ss.str());
        app.draw(text);

        app.display();
    }

    return 0;





}

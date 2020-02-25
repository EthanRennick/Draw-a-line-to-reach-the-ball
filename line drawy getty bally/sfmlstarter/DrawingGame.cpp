// Author: Dr Noel O'Hara
// SFML Line Drawing Game starter!
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>

// I use a couple of h files from thor library.
//https://github.com/Bromeon/Thor
#include "VectorAlgebra2D.h"


#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>

enum class DrawingStates { NONE, DRAWING };
enum class GameState { PLAYING, DRAWING };
class Line
{
public:
	sf::Vector2f endPoints[2];
};
class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum = 0;
	DrawingStates drawingState;
	sf::CircleShape playerShape;
	sf::CircleShape targetShape;
	GameState gameState;

	sf::Vector2f velocity;
	sf::Vector2f position;
	Line drawLine;
	std::vector<Line> Lines;
	float playerRadius = 10;

	sf::Vector2f gravity;
	float SCALE = 50;
	int score;
	int timer = 500;
	bool moveBall = false;
	int allowance = 0;

	Game()
	{
		drawingState = DrawingStates::NONE;
		gameState = GameState::DRAWING;
		window.create(sf::VideoMode(800, 600), "Pixel Physics");
	}

	bool CollisionResponseCircleLine(const  sf::Vector2f& endPoint1, const sf::Vector2f& endPoint2, sf::CircleShape& playerShape, sf::Vector2f& velocity)
	{
		sf::Vector2f wallMovedtoZero = endPoint2 - endPoint1;
		if (wallMovedtoZero.x == 0.0 && wallMovedtoZero.y == 0.0)
		{
			return false;
		}
		float angleToRotate = thor::polarAngle(wallMovedtoZero);
		thor::rotate(wallMovedtoZero, -angleToRotate);

		sf::Vector2f transformedPlayerPos = playerShape.getPosition() - endPoint1;
		sf::Vector2f velocityMoved = transformedPlayerPos + velocity;

		thor::rotate(transformedPlayerPos, -angleToRotate);
		thor::rotate(velocityMoved, -angleToRotate);

		velocityMoved = velocityMoved - transformedPlayerPos;

		if (velocityMoved.y <= 0)
		{
			return false;
		}

		if (abs(transformedPlayerPos.y) > playerShape.getRadius())
		{
			return false;
		}
		if (transformedPlayerPos.x + playerShape.getRadius() < 0)
		{
			return false;
		}
		if (transformedPlayerPos.x - playerShape.getRadius() > wallMovedtoZero.x)
		{
			return false;
		}

		transformedPlayerPos.y = -playerShape.getRadius();


		velocityMoved.y = -1.0 * velocityMoved.y;


		velocityMoved = velocityMoved + transformedPlayerPos;
		thor::rotate(velocityMoved, angleToRotate);
		thor::rotate(transformedPlayerPos, angleToRotate);
		velocityMoved = velocityMoved - transformedPlayerPos;
		transformedPlayerPos = transformedPlayerPos + endPoint1;
		velocity = velocityMoved;

		playerShape.setPosition(transformedPlayerPos);
		return true;

	}

	void init()
	{
		allowance = rand() % 10 + 5;
		std::cout << "Allowance: " << allowance << std::endl;
		
		Lines.clear();
		Line wall;
		wall.endPoints[0] = sf::Vector2f(800, 0);
		wall.endPoints[1] = sf::Vector2f(0, 0);
		Lines.push_back(wall);
		wall.endPoints[0] = sf::Vector2f(800, 600);
		wall.endPoints[1] = sf::Vector2f(800, 0);
		Lines.push_back(wall);
		wall.endPoints[0] = sf::Vector2f(0, 600);
		wall.endPoints[1] = sf::Vector2f(800, 600);
		Lines.push_back(wall);
		wall.endPoints[0] = sf::Vector2f(0, 0);
		wall.endPoints[1] = sf::Vector2f(0, 600);
		Lines.push_back(wall);
		wall.endPoints[0] = sf::Vector2f(rand() % 600, rand() % 600);
		wall.endPoints[1] = sf::Vector2f(rand() % 600, rand() % 600);
		Lines.push_back(wall);

		view = window.getDefaultView();
		playerShape.setRadius(playerRadius);
		playerShape.setPosition(100, 100);
		playerShape.setOrigin(sf::Vector2f(playerRadius, playerRadius));
		velocity = sf::Vector2f(0.0f, 0.0f);
		position = sf::Vector2f(100, 50);
		targetShape.setPosition(rand() % 600, rand() % 600);
		targetShape.setRadius(5);
		gameState = GameState::DRAWING;

		gravity.x = 0.0;
		gravity.y = 9.8f * SCALE;

	}
	void run()
	{

		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			timeSinceLastUpdate += clock.restart();
			if (timeSinceLastUpdate > timePerFrame)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					gameState = GameState::PLAYING;


				}
				if (drawingState == DrawingStates::NONE)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						drawLine.endPoints[0] = (sf::Vector2f)sf::Mouse::getPosition(window);
						drawLine.endPoints[1] = drawLine.endPoints[0];
						drawingState = DrawingStates::DRAWING;
					}

				}
				else if (drawingState == DrawingStates::DRAWING) {

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						drawLine.endPoints[1] = (sf::Vector2f)sf::Mouse::getPosition(window);

					}
					else {
						drawingState = DrawingStates::NONE;
						Lines.push_back(drawLine);
					}

				}


				float timeChange = (float)timeSinceLastUpdate.asSeconds();
				timeChange = 1.0f / 60.0f;
				playerShape.setPosition(position);

				for (int i = 0; i < Lines.size(); i++)
				{


					if (CollisionResponseCircleLine(Lines[i].endPoints[0], Lines[i].endPoints[1], playerShape, velocity))
					{
						playerShape.setFillColor(sf::Color::Red);
						break;
					}
					else {
						playerShape.setFillColor(sf::Color::Blue);
					}
				}
				if (gameState == GameState::PLAYING)
				{
					
					timer -= .1;
					std::cout << timer << std::endl;
					position.x = position.x + velocity.x * timeChange;
					position.y = position.y + velocity.y * timeChange;

					velocity.x = velocity.x + gravity.x * timeChange;
					velocity.y = velocity.y + gravity.y * timeChange;
					velocity.x *= 0.99;
					velocity.y *= 0.99;
				}
				if (targetShape.getGlobalBounds().intersects(playerShape.getGlobalBounds()))
				{
					score++;
					std::cout << "Score: " << score << std::endl;
					timer = 500 + timer;
					init();
				}
				if (timer == 0)
				{
					timer = 500;
					score--;
					std::cout << "Score: " << score << std::endl;
					init();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					init();
				}
				window.clear();
				if (drawingState == DrawingStates::DRAWING)
				{
					sf::Vertex line[] =
					{
						sf::Vertex(drawLine.endPoints[0]),
						sf::Vertex(drawLine.endPoints[1])
					};
					window.draw(line, 2, sf::Lines);
				}
				for (int i = 0; i < Lines.size(); i++)
				{
					sf::Vertex line[] =
					{
						sf::Vertex(Lines[i].endPoints[0]),
						sf::Vertex(Lines[i].endPoints[1])
					};
					window.draw(line, 2, sf::Lines);
				}
				window.draw(playerShape);
				window.draw(targetShape);

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};


int main()
{

	Game game;
	game.init();
	game.run();
	return 0;
}
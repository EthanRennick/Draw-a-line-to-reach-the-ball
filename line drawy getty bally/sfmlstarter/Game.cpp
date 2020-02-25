//// Author: Dr Noel O'Hara
//// SFML Starter for an awesome game you can make!
//#ifdef _DEBUG 
//#pragma comment(lib,"sfml-graphics-d.lib") 
//#pragma comment(lib,"sfml-audio-d.lib") 
//#pragma comment(lib,"sfml-system-d.lib") 
//#pragma comment(lib,"sfml-window-d.lib") 
//#pragma comment(lib,"sfml-network-d.lib") 
//#else 
//#pragma comment(lib,"sfml-graphics.lib") 
//#pragma comment(lib,"sfml-audio.lib") 
//#pragma comment(lib,"sfml-system.lib") 
//#pragma comment(lib,"sfml-window.lib") 
//#pragma comment(lib,"sfml-network.lib") 
//#endif 
//
//#include <SFML/Graphics.hpp>
//// I use a couple of h files from thor library.
////https://github.com/Bromeon/Thor
//#include "VectorAlgebra2D.h"
//
//
//#include <iostream>
//#include <stdlib.h> 
//#include <time.h> 
//#include <list>
//#include <vector>
//
//enum PlayerState { ready, drawingLine, Jump };
//class Game
//{
//public:
//	//create Window
//	sf::RenderWindow window;
//	sf::View view;
//	float randomNum = 0;
//
//	sf::CircleShape playerShape;
//	sf::Vector2f moveForce;
//	PlayerState playerState = ready;
//	float gravityScale = 20;
//	sf::Vector2f velocity = { 0,0 };
//	float playerMaxSpeed = 400;
//	sf::Vector2f gravity{ 0.0f, 9.8f * gravityScale };
//	
//	sf::Vector2f normalised ;
//
//	sf::CircleShape bird;
//	sf::Vector2f birdPosition{ 0,0 };
//	
//	int level = 0;
//	int score = 0;
//	sf::Text scoreText;
//	sf::Text clickText;
//	sf::Font font;
//	int clicks = 0;
//
//	
//
//	Game()
//	{
//		window.create(sf::VideoMode(1200, 600), "Ball bird rope game");
//	}
//	
//	void init()
//	{
//
//		view = window.getDefaultView();
//		playerShape.setRadius(20);
//		playerShape.setPosition(160, 500);
//		playerShape.setOrigin(sf::Vector2f(20, 20));
//		sf::Vector2f normalised = thor::unitVector(playerShape.getPosition());
//		float l = thor::length(gravity);
//		float r = thor::toDegree(10.0);
//		
//		thor::setLength(normalised, 100.0f);
//		thor::rotate(normalised, 10.0f);
//
//		bird.setRadius(10);
//		birdPosition.x = rand() % 1200 + 1;
//		birdPosition.y = rand() % 600 + 1;
//		bird.setPosition(birdPosition);
//		bird.setFillColor(sf::Color::Red);
//		
//		if (!font.loadFromFile("arial.ttf"))
//		{
//			// error...
//		}
//		scoreText.setFont(font);
//		scoreText.setString("Score: " + std::to_string(score));
//		scoreText.setCharacterSize(24);
//		scoreText.setFillColor(sf::Color::White);
//
//		clickText.setFont(font);
//		clickText.setString("Clicks: " + std::to_string(clicks));
//		clickText.setCharacterSize(24);
//		clickText.setFillColor(sf::Color::White);
//		clickText.setPosition(0, 28);
//
//	}
//
//	void run()
//	{
//	
//		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
//
//
//		sf::Time timeSinceLastUpdate = sf::Time::Zero;
//
//		
//		sf::Clock clock;
//
//		clock.restart();
//
//		while (window.isOpen())
//		{
//			
//			sf::Event event;
//			while (window.pollEvent(event))
//			{
//				if (event.type == sf::Event::Closed)
//					window.close();
//			}
//
//			
//			timeSinceLastUpdate += clock.restart();
//
//			
//
//			if (timeSinceLastUpdate > timePerFrame)
//			{
//
//				if (playerState == ready)
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//					{
//						playerState = drawingLine;
//					}
//				}
//				if (playerState == drawingLine)
//				{
//					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
//					{
//						sf::Vector2f localPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
//						sf::Vector2f newVelocity;
//						newVelocity = localPosition - playerShape.getPosition();
//						clicks++;
//						clickText.setString("Clicks: " + std::to_string(score));
//
//						if (thor::length(moveForce) < playerMaxSpeed)
//						{
//							velocity = -newVelocity;
//							clicks++;
//							clickText.setString("Clicks: " + std::to_string(score));
//
//						}
//						else {
//							thor::setLength(moveForce, playerMaxSpeed);
//							velocity = -newVelocity;
//							clicks++;
//							clickText.setString("Clicks: " + std::to_string(score));
//
//						}
//						
//
//						playerState = Jump;
//						gravity.y = 9.8 * gravityScale;
//					}
//				}
//				if (playerState == Jump)
//				{
//					playerState = ready;
//				}
//
//
//
//				
//				
//				velocity = velocity + (gravity * timeSinceLastUpdate.asSeconds());
//				
//				playerShape.move(velocity.x * timeSinceLastUpdate.asSeconds(), velocity.y * timeSinceLastUpdate.asSeconds());
//
//
//
//				if (playerShape.getPosition().y > 600 - playerShape.getRadius())
//				{
//					playerShape.setPosition(playerShape.getPosition().x, 600 - playerShape.getRadius());
//					velocity.y = (velocity.y * -1);
//				}
//				if (playerShape.getPosition().x > 1200 - playerShape.getRadius())
//				{
//					velocity.x = (velocity.x * -1);
//				}
//				if (playerShape.getPosition().x < -1)
//				{
//					velocity.x = (velocity.x * -1);
//				}
//				if (playerShape.getPosition().y < 0)
//				{
//					velocity.y = (velocity.y * -1);
//				}
//
//				if (playerShape.getGlobalBounds().intersects(bird.getGlobalBounds()))
//				{
//					level++;
//					score++;
//					scoreText.setString("Score: " + std::to_string(score));
//					birdPosition.x = rand() % 1200 + 1;
//					birdPosition.y = rand() % 600 + 1;
//					bird.setPosition(birdPosition);
//				}
//				
//				window.clear();
//				if (playerState == drawingLine)
//				{
//					sf::Vector2i localPosition = sf::Mouse::getPosition(window);
//					sf::Vertex line[] =
//					{
//						sf::Vertex(sf::Vector2f(localPosition.x, localPosition.y)),
//						sf::Vertex(sf::Vector2f(playerShape.getPosition().x, playerShape.getPosition().y))
//					};
//
//					window.draw(line, 2, sf::Lines);
//				}
//				window.draw(playerShape);
//				/*for (int i = 0; i < level + 1; i++)
//				{
//					birdPosition.x = rand() % 1200 + 1;
//					birdPosition.y = rand() % 600 + 1;
//					bird.setPosition(birdPosition);
//					window.draw(bird);
//				}*/
//				window.draw(scoreText);
//				window.draw(clickText);
//				window.draw(bird);
//
//				window.display();
//
//				
//				timeSinceLastUpdate = sf::Time::Zero;
//			}
//		}
//	}
//};
//
//
//int main()
//{
//
//
//	Game game;
//	
//
//	game.init();
//
//	game.run();
//
//
//
//	return 0;
//}
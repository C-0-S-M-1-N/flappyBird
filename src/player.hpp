#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

#define gVector 9.8

extern bool gameOver;

class Player{
	float Y; //height
	const int x, mass;
	sf::Texture idle, up, down;
	sf::RectangleShape body;
	float speed = 0, previousSpeed = 0, force = 0, acc = 0;

public:
	Player(int _x, int m): x{_x}, mass{m} {
		Y = 180.0f;
		force = gVector / (mass*1.0f);
	}
	void addForce(float f){
		speed = 0;
		acc = f / mass;
	}

	void draw(sf::RenderWindow &win, sf::Time t){
		if(Y <= body.getSize().y || Y >= win.getSize().y - body.getSize().y) {addForce(0); gameOver = true;}
		// std::cout<<"speed: "<<speed<<" acc: "<<acc<<" force: "<<force<<" Y: "<<Y<<std::endl;
		speed += acc;
		Y -= speed*t.asSeconds();
		acc = -gVector;
		// force = 0;
		if(speed > 0) {
			body.setTexture(&down);	
		}
		else if(speed < 0) {
			body.setTexture(&up);
		}
		else body.setTexture(&idle);

		body.setPosition(x, Y);
		win.draw(body);
		
	}
	void setTexture(sf::Texture &id, sf::Texture &u, sf::Texture &dw){
		idle = id;
		up = u;
		down = dw;
		
		body.setSize(sf::Vector2f(idle.getSize().x, idle.getSize().y));
		body.setTexture(&idle);
		body.setOrigin(body.getSize().x/2, body.getSize().y/2);	
		body.setScale(3, 3);	
	}

	bool colision(sf::RectangleShape &col){
		sf::FloatRect b(body.getPosition().x, body.getPosition().y, body.getSize().x/2, body.getSize().y/2);
		return b.intersects(col.getGlobalBounds());
	}
	float getSpeed(){ return speed;}
};

class Pipe{
	sf::Texture up, down;
	sf::RectangleShape U, D;
public:
	Pipe(){}
	void setTexture(sf::Texture &u, sf::Texture &d){
		up = u;
		down = d;
		U.setSize(sf::Vector2f(up.getSize()));
		D.setSize(sf::Vector2f(down.getSize()));
		U.setTexture(&up);	D.setTexture(&down);
		U.setScale(3, 3);	D.setScale(3, 3);
		U.setOrigin(U.getSize().x/2, 0-70);	D.setOrigin(D.getSize().x/2, D.getSize().y);
		// D.setOrigin(D.getSize().x/2, 0-70);
	}
	void setPos(int x, int y){
		U.setPosition(x, y);
		D.setPosition(x, y);	
	}
	void draw(sf::RenderWindow &win){
		win.draw(U);
		win.draw(D);
	}
	sf::RectangleShape& getU(){ return U;}
	sf::RectangleShape& getD(){ return D;}
};

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#define MIN 80
#define MAX win.getSize().y-80*4

bool gameOver = 0;
int score = 0;
Player player(512/4, 20);
Pipe _pipe_;
sf::Sprite bkg;
sf::Texture t, b, ti, td, pipeU, pipeD;
std::vector<int> pipePos;
std::vector<std::pair<float, float>> pos;
sf::Font font;

void draw(sf::RenderWindow &win, sf::Time time){
	player.draw(win, time);
	// _pipe_.draw(win);
}
void logic(sf::RenderWindow &win){
	if(pos.empty()){
		pos.push_back(std::make_pair(win.getSize().x, rand()%(MAX-MIN)+MIN));
	}
	for(int i = 0; i<pos.size(); i++){
		pos[i].first -= 1.5f;

		_pipe_.setPos(pos[i].first, pos[i].second);
		
		if(player.colision(_pipe_.getD()) || player.colision(_pipe_.getU())){
			std::cout<<"Game Over"<<std::endl;
			gameOver = 1;
		}
		if(pos[i].first == 512/4) score++;
		_pipe_.draw(win);
	}
	if(pos[0].first <= -30) pos.erase(pos.begin());
	if((int)pos[pos.size()-1].first == win.getSize().x - 270){
		pos.push_back(std::make_pair(win.getSize().x + 30, rand()%(MAX-MIN)+MIN));
	}
}

auto main() -> int{
	srand(unsigned(time(NULL)));
	sf::RenderWindow win(sf::VideoMode(512, 768), "Flappy Bird");
	sf::Event _e;
	sf::Clock c;
	sf::Time time;

	b.loadFromFile("src/sprite.png", sf::IntRect(0, 0, 128, 256));
	bkg.setTexture(b);
	bkg.setScale(4, 3);
	
	t.loadFromFile("src/sprite.png", sf::IntRect(0, 490, 24, 24));
	ti.loadFromFile("src/sprite.png", sf::IntRect(24, 490, 24, 24));
	td.loadFromFile("src/sprite.png", sf::IntRect(56, 490, 24, 24));
	pipeD.loadFromFile("src/sprite.png", sf::IntRect(55, 325, 30, 160));
	pipeU.loadFromFile("src/sprite.png", sf::IntRect(82, 323, 30, 160));

	font.loadFromFile("src/font.ttf");
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(50);
	scoreText.setOrigin(scoreText.getGlobalBounds().width/2, scoreText.getGlobalBounds().height/2);
	scoreText.setPosition(win.getSize().x/2, win.getSize().y/2);

	player.setTexture(ti, t, td);
	_pipe_.setTexture(pipeU, pipeD);
	// min = 80
	// max = win.getSize().y - 80*4
	// _pipe_.setPos(512/4, win.getSize().y-80*4);

	win.setVerticalSyncEnabled(1);
	time = c.getElapsedTime();
	while(win.isOpen()){
		win.clear();
		win.draw(bkg);
		
		/*Handle Window events (closing and space input)*/
		while(win.pollEvent(_e)){
			switch(_e.type){
				case sf::Event::Closed:
					win.close();
					break;
				case sf::Event::KeyReleased:
					if(_e.key.code == sf::Keyboard::Space) player.addForce(7000);
					break;
			}
		}

		/*accual code*/
		if(!gameOver){
			logic(win);
			time = c.getElapsedTime();
			c.restart();
			draw(win, time);

			scoreText.setString(std::to_string(score));
			scoreText.setOrigin(scoreText.getGlobalBounds().width/2, scoreText.getGlobalBounds().height/2);
			scoreText.setPosition(win.getSize().x/2, 0+scoreText.getGlobalBounds().height);
			win.draw(scoreText);


			win.display();
		}
	}
}

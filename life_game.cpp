#include <SFML/Graphics.hpp> 
#include <time.h> 
#include<iostream>
#define WINDOW_WIDTH 300 
#define WINDOW_HEIGHT 300 
#define WINDOW_TITLE "Life Game" 
#define CELL_SIZE 5
#define MAP_WIDTH WINDOW_WIDTH/CELL_SIZE 
#define MAP_HEIGHT WINDOW_HEIGHT/CELL_SIZE 
#define FPS 30 

using namespace std;

int Generation[MAP_WIDTH][MAP_HEIGHT]; 
int OldGeneration[MAP_WIDTH][MAP_HEIGHT]; 

void Generate() 
{ 
	for(int y = 0; y < MAP_HEIGHT; y++) 
	{ 
		for(int x = 0; x < MAP_WIDTH; x++) 
		{ 
			if(0 == 1) //if(rand()%5 == 1) 
			{ 
				Generation[x][y] = OldGeneration[x][y] = 1;
			} 
			else 
			{ 
				Generation[x][y] = OldGeneration[x][y] = 0; 
			} 
		} 
	} 
} 

void Generate1(int x, int y) 
{ 
	Generation[x][y] = OldGeneration[x][y] = 1;
				
} 

void UpdateOldGeneration() 
{ 
	for(int y = 0; y < MAP_HEIGHT; y++) 
	{ 
		for(int x = 0; x < MAP_WIDTH; x++) 
		{ 
			OldGeneration[x][y] = Generation[x][y]; 
		} 
	} 
} 

char GetCell(int x, int y) 
{ 
	if((x < 0)||(x > MAP_WIDTH - 1)||(y < 0)||(y > MAP_HEIGHT - 1)) 
	{ 
		return 0; 
	} 
	return (int) OldGeneration[x][y]; 
} 

char GetCellsCount(int x, int y) 
{ 
	return (int) GetCell(x-1,y)+GetCell(x-1,y-1)+GetCell(x,y-1)+GetCell(x+1,y-1)+ 
	GetCell(x+1,y)+GetCell(x+1,y+1)+GetCell(x,y+1)+GetCell(x-1,y+1); 
} 

void Update() 
{ 
	UpdateOldGeneration(); 
	for(int y = 0; y < MAP_HEIGHT; y++) 
	{ 
		for(int x = 0; x < MAP_WIDTH; x++) 
		{ 
			int cellsCount = GetCellsCount(x,y);
			//cout<<cellsCount<<endl;
			if (OldGeneration[x][y] == 0) 
			{
				if (cellsCount == 3) 
				{
					Generation[x][y] = 1;
				}
			}					
			else  
			{
				if((cellsCount < 2) || (cellsCount > 3)) 
				{
					Generation[x][y] = 0;
				}
				
			}
		} 
	} 
} 

void Draw(sf::RenderWindow *window, sf::RectangleShape *rectangle) 
{ 
	for(int y = 0; y < MAP_HEIGHT; y++) //MAP_HEIGHT
	{ 
		for(int x = 0; x < MAP_WIDTH; x++) //MAP_WIDTH
		{ 
			if(Generation[x][y]) 
			{ 
				 rectangle->setPosition(x*CELL_SIZE, y*CELL_SIZE); 
				 window->draw(*rectangle); 
			} 
		} 
	} 
} 

int main() 
{ 
srand(time(NULL)); 
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE); 
window.setFramerateLimit(FPS); 
sf::RectangleShape rectangle; 
rectangle.setFillColor(sf::Color(143,254,9)); 
rectangle.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE)); 
Generate();
while (window.isOpen()) 
{ 
	sf::Event event; 
	
	//int X = (int) event.mouseMove.x/CELL_SIZE;
	//int Y = (int) event.mouseMove.y/CELL_SIZE;
	int X= (int)sf::Mouse::getPosition(window).x/CELL_SIZE;
	int Y= (int)sf::Mouse::getPosition(window).y/CELL_SIZE;
	
	while (window.pollEvent(event)) 
	{ 
		if (event.type == sf::Event::Closed) 
		window.close();
		
		//if (event.type == sf::Event::MouseButtonPressed)
		//{
		//	if (event.mouseButton.button == sf::Mouse::Left)
		//	Generate1(X, Y);
		//}
		
		
	}; 
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
	if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{  
		Generate(); 
	}; 

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		Generate1(X, Y);
	}
	else { Update();
	} 
 
	window.clear(); 
	Draw(&window,&rectangle); 
	window.display(); 
};
return 0; 
}


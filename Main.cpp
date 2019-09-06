#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

//tamano de pantalla
int N = 30, M = 20;
int Tamano = 16;
//Tamano 
int w = Tamano * N;
int h = Tamano * M;
bool arriba=true, abajo=true, derecha=true, izquierda=true;

int dir, num = 4;

//snake
struct Snake
{
	int x, y;
}  s[100];

//comida
struct Fruct
{
	int x, y;
} f;

void SnakeMov()
{

	//Union de piezas del snake
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	// Lee teclas presionadas validacion
	if (dir == 0) {
		s[0].y += 1;
	}
	if (dir == 1) {
		s[0].x -= 1;
	}
	if (dir == 2) {
		s[0].x += 1;
	}
	if (dir == 3) {
		s[0].y -= 1;
	}

	//tamano de snake cuando come comida
	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		//Funcion random para Comida
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}


	//Validacion entre paredes
	if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
	if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;


	// validacion de piezas que se remueven al tocarse el mismo

}

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake");

	Texture t1, t2;
	t1.loadFromFile("C:\\Users\\Mauricio\\source\\repos\\Sna\\images\\white.png");
	t2.loadFromFile("C:\\Users\\Mauricio\\source\\repos\\Sna\\images\\green.png");

	//carga imagenes al sprite
	Sprite sprite1(t1);
	Sprite sprite2(t2);

	Clock clock;
	float tiempo = 0, delay = 0.1;

	//posicion de comida
	f.x = 20;
	f.y = 10;

	//Ventana Abierta
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		tiempo += time;


		Event e;//Creacion de eventos
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		//Manejo de teclas.
		if (Keyboard::isKeyPressed(Keyboard::Left)&&izquierda) {
			derecha = false;
			abajo = true;
			arriba = true;
			dir = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)&&derecha) {
			izquierda = false;
			abajo = true;
			arriba = true;
			dir = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)&&arriba) {
			izquierda = true;
			derecha = true;
			abajo = false;
			dir = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)&&abajo) {
			dir = 0;
			derecha = true;
			izquierda = true;
			arriba = false;
		}

		//Andir movimiento
		if (tiempo > delay) {

			//movimiento snake
			tiempo = 0;
			// algoritmo de movimiento
			SnakeMov();
		}

		window.clear();


		// Compilacion de juego 

		for (int i = 0; i < num; i++)
		{
			if (s[i].x!=s[i].y)
			{

			}
			else {
				break;
			}
		}
			for (int i = 0; i < num; i++)
			{
				//Spawnear Serpiente
				sprite2.setPosition(s[i].x*Tamano, s[i].y*Tamano); 
				window.draw(sprite2);
			}
		//Spawnear la comida
		sprite2.setPosition(f.x*Tamano, f.y*Tamano);  window.draw(sprite2);

		window.display();
	}
	     
	return 0;
}

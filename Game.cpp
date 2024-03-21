#include "Game.h"
#include <chrono>
#include <iomanip> 
#include "Menu.h"
#include <sstream>
#include "AppGrafos.h"
SDL_Texture* imagetext;
Menu* menu;

using namespace std;

Game::Game()
{
   
}

Game::~Game()
{}


void Game::init(const char* title, int xpos, int ypos,int WIDTH, int HEIGHT, bool fullscreen)
{
	pantalla = 0;
	cnt = 0;
	int flahs = 0;
	if(fullscreen)
	{
		flahs = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		TTF_Init();
		window = SDL_CreateWindow(title, xpos, ypos, WIDTH, HEIGHT, flahs);
		renderer = SDL_CreateRenderer(window, -1, 0);
		
		isRunning = true;
		

	}
	else 
	{
		isRunning = false;
	}
	// Inicializar SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		isRunning = false;
	}

	// Cargar la fuente
	font = TTF_OpenFont("Assets\\SegoeUIItalic.ttf", 24); // Cambia la ruta a tu fuente y el tamaño segun sea necesario
	if (font == nullptr) {
		std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
		isRunning = false;
	}
	menu = new Menu();
}

void Game::handleEvents() 
{
	

	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		MouseX = event.motion.x;
		MouseY = event.motion.y;
		cout << "Mouse posicion x = " << MouseX << endl;
		cout << "Mouse posicion Y = " << MouseY << endl;

		if (MouseX >= 137 && MouseX <= 414 && MouseY >= 318 && MouseY <= 385)
		{
			cout << "Mochila";
			pantalla = 1;
			SDL_Quit();
			Mochila();

		}
		else if (MouseX >= 137 && MouseX <= 414 && MouseY >= 421 && MouseY <= 488)
		{
			// Limpia los recursos de SDL antes de llamar a SDL_Quit()
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);

			// Ahora puedes llamar a SDL_Quit()
			SDL_Quit();

			Aplicacion appGrafos;
			bool continuar = appGrafos.ejecutar();

			if (!continuar) {
				// Inicializa SDL de nuevo y crea una nueva ventana y un nuevo renderizador
					// Inicializa SDL de nuevo y crea una nueva ventana y un nuevo renderizador
				init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 650, false);
				run();
			}
		}


		else if (MouseX >= 137 && MouseX <= 414 && MouseY >= 524 && MouseY <= 596)
		{
			cout << "Subconjuntos";
			SubConjuntos();
		}

		break;

	default:
		MouseX = event.motion.x;
		MouseY = event.motion.y;
		break;
	}
	isRunning = menu->handleEvents(MouseX, MouseY);
	

}
void Game::renderText(const char* text, int x, int y) {
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}
void Game::run() {
	while (running())
	{
		handleEvents();
		update();
		render();
	}
	clean();
}


void Game::update()
{
	if (pantalla == 0) {
		menu->updateMenu(MouseX, MouseY);
	}
	else if (pantalla == 1) 
	{
		DsetObj1.x = -20;
	}
	//std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	menu->LoadMenu(window, renderer, MouseX, MouseY);
	//SDL_RenderCopy(renderer, imagetext, NULL, NULL);
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit;
}


void Game::Mochila() 
{

	//logica cada ocjeto tiene un peso diferente
	
	srand(time(NULL));

	SizeMochila = 1 + rand() % 100;
	
	ValorMochila = 0;
	SizeObjMochi = 0;
	Resultados = 0;
	Avisos = 0;
	frameindex = 0;
	scaso1 = "[ ";
	scaso2 = "[ ";
	scaso3 = "[ ";
	scasoM = "[ ";
	scasoU = "[ ";
	sValor1 = "a";
	sValor2 = "a";
	sValor3 = "a";
	sValorM = "a";
	tiempoEjeM = "";
	tiempoEje1 = "";
	tiempoEje2 = "";
	tiempoEje3 = "";

	cout << "Mochila " << " su tamaño es: " << SizeMochila << endl;
	for (int i = 0; i < 10; ++i) {
		pesoObj[i] = 1 + rand() % (SizeMochila);
		Menores[i] = pesoObj[i];
		Mayores[i] = pesoObj[i];
		ObjeYa[i] = 0;
		ValorObj[i] = 1 + rand() % 1000;
		if (i == 9)
		{
			caso1[i + 1] = 0;
			caso1[i] = 11;
			caso2[i + 1] = 0;
			caso2[i] = 11;
			caso3[i + 1] = 0;
			caso3[i] = 11;
			casoM[i + 1] = 0;
			casoM[i] = 11;
		}
		else
		{
			caso1[i] = 11;
			caso2[i] = 11;
			caso3[i] = 11;
			casoM[i] = 11;

		}

		cout << "Objeto " << i + 1 << " su peso es: " << pesoObj[i] << " Y su valor es " << ValorObj[i] << endl;
	}

	CasosM();
	Casos1();
	Casos2();
	Casos3();
	DsetObj1.x = 0;
	DsetObj2.x = 0;
	DsetObj3.x = 0;
	DsetObj4.x = 0;
	DsetObj5.x = 0;
	DsetObj6.x = 0;
	DsetObj7.x = 0;
	DsetObj8.x = 0;
	DsetObj9.x = 0;
	DsetObj10.x = 0;
	DsetObj1.y = 0;
	DsetObj2.y = 0;
	DsetObj3.y = 0;
	DsetObj4.y = 0;
	DsetObj5.y = 0;
	DsetObj6.y = 0;
	DsetObj7.y = 0;
	DsetObj8.y = 0;
	DsetObj9.y = 0;
	DsetObj10.y = 0;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window2 = SDL_CreateWindow("Kaspsap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 650, false);

		renderer2 = SDL_CreateRenderer(window2, -1, 0);

		isRunning = true;

		SDL_Surface* background = IMG_Load("Assets/FondoMochila.png");
		TextureBc = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		
		SrcSkanp.x = 0;
		SrcSkanp.y = 0;
		SrcSkanp.w = 1000;
		SrcSkanp.h = 650;
		DestSkanp.x = 0;
		DestSkanp.y = 0;
		DestSkanp.w = 1000;
		DestSkanp.h = 650;

		//Objeto1
		background = IMG_Load("Assets/Objeto1.png");
		TexObj1 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);
		
		DsetObj1.w = 1000;
		DsetObj1.h = 650;

		//Objeto2
		background = IMG_Load("Assets/Objeto2.png");
		TexObj2 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj2.w = 1000;
		DsetObj2.h = 650;

		//Objeto3
		background = IMG_Load("Assets/Objeto3.png");
		TexObj3 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj3.w = 1000;
		DsetObj3.h = 650;

		//Objeto4
		background = IMG_Load("Assets/Objeto4.png");
		TexObj4 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj4.w = 1000;
		DsetObj4.h = 650;

		//Objeto5
		background = IMG_Load("Assets/Objeto5.png");
		TexObj5 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj5.w = 1000;
		DsetObj5.h = 650;

		//Objeto6
		background = IMG_Load("Assets/Objeto6.png");
		TexObj6 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj6.w = 1000;
		DsetObj6.h = 650;

		//Objeto7
		background = IMG_Load("Assets/Objeto7.png");
		TexObj7 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj7.w = 1000;
		DsetObj7.h = 650;

		//Objeto8
		background = IMG_Load("Assets/Objeto8.png");
		TexObj8 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj8.w = 1000;
		DsetObj8.h = 650;

		//Objeto9
		background = IMG_Load("Assets/Objeto9.png");
		TexObj9 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj9.w = 1000;
		DsetObj9.h = 650;

		//Objeto10
		background = IMG_Load("Assets/Objeto10.png");
		TexObj10 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		DsetObj10.w = 1000;
		DsetObj10.h = 650;
		
		string peso = "Peso: " + to_string(pesoObj[0]);
		string valor = "Valor: " + to_string(ValorObj[0]);
		TTF_Font* font = TTF_OpenFont("Assets/Roboto-Bold.ttf", 15);

		//PesoObj1
		peso = "Peso: " + to_string(pesoObj[0]);
		SDL_Surface* textSurf1 = TTF_RenderText_Solid(font, peso.c_str(), {255,255,255});
		Texttext1 = SDL_CreateTextureFromSurface(renderer2, textSurf1);
		SDL_FreeSurface(textSurf1);
		
		//PesoObj2
		peso = "Peso: " + to_string(pesoObj[1]);
		SDL_Surface* textSurf2 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext2 = SDL_CreateTextureFromSurface(renderer2, textSurf2);
		SDL_FreeSurface(textSurf2);

		//PesoObj3
		peso = "Peso: " + to_string(pesoObj[2]);
		SDL_Surface* textSurf3 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext3= SDL_CreateTextureFromSurface(renderer2, textSurf3);
		SDL_FreeSurface(textSurf3);

		//PesoObj4
		peso = "Peso: " + to_string(pesoObj[3]);
		SDL_Surface* textSurf4 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext4 = SDL_CreateTextureFromSurface(renderer2, textSurf4);
		SDL_FreeSurface(textSurf4);

		// 
		//PesoObj5
		peso = "Peso: " + to_string(pesoObj[4]);
		SDL_Surface* textSurf5 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext5 = SDL_CreateTextureFromSurface(renderer2, textSurf5);
		SDL_FreeSurface(textSurf5);

		//PesoObj6
		peso = "Peso: " + to_string(pesoObj[5]);
		SDL_Surface* textSurf6 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext6 = SDL_CreateTextureFromSurface(renderer2, textSurf6);
		SDL_FreeSurface(textSurf6);

		//PesoObj7
		peso = "Peso: " + to_string(pesoObj[6]);
		SDL_Surface* textSurf7 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext7 = SDL_CreateTextureFromSurface(renderer2, textSurf7);
		SDL_FreeSurface(textSurf7);

		//PesoObj8
		peso = "Peso: " + to_string(pesoObj[7]);
		SDL_Surface* textSurf8 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext8 = SDL_CreateTextureFromSurface(renderer2, textSurf8);
		SDL_FreeSurface(textSurf8);

		//PesoObj9
		peso = "Peso: " + to_string(pesoObj[8]);
		SDL_Surface* textSurf9 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext9 = SDL_CreateTextureFromSurface(renderer2, textSurf9);
		SDL_FreeSurface(textSurf9);

		//PesoObj10
		peso = "Peso: " + to_string(pesoObj[9]);
		SDL_Surface* textSurf10 = TTF_RenderText_Solid(font, peso.c_str(), { 255,255,255 });
		Texttext10 = SDL_CreateTextureFromSurface(renderer2, textSurf10);
		SDL_FreeSurface(textSurf10);


		//Valor

		//PesoObj1
		valor = "Valor: " + to_string(ValorObj[0]);
		SDL_Surface* textSurfValor1 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor1 = SDL_CreateTextureFromSurface(renderer2, textSurfValor1);
		SDL_FreeSurface(textSurfValor1);

		//PesoObj2
		valor = "Valor: " + to_string(ValorObj[1]);
		SDL_Surface* textSurfValor2 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor2 = SDL_CreateTextureFromSurface(renderer2, textSurfValor2);
		SDL_FreeSurface(textSurfValor2);

		//PesoObj3
		valor = "Valor: " + to_string(ValorObj[2]);
		SDL_Surface* textSurfValor3 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor3 = SDL_CreateTextureFromSurface(renderer2, textSurfValor3);
		SDL_FreeSurface(textSurfValor3);

		//PesoObj4
		valor = "Valor: " + to_string(ValorObj[3]);
		SDL_Surface* textSurfValor4 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor4 = SDL_CreateTextureFromSurface(renderer2, textSurfValor4);
		SDL_FreeSurface(textSurfValor4);

		// 
		//PesoObj5
		valor = "Valor: " + to_string(ValorObj[4]);
		SDL_Surface* textSurfValor5 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor5 = SDL_CreateTextureFromSurface(renderer2, textSurfValor5);
		SDL_FreeSurface(textSurfValor5);

		//PesoObj6
		valor = "Valor: " + to_string(ValorObj[5]);
		SDL_Surface* textSurfValor6 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor6 = SDL_CreateTextureFromSurface(renderer2, textSurfValor6);
		SDL_FreeSurface(textSurfValor6);
		
		

		//PesoObj7
		valor = "Valor: " + to_string(ValorObj[6]);
		SDL_Surface* textSurfValor7 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor7 = SDL_CreateTextureFromSurface(renderer2, textSurfValor7);
		SDL_FreeSurface(textSurfValor7);

		//PesoObj8
		valor = "Valor: " + to_string(ValorObj[7]);
		SDL_Surface* textSurfValor8 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor8 = SDL_CreateTextureFromSurface(renderer2, textSurfValor8);
		SDL_FreeSurface(textSurfValor8);

		//PesoObj9
		valor = "Valor: " + to_string(ValorObj[8]);
		SDL_Surface* textSurfValor9 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor9 = SDL_CreateTextureFromSurface(renderer2, textSurfValor9);
		SDL_FreeSurface(textSurfValor9);

		//PesoObj10
		valor = "Valor: " + to_string(ValorObj[9]);
		SDL_Surface* textSurfValor10 = TTF_RenderText_Solid(font, valor.c_str(), { 255,255,255 });
		TexttextValor10 = SDL_CreateTextureFromSurface(renderer2, textSurfValor10);
		SDL_FreeSurface(textSurfValor10);


		//Peso Mochila
		string mochila = "Capacidad: " + to_string(SizeMochila);
		SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
		DsetMochi = { 180,586,textSurfmoch->w,textSurfmoch->h };
		TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);
		SDL_FreeSurface(textSurfmoch);

		string valormochila = "Valor: " + to_string(ValorMochila);
		SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
		DsetMochiValor = { 180,566,textSurfmoch2->w,textSurfmoch2->h };
		TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
		SDL_FreeSurface(textSurfmoch2);

		//Avisos
		Avisorect = { 0,0,1000,650 };
		background = IMG_Load("Assets/Aviso1.png");
		Aviso1 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = IMG_Load("Assets/Aviso2.png");
		Aviso2 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = IMG_Load("Assets/Aviso3.png");
		Aviso3 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = IMG_Load("Assets/Aviso4.png");
		Aviso4 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);


		//Pantalla resultados
		font2 = TTF_OpenFont("Assets/Roboto-Bold.ttf", 18);
		background = IMG_Load("Assets/ResultadosFrame.png");
		ResultadosPan = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = IMG_Load("Assets/TituloResults.png");
		ResultadosTitulo = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		//Texto casos

		//casoM
		string CasoM = "Mejor de los casos: Valor: " + sValorM ;
		string CasoM2 = "Objetos tomados: " + scasoM + " Tiempo Eje: " + tiempoEjeM;
		background = TTF_RenderText_Solid(font2, CasoM.c_str(), { 0,0,0 });
		TextResultM = { 33,290,background->w,background->h };
		ResulTextCM = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = TTF_RenderText_Solid(font2, CasoM2.c_str(), { 0,0,0 });
		TextResultM2 = { 33 ,330,background->w,background->h };
		ResulTextCM2 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);


		//caso1
		string Caso1 = "Tomar el primero que ve: Valor: " + sValor1;
		string Caso12 = "Objetos tomados: " + scaso1 +" Tiempo Eje: " + tiempoEje1;
		background = TTF_RenderText_Solid(font2, Caso1.c_str(), { 0,0,0 });
		TextResult1 = { 33,380,background->w,background->h };
		ResulTextC1 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = TTF_RenderText_Solid(font2, Caso12.c_str(), { 0,0,0 });
		TextResult12 = { 33 ,420,background->w,background->h };
		ResulTextC12 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		//caso2
		string Caso2 = "Tomar el objeto de menor peso: Valor: " + sValor2;
		string Caso22 = "Objetos tomados: " + scaso2 +" Tiempo Eje: " + tiempoEje2;
		background = TTF_RenderText_Solid(font2, Caso2.c_str(), { 0,0,0 });
		TextResult2 = { 33,470,background->w,background->h };
		ResulTextC2 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = TTF_RenderText_Solid(font2, Caso22.c_str(), { 0,0,0 });
		TextResult22 = {33 ,510,background->w,background->h };
		ResulTextC22 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);
		//caso3
	
		string Caso3 = "Tomar el objeto de mayor peso: Valor: " + sValor3;
		string Caso32 = "Objetos tomados: " + scaso3 + " Tiempo Eje: " + tiempoEje3;
		background = TTF_RenderText_Solid(font2, Caso3.c_str(), { 0,0,0 });
		TextResult3 = { 33,550,background->w,background->h };
		ResulTextC3 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);

		background = TTF_RenderText_Solid(font2, Caso32.c_str(), { 0,0,0 });
		TextResult32 = { 33 ,590,background->w,background->h };
		ResulTextC32 = SDL_CreateTextureFromSurface(renderer2, background);
		SDL_FreeSurface(background);


		RestInicial.y = 0;
		RestInicial.w = 800;
		RestInicial.h = 600;
		RestFinal.x = 0;
		RestFinal.y = 0;
		RestFinal.w = 1000;
		RestFinal.h = 650;

		TTF_CloseFont(font);

	}
	else
	{
		isRunning = false;
	}
	const int FPS = 60;
	const int frameDelay = 100 / FPS;

	Uint32 frameStart;
	int frameTime;
	
	while (running())
	{


		frameStart = SDL_GetTicks();
		EventMochila();
		Updatemochila();
		renderMochila();

		frameTime = SDL_GetTicks() - frameStart;

		//Sin esto no hay delay ******
		if (frameDelay > frameStart) {
			SDL_Delay(frameDelay - frameTime);
		}

	}

}

void Game::Updatemochila()
{

	TTF_Font* font = TTF_OpenFont("Assets/Roboto-Bold.ttf", 15);
	string mochila = "Capacidad: " + to_string(SizeMochila - SizeObjMochi);
	string valormochila = "Valor: " + to_string(ValorMochila);
	//100 significa que esta dentro de la mochila y termino la animacion
	if (ObjeYa[0] != 0 && ObjeYa[0] != 100 && ObjeYa[0] != 200 && ObjeYa[0] != 300 && ObjeYa[0] != 400 && ObjeYa[0] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 8));

		if (frameindex <= 2)
		{
			DsetObj1.x = ((frameindex) * 26);
			DsetObj1.y = ((frameindex) * 56);

		}
		else if (frameindex <= 4)
		{
			DsetObj1.y = ((frameindex) * 56);


		}
		else if (frameindex == 5)
		{
			ObjeYa[0] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj1.x = -200;


			if (SizeMochila == SizeObjMochi)
			{
				
				Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}

		}

		
	}
	else if (ObjeYa[1] != 0 && ObjeYa[1] != 100 && ObjeYa[1] != 200 && ObjeYa[1] != 300 && ObjeYa[1] != 400 && ObjeYa[1] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 8));

		if (frameindex <= 2)
		{
			DsetObj2.x = ((frameindex) * -42);
			DsetObj2.y = ((frameindex) * 33);

		}
		else if (frameindex <= 4)
		{
			DsetObj2.y = ((frameindex) * 33);


		}
		else if (frameindex == 5)
		{

			ObjeYa[1] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj2.x = -400;
			if (SizeMochila == SizeObjMochi)
			{
				
					Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}
	else if (ObjeYa[2] != 0 && ObjeYa[2] != 100 && ObjeYa[2] != 200 && ObjeYa[2] != 300 && ObjeYa[2] != 400 && ObjeYa[2] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 10));

		if (frameindex <= 4)
		{
			DsetObj3.x = ((frameindex) * -30);
			DsetObj3.y = ((frameindex) * 63);

		}
		else if (frameindex <= 6)
		{
			DsetObj3.y = ((frameindex) * 63);


		}
		else if (frameindex == 7)
		{

			ObjeYa[2] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj3.x = -400;
			if (SizeMochila == SizeObjMochi)
			{
				
					Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}
	else if (ObjeYa[3] != 0 && ObjeYa[3] != 100 && ObjeYa[3] != 200 && ObjeYa[3] != 300 && ObjeYa[3] != 400 && ObjeYa[3] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 13));

		if (frameindex <= 6)
		{
			DsetObj4.x = ((frameindex) * -36);
			DsetObj4.y = ((frameindex) * 44);

		}
		else if (frameindex <= 9)
		{
			DsetObj4.y = ((frameindex) * 44);


		}
		else if (frameindex == 10)
		{

			ObjeYa[3] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj4.x = -500;
			if (SizeMochila == SizeObjMochi)
			{
				
					Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}
		
	}
	else if (ObjeYa[4] != 0 && ObjeYa[4] != 100 && ObjeYa[4] != 200 && ObjeYa[4] != 300 && ObjeYa[4] != 400 && ObjeYa[4] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 10));

		if (frameindex <= 2)
		{
			DsetObj5.x = ((frameindex) * -51);
			DsetObj5.y = ((frameindex) * 48);

		}
		else if (frameindex <= 5)
		{
			DsetObj5.x = ((frameindex) * -51);


		}
		else if (frameindex <= 6)
		{
			DsetObj5.y = ((frameindex) * 38);

		}
		else if (frameindex == 7)
		{

			ObjeYa[4] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj5.x = -600;
			if (SizeMochila == SizeObjMochi)
			{
				
					Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}
	else if (ObjeYa[5] != 0 && ObjeYa[5] != 100 && ObjeYa[5] != 200 && ObjeYa[5] != 300 && ObjeYa[5] != 400 && ObjeYa[5] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 17));

		if (frameindex <= 7)
		{
			DsetObj6.x = ((frameindex) * -27);
			DsetObj6.y = ((frameindex) * 38);

		}
		else if (frameindex <= 11)
		{
			DsetObj6.x = ((frameindex) * -27);


		}
		else if (frameindex <= 13)
		{
			DsetObj6.y = ((frameindex) * 30);

		}
		else if (frameindex == 14)
		{

			ObjeYa[5] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj6.x = -700;
			if (SizeMochila == SizeObjMochi)
			{
				
				Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}
	else if (ObjeYa[6] != 0 && ObjeYa[6] != 100 && ObjeYa[6] != 200 && ObjeYa[6] != 300 && ObjeYa[6] != 400 && ObjeYa[6] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 12));

		if (frameindex <= 2)
		{
			DsetObj7.x = ((frameindex) * -53);
			DsetObj7.y = ((frameindex) * 45);

		}
		else if (frameindex <= 7)
		{
			DsetObj7.x = ((frameindex) * -53);


		}
		else if (frameindex <= 8)
		{
			DsetObj7.y = ((frameindex) * 20);

		}
		else if (frameindex == 9)
		{

			ObjeYa[6] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj7.x = -700;
			if (SizeMochila == SizeObjMochi)
			{
				
				Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}
	else if (ObjeYa[7] != 0 && ObjeYa[7] != 100 && ObjeYa[7] != 200 && ObjeYa[7] != 300 && ObjeYa[7] != 400 && ObjeYa[7] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 13));

		if (frameindex <= 6)
		{
			DsetObj8.x = ((frameindex) * -57);
			DsetObj8.y = ((frameindex) * 30);

		}
		else if (frameindex <= 8)
		{
			DsetObj8.x = ((frameindex) * -57);


		}
		else if (frameindex <= 9)
		{
			DsetObj8.y = ((frameindex) * 30);

		}
		else if (frameindex == 10)
		{

			ObjeYa[7] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj8.x = -700;

			if (SizeMochila == SizeObjMochi)
			{
				
				Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

	}
	else if (ObjeYa[8] != 0 && ObjeYa[8] != 100 && ObjeYa[8] != 200 && ObjeYa[8] != 300 && ObjeYa[8] != 400 && ObjeYa[8] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 17));

		if (frameindex <= 1)
		{
			DsetObj9.x = ((frameindex) * -45);
			DsetObj9.y = ((frameindex) * 76);

		}
		else if (frameindex <= 12)
		{
			DsetObj9.x = ((frameindex) * -50);


		}
		else if (frameindex <= 13)
		{
			DsetObj9.y = ((frameindex) * 12);

		}
		else if (frameindex == 14)
		{

			ObjeYa[8] = 100;
			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj9.x = -900;
			if (SizeMochila == SizeObjMochi)
			{
					Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}
	else if (ObjeYa[9] != 0 && ObjeYa[9] != 100 && ObjeYa[9] != 200 && ObjeYa[9] != 300 && ObjeYa[9] != 400 && ObjeYa[9] != 500) {
		frameindex = int(((SDL_GetTicks() / 2000) % 19));
		
		if (frameindex <= 3)
		{
			DsetObj10.x = ((frameindex) * -48);
			DsetObj10.y = ((frameindex) * 62);

		}
		else if (frameindex <= 14)
		{
			DsetObj10.x = ((frameindex) * -48);


		}
		else if (frameindex <= 15)
		{
			DsetObj10.y = ((frameindex) * 18);

		}
		else if (frameindex == 16)
		{

			ObjeYa[9] = 100;


			SDL_Surface* textSurfmoch = TTF_RenderText_Solid(font, mochila.c_str(), { 0,0,0 });
			TexttextMochi = SDL_CreateTextureFromSurface(renderer2, textSurfmoch);

			SDL_Surface* textSurfmoch2 = TTF_RenderText_Solid(font, valormochila.c_str(), { 0,0,0 });
			TexttextMochiValor = SDL_CreateTextureFromSurface(renderer2, textSurfmoch2);
			SDL_FreeSurface(textSurfmoch2);
			SDL_FreeSurface(textSurfmoch);
			DsetObj10.x = -900;
			if (SizeMochila == SizeObjMochi)
			{
				Resultados = 3;
				
			}
			if (existe() == 0)
			{
				Resultados = 4;
			}
		}

		
	}


	if (ObjeYa[0] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if(frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[0] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[1] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[1] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[2] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[2] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[3] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[3] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[4] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			ObjeYa[4] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[5] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[5] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[6] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[6] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[7] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[7] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[8] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 7));
		cout << "Frame " << frameindex << endl;
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[8] = 0;
			Avisos = 0;
		}
	}
	else if (ObjeYa[9] == 300)
	{
		frameindex = int(((SDL_GetTicks() / 2000) % 7));
		
		if (frameindex <= 4)
		{
			Avisos = 1;
		}
		else if (frameindex == 5)
		{
			cout << "Temrino animacion ob2";
			ObjeYa[9] = 0;
			Avisos = 0;
		}
	}

	SDL_Surface* background;
	if (Resultados == 3)
	{
		frameindex = int(((SDL_GetTicks() / 1500) % 10));
		cout << "Frame resultadors 3 " << frameindex << " GetTicks " << SDL_GetTicks() << endl;
		if (frameindex <= 4)
		{
			Avisos = 2;
		}
		else if (frameindex <= 8)
		{
			Avisos = 4;
		}
		else if (frameindex == 9)
		{
			Avisos = 0;
			for (int i = 0; i < 10; i++) 
			{
				if (ObjeYa[i] == 100)
				{
					scasoU = scasoU + to_string((i+1)) + ", ";
				}

			}

			scasoU.erase(scasoU.length() - 2);
			scasoU = scasoU + " ]";
			string Robado = "Usuario Robaste: " + to_string(ValorMochila);
			string robado2 = "Objetos tomados: " + scasoU;
			background = TTF_RenderText_Solid(font2, Robado.c_str(), { 0,0,0 });
			TextResult = { 33,200, background->w,background->h };
			RestTextRob = SDL_CreateTextureFromSurface(renderer2, background);

			background = TTF_RenderText_Solid(font2, robado2.c_str(), { 0,0,0 });
			TextResult0 = { 33,240, background->w,background->h };
			RestTextRob2 = SDL_CreateTextureFromSurface(renderer2, background);

			SDL_FreeSurface(background);
			Resultados = 1;
		}
	}
	else if (Resultados == 4) {

		
		frameindex = int(((SDL_GetTicks() / 1500) % 10));
		cout << "frame result 4" << frameindex;
		if (frameindex <= 4)
		{
			Avisos = 3;
		}
		else if (frameindex <= 8)
		{
			Avisos = 4;
		}
		else if (frameindex == 9)
		{

			Avisos = 0;
			for (int i = 0; i < 10; i++)
			{
				if (ObjeYa[i] == 100)
				{
					scasoU = scasoU + to_string((i + 1)) + ", ";
				}

			}

			scasoU.erase(scasoU.length() - 2);
			scasoU = scasoU + " ]";
			string Robado = "Usuario Robaste: " + to_string(ValorMochila);
			string robado2 = "Objetos tomados: " + scasoU;
			background = TTF_RenderText_Solid(font2, Robado.c_str(), { 0,0,0 });
			TextResult = { 33,200, background->w,background->h };
			RestTextRob = SDL_CreateTextureFromSurface(renderer2, background);

			background = TTF_RenderText_Solid(font2, robado2.c_str(), { 0,0,0 });
			TextResult0 = { 33,240, background->w,background->h };
			RestTextRob2 = SDL_CreateTextureFromSurface(renderer2, background);
			
			SDL_FreeSurface(background);

			Resultados = 1;
		}



	}

	if (Resultados == 1) 
	{
		frameindex = int(((SDL_GetTicks() / 200) % 6));
		RestInicial.x = ((frameindex) * 800);
	}

}

void Game::EventMochila()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (Resultados != 1) {
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			MouseX = event.motion.x;
			MouseY = event.motion.y;
			cout << "2Mouse posicion x = " << MouseX << endl;
			cout << "2Mouse posicion Y = " << MouseY << endl;
			if (MouseX >= 113 && MouseX <= 139 && MouseY >= 302 && MouseY <= 358)
			{


				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[0]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 
						//cout << "cabe en la mochila";
						SizeObjMochi += pesoObj[0];
						ValorMochila += ValorObj[0];
						//cout << "MochilaSize" << SizeObjMochi;
						ObjeYa[0] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[0] = 300;
						cout << "No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}


			}
			else if (MouseX >= 278 && MouseX <= 320 && MouseY >= 356 && MouseY <= 389)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[1]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 

						SizeObjMochi += pesoObj[1];
						ValorMochila += ValorObj[1];
						ObjeYa[1] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[1] = 300;
						cout << "2 - No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 313 && MouseX <= 343 && MouseY >= 116 && MouseY <= 179)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[2]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 

						SizeObjMochi += pesoObj[2];
						ValorMochila += ValorObj[2];
						ObjeYa[2] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[2] = 300;
						cout << "2-No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 377 && MouseX <= 413 && MouseY >= 74 && MouseY <= 118)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[3]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 

						SizeObjMochi += pesoObj[3];
						ValorMochila += ValorObj[3];
						ObjeYa[3] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[3] = 300;
						cout << "No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 462 && MouseX <= 513 && MouseY >= 262 && MouseY <= 310)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[4]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 

						SizeObjMochi += pesoObj[4];
						ValorMochila += ValorObj[4];
						ObjeYa[4] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[4] = 300;
						cout << "No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 514 && MouseX <= 541 && MouseY >= 91 && MouseY <= 129)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[5]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 

						SizeObjMochi += pesoObj[5];
						ValorMochila += ValorObj[5];
						ObjeYa[5] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[5] = 300;
						cout << "No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 580 && MouseX <= 633 && MouseY >= 305 && MouseY <= 350)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[6]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 
						cout << "cabe en la mochila";
						SizeObjMochi += pesoObj[6];
						ValorMochila += ValorObj[6];
						ObjeYa[6] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[6] = 300;
						cout << "No cabe en la mochila";
					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 656 && MouseX <= 686 && MouseY >= 201 && MouseY <= 258)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[7]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 
						cout << "cabe en la mochila";
						SizeObjMochi += pesoObj[7];
						ValorMochila += ValorObj[7];
						ObjeYa[7] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[7] = 300;
						cout << "No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}
			}
			else if (MouseX >= 783 && MouseX <= 808 && MouseY >= 295 && MouseY <= 371)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[8]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 
						cout << "cabe en la mochila";
						SizeObjMochi += pesoObj[8];
						ValorMochila += ValorObj[8];
						ObjeYa[8] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[8] = 300;
						cout << "No cabe en la mochila";

					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					cout << "Mochila llena";
					Resultados = 3;
				}
				else if (exits == 0)
				{
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
					Resultados = 4;
				}

			}
			else if (MouseX >= 856 && MouseX <= 884 && MouseY >= 216 && MouseY <= 278)
			{
				int exits = existe();
				if (exits == 1)
				{
					if (((SizeMochila - SizeObjMochi) / pesoObj[9]) > 0)
					{
						//verifico que el objeto tocado sea el objeto con el peso si puede caben en la mochila
						//si lo es le cambiaremos el valor a 1 para que pase a la animacion 
						cout << "cabe en la mochila";
						SizeObjMochi += pesoObj[9];
						ValorMochila += ValorObj[9];
						ObjeYa[9] = 1;
					}
					else
					{
						//significa que este objeto no cabe en la mochila  
						//le daremos un aviso que este objeto no cabe en la mochila y seguira en estado 0
						ObjeYa[9] = 300;
						cout << "No cabe en la mochila";
					}
				}
				else if (exits == 2)
				{
					//esta llena la mochila
					//como la mochila ya esta llena pasaria a la imagen de resultados
					Resultados = 3;
					cout << "Mochila llena";
				}
				else if (exits == 0)
				{
					Resultados = 4;
					//no hay mas objetos que quepan en la mochila
					//como no hya objetos que quepan mas mandaremos un aviso y luego pasara a la pantalla de resultados
					cout << "Mochila llena no hay ojetos que quepan en la mochila";
				}
			}
			break;
		case SDL_MOUSEMOTION:
			MouseX = event.motion.x;
			MouseY = event.motion.y;
			if (MouseX >= 113 && MouseX <= 139 && MouseY >= 302 && MouseY <= 358 && ObjeYa[0] != 1 && ObjeYa[0] != 100)
			{
				ObjeYa[0] = 200;

			}
			else if (MouseX >= 278 && MouseX <= 320 && MouseY >= 356 && MouseY <= 389 && ObjeYa[1] != 1 && ObjeYa[1] != 100)
			{
				ObjeYa[1] = 200;
				//cout << "Obj2";
			}
			else if (MouseX >= 313 && MouseX <= 343 && MouseY >= 116 && MouseY <= 179 && ObjeYa[2] != 1 && ObjeYa[2] != 100)
			{
				ObjeYa[2] = 200;
				//cout << "Obj3";
			}
			else if (MouseX >= 377 && MouseX <= 413 && MouseY >= 74 && MouseY <= 118 && ObjeYa[3] != 1 && ObjeYa[3] != 100)
			{
				ObjeYa[3] = 200;
				//cout << "Obj4";
			}
			else if (MouseX >= 462 && MouseX <= 513 && MouseY >= 262 && MouseY <= 310 && ObjeYa[4] != 1 && ObjeYa[4] != 100)
			{
				ObjeYa[4] = 200;
				//cout << "Obj5";
			}
			else if (MouseX >= 514 && MouseX <= 541 && MouseY >= 91 && MouseY <= 129 && ObjeYa[5] != 1 && ObjeYa[5] != 100)
			{
				ObjeYa[5] = 200;
				//cout << "Obj6";
			}
			else if (MouseX >= 580 && MouseX <= 633 && MouseY >= 305 && MouseY <= 350 && ObjeYa[6] != 1 && ObjeYa[6] != 100)
			{
				ObjeYa[6] = 200;
				// << "Obj7";
			}
			else if (MouseX >= 656 && MouseX <= 686 && MouseY >= 201 && MouseY <= 258 && ObjeYa[7] != 1 && ObjeYa[7] != 100)
			{
				ObjeYa[7] = 200;
				//cout << "Obj8";
			}
			else if (MouseX >= 783 && MouseX <= 808 && MouseY >= 295 && MouseY <= 371 && ObjeYa[8] != 1 && ObjeYa[8] != 100)
			{
				ObjeYa[8] = 200;
				//cout << "Obj9";

			}
			else if (MouseX >= 856 && MouseX <= 884 && MouseY >= 216 && MouseY <= 278 && ObjeYa[9] != 1 && ObjeYa[9] != 100)
			{
				ObjeYa[9] = 200;
				//cout << "Obj10";
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (ObjeYa[i] == 200)
					{
						ObjeYa[i] = 0;
					}

				}
			}
			break;
		default:
			MouseX = event.motion.x;
			MouseY = event.motion.y;
			break;
		}
	}
	else if (Resultados == 1)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			MouseX = event.motion.x;
			MouseY = event.motion.y;
			cout << "3Mouse posicion x = " << MouseX << endl;
			cout << "3Mouse posicion Y = " << MouseY << endl;
			if (MouseX >= 781 && MouseX <= 864 && MouseY >= 545 && MouseY <= 628)
			{
				//salir
				SDL_Quit();
				Resultados = 0;
				init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 650, false);
				run();
			}
			else if (MouseX >= 894 && MouseX <= 978 && MouseY >= 545 && MouseY <= 628)
			{
				SDL_Quit();
				Resultados = 0;
				Mochila();
			}
		default:
			MouseX = event.motion.x;
			MouseY = event.motion.y;
			break;
		}
	}
}

int Game::existe()
{
	if (SizeObjMochi == SizeMochila)
	{
		return 2;
	}
	else if (SizeObjMochi != SizeMochila)
	{

		int x = SizeMochila - SizeObjMochi;
		cout << endl << "x" << x << endl;
		for (int i = 0; i < 10; i++)
		{
			if (ObjeYa[i] != 100 && (x / pesoObj[i]) > 0)
			{
				//existen objetos que no estan en la mcohila que todavian pueden ser llevados.
				return 1;
			}
		}
	}
	return 0;
}

void Game::renderMochila()
{
	SDL_RenderClear(renderer2);
	if(Resultados != 1)
	{
		SDL_RenderCopy(renderer2, TextureBc, &SrcSkanp, &DestSkanp);
		SDL_RenderCopy(renderer2, TexObj1, &SrcSkanp, &DsetObj1);
		SDL_RenderCopy(renderer2, TexObj2, &SrcSkanp, &DsetObj2);
		SDL_RenderCopy(renderer2, TexObj3, &SrcSkanp, &DsetObj3);
		SDL_RenderCopy(renderer2, TexObj4, &SrcSkanp, &DsetObj4);
		SDL_RenderCopy(renderer2, TexObj5, &SrcSkanp, &DsetObj5);
		SDL_RenderCopy(renderer2, TexObj6, &SrcSkanp, &DsetObj6);
		SDL_RenderCopy(renderer2, TexObj7, &SrcSkanp, &DsetObj7);
		SDL_RenderCopy(renderer2, TexObj8, &SrcSkanp, &DsetObj8);
		SDL_RenderCopy(renderer2, TexObj9, &SrcSkanp, &DsetObj9);
		SDL_RenderCopy(renderer2, TexObj10, &SrcSkanp, &DsetObj10);

		SDL_RenderCopy(renderer2, TexttextMochi, NULL, &DsetMochi);
		SDL_RenderCopy(renderer2, TexttextMochiValor, NULL, &DsetMochiValor);

		if (ObjeYa[0] == 200)
		{
			textrec = { 115,260,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor1, NULL, &textrec);
			textrec = { 115,280,50,18 };
			SDL_RenderCopy(renderer2, Texttext1, NULL, &textrec);
		}
		else if (ObjeYa[1] == 200)
		{
			textrec = { 280,316,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor2, NULL, &textrec);
			textrec = { 280,336,50,18 };
			SDL_RenderCopy(renderer2, Texttext2, NULL, &textrec);
		}
		else if (ObjeYa[2] == 200)
		{
			textrec = { 315,76,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor3, NULL, &textrec);
			textrec = { 315,96,50,18 };
			SDL_RenderCopy(renderer2, Texttext3, NULL, &textrec);
		}
		else if (ObjeYa[3] == 200)
		{
			textrec = { 380,34,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor4, NULL, &textrec);
			textrec = { 380,54,50,18 };
			SDL_RenderCopy(renderer2, Texttext4, NULL, &textrec);
		}
		else if (ObjeYa[4] == 200)
		{
			textrec = { 465,226,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor5, NULL, &textrec);
			textrec = { 465,246,50,18 };
			SDL_RenderCopy(renderer2, Texttext5, NULL, &textrec);
		}
		else if (ObjeYa[5] == 200)
		{
			textrec = { 513,51,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor6, NULL, &textrec);
			textrec = { 513,71,50,18 };
			SDL_RenderCopy(renderer2, Texttext6, NULL, &textrec);
		}
		else if (ObjeYa[6] == 200)
		{
			textrec = { 582,265,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor7, NULL, &textrec);
			textrec = { 582,285,50,18 };
			SDL_RenderCopy(renderer2, Texttext7, NULL, &textrec);
		}
		else if (ObjeYa[7] == 200)
		{
			textrec = { 656,161,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor8, NULL, &textrec);
			textrec = { 656,181,50,18 };
			SDL_RenderCopy(renderer2, Texttext8, NULL, &textrec);
		}
		else if (ObjeYa[8] == 200)
		{
			textrec = { 776,255,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor9, NULL, &textrec);
			textrec = { 776,275,50,18 };
			SDL_RenderCopy(renderer2, Texttext9, NULL, &textrec);
		}
		else if (ObjeYa[9] == 200)
		{
			textrec = { 856,176,69,18 };
			SDL_RenderCopy(renderer2, TexttextValor10, NULL, &textrec);
			textrec = { 856,196,50,18 };
			SDL_RenderCopy(renderer2, Texttext10, NULL, &textrec);
		}


		if (Avisos == 1) 
		{
			SDL_RenderCopy(renderer2, Aviso1, NULL, &Avisorect);
			
		}
		else if (Avisos == 2) 
		{
			SDL_RenderCopy(renderer2, Aviso2, NULL, &Avisorect);
			
		}
		else if (Avisos == 3)
		{
			SDL_RenderCopy(renderer2, Aviso3, NULL, &Avisorect);
		}
		else if (Avisos == 4)
		{
			SDL_RenderCopy(renderer2, Aviso4, NULL, &Avisorect);
		}
	}
	else if (Resultados == 1) 
	{
	
		SDL_RenderCopy(renderer2, ResultadosPan, &RestInicial, &RestFinal);
		SDL_RenderCopy(renderer2, ResultadosTitulo, NULL, &Avisorect);
		SDL_RenderCopy(renderer2, RestTextRob, NULL, &TextResult);
		SDL_RenderCopy(renderer2, RestTextRob2, NULL, &TextResult0);
		SDL_RenderCopy(renderer2, ResulTextCM, NULL, &TextResultM);
		SDL_RenderCopy(renderer2, ResulTextCM2, NULL, &TextResultM2);
		SDL_RenderCopy(renderer2, ResulTextC1, NULL, &TextResult1);
		SDL_RenderCopy(renderer2, ResulTextC12, NULL, &TextResult12);
		SDL_RenderCopy(renderer2, ResulTextC2, NULL, &TextResult2);
		SDL_RenderCopy(renderer2, ResulTextC22, NULL, &TextResult22);
		SDL_RenderCopy(renderer2, ResulTextC3, NULL, &TextResult3);
		SDL_RenderCopy(renderer2, ResulTextC32, NULL, &TextResult32);
	}
	

	SDL_RenderPresent(renderer2);
}

int* Game::CasosM()
{
	auto start = chrono::high_resolution_clock::now();
	
	int max_value = 0;
	
	for (int i = 0; i < (1 << 10); ++i) {
		int current_weight = 0;
		int current_value = 0;
		int current_set[10];
		int set_index = 0;

		
		for (int j = 0; j < 10; ++j) {
			if (i & (1 << j)) {
				current_weight += pesoObj[j];
				current_value += ValorObj[j];
				current_set[set_index++] = (j+1);
			}
		}

		
		if (current_weight <= SizeMochila && current_value > max_value) {
			casoM[10] = current_value;
			max_value = current_value;
			for (int k = 0; k < set_index; ++k) {
				casoM[k] = current_set[k];
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tiempo_transcurrido = end - start;
	std::cout << "\nTiempo transcurridoM: " << std::fixed << std::setprecision(8) << tiempo_transcurrido.count() << " segundos" << std::endl;
	ostringstream oss;
	oss << std::fixed << std::setprecision(8) << tiempo_transcurrido.count();
	tiempoEjeM = oss.str();

	cout << "\nCaso M ";
	for (int i = 0; i < 10; i++)
	{
		if(casoM[i] != 11)
		{
			scasoM = scasoM + to_string(casoM[i]) + ", ";
		}

		
	}
	sValorM = to_string(casoM[10]);
	

	scasoM.erase(scasoM.length() - 2);
	scasoM = scasoM + " ]";

	cout << scasoM;
	cout << "\nRobado: " << sValorM;


	return casoM;
}

int* Game::Casos1()
{
	auto start = chrono::high_resolution_clock::now();


	int temp = SizeMochila;
	int x = 0;

	for (int i = 0; i < 10; i++) 
	{
		if ((temp / pesoObj[i]) > 0 || temp == pesoObj[i])
		{
			temp = temp - pesoObj[i];
			caso1[10] += ValorObj[i];
			
			caso1[x] = i + 1;
			x++;
			if (temp == 0) 
			{
				break;
			}
		}
	}



	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tiempo_transcurrido = end - start;
	std::cout << "\nTiempo transcurrido1: " << std::fixed << std::setprecision(8) << tiempo_transcurrido.count() << " segundos" << std::endl;

	ostringstream oss;
	oss << std::fixed << std::setprecision(8) << tiempo_transcurrido.count();
	tiempoEje1 = oss.str();

	cout << "\nCaso 1 ";
	for (int i = 0; i < 10; i++)
	{
		if (caso1[i] != 11)
		{
			scaso1 = scaso1 + to_string(caso1[i]) + ", ";
		}
	}
	sValor1 = to_string(caso1[10]);

	scaso1.erase(scaso1.length() - 2);
	scaso1 = scaso1 + " ]";

	cout << scaso1;
	cout << "\nRobado: " << sValor1;
	return caso1;
}

int* Game::Casos2()
{
	auto start = chrono::high_resolution_clock::now();
	
	//Eleguir el objeto con el menor peso
	int temp = SizeMochila;
	int menorin = menor();
	int i = 0;
	while ((temp / pesoObj[menorin]) > 0 || pesoObj[menorin] == temp)
	{
		temp = temp - pesoObj[menorin];
		caso2[i] = menorin+1;
		i++;
		caso2[10] += ValorObj[menorin];
		Menores[menorin] = 0;
		
		menorin = menor();
		if (temp == 0)
		{
			break;
		}
	}


	auto end = std::chrono::high_resolution_clock::now();
	chrono::duration<double> tiempo_transcurrido = end - start;
	cout << "\nTiempo transcurrido2: " <<fixed << std::setprecision(8) << tiempo_transcurrido.count() << " segundos" << std::endl;
	ostringstream oss;
	oss << std::fixed << std::setprecision(8) << tiempo_transcurrido.count();
	tiempoEje2 = oss.str();

	cout << "\n Caso 2:";
	for (int i = 0; i < 10; i++)
	{
		if (caso2[i] != 11)
		{
			scaso2 = scaso2 + to_string(caso2[i]) + ", ";
		}
		
	}

	sValor2 = to_string(caso2[10]);
	scaso2.erase(scaso2.length() - 2);
	scaso2 = scaso2 + " ]";

	cout << scaso2;
	cout << "\nRobado: " << sValor2;
	return caso2;
}

int* Game::Casos3()
{
	auto start = chrono::high_resolution_clock::now();

	//Eleguir el objeto con el mayor peso
	int temp = SizeMochila;
	int mayorin = 0;
	int j = 0;

	
	for (int i = 0; i < 10; i++) 
	{
		
		mayorin = mayor();
 		if((temp / pesoObj[mayorin]) > 0 || pesoObj[mayorin] == temp)
		{
			
			temp = temp - pesoObj[mayorin];
			caso3[j] = mayorin + 1;
			j++;
			caso3[10] += ValorObj[mayorin];
			Mayores[mayorin] = 0;
			
			if (temp == 0) 
			{
				break;
			}
		}
		else 
		{

			Mayores[mayorin] = 0;
		}

	}
	
	auto end = std::chrono::high_resolution_clock::now();
	chrono::duration<double> tiempo_transcurrido = end - start;
	cout << "\nTiempo transcurrido3: " << fixed << std::setprecision(8) << tiempo_transcurrido.count() << " segundos" << std::endl;
	ostringstream oss;
	oss << std::fixed << std::setprecision(8) << tiempo_transcurrido.count();
	tiempoEje3 = oss.str();
	
	

	cout << "\n Caso 3:";
	for (int i = 0; i < 10; i++)
	{

		if (caso3[i] != 11)
		{
			scaso3 = scaso3 + to_string(caso3[i]) + ", ";
		}
	}
	sValor3 = to_string(caso3[10]);
	scaso3.erase(scaso3.length() - 2);
	scaso3 = scaso3 + " ]";

	cout << scaso3;
	cout << "\nRobado: " << sValor3;
	return caso3;
}

void Game::SubConjuntos()
{

	SDL_Event event;
	bool keepRunning = true;
	while (keepRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_s)
				{
					keepRunning = false;
				}
			}
		}

		SDL_RenderClear(renderer);

		// Renderizar un marco blanco alrededor de la pantalla
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco

		// Definir las dimensiones del marco
		int frameWidth = 10; // Ancho del marco en pixeles
		SDL_Rect frameRect = { frameWidth, frameWidth, 800 - 2 * frameWidth, 600 - 2 * frameWidth }; // Rectangulo interior que representa el area del marco

		// Dibujar el marco blanco
		SDL_RenderFillRect(renderer, &frameRect);

		// Dibujar un rectangulo interior mas pequeño para representar el area principal de la pantalla
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color negro para el interior
		SDL_Rect innerRect = { 2 * frameWidth, 2 * frameWidth, 800 - 4 * frameWidth, 600 - 4 * frameWidth }; // Rectangulo interior mas pequeño
		SDL_RenderFillRect(renderer, &innerRect);

		// Renderizar la imagen en el centro de la pantalla
		SDL_Surface* imageSurface = IMG_Load("Assets\\Pizarra.jpg");
		if (imageSurface == nullptr) {
			std::cerr << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
			// Manejar el error adecuadamente
		}
		else {
			SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
			if (imageTexture == nullptr) {
				std::cerr << "Error al crear la textura de la imagen: " << SDL_GetError() << std::endl;
				// Manejar el error adecuadamente
			}
			else {
				SDL_Rect imageRect; // Rectangulo para definir la posicion y tamaño de la imagen
				imageRect.w = imageSurface->w;
				imageRect.h = imageSurface->h;
				imageRect.x = (800 - imageSurface->w) / 2; // Centrar horizontalmente
				imageRect.y = (600 - imageSurface->h) / 2; // Centrar verticalmente

				SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);

				SDL_DestroyTexture(imageTexture);
			}
			SDL_FreeSurface(imageSurface);
		}

		// Renderizar titulo "Problema del subconjunto"
		std::string titleText = "Problema del subconjunto";
		renderText(titleText.c_str(), (800 - titleText.length() * 10) / 2, 50); // Centrado horizontalmente

		// Renderizar conjunto de numeros
		std::string numbersText = "Conjunto de numeros: ";
		for (size_t i = 0; i < numbers.size(); ++i) {
			numbersText += std::to_string(numbers[i]);
			if (i != numbers.size() - 1) {
				numbersText += ", ";
			}
		}
		renderText(numbersText.c_str(), 100, 100); // Renderizar conjunto de numeros en (100, 100)

		// Verificar si el subconjunto existe y calcular el tiempo de ejecucion
		SubsetSumSolver solver(numbers, targetSum);
		bool existsSubset;
		double subsetSumTime;
		{
			auto start = std::chrono::high_resolution_clock::now();
			existsSubset = solver.existsSubset();
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			subsetSumTime = elapsed_seconds.count(); // Almacenar el tiempo de ejecucion en segundos
		}
		std::string subsetResultText = existsSubset ? "El subconjunto con la suma objetivo existe." : "El subconjunto con la suma objetivo no existe.";
		renderText(subsetResultText.c_str(), 100, 150); // Renderizar resultado de la verificacion en (100, 150)

		// Renderizar tiempo de ejecucion del subset sum
		std::string timeText = "Tiempo de ejecucion: " + std::to_string(subsetSumTime) + " segundos";
		renderText(timeText.c_str(), 100, 200); // Renderizar tiempo de ejecucion en (100, 200)

		SDL_RenderPresent(renderer);
	}
}

int Game::menor()
{
	int indice = 0;
	int menor = Menores[0]; 
	
	for (int i = 1; i < 10; ++i) {

		if (Menores[i] != 0) {
			if (menor == 0)
			{
				menor = Menores[i];
				indice = i;
			}
			
			if (pesoObj[i] < menor) {
				menor = Menores[i];
				indice = i;
			}
			
		}
	}

	
	return indice;
}

int Game::mayor()
{
	int indice = 0;
	
	int mayor = Mayores[0]; 
	for (int i = 1; i < 10; ++i) {
		if (Mayores[i] != 0) 
		{
			if (Mayores[i] > mayor) {
				mayor = Mayores[i];
				indice = i;
			}
		}
	}
	return indice;
}


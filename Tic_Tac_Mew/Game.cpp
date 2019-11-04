#include "DEFINITIONS.h"
#include "RunGame.h"
#include "StandardCursor.h"

using namespace sf;

void Game::loadTextures() {
	texmgr_.loadTexture("catBackground", CAT_BACKGROUND_MENU);
	texmgr_.loadTexture("background", MAIN_BACKGROUND);
	texmgr_.loadTexture("grid", GRID_SPRITE_FILEPATH);
	texmgr_.loadTexture("new game headline", NEW_GAME_MENU);
	texmgr_.loadTexture("info headline", INFO_MENU);
	texmgr_.loadTexture("exit headline", EXIT_MENU);
	texmgr_.loadTexture("about", PRAVILA);
	texmgr_.loadTexture("return esc", RETURN_MENU_ESC);
}

Game::Game() {
	//загружаем необходимые текстуры
	this->loadTextures();

	//создаем окно приложени€
	this->window_.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tic Tac Mew", Style::None);

	//устанавливаем значок
	Image icon;
	icon.loadFromFile(ICON);
	window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//частота кадров
	this->window_.setFramerateLimit(60);
}

//ƒеструктор
Game::~Game() { }


void Game::menu() {

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture,
		menuBackground, mainBackground, grid, xPiece,
		retEsc;

	menuTexture1 = texmgr_.getRef("new game headline"); //надпись "нова€ игра"
	menuTexture2 = texmgr_.getRef("info headline"); //надпись "об игре"
	menuTexture3 = texmgr_.getRef("exit headline"); //надпись "выход"
	aboutTexture = texmgr_.getRef("about"); // текст "об игре.."
	menuBackground = texmgr_.getRef("catBackground"); //фон главного меню
	mainBackground = texmgr_.getRef("background"); //основной фон игры
	grid = texmgr_.getRef("grid"); // клеточки
	retEsc = texmgr_.getRef("return esc"); //надпись вернутьс€ в меню esc


	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3),
		about(aboutTexture), menuBg(menuBackground), mainBg(mainBackground),
		gameGrid(grid), xSprite(xPiece),
		retEscSprite(retEsc);

	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(150, 200);
	menu2.setPosition(150, 260);
	menu3.setPosition(150, 320);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window_.clear(Color(129, 181, 221));

		//если курсор попадает на кнопки, они мен€т цвет
		if (IntRect(150, 200, 300, 50).contains(Mouse::getPosition(window_))) {
			menu1.setColor(Color::Magenta);
			menuNum = 1;
		}
		if (IntRect(150, 260, 300, 50).contains(Mouse::getPosition(window_))) {
			menu2.setColor(Color::Magenta);
			menuNum = 2;
		}
		if (IntRect(150, 320, 300, 50).contains(Mouse::getPosition(window_))) {
			menu3.setColor(Color::Magenta);
			menuNum = 3;
		}

		//если была нажата лева€ кнопка мыши
		Event eventM;
		window_.pollEvent(eventM);
		if (eventM.type == Event::MouseButtonPressed)
			//if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				//рисуем фон дл€ игры и клеточки
				window_.draw(mainBg);
				gameGrid.setPosition(150, 75);
				window_.draw(gameGrid);
				window_.display();

				//мен€ем на обычный курсор
				window_.setMouseCursorVisible(true);
				StandardCursor Cursor(sf::StandardCursor::HAND);
				Cursor.set(window_.getSystemHandle());

				//запускаем алгоритм игры
				runGame(window_);

			}
			if (menuNum == 2) {
				//рисуем фон и текст с информацией пока не нажата клавиша esc
				window_.draw(mainBg);

				about.setPosition(150, 75);
				window_.draw(about);

				retEscSprite.setPosition(150, 650);
				window_.draw(retEscSprite);

				window_.display();

				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuNum == 3) {
				//закрываем окно
				window_.close();
				isMenu = false;
			}

		}

		window_.draw(menuBg);
		window_.draw(menu1);
		window_.draw(menu2);
		window_.draw(menu3);


		//пр€чем курсор
		window_.setMouseCursorVisible(false);
		View fixed = window_.getView(); // создаем фиксированный вид

		// загружаем изображение курсора и создаем спрайт
		Texture cursor;
		cursor.loadFromFile(CURSOR);
		Sprite cursorSprite(cursor);

		cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window_)));

		window_.setView(fixed);
		window_.draw(cursorSprite);


		window_.display();
	}
}

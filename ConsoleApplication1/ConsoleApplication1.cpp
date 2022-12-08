
#include <SFML/Graphics.hpp> 
#include <SFML/Window.hpp> 
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>
#include <iostream>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <stdio.h>

// main prototypes
void testCode();
void foo(void);
int ProgramLoop();
int LoadResorces();

//  links to sfml prototypes
void sfPrint(std::string s1, float x1, float y1, int size, _int32 cl);
void sfPlot(float x, float y, _int32 cl);
void sfLine(float x1, float y1, float  x2, float y2, _int32 cl);
void sfGetKey();
int sfGetSprite(std::string fileName);
void sfPutSprite(float x, float y, int spriteId);


// globals
int					spriteId{};							// start at zero
const int		MaxSprites{ 10 };				// maximum number of sprites, can be increased
sf::Sprite		Sprites[MaxSprites];				// setup sprite array	
sf::Texture		SpriteTexture[MaxSprites];	// texture to convert to Sprite[n]
const int		WW{ 1024 };						// window width in pixels (windows in side main window)
const int		WH{ 768 };							// window hight in pixels as WW
const std::string	WT("Main window");			// window title



#include "RGB-Colours.txt"		// limited RGB palette const sf::Uint32 
#include "SfmkKbdEnum.txt"	//  enumeration values for sfml keycodes enum class Key

std::string errorName;				//error message for console otput
sf::RenderTexture finalTexture;	// pointer to textture to send all output to
sf::Font font;								// holder for working font
sf::Event event;							// holder for event in window

void foo(void)
{
	__asm
	{
		push	ecx
		mov		ecx, 0xFFFFFFFF
		l2:		dec		ecx
				jnz		l2
				pop		ecx
				leave
				ret
	};
}

class MyClass {       // The class
public:             // Access specifier
	int myNum;        // Attribute (int variable)
	std::string myString;  // Attribute (string variable)
};

int main()
{
	int end;								//  program exit status
	end = (ProgramLoop());					// do program logic
	if (end)
	{
		std::cout << "resource load error  " << errorName << std::endl;
		return EXIT_FAILURE;	// for development purpose 
	}
}


int ProgramLoop()
{
	if (LoadResorces())	return EXIT_FAILURE;
	const sf::Texture& allTextures = finalTexture.getTexture(); // pointer for all redering
	sf::RenderWindow window(sf::VideoMode(WW, WH), WT);		// Create the main window at sw,sh with title wt
	while (window.isOpen())			// Start the game loop
	{
		while (window.pollEvent(event))	// Process events
		{
			if (event.type == sf::Event::Closed)	// Close window and exit
				window.close();							// save game etc at this point

			if (event.type == sf::Event::EventType::KeyPressed)
				sfGetKey();		// capture key press

		}
		testCode();					// test routines while progam utils are written
				
		sf::Sprite t2s(allTextures);		// final texture everything is rendered to
		t2s.setPosition(0, 0);				// postion 0,0 of window
		window.draw(t2s);				// draw final texture in window
		window.display();					// display window
		}											// loop while window is open
	return  EXIT_SUCCESS;
}

void testCode()
{
	MyClass myObj;								// Create an object of MyClass
	myObj.myNum = 15;						// Access attributes and set values
	myObj.myString = "Some text";			// test output some text
	std::cout << myObj.myNum << "\n";	// Print attribute values
	std::cout << myObj.myString << "\n";
	sfPrint("hello", 500, 100, 100,Blue);
	sfLine(100, 100, 800, 800, pink);
	sfPutSprite(300, 300, 1);					// display sprite 1 at 300,300
	sfPutSprite(0, 0, 0);							// display sprite 0 at 0,0
	return;
}

int LoadResorces(void)
{
	int error{1};					// inital error number
	std::string fileName{};	// resorce file name
	static sf::Music music;	// load music to play
	errorName = { "c:\\Resources\\arial.ttf" }; // load font for text output
	fileName = errorName;
	if (!font.loadFromFile(fileName)) return(error); //error
	error++;
	errorName = { "c:\\Resources\\cute_image.jpeg" };
	fileName = errorName;
	if (sfGetSprite(fileName) == EXIT_FAILURE) return (error);
	error++;
	errorName = { "c:\\Resources\\cute-tabby.jpg" };
	fileName = errorName;
	if (sfGetSprite(fileName) == EXIT_FAILURE) return (error);
	error++;
	errorName = { "C:\\Resources\\JMJ4SFML01.ogg" };
	fileName = errorName;
	if (!music.openFromFile(fileName)) return (error); //error

	// build back screen
	errorName = { "texture create failed." };
	if (!finalTexture.create(WW, WH)) return 100;  // error...
	music.play(); 		// Play the music
	return EXIT_SUCCESS;
}

int sfGetSprite(std::string fileName)
{
	errorName = fileName;					// filename becomes error name for failure
	if (!SpriteTexture[spriteId].loadFromFile(fileName)) return (EXIT_FAILURE);	//error
	Sprites[spriteId].setTexture(SpriteTexture[spriteId]);
	spriteId++;									// texture loaded, so increase sprite id for next load
	return (EXIT_SUCCESS);
}
void sfPutSprite(float x, float y, int spriteid)
{
		if (spriteid >= ::spriteId)
		{
			std::cout << "SpriteId = " << spriteid <<  " not defined" << std::endl;
		}

	Sprites[spriteid].setPosition(x, y);		// display sprite from array at x,y
	finalTexture.draw(Sprites[spriteid]);
	return;
}
void sfPrint(std::string s1, float x1, float y1, int size, _int32 cl)
{
	sf::Text text(s1, font, size);
	text.setFillColor(sf::Color(cl));
	text.setPosition(x1, y1);
	finalTexture.draw(text);
	return ;
}

void sfPlot(float x, float y, _int32 cl)
{
	sfLine(x, y, x+1, y+1,cl);
	return;
}

void sfLine( float x1, float y1, float  x2, float y2, _int32 cl)
{
	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};
	line2[0].color = sf::Color(cl);
	line2[1].color = sf::Color(cl);
	finalTexture.draw(line2, 2, sf::Lines);
	finalTexture.display();
	return;
}

void sfGetKey()
{
	char  key = event.key.code;			// key pressed 'a' returns 0
	Key alphaA(Key::A);					// enum Key class const A
	Key alphaZ(Key::Z);						// enum Key class const Z
	Key num0(Key::Num0);				// enum Key class const 0 
	Key num9(Key::Num9);				// enum Key class const 9
	Key comma(Key::Comma);			// enum key class comma
	Key period(Key::Period);				// enum key class period
	Key space(Key::Space);				// enum key class space
	Key equal(Key::Equal);					// enum key class =
	Key hypen(Key::Hyphen);				// enum class -
	Key add(Key::Add);						// enum key class +
	Key subtract(Key::Subtract);			// enum key class -
	Key multiply(Key::Multiply);			// enum class *
	Key devide(Key::Divide);				// enum class /
	Key tilde(Key::Tilde);					// enum class ~
	Key rbracket(Key::RBracket);		// enum class )
	Key lbracket(Key::LBracket);		// enum class (

	if (key >= (static_cast<char>(alphaA)) && key <= (static_cast<char>(alphaZ)))
	{
		key += 65;	// shift to  ascii a-z
		std::cout << key << std::endl;
		return;
	}
	if (key >= (static_cast<char>(num0)) && key <= (static_cast<char>(num9)))
	{
		key += 22; // shift to ascii 0-9
		std::cout << key << std::endl;
		return;
	}
	if (key == (static_cast<char> (comma)))
	{
		key = (static_cast<char> (','));
		std::cout << key << std::endl;
		return;
	}
	if (key == (static_cast<char> (period)))
	{
		key = (static_cast<char> ('.'));
		std::cout << key << std::endl;
		return;
	}

	if (key == (static_cast<char> (space)))
	{
		key = (static_cast<char> (' '));
		std::cout << key << std::endl;
		return;
	}

	if (key == (static_cast<char> (equal)))
	{
		key = (static_cast<char> ('='));
	}

	if (key == (static_cast<char> (add)))
	{
		key = (static_cast<char> ('+'));		// not caught
	}
	
	if (key == (static_cast<char> (subtract)))
	{
		key = (static_cast<char> ('-'));
	}

	if (key == (static_cast<char> (devide)))	// not caught
	{
		key = (static_cast<char> ('/'));			// not caught
	}
	if (key == (static_cast<char> (multiply)))
	{
		key = (static_cast<char> ('*'));		// not caught
		std::cout << key << std::endl;
	}

	if (key == (static_cast<char> (tilde)))
	{

		key = (static_cast<char> ('~'));		// not caught
		std::cout << key << std::endl;
	}

	if (key == (static_cast<char> (rbracket)))	// not caught
	{
		key = (static_cast<char> (')'));	// not caught
		std::cout << key << std::endl;
	}

	if (key == (static_cast<char> (lbracket)))
	{
		key = (static_cast<char> ('('));	// not caught
		std::cout << key << std::endl;
	}

	if (key == (static_cast<char> (hypen))) key = (static_cast<char> ('-'));	// not caught
	{
		std::cout << key << std::endl;
		return;
	}
}

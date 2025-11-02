#include "Cfg.h"

ResourceManager<sf::Texture, Cfg::Textures> Cfg::textures = {};
ResourceManager<sf::Font, Cfg::Fonts> Cfg::fonts = {};
ResourceManager<sf::Music, Cfg::Music> Cfg::music = {};
ResourceManager<sf::SoundBuffer, Cfg::Sounds> Cfg::sounds = {};


void Cfg::Initialize()
{
    initTextures();
    initFonts();
	initMusic();
    initSounds();
}

void Cfg::Uninitialize()
{
	Cfg::textures.unloadAll();
}

void Cfg::initMusic()
{
	//music.load(Music::Intro, "assets/sfx/intro.wav");
}

void Cfg::initSounds()
{
	//sounds.load(Sounds::MM_BigDmg, "assets/sfx/bigdmg.wav");


}

void Cfg::initTextures()
{
	//textures.load(Textures::Tileset1, "../Client/Textures/tiles.png");
	textures.load(Textures::PlayerAtlas, "assets/PlayerAtlas.png");
	textures.load(Textures::Tileset1, "assets/textures/tilesets/tileset1.png");
	
}


void Cfg::destroyTextures()
{
	
}


void Cfg::initFonts()
{
	//fonts.load(Cfg::Fonts::Font1, "../Client/Fonts/font1.ttf");
}
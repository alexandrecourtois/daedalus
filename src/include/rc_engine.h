#ifndef RC_ENGINE_H
#define RC_ENGINE_H

#include <tools.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <player.h>


const int screenWidth = 1280;
const int screenHeight = 720;

const float cameraHeight = 0.66f; // height of player camera(1.0 is ceiling, 0.0 is floor)

const int texture_size = 512; // size(width and height) of texture that will hold all wall textures
const int texture_wall_size = 128; // size(width and height) of each wall type in the full texture

const float fps_refresh_time = 0.1f; // time between FPS text refresh. FPS is smoothed out over this time

// list of wall texture types, in order as they appear in the full texture
enum class WallTexture {
    Smiley,
    Red,
    Bush,
    Sky,
    Pink,
    Wallpaper,
    Dirt,
    Exit,
};

// valid wall types and their texture for the world map
const std::unordered_map<char, WallTexture> wallTypes {
    {'#', WallTexture::Pink},
    {'=', WallTexture::Dirt},
    {'M', WallTexture::Wallpaper},
    {'N', WallTexture::Bush},
    {'~', WallTexture::Sky},
    {'!', WallTexture::Red},
    {'@', WallTexture::Smiley},
    {'^', WallTexture::Exit},
};

// size of the top-down world map in tiles
const int mapWidth = 24;
const int mapHeight = 24;

// top-down view of world map
const char worldMap[] =
    "~~~~~~~~~~~~~~~~MMM@MMMM"
    "~..............=M......M"
    "~..............=M......M"
    "~..............=@......@"
    "~..............=M......M"
    "~....N......N..........M"
    "~..............=MMM@MM.M"
    "~..............======M.M"
    "~..............=MMMMMM.M"
    "~..............=M......M"
    "~...N....N.....=M..N..M#"
    "~.....................M#"
    "~..............=M..N..M#"
    "~..............=M.....M#"
    "~...........N..=MMMMM.M#"
    "~..............======.=#"
    "#.!!!!!!.!!!!!!........#"
    "#.!....!.!..........=..#"
    "#.!.N..!.!..==..=...=..#"
    "#...........==..==..=..#"
    "#.!!!!!!.!..==.........#"
    "#.######.#..==....=....#"
    "N......................^"
    "########################";

class RC_engine {
public:
	RC_engine();

	char				getTile(int x, int y);
	bool				mapCheck();
	bool 				canMove(sf::Vector2f position, sf::Vector2f size);
	sf::Vector2f 		rotateVec(sf::Vector2f vec, float value);
	void 				render();
	void				init(Player* player);
	sf::Vector2f		m_plane;
	sf::Texture			m_texture;
	sf::RenderStates	m_renderState;
	sf::VertexArray 	m_lines;
	Player*				m_player;
	float				m_moveDir;
	float				m_rotateDir;
	void				moveForward();
	void				moveBackward();
	void				rotateLeft();
	void				rotateRight();
};

#endif // RC_ENGINE_H
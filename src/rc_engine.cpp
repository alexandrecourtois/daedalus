#include <rc_engine.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <viewport.h>
#include <iostream>

RC_engine::RC_engine() {
}

char RC_engine::getTile(int x, int y) {
    return worldMap[y * mapWidth + x];
}

// checks worldMap for errors
// returns: true on success, false on errors found
bool RC_engine::mapCheck() {
    // check size
    int mapSize = sizeof(worldMap) - 1; // - 1 because sizeof also counts the final NULL character
    if (mapSize != mapWidth * mapHeight) {
        fprintf(stderr, "Map size(%d) is not mapWidth * mapHeight(%d)\n", mapSize, mapWidth * mapHeight);
        return false;
    }

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            char tile = getTile(x, y);
            // check if tile type is valid
            if (tile != '.' && wallTypes.find(tile) == wallTypes.end()) {
                fprintf(stderr, "map tile at [%3d,%3d] has an unknown tile type(%c)\n", x, y, tile);
                return false;
            }
            // check if edges are walls
            if ((y == 0 || x == 0 || y == mapHeight - 1 || x == mapWidth - 1) &&
                    tile == '.') {
                fprintf(stderr, "map edge at [%3d,%3d] is a floor (should be wall)\n", x, y);
                return false;
            }
        }
    }
    return true;
}

// check if a rectangular thing with given size can move to given m_player->getPosition() without colliding with walls or
// being outside of the map
// m_player->getPosition() is considered the middle of the rectangle
bool RC_engine::canMove(sf::Vector2f position, sf::Vector2f size) {
    // create the corners of the rectangle
    sf::Vector2i upper_left(position - size / 2.0f);
    sf::Vector2i lower_right(position + size / 2.0f);
    if (upper_left.x < 0 || upper_left.y < 0 || lower_right.x >= mapWidth || lower_right.y >= mapHeight) {
        return false; // out of map bounds
    }
    // loop through each map tile within the rectangle. The rectangle could be multiple tiles in size!
    for (int y = upper_left.y; y <= lower_right.y; ++y) {
        for (int x = upper_left.x; x <= lower_right.x; ++x) {
            if (getTile(x, y) != '.') {
                return false;
            }
        }
    }
    return true;
}

// rotate a given vector with given float value in radians and return the result
// see: https://en.wikipedia.org/wiki/Rotation_matrix#In_two_dimensions
sf::Vector2f RC_engine::rotateVec(sf::Vector2f vec, float value) {
    return sf::Vector2f(
            vec.x * std::cos(value) - vec.y * std::sin(value),
            vec.x * std::sin(value) + vec.y * std::cos(value)
    );
}

void RC_engine::init(Player* player) {
	m_player = player;
	
    if (!mapCheck()) {
        fprintf(stderr, "Map is invalid!\n");
        return;
    }

	if (!m_texture.loadFromFile("data/texture/walls.png")) {
        fprintf(stderr, "Cannot open texture!\n");
        return;
    }
	
	m_renderState = sf::RenderStates(&m_texture);
	m_lines = sf::VertexArray(sf::Lines, 18 * VIEWPORT->getSize().x);
}

void RC_engine::render() {
            // handle movement
            if (m_moveDir != 0.0f) {
				sf::Vector2f moveVec = m_player->getDirection() * m_player->getMoveSpeed() * m_moveDir * VIEWPORT->getElapsedTime();
				std::cout << moveVec.x << "/" << moveVec.y << "\n";

                if (canMove(sf::Vector2f(m_player->getPosition().x + moveVec.x, m_player->getPosition().y), m_player->getBox2D())) {
                    m_player->setPosition(m_player->getPosition().x + moveVec.x, m_player->getPosition().y);
										std::cout << "pos:" << m_player->getPosition().x << "/" << m_player->getPosition().y << "\n";

                }
                if (canMove(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y + moveVec.y), m_player->getBox2D())) {
                    m_player->setPosition(m_player->getPosition().x, m_player->getPosition().y + moveVec.y);
															std::cout << "pos:" << m_player->getPosition().x << "/" << m_player->getPosition().y << "\n";

                }
            }

            // handle rotation
			
            if (m_rotateDir != 0.0f) {
                float rotation = m_player->getRotateSpeed() * m_rotateDir * VIEWPORT->getElapsedTime();// * dt;
                m_player->setDirection(rotateVec(m_player->getDirection(), rotation).x, rotateVec(m_player->getDirection(), rotation).y);
                m_player->setPlane(rotateVec(m_player->getPlane(), rotation).x, rotateVec(m_player->getPlane(), rotation).y);
            }

		m_moveDir = 0.0f;
		m_rotateDir = 0.0f;
        m_lines.resize(0);

        // loop through vertical screen lines, draw a line of wall for each
        for (int x = 0; x < VIEWPORT->getSize().x; ++x) {

            // ray to emit
            float cameraX = 2 * x / (float)VIEWPORT->getSize().x - 1.0f; // x in camera space (between -1 and +1)
            sf::Vector2f rayPos = m_player->getPosition();
            sf::Vector2f rayDir = m_player->getDirection() + m_player->getPlane() * cameraX;

            // NOTE: with floats, division by zero gives you the "infinity" value. This code depends on this.

            // calculate distance traversed between each grid line for x and y based on m_player->getDirection()
            sf::Vector2f deltaDist(
                    sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
                    sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y))
            );

            sf::Vector2i mapPos(rayPos); // which box of the map we're in

            sf::Vector2i step; // what m_player->getDirection() to step in (+1 or -1 for each dimension)
            sf::Vector2f sideDist; // distance from current m_player->getPosition() to next gridline, for x and y separately

            // calculate step and initial sideDist
            if (rayDir.x < 0.0f) {
                step.x = -1;
                sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
            } else {
                step.x = 1;
                sideDist.x = (mapPos.x + 1.0f - rayPos.x) * deltaDist.x;
            }
            if (rayDir.y < 0.0f) {
                step.y = -1;
                sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
            } else {
                step.y = 1;
                sideDist.y = (mapPos.y + 1.0f - rayPos.y) * deltaDist.y;
            }

            char tile = '.'; // tile type that got hit
            bool horizontal; // did we hit a horizontal side? Otherwise it's vertical

            float perpWallDist = 0.0f; // wall distance, projected on camera m_player->getDirection()
            int wallHeight; // height of wall to draw on the screen at each distance
            int ceilingPixel = 0; // m_player->getPosition() of ceiling pixel on the screen
            int groundPixel = VIEWPORT->getSize().y; // m_player->getPosition() of ground pixel on the screen

            // colors for floor tiles
            sf::Color color1 = sf::Color::Green;
            sf::Color color2 = sf::Color::Cyan;

            // current floor color
            sf::Color color = ((mapPos.x % 2 == 0 && mapPos.y % 2 == 0) ||
                               (mapPos.x % 2 == 1 && mapPos.y % 2 == 1)) ? color1 : color2;

            // cast the ray until we hit a wall, meanwhile draw floors
            while (tile == '.') {
                if (sideDist.x < sideDist.y) {
                    sideDist.x += deltaDist.x;
                    mapPos.x += step.x;
                    horizontal = true;
                    perpWallDist = (mapPos.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
                } else {
                    sideDist.y += deltaDist.y;
                    mapPos.y += step.y;
                    horizontal = false;
                    perpWallDist = (mapPos.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;
                }

                wallHeight = VIEWPORT->getSize().y / perpWallDist;

                // add floor

                m_lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(385.0f, 129.0f)));
                groundPixel = int(wallHeight * cameraHeight + VIEWPORT->getSize().y * 0.5f);
                m_lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(385.0f, 129.0f)));

                // add ceiling

                sf::Color color_c = color;
                color_c.r /= 2;
                color_c.g /= 2;
                color_c.b /= 2;

                m_lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(385.0f, 129.0f)));
                ceilingPixel = int(-wallHeight * (1.0f - cameraHeight) + VIEWPORT->getSize().y * 0.5f);
                m_lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(385.0f, 129.0f)));

                // change color and find tile type

                color = (color == color1) ? color2 : color1;

                tile = getTile(mapPos.x, mapPos.y);
            }

            // calculate lowest and highest pixel to fill in current line
            int drawStart = ceilingPixel;
            int drawEnd = groundPixel;

            // get m_player->getPosition() of the wall texture in the full texture
            int wallTextureNum = (int)wallTypes.find(tile)->second;
            sf::Vector2i texture_coords(
                    wallTextureNum * texture_wall_size % texture_size,
                    wallTextureNum * texture_wall_size / texture_size * texture_wall_size
            );

            // calculate where the wall was hit
            float wall_x;
            if (horizontal) {
                wall_x = rayPos.y + perpWallDist * rayDir.y;
            } else {
                wall_x = rayPos.x + perpWallDist * rayDir.x;
            }
            wall_x -= floor(wall_x);

            // get x coordinate on the wall texture
            int tex_x = int(wall_x * float(texture_wall_size));

            // flip texture if we see it on the other side of us, this prevents a mirrored effect for the texture
            if ((horizontal && rayDir.x <= 0) || (!horizontal && rayDir.y >= 0)) {
                tex_x = texture_wall_size - tex_x - 1;
            }

            texture_coords.x += tex_x;

            // illusion of shadows by making horizontal walls darker
            color = sf::Color::White;
            if (horizontal) {
                color.r /= 2;
                color.g /= 2;
                color.b /= 2;
            }

            // add line to vertex buffer
            m_lines.append(sf::Vertex(
                        sf::Vector2f((float)x, (float)drawStart),
                        color,
                        sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1)
            ));
            m_lines.append(sf::Vertex(
                        sf::Vector2f((float)x, (float)drawEnd),
                        color,
                        sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + texture_wall_size - 1))
            ));
        }

		VIEWPORT->draw(m_lines, m_renderState);
    }
	
	void RC_engine::moveForward() {
		m_moveDir = 1.0f;
	}
	
	void RC_engine::moveBackward() {
		m_moveDir = -1.0f;
	}
	
	void RC_engine::rotateLeft() {
		m_rotateDir = -1.0f;
	}
	
	void RC_engine::rotateRight() {
		m_rotateDir = 1.0f;
	}

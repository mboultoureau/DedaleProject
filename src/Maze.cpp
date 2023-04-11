#include "Maze.h"

#include <fstream>

Maze::Maze(const std::string& filepath)
{
    std::ifstream stream(filepath);

    m_Height = 1;
    m_Width = 3;
    m_Length = 3;
    m_Cells = {
        {
            {WALL_EAST, 0, 0},
            {0, WALL_NORTH, 0},
            {WALL_NORTH, WALL_NORTH, 0}
        }
    };
}

Maze::~Maze()
{
    
}
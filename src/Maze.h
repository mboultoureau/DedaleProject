#pragma once

#include <vector>
#include <string>

enum WALL {
    WALL_NORTH = 0x01,
    WALL_EAST = 0x02
};

class Maze
{
public:
    Maze(const std::string& filepath);
    ~Maze();

    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetLength() const { return m_Length; }
    inline unsigned int GetHeight() const { return m_Height; }
    inline unsigned char GetCell(unsigned int x, unsigned int y, unsigned z) { return m_Cells[z][y][x]; }

private:
    unsigned int m_Width;
    unsigned int m_Length;
    unsigned int m_Height;
    std::vector<std::vector<std::vector<unsigned char>>> m_Cells;
};
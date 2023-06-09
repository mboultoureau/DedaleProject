#pragma once

#include <vector>
#include <string>

enum WALL_TYPE {
    WALL_NORTH = 0x01,
    WALL_SOUTH = 0x02,
    WALL_EAST = 0x04,
    WALL_WEST = 0x08
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
    inline float GetCellSize() const { return m_CellSize; }

    void Print();
private:
    unsigned int m_Width;
    unsigned int m_Length;
    unsigned int m_Height;
    float m_CellSize = 50.0f;

    std::vector<std::vector<std::vector<unsigned char>>> m_Cells;
};
#include "Maze.h"

#include <iostream>
#include <fstream>
#include <sstream>

Maze::Maze(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line, number;

    // Open file
    if (!stream.is_open())
    {
        std::cout << "Unable to read file: " << filepath << std::endl;
        return;
    }

    // Get first line (size of maze)
    if (!getline(stream, line))
    {
        std::cout << "Unable to read first line at file: " << filepath << std::endl;
        return;
    }

    // Parse size of maze : x, y, z
    std::stringstream lineStream(line);
    if (!getline(lineStream, number, ' '))
    {
        std::cout << "Unable to read x dimension size: " << filepath << std::endl;
        return;
    }
    m_Length = std::stoi(number);

    if (!getline(lineStream, number, ' '))
    {
        std::cout << "Unable to read y dimension size: " << filepath << std::endl;
        return;
    }
    m_Width = std::stoi(number);

    if (!getline(lineStream, number, ' '))
    {
        std::cout << "Unable to read z dimension size: " << filepath << std::endl;
        return;
    }
    m_Height = std::stoi(number);

    std::cout << "Maze size: " << m_Length << "x" << m_Width << "x" << m_Height << std::endl;
    
    // Parse maze
    std::vector<std::vector<unsigned char>> layer;
    unsigned int y = 0;
    unsigned int x = 0;
    while (getline(stream, line))
    {
        x = 0;

        std::stringstream lineStream(line);
        std::vector<unsigned char> row;
        
        while (getline(lineStream, number, ' '))
        {
            row.push_back(std::stoi(number));
            x++;
        }
        
        if (x != m_Length)
        {
            std::cout << x << std::endl;
            std::cout << "Wrong number of columns in row " << y << " at file: " << filepath << std::endl;
            return;
        }

        layer.push_back(row);
        y++;
    }

    m_Cells.push_back(layer);

    if (y != m_Width)
    {
        std::cout << "Wrong number of lines at file: " << filepath << std::endl;
        return;
    }

    Print();

    stream.close();
}

Maze::~Maze()
{
    
}

void Maze::Print()
{
    for (unsigned int z = 0; z < m_Height; z++)
    {
        for (unsigned int y = 0; y < m_Width; y++)
        {
            for (unsigned int x = 0; x < m_Length; x++)
            {
                std::cout << (int)m_Cells[z][y][x] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
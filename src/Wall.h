#pragma once

#include <Mesh.h>
#include <gl-matrix.h>

#include "Maze.h"

class Wall: public Mesh
{
private:

    /** matériau */
    Material* m_Material;

    /** buffers pour la gestion du son */
    ALuint buffer, source;

    /** position 3D du mur */
    vec3 m_Position;

    /** type du mur */
    WALL_TYPE m_Type;

public:

    /** constructeur, crée le VBO et le shader */
    Wall(std::string soundpathname);

    /** destructeur, libère le VBO et le shader */
    ~Wall();

    /**
     * dessiner le mur
     * @param matP : matrice de projection
     * @param matMV : matrice view
     */
    void onRender(const mat4& matP, const mat4& matV);

    /**
     * retourne la position % scène du mur
     * @return vec3 position
     */
    vec3& getPosition();

    /**
     * affecte la position % scène du mur
     * @param vec3 pos position
     */
    void setPosition(vec3 pos);

    /**
     * retourne le type du mur
     * @return WALL type du mur
     */
    WALL_TYPE getType();

    /**
     * affecte le type du mur
     * @param WALL type du mur
     */
    void setType(WALL_TYPE type);
};


#pragma once

// Définition de la classe Wall

#include <Mesh.h>
#include <gl-matrix.h>

class Wall: public Mesh
{
private:

    /** matériau */
    Material* m_Material;

    /** buffers pour la gestion du son */
    ALuint buffer, source;

    /** position 3D du mur */
    vec3 m_Position;


public:

    /** constructeur, crée le VBO et le shader */
    Wall(std::string soundpathname);

    /** destructeur, libère le VBO et le shader */
    ~Wall();

    /**
     * dessiner le mur
     * @param matP : matrice de projection
     * @param matMV : matrice view*model (caméra * position objet)
     */
    void onRender(const mat4& matP, const mat4& matMV);

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
};

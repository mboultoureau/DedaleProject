#ifndef SCENE_H
#define SCENE_H

// Définition de la classe Scene

#include <gl-matrix.h>
#include <vector>

#include "Light.h"

#include "Cube.h"
#include "Wall.h"
#include "Duck.h"
#include "Ground.h"

#include "Maze.h"


class Scene
{
private:

    /** buffers pour la gestion du son */
    ALuint buffer, source;


    // objets de la scène
    Cube* m_Cube;
    std::vector<Wall*> m_Walls;
    Duck* m_Duck;
    Ground* m_Ground;

    // lampes
    Light* m_Light;

    // matrices de transformation des objets de la scène
    mat4 m_MatP;
    mat4 m_MatV;
    mat4 m_MatR;
    mat4 m_MatVM;

    // caméra table tournante
    float m_Azimut;
    float m_Elevation;
    float m_Distance;
    vec3 m_InvPosCam;

    // souris
    bool m_Clicked;
    double m_MousePrecX;
    double m_MousePrecY;

    // chronomètre
    float m_PredTime;

    // vitesse de déplacement
    float m_Vy;

    // labyrinthe
    Maze* m_Maze;


public:

    /** constructeur, crée les objets 3D à dessiner */
    Scene();

    /** destructeur, libère les ressources */
    ~Scene();

    /**
     * appelée quand la taille de la vue OpenGL change
     * @param width : largeur en nombre de pixels de la fenêtre
     * @param height : hauteur en nombre de pixels de la fenêtre
     */
    void onSurfaceChanged(int width, int height);


    /**
     * appelée quand on enfonce un bouton de la souris
     * @param btn : GLFW_MOUSE_BUTTON_LEFT pour le bouton gauche
     * @param x coordonnée horizontale relative à la fenêtre
     * @param y coordonnée verticale relative à la fenêtre
     */
    void onMouseDown(int btn, double x, double y);

    /**
     * appelée quand on relache un bouton de la souris
     * @param btn : GLFW_MOUSE_BUTTON_LEFT pour le bouton gauche
     * @param x coordonnée horizontale relative à la fenêtre
     * @param y coordonnée verticale relative à la fenêtre
     */
    void onMouseUp(int btn, double x, double y);

    /**
     * appelée quand on bouge la souris
     * @param x coordonnée horizontale relative à la fenêtre
     * @param y coordonnée verticale relative à la fenêtre
     */
    void onMouseMove(double x, double y);

    /**
     * appelée quand on appuie sur une touche du clavier
     * @param code : touche enfoncée
     */
    void onKeyDown(unsigned char code);

    /** Dessine l'image courante */
    void onDrawFrame();

    /** retourne la distance entre les murs et la caméra **/
    void get_wall_distance(float limit);

    void PlaySound(float value1, float value2, float value3);

    void CheckWall(float limit);



};

#endif

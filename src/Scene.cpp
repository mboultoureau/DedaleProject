#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <utils.h>

#include "Scene.h"


/** constructeur */
Scene::Scene()
{
    // importer le labyrinthe
    m_Maze = new Maze("data/level2.level");

    // créer les objets à dessiner
    // m_Cube = new Cube("data/white_noise.wav");
    // m_Cube->setPosition(vec3::fromValues(0.0, -0.5, -10.0));

    // Renderer wall
    for (unsigned int z = 0; z < m_Maze->GetHeight(); z++)
    {
        for (unsigned int y = 0; y < m_Maze->GetWidth(); y++)
        {
            for (unsigned int x = 0; x < m_Maze->GetLength(); x++)
            {
                // Check all sides
                if (m_Maze->GetCell(x, y, z) & WALL_NORTH) {
                    m_Walls.push_back(new Wall("data/white_noise.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0, 0, y * 5.0 - 2.5));
                    m_Walls.back()->setType(WALL_NORTH);
                }

                if (m_Maze->GetCell(x, y, z) & WALL_SOUTH) {
                    m_Walls.push_back(new Wall("data/white_noise.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0, 0, y * 5.0 + 2.5));
                    m_Walls.back()->setType(WALL_SOUTH);
                }

                if (m_Maze->GetCell(x, y, z) & WALL_EAST) {
                    m_Walls.push_back(new Wall("data/white_noise.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0 + 2.5, 0, y * 5.0));
                    m_Walls.back()->setType(WALL_EAST);
                }

                if (m_Maze->GetCell(x, y, z) & WALL_WEST) {
                    m_Walls.push_back(new Wall("data/white_noise.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0 - 2.5, 0, y * 5.0));
                    m_Walls.back()->setType(WALL_WEST);
                }
            }
        }
    }

    m_Duck = new Duck();
    m_Ground = new Ground();

    // caractéristiques de la lampe
    m_Light = new Light();
    m_Light->setColor(500.0, 500.0, 500.0);
    m_Light->setPosition(0.0,  16.0,  13.0, 1.0);
    m_Light->setDirection(0.0, -1.0, -1.0, 0.0);
    m_Light->setAngles(30.0, 40.0);

    // couleur du fond : gris foncé
    glClearColor(0.4, 0.4, 0.4, 0.0);

    // activer le depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // activer la suppression des faces cachées
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // initialiser les matrices
    m_MatP = mat4::create();
    m_MatV = mat4::create();
    m_MatR = mat4::create();
    m_MatVM = mat4::create();

    m_Azimut    = 90.0f;
    m_Elevation = 90.0f;
    m_Distance  = 40.0f;
    // m_InvPosCam = vec3::fromValues(-8.0f, -2.0f, -11.0f);
    m_InvPosCam = vec3::fromValues(0.0f, 0.0f, 0.0f);

    m_Vy = 0.0f;
    m_PredTime = 0.0f;
    m_Clicked   = false;
}


/**
 * appelée quand la taille de la vue OpenGL change
 * @param width : largeur en nombre de pixels de la fenêtre
 * @param height : hauteur en nombre de pixels de la fenêtre
 */
void Scene::onSurfaceChanged(int width, int height)
{
    // met en place le viewport
    glViewport(0, 0, width, height);

    // matrice de projection (champ de vision)
    mat4::perspective(m_MatP, Utils::radians(25.0), (float)width / height, 0.1, 100.0);
}


/**
 * appelée quand on enfonce un bouton de la souris
 * @param btn : GLFW_MOUSE_BUTTON_LEFT pour le bouton gauche
 * @param x coordonnée horizontale relative à la fenêtre
 * @param y coordonnée verticale relative à la fenêtre
 */
void Scene::onMouseDown(int btn, double x, double y)
{
    if (btn != GLFW_MOUSE_BUTTON_LEFT) return;
    m_Clicked = true;
    m_MousePrecX = x;
    m_MousePrecY = y;
}


/**
 * appelée quand on relache un bouton de la souris
 * @param btn : GLFW_MOUSE_BUTTON_LEFT pour le bouton gauche
 * @param x coordonnée horizontale relative à la fenêtre
 * @param y coordonnée verticale relative à la fenêtre
 */
void Scene::onMouseUp(int btn, double x, double y)
{
    m_Clicked = false;
}


/**
 * appelée quand on bouge la souris
 * @param x coordonnée horizontale relative à la fenêtre
 * @param y coordonnée verticale relative à la fenêtre
 */
void Scene::onMouseMove(double x, double y)
{
    if (! m_Clicked) return;
    m_Azimut  += (x - m_MousePrecX) * 0.1;
    m_Elevation += (y - m_MousePrecY) * 0.1;
    if (m_Elevation >  90.0) m_Elevation =  90.0;
    if (m_Elevation < -40.0) m_Elevation = -40.0;
    m_MousePrecX = x;
    m_MousePrecY = y;
}


/**
 * appelée quand on appuie sur une touche du clavier
 * @param code : touche enfoncée
 */
void Scene::onKeyDown(unsigned char code)
{
    const float step = 0.1f;
    vec3 mvt = vec3::create();

    switch (code) {
        case GLFW_KEY_W: // avant
            mvt = vec3::fromValues(0.0f, 0.0f, +step);
            break;

        case GLFW_KEY_S: // avant
            mvt = vec3::fromValues(0.0f, 0.0f, -step);
            break;

        case GLFW_KEY_A: // droite
            mvt = vec3::fromValues(+step, 0.0f, 0.0f);
            break;

        case GLFW_KEY_D: // gauche
            mvt = vec3::fromValues(-step, 0.0f, 0.0f);
            break;
        // case GLFW_KEY_Q: // haut
        //     vec3::transformMat4(offset, vec3::fromValues(0, -0.1, 0), m_MatTMP);
        //     break;
        // case GLFW_KEY_Z: // bas
        //     vec3::transformMat4(offset, vec3::fromValues(0, +0.1, 0), m_MatTMP);
        //     break;
        default:
            return;
    }

    mat4::identity(m_MatR);
    mat4::rotateY(m_MatR, m_MatR, Utils::radians(-m_Azimut));
    mat4::rotateX(m_MatR, m_MatR, Utils::radians(-m_Elevation));
    vec3::transformMat4(mvt, mvt, m_MatR);
    vec3::add(m_InvPosCam, m_InvPosCam, mvt);

    m_InvPosCam[1] = Utils::clamp(m_InvPosCam[1], -9.0, 0.0);
}


/**
 * Dessine l'image courante
 */
void Scene::onDrawFrame()
{
    // Calcul vitesse saut
    float dt = Utils::Time - m_PredTime;
    m_Vy -= 9.81 * dt;
    m_InvPosCam[1] -= m_Vy * dt;
    m_InvPosCam[1] = Utils::clamp(m_InvPosCam[1], -16.0, -2.0);
    m_PredTime = Utils::Time;

    // orienter et positionner la caméra
    mat4::identity(m_MatV);
    mat4::rotateX(m_MatV, m_MatV, Utils::radians(m_Elevation));
    mat4::rotateY(m_MatV, m_MatV, Utils::radians(m_Azimut));
    mat4::translate(m_MatV, m_MatV, m_InvPosCam);

    /** gestion des lampes **/

    // calculer la position et la direction de la lampe par rapport à la scène
    m_Light->transform(m_MatV);

    // fournir position et direction en coordonnées caméra aux objets éclairés
    m_Ground->setLight(m_Light);
    // m_Duck->setLight(m_Light);


    /** dessin de l'image **/

    // effacer l'écran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // dessiner le sol
    m_Ground->onDraw(m_MatP, m_MatV);

    // m_Cube->onRender(m_MatP, m_MatV);
    // Render all walls
    for (int i = 0; i < m_Walls.size(); i++) {
        // mat4::translate(m_MatVM, m_MatV, m_Walls[i]->getPosition());
        m_Walls[i]->onRender(m_MatP, m_MatV);
    }

    // dessiner le canard en mouvement
    m_Duck->onRender(m_MatP, m_MatV);

}


/** supprime tous les objets de cette scène */
Scene::~Scene()
{
    // delete m_Cube;
    // delete m_Duck;
    delete m_Ground;
}

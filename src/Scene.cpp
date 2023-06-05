#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <utils.h>

#include<unistd.h>
#include <chrono>
#include <thread>


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
                    m_Walls.push_back(new Wall("data/wall.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0, 0, y * 5.0 - 2.5));
                    m_Walls.back()->setType(WALL_NORTH);
                }

                if (m_Maze->GetCell(x, y, z) & WALL_SOUTH) {
                    m_Walls.push_back(new Wall("data/wall.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0, 0, y * 5.0 + 2.5));
                    m_Walls.back()->setType(WALL_SOUTH);
                }

                if (m_Maze->GetCell(x, y, z) & WALL_EAST) {
                    m_Walls.push_back(new Wall("data/wall.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0 + 2.5, 0, y * 5.0));
                    m_Walls.back()->setType(WALL_EAST);
                }

                if (m_Maze->GetCell(x, y, z) & WALL_WEST) {
                    m_Walls.push_back(new Wall("data/wall.wav"));
                    m_Walls.back()->setPosition(vec3::fromValues(x * 5.0 - 2.5, 0, y * 5.0));
                    m_Walls.back()->setType(WALL_WEST);
                }
            }
        }
    }

    //m_Duck = new Duck();
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

        case GLFW_KEY_Q: // check walls
            std::cout << "Check walls \n";
            this->CheckWall(0.2);
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

    // check collision
    // we check collision with every wall
    // TODO: performance issue: check collision only with walls near the camera

    const float depth = 0.05;
    const float width = 2.5;
    const float height = 2.0;

    for (Wall* wall : m_Walls) {

        vec3 wall_position = wall->getPosition();
        float x1, x2, y1, y2;

        // check collision with the wall (we don't check height)
        switch (wall->getType()) {
            case WALL_NORTH:
                x1 = -wall_position[0] - width;
                x2 = -wall_position[0] + width;
                y1 = -wall_position[2] - depth * 10;
                y2 = -wall_position[2] + depth * 10;
                break;
            case WALL_SOUTH:
                x1 = -wall_position[0] - width;
                x2 = -wall_position[0] + width;
                y1 = -wall_position[2] - depth * 10;
                y2 = -wall_position[2] + depth * 10;
                break;
            case WALL_EAST:
                x1 = -wall_position[0] - depth * 10;
                x2 = -wall_position[0] + depth * 10;
                y1 = -wall_position[2] - width;
                y2 = -wall_position[2] + width;
                break;
            case WALL_WEST:
                x1 = -wall_position[0] - depth * 10;
                x2 = -wall_position[0] + depth * 10;
                y1 = -wall_position[2] - width;
                y2 = -wall_position[2] + width;
                break;
        }
        
            //std::cout << "Player position: " << m_InvPosCam[0] << " " << m_InvPosCam[1] << " " << m_InvPosCam[2] << std::endl;
            // Print x1, x2, y1, y2
            //std::cout << "x1: " << x1 << " x2: " << x2 << " y1: " << y1 << " y2: " << y2 << std::endl;

        if (m_InvPosCam[0] > x1 && m_InvPosCam[0] < x2 && m_InvPosCam[2] > y1 && m_InvPosCam[2] < y2) {
            //std::cout << "Collision with wall" << std::endl;
            vec3::subtract(m_InvPosCam, m_InvPosCam, mvt);
        }
    }
    //this->get_wall_distance(0.5);

}

void Scene::CheckWall(float limit){
    for (int j = 0; j < m_Walls.size(); j++){
        vec3 position = m_Walls[j]->getPosition();
        for(unsigned int i = 0; i <3; i+=2){
            float differenceMoins = std::abs(position[i] - m_InvPosCam[i]);
            float differencePlus = std::abs(position[i] + m_InvPosCam[i]);


            if ((differenceMoins<limit)||(differencePlus<limit)){
                std::cout << differenceMoins << "m \n";
                std::cout << differencePlus << "m \n";
                //this->PlaySound(position[0],position[1],0);
                this->PlaySound(-1,0,0);
                std::cout << position[0] << position[1] << position[2] << "\n";
                //std::cout << "Mur proche \n";
            }
        }
    }
}

void Scene::PlaySound(float value1, float value2, float value3){

    std::chrono::steady_clock::time_point lastSoundTime;
    int soundDelay = 1000; // 1 second

    // Check if enough time has passed since the last sound
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSoundTime);
    if (timeDifference.count() < soundDelay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(soundDelay - timeDifference.count()));
    }


    // Update the last sound time to the current time
    lastSoundTime = std::chrono::steady_clock::now();

    // ouverture du flux audio à placer dans le buffer
    std::string soundpathname = "data/wall.wav";
    buffer = alutCreateBufferFromFile(soundpathname.c_str());
    if (buffer == AL_NONE) {
        std::cerr << "unable to open file " << soundpathname << std::endl;
        alGetError();
        throw std::runtime_error("file not found or not readable");
    }

    // lien buffer -> source
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    // propriétés de la source à l'origine
    alSource3f(source, AL_POSITION, value1, value1, value1); // on positionne la source sur la position du mur
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    // dans un cone d'angle [-inner/2,inner/2] il n'y a pas d'attenuation
    alSourcef(source, AL_CONE_INNER_ANGLE, 80);
    // dans un cone d'angle [-outer/2,outer/2] il y a une attenuation linéaire entre 0 et le gain
    alSourcef(source, AL_CONE_OUTER_GAIN, 0);
    alSourcef(source, AL_CONE_OUTER_ANGLE, 120);
    // à l'extérieur de [-outer/2,outer/2] il y a une attenuation totale

    float listenerOrientation[6] = { -1.0f, 0.0f, 0.0f,  // Listener's forward direction
                                     0.0f, 1.0f, 0.0f }; // Listener's up direction

    alListenerfv(AL_ORIENTATION, listenerOrientation);

    ALint sourceState;
    alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
    if (sourceState != AL_PLAYING){
        alSourcePlay(source);
        std::cout << "Joue son \n";
    }


    if (sourceState == AL_STOPPED){
        // Delete the source and buffer after the sound has finished playing
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
        std::cout << "Delete source \n";
    }


}


void Scene::get_wall_distance(float limit){

    for (int j = 0; j < m_Walls.size(); j++){
        vec3 position = m_Walls[j]->getPosition();
        for(unsigned int i = 0; i <3; i+=2){
            float differenceMoins = std::abs(position[i] - m_InvPosCam[i]);
            //std::cout << differenceMoins << "m \n";
            float differencePlus = std::abs(position[i] + m_InvPosCam[i]);
            //std::cout << differencePlus << "m \n";

            if ((differenceMoins<limit)||(differencePlus<limit)){
                this->PlaySound(position[0],position[1],position[2]);
                //std::cout << "Mur proche \n";
            }
        }
    }
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
    //m_Duck->onRender(m_MatP, m_MatV);

}


/** supprime tous les objets de cette scène */
Scene::~Scene()
{
    // delete m_Cube;
    // delete m_Duck;
    delete m_Ground;

}

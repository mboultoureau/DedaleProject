#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <utils.h>

#include <Wall.h>
#include <Material.h>

using namespace mesh;

/** matériau pour le mur **/
class MaterialWall: public Material
{
public:

    MaterialWall() : Material("MatWall")
    {
        // vertex shader
        std::string srcVertexShader =
                "#version 300 es\n"
                "uniform mat4 matP;\n"
                "uniform mat4 matVM;\n"
                "in vec3 glVertex;\n"
                "in vec3 glColor;\n"
                "out vec3 frgColor;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = matP * matVM * vec4(glVertex, 1.0);\n"
                "    frgColor = glColor;\n"
                "}";

        // fragment shader
        std::string srcFragmentShader =
                "#version 300 es\n"
                "precision mediump float;\n"
                "in vec3 frgColor;\n"
                "out vec4 glFragColor;\n"
                "void main()\n"
                "{\n"
                "    glFragColor = vec4(frgColor, 1.0);\n"
                "}";

        setShaders(srcVertexShader, srcFragmentShader);
    }
};





/** constructeur */
Wall::Wall(std::string soundpathname): Mesh("wall")
{
    // matériau
    m_Material = new MaterialWall();
    setMaterials(m_Material);

    // maillage
    const float depth = 0.05;
    const float width = 2.5;
    const float height = 2.0;

    // sommets
    /*
          p3  ____    p0
        p2  /|___/| p1
         p7 |/___|/   p4
        p6          p5
    */
    Vertex* P0 = new Vertex(this, +width, +height, +depth);
    Vertex* P1 = new Vertex(this, +width, +height, -depth);
    Vertex* P2 = new Vertex(this, -width, +height, -depth);
    Vertex* P3 = new Vertex(this, -width, +height, +depth);
    Vertex* P4 = new Vertex(this, +width, -height, +depth);
    Vertex* P5 = new Vertex(this, +width, -height, -depth);
    Vertex* P6 = new Vertex(this, -width, -height, -depth);
    Vertex* P7 = new Vertex(this, -width, -height, +depth);

    // couleurs
    P0->setColor(0.0, 0.5, 1.0);  // P0 bleu
    P1->setColor(1.0, 0.5, 0.0);  // P1 orange
    P2->setColor(0.0, 0.7, 0.0);  // P2 vert foncé
    P3->setColor(0.7, 0.0, 0.7);  // P3 violet
    P4->setColor(0.0, 1.0, 1.0);  // P4 cyan
    P5->setColor(0.5, 1.0, 0.0);  // P7 vert clair
    P6->setColor(0.5, 0.0, 0.5);  // P5 magenta
    P7->setColor(1.0, 1.0, 0.0);  // P6 jaune

    // quads
    addQuad(P1,P0,P3,P2);
    addQuad(P4,P5,P6,P7);
    addQuad(P5,P4,P0,P1);
    addQuad(P4,P7,P3,P0);
    addQuad(P7,P6,P2,P3);
    addQuad(P6,P5,P1,P2);


}


/**
     * dessiner le mur
     * @param matP : matrice de projection
     * @param matMV : matrice view*model (caméra * position objet)
 */
void Wall::onRender(const mat4& matP, const mat4& matV)
{
    /** dessin OpenGL **/

    // calculer la matrice MV pour les shaders
    mat4 matVM = mat4::create();
    mat4::translate(matVM, matV, m_Position);
    
    // applique une rotation selon le type de mur
    switch (m_Type) {
        case WALL_NORTH:
            mat4::rotateY(matVM, matVM, Utils::radians(0));
            break;
        case WALL_EAST:
            mat4::rotateY(matVM, matVM, Utils::radians(90));
            break;
        case WALL_SOUTH:
            mat4::rotateY(matVM, matVM, Utils::radians(180));
            break;
        case WALL_WEST:
            mat4::rotateY(matVM, matVM, Utils::radians(270));
            break;
    }

    onDraw(matP, matVM);


}



vec3& Wall::getPosition()
{
    return m_Position;
}

void Wall::setPosition(vec3 pos)
{
    vec3::copy(m_Position, pos);
}

WALL_TYPE Wall::getType()
{
    return m_Type;
}

void Wall::setType(WALL_TYPE type)
{
    m_Type = type;
}


/** destructeur */
Wall::~Wall()
{
    // libération du matériau
    delete m_Material;

    // libération des ressources openal
    // alDeleteSources(1, &source);
    // alDeleteBuffers(1, &buffer);
}

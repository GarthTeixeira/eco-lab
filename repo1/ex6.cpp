#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/io.hpp>

#include <vector>
#include <iostream>
#include <map>
#include <math.h>

// Instale as seguintes bibliotecas:
//sudo apt-get install cmake build-essential libgl1-mesa-dev freeglut3 libglm-dev

// Para compilar execute no terminal:
// g++ -o Transformacao exemplo_transformacao.cpp -lglut -lGLU -lGL -lm

std::vector<glm::vec3> cube;


void keyboard(unsigned char key, int x , int y);



GLfloat horientacao[3] = {0.0,0.0,1.0};

GLfloat offset = 0.01;

GLfloat distanciaCamera = 50.0;

GLfloat distanciaCentroide = 3.0;

GLfloat posicaoAtual[3] = {50.0f,50.0f,50.0f} ;


std::map<char,std::vector<GLfloat>> first;

std::vector<std::vector<GLfloat>> posicoes = {
    {10.0f, 6.0f, 3.0f + distanciaCamera}, // Vista frontal
    {10.0f, 6.0f, 3.0f - distanciaCamera}, // Vista traseira
    {10.0f+ distanciaCamera, 6.0f, 3.0f}, // Vista direita
    {10.0f- distanciaCamera, 6.0f, 3.0f}, // Vista esquerda
    {10.0f,6.0f-distanciaCamera,3.0f}, //Vista de baixo
    {10.0f,6.0f+distanciaCamera,3.0f} //Vista de cima

};

void teclas_faces(){
   
    first['q'] = posicoes[0];
    first['w'] = posicoes[1];
    first['e'] = posicoes[2];
    first['r'] = posicoes[3];
    first['t'] = posicoes[4];
    first['y'] = posicoes[5];
    
}

void pontos_cubo()
{
	// Face frontal
    cube.push_back(glm::vec3(10.0f - distanciaCentroide, 6.0f - distanciaCentroide, 3.0f + distanciaCentroide)); // Vértice 0
    cube.push_back(glm::vec3(10.0f + distanciaCentroide, 6.0f - distanciaCentroide, 3.0f + distanciaCentroide)); // Vértice 1
    cube.push_back(glm::vec3(10.0f + distanciaCentroide, 6.0f + distanciaCentroide, 3.0f + distanciaCentroide)); // Vértice 2
    cube.push_back(glm::vec3(10.0f - distanciaCentroide, 6.0f + distanciaCentroide, 3.0f + distanciaCentroide)); // Vértice 3

    // Face traseira
    cube.push_back(glm::vec3(10.0f - distanciaCentroide, 6.0f - distanciaCentroide, 3.0f - distanciaCentroide)); // Vértice 4
    cube.push_back(glm::vec3(10.0f + distanciaCentroide, 6.0f - distanciaCentroide, 3.0f - distanciaCentroide)); // Vértice 5
    cube.push_back(glm::vec3(10.0f + distanciaCentroide, 6.0f + distanciaCentroide, 3.0f - distanciaCentroide)); // Vértice 6
    cube.push_back(glm::vec3(10.0f - distanciaCentroide, 6.0f + distanciaCentroide, 3.0f - distanciaCentroide)); // Vértice 7
}

std::vector<glm::vec4> transformacao(std::vector<glm::vec4> cube_in)
{
	std::cout << "Initial points: \n";	
	for(int i=0;i<cube.size();i++)
		std::cout << cube_in[i] << "\n";
	
	glm::mat4 T = glm::translate( glm::mat4( 1.0f ), glm::vec3( -1.0f, -1.0f,1.0f ) );
		
	std::cout << "Matrix: \n " << T << "\n";
	
	std::vector<glm::vec4> cube_out;
	
	for(int i=0;i<cube.size();i++)
	{
		glm::vec4 point = T * cube_in[i];
		cube_out.push_back(point);
	}
	
	std::cout << "Final points: \n";
	for(int i=0;i<cube.size();i++)
		std::cout << cube_out[i] << "\n";
	
	return cube_out;

}

void referencia()
{
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);
    glEnd();

}

void draw_cubo(std::vector<glm::vec3> cube_in)
{
    
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);
    glVertex3f(cube_in[3].x,cube_in[3].y,cube_in[3].z);
    glEnd();
    
    
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[5].x,cube_in[5].y,cube_in[5].z);
    glVertex3f(cube_in[4].x,cube_in[4].y,cube_in[4].z);
    glEnd();
    
    
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(cube_in[4].x,cube_in[4].y,cube_in[4].z);
    glVertex3f(cube_in[5].x,cube_in[5].y,cube_in[5].z);
    glVertex3f(cube_in[6].x,cube_in[6].y,cube_in[6].z);
    glVertex3f(cube_in[7].x,cube_in[7].y,cube_in[7].z);
    glEnd();
    
    
    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[3].x,cube_in[3].y,cube_in[3].z);
    glVertex3f(cube_in[7].x,cube_in[7].y,cube_in[7].z);
    glVertex3f(cube_in[4].x,cube_in[4].y,cube_in[4].z);
    glEnd();
    
    
     glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(cube_in[3].x,cube_in[3].y,cube_in[3].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);
    glVertex3f(cube_in[6].x,cube_in[6].y,cube_in[6].z);
    glVertex3f(cube_in[7].x,cube_in[7].y,cube_in[7].z);
    glEnd();
    
    
    
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);
    glVertex3f(cube_in[6].x,cube_in[6].y,cube_in[6].z);
    glVertex3f(cube_in[5].x,cube_in[5].y,cube_in[5].z);
    glEnd();
    
   
}


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(10, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), 0.5, 500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(posicaoAtual[0] ,posicaoAtual[1] - offset , posicaoAtual[2] - offset, 10.0f, 6.0f, 3.0f, 0.0, 0.0, 1.0);


    referencia();
    draw_cubo(cube);
    glutPostRedisplay();
    glutSwapBuffers();
    glutKeyboardFunc(keyboard);
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
   
}

// Programa Principal
int main(int argc, char **argv)
{

    pontos_cubo();
    teclas_faces();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Display);
    //glutReshapeFunc(AlteraTamanhoJanela);
    //glutMouseFunc(GerenciaMouse);
    Inicializa();
    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y){

    std::cout << key << std::endl;

    if(first.find(key) == first.end()){
        std::cout<<"not found"<<std::endl;
        posicaoAtual[0] = 50.0;
        posicaoAtual[1] = 50.0;
        posicaoAtual[2] = 50.0;
        horientacao[0] = 0.0;
        horientacao[1] = 0.0;
        horientacao[2] = 1.0;
        return;
    }

    posicaoAtual[0] = first[key][0];
    posicaoAtual[1] = first[key][1];
    posicaoAtual[2] = first[key][2];

   


    glutPostRedisplay();
}
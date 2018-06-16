#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>

// Variavel global que define o incremento
double increment = 2.1180;

// Variavel global que define a escala
double zoom = 1;

// Variaveis globais que definem os angulos de rotacao nos eixos x, y e z
double angle_x = 0;
double angle_y = 0;
double angle_z = 0;

// Numero de iteracoes (profundidade)
int N = 1;

double pot3[6];

void init() {
	
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Fractal");

	glClearColor(1, 1, 1, 0);
}

void keyPressEvent(GLubyte key, GLint x, GLint y) {

	if (key == 27)
		exit(0); // Sai do programa se apertar ESC

	if (key == 'q') angle_x += increment; // Rotaciona em x no sentido anti horario
	else if(key == 'a') angle_x -= increment; // Rotaciona em x no sentido horario
	else if(key == 'w') angle_y += increment; // Rotaciona em y no sentido anti horario
	else if(key == 's') angle_y -= increment; // Rotaciona em y no sentido horario
	else if(key == 'e') angle_z += increment; // Rotaciona em z no sentido anti horario
	else if(key == 'd') angle_z -= increment; // Rotaciona em z no sentido horario

	if(key == '0') N = 0;
	else if(key == '1')	N = 1;
	else if(key == '2')	N = 2;
	else if(key == '3')	N = 3;
	else if(key == '4')	N = 4;

	if (key == '+') {
		zoom += 0.1; // Aumenta a escala
		if (zoom > 4) zoom = 4; // valor maximo de escala		
	}
	else if(key == '-') {
		zoom -= 0.1; // Diminui a escala
		if(zoom < 0.1) zoom = 0.1; // valor minimo de escala
	}

	glutPostRedisplay();
}

void drawFractal(int n, double x, double y, double z) {
	if (n > N) {
		// desenha o cubo pequeno
		glPushMatrix();
		glTranslatef(x, y, z);

		glutSolidCube(1.0/(pot3[N]));

		glPopMatrix();
		return;
	}

	for(int _x = -1; _x <= 1; ++_x)
		for(int _y = -1; _y <= 1; ++_y)
			for(int _z = -1; _z <= 1; ++_z)
				if(_x*_x + _y*_y + _z*_z > 1)
					drawFractal(n+1, x + _x/(pot3[n]), y + _y/(pot3[n]), z + _z/(pot3[n]));
}

void drawFractal() {
	drawFractal(1, 0, 0, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Seta a projecao
	glMatrixMode(GL_PROJECTION); // Define que ira trabalhar com a matriz de projecao
	glLoadIdentity(); // Carrega a matriz identidade

	glOrtho(-5, 5, -5, 5, -5, 5);

	// Define as configuracoes do observador
	gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	// Define que ira trabalhar com a matriz de modelo/visao
	glMatrixMode(GL_MODELVIEW);

	// Carrega a matriz identidade
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);


	// Rotaciona o objeto
	glRotatef(angle_x, 1, 0, 0);
	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_z, 0, 0, 1);

	// Escala o objeto
	glScalef(zoom, zoom, zoom);
	
	drawFractal();

	glutSwapBuffers();
}



int main(int argc, char * argv[]) {
	pot3[0] = 1;
	for(int i = 1; i <= 4; ++i) pot3[i] = pot3[i-1] * 3;


	printf("COMANDOS\n");
	printf("========\n");
	printf("\tROTACAO\n");
	printf("\t\t(q) --> sentido anti horario no eixo x\n");
	printf("\t\t(a) --> sentido horario no eixo x\n");
	printf("\t\t(w) --> sentido anti horario no eixo y\n");
	printf("\t\t(s) --> sentido horario no eixo y\n");
	printf("\t\t(e) --> sentido anti horario no eixo z\n");
	printf("\t\t(d) --> sentido horario no eixo z\n");
	printf("\tZOOM\n");
	printf("\t\t(+) (shift + =) --> aumenta a escala\n");
	printf("\t\t(-) --> diminui a escala\n");

	printf("Pressione ENTER para continuar\n");
	scanf("%*c");

	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressEvent);

	printf("Pressione ESC para sair\n");

	glutMainLoop();
}
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

# Variavel global que define o incremento
increment = 2.1180
# Variavel global que define a escala
zoom = 1
# Variaveis globais que definem os angulos de rotacao nos eixos x, y e z
angle_x = 0
angle_y = 0
angle_z = 0
# Variaveis globais que definem as posicoes de translacao nos eixos x, y e z
N = 1

def init():
	glutInit()
	glutInitDisplayMode(GLUT_DOUBLE)
	glutInitWindowSize(700, 700)
	glutCreateWindow("Fractal")

	glClearColor(1, 1, 1, 0)

def _drawFractal(n, x, y, z):
	global angle_x, angle_y, angle_z, zoom
	if n > N:
		# desenha o cubo pequeno
		glPushMatrix()
		glTranslatef(x, y, z)

		# Rotaciona o objeto
		glRotatef(angle_x, 1, 0, 0)
		glRotatef(angle_y, 0, 1, 0)
		glRotatef(angle_z, 0, 0, 1)

		# Escala o objeto
		glScalef(zoom, zoom, zoom)

		glutSolidCube(1.0/(3**N))
		
		glPopMatrix()
		return

	for _x in range(-1, 2):
		for _y in range(-1, 2):
			for _z in range(-1, 2):
				if(_x**2 + _y**2 + _z**2 > 1):
					_drawFractal(n+1, x + _x/3, y + _y/3, z + _z/3);



def drawFractal():
	_drawFractal(1, 0, 0, 0)
	
# Funcao para capturar os eventos do teclado
def keyPressEvent(key, x, y) :
	global angle_x, angle_y, angle_z, increment, zoom, N

	if key == '\x1b':
		exit(0) # Sai do programa se apertar ESC
	
	if (key == 'q'):
		angle_x += increment # Rotaciona em x no sentido anti horario
	elif (key == 'a'):
		angle_x -= increment # Rotaciona em x no sentido horario
	elif (key == 'w'):
		angle_y += increment # Rotaciona em y no sentido anti horario
	elif (key == 's'):
		angle_y -= increment # Rotaciona em y no sentido horario
	elif (key == 'e'):
		angle_z += increment # Rotaciona em z no sentido anti horario
	elif (key == 'd'):
		angle_z -= increment # Rotaciona em z no sentido horario
	else: 
		pass

	if key == '0':
		N = 0
	elif key == '1':
		N = 1
	elif key == '2':
		N = 2
	elif key == '3':
		N = 3
	elif key == '4':
		N = 4
	elif key == '5':
		N = 5
	else:
		pass

	print(key)
	if (key == 'b\'+\''):
		zoom += 0.1 # Aumenta a escala
		if (zoom > 4):
			zoom = 10 # valor maximo de escala		
	elif (key == 'b\'-\''):
		zoom -= 0.1 # Diminui a escala
		if (zoom < 0.1):
			zoom = 0.1 # valor minimo de escala
	else:
		pass

	display()


def display():

	# Seta a projecao
	glMatrixMode(GL_PROJECTION) # Define que ira trabalhar com a matriz de projecao
	glLoadIdentity() # Carrega a matriz identidade

	glOrtho(-20, 20, -20, 20, -200, 200)


	# Define as configuracoes do observador
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0)

	glClear(GL_COLOR_BUFFER_BIT)

	# Define que ira trabalhar com a matriz de modelo/visao
	glMatrixMode(GL_MODELVIEW)

	# Carrega a matriz identidade
	glLoadIdentity()
	glColor3f(0.0, 0.0, 0.0)

	drawFractal()

	# glutSolidCube(10.0) # Desenha um cubo de arame na cor verde


	glutSwapBuffers() #atualizar a tela


print("COMANDOS")
print("========\n")
print("\tROTACAO")
print("\t\t(q) --> sentido anti horario no eixo x")
print("\t\t(a) --> sentido horario no eixo x")
print("\t\t(w) --> sentido anti horario no eixo y")
print("\t\t(s) --> sentido horario no eixo y")
print("\t\t(e) --> sentido anti horario no eixo z")
print("\t\t(d) --> sentido horario no eixo z\n")
print("\tZOOM")
print("\t\t(+) (shift + =) --> aumenta a escala")
print("\t\t(-) --> diminui a escala\n")


input("Pressione ENTER para continuar")

init()
glutDisplayFunc(display)
glutKeyboardFunc(keyPressEvent)

print("Pressione ESC para sair")

glutMainLoop()

#include<Iostream>
#include<gl/freeglut.h>
#include<gl/freeglut_std.h>
#include<windows.h>
#include<ctime>
using namespace std;
#define _1080p_ 1920,1080
#define _720p_ 1280,720
#define _480p_ 720,480
float x = 3.141 / 2;
int NumCheck = 0;  //Sort-algorithm calls
int mode;  //Program mode to choose algorithm
//Dimension of orthogonal box dim = 2
class NodeBlock
{
public:
	NodeBlock(double mag)
	{
		magnitude = mag;
		//offset = x;
	}
	double getMag()
	{
		return magnitude;
	}
	void setMag(double mag)
	{
		magnitude = mag;
	}

private:
	double magnitude;
	//	int offset;
};

class NodeStack
{

public:
	NodeStack()
	{
		isSorted = false;
		//yoursort = bsort;
		bSize = 250;
		NB = new NodeBlock*[bSize];
		for (int i = 0; i < bSize; i++)
		{
			NB[i] = new NodeBlock( (rand()%(i+1))* 5); // cant mod 0
		}
	}


	void printStack()
	{
	#define floor 1  //normal value to calculate the bottem of screen
	#define offset i/125.0 //displacement per node
	#define gap 1/150.0  //Crevis between two nodes
		for (int i = 0; i < bSize; i++)
		{
			double mag;
			mag = NB[i]->getMag();
			glBegin(GL_QUAD_STRIP);
			glColor3f(125/mag,1, 1370/mag);
			glVertex2d(offset    -1,	           0-floor);
			glVertex2d(offset+gap-1,    		   0-floor);
			glVertex2d(offset    -1,		 mag/500-floor);
			glVertex2d(offset+gap-1,		 mag/500-floor);
			glEnd();
		}
	}
	void bsort() // elementry bubblesort
	{
		double temp;

		for (int i = 1; i < bSize && !isSorted; i++){
			if(NB[i]->getMag() < NB[i-1]->getMag()){

				temp = NB[i]->getMag();
		        NB[i]->setMag(NB[i - 1]->getMag());
				NB[i - 1]->setMag(temp);
				//isSorted = false;
			}
			NumCheck++;
	}	


		Beep(NB[5]->getMag() * 10, 100);
		cout << "This algorithm took " << NumCheck << " tries\n";
	}

	void Bouncy_bsort() // A Hybrid bouncing bubble sort: carrys data forward then back
	{
		double temp;
		int i = 1;
		for (; i < bSize && !isSorted; i++) {
			if (NB[i]->getMag() < NB[i - 1]->getMag()) {

				temp = NB[i]->getMag();
				NB[i]->setMag(NB[i - 1]->getMag());
				NB[i - 1]->setMag(temp);
				//isSorted = false;
			}
			NumCheck++;
		}
		i--;
		Beep(NB[i]->getMag() * 10, 100);
		for (; i > 0 && !isSorted; i--) {
			if (NB[i]->getMag() < NB[i - 1]->getMag()) {

				temp = NB[i]->getMag();
				NB[i]->setMag(NB[i - 1]->getMag());
				NB[i - 1]->setMag(temp);
				//isSorted = false;
			}
			NumCheck++;

		}


		Beep(NB[i]->getMag() * 10, 100);
		cout << "This algorithm took " << NumCheck << " tries\n";
	}
	void W_bsort() // BAD bubblesort
	{
		double temp;

		for (int i = 1, j = 0; i < bSize-j && !isSorted; i++) {
			if (NB[i]->getMag() < NB[i - 1]->getMag()) {

				temp = NB[i]->getMag();
				NB[i]->setMag(NB[i - 1]->getMag());
				NB[i - 1]->setMag(temp);
				j++;
				isSorted = false;
			}
			NumCheck++;
		}


		Beep(NB[5]->getMag() * 10, 100);
			cout << "This algorithm took " << NumCheck << " tries\n";
	}
	void Mysort(void(*sortin)(NodeBlock,NodeBlock)) // inject your sort algorithm here
	{
		//sortin();
	}
	void Shuffle()  //any ideas?
	{}
private:
	NodeBlock** NB;
	 //put your function in this.
	int bSize;
	bool isSorted;

};

NodeStack trius; //global structure of data


//NodeStack trius;
void $Render()
{
#define badzone 25000.0 // value in which the colors change for thet worse

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1, 0, 0, 0); 

	glClearColor((double)(NumCheck) / badzone, (NumCheck > badzone) ? (NumCheck - badzone) / badzone : 0, (NumCheck > badzone + badzone) ? (NumCheck - badzone - badzone) / badzone : 0, 0);
	/* if the algorithm takes too much time
	the screen will progressively get red-er!*/

	trius.printStack(); // the objects are drawn here

	// load matrix identity

	glPopMatrix();
	glFlush(); // dump to monitor
	glutSwapBuffers();


	switch (mode) 
	{
		case 1:
			trius.bsort();  // the objects are sorted here
			break;
		case 2:
			trius.W_bsort();
			break;
		case 3:
			trius.Bouncy_bsort();
			break;
		default:
			system("CLS");
			cout << "Not a valid mode; Pick another mode:\n";
			cout << "1) for Bubblesort\n2) for worse Bubblesort\n3) for Bouncy Bubblesort\n";
			cin >> mode;

	}
}
void keyboardthing(unsigned char keyval, int i, int o)
{
	switch (keyval)
	{
	case 'o':glutFullScreenToggle();
	}
	cout << keyval << i << "  " << o << endl;
}
void reshaper(int _x, int _y)
{
	glViewport(0, 0, _x, _y);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); // what you see
								 //glOrtho()
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void main(int argcp, char** argv)
{
	srand(time(NULL));
	cout << "Pick mode:\n";
	cout << "1) for Bubblesort\n2) for worse Bubblesort\n3) for Bouncy Bubblesort\n";
	cin >> mode;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(_720p_);
	glutInit(&argcp, argv);
	glutCreateWindow("INDUSTRY ORIENTED PROGRAMMING CLUB: ALGORITHM VISUALIZER");

	glutDisplayFunc($Render);
	glutReshapeFunc(reshaper);

	glutIdleFunc($Render);
	//	glutMotionFunc($Render);
	//glutCreateMenu(dosomething);
	glutKeyboardFunc(keyboardthing);

	glutMainLoop();

}


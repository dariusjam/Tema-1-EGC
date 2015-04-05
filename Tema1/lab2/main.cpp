#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#include <time.h>


#define PI 3.14159265358979323846

using namespace std;

void jump();
void isDead();
void fall();
void propulsion();


vector <Object2D*> objects;
vector <Object2D*> triangles;
vector <Object2D*> rectangles;
Visual2D *v2d1, *v2d2;
Rectangle2D *rect,*rect2, *rect3, *rect4, *background[20], *baza[5], *rectg[30];
Polygon2D *triang[40];
Polygon2D *checkpoint[5];
Polygon2D *gura;
Circle2D *eyes[2], *prop;
Text *text, *text2, *text3;
int vieti = 3, steag = 0;

int isPressed = -2;
float pas_joc = 0, pas_om = 0, pas_rot, height1 = 0, height_prev = 0, inc = 5, r;
int i, j;
int lastCheckpoint = 50;
int flags = 0, lives = 3;
bool dead = false, urcare = true, falling = false;
bool pl1 = false, pl2 = false, pl3 = false;


//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0.0f,0.0f,(float)DrawingWindow::width,(float)DrawingWindow::height,0,0,DrawingWindow::width,DrawingWindow::height);  
	addVisual2D(v2d1);
	v2d2 = new Visual2D(0.0f,510.0f,(float)DrawingWindow::width,(float)DrawingWindow::height,0,0,DrawingWindow::width, 90);  
	addVisual2D(v2d2);

	/* Omulet */
	gura = new Polygon2D(Color(0.1f, 0.1f, 1), true);
	gura->addPoint(Point2D(110, 70));
	gura->addPoint(Point2D(120, 57));
	gura->addPoint(Point2D(140, 70));
	addObject2D_to_Visual2D(gura, v2d1);
	eyes[0] = new Circle2D(Point2D(115,85), 6, Color(0.1f,0.1f,1), true);
	eyes[1] = new Circle2D(Point2D(135,85), 6, Color(0.1f,0.1f,1), true);
	addObject2D_to_Visual2D(eyes[0],v2d1);
	addObject2D_to_Visual2D(eyes[1], v2d1);
	rect2 = new Rectangle2D(Point2D(100,50),50,50, Color(0,0,0), false);
	addObject2D_to_Visual2D(rect2, v2d1);
	rect = new Rectangle2D(Point2D(100,50),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rect, v2d1);


	/* Portiunea 1/5 */
	triang[0] = new Polygon2D(Color(0,1,0), true);
	triang[0]->addPoint(Point2D(400, 50));
	triang[0]->addPoint(Point2D(450, 50));
	triang[0]->addPoint(Point2D(425, 90));
	triangles.push_back(triang[0]);
	objects.push_back(triang[0]);
	addObject2D_to_Visual2D(triang[0], v2d1);

	
	triang[1] = new Polygon2D(Color(0,1,0), true);
	triang[1]->addPoint(Point2D(700, 50));
	triang[1]->addPoint(Point2D(750, 50));
	triang[1]->addPoint(Point2D(725, 90));
	triangles.push_back(triang[1]);
	objects.push_back(triang[1]);
	addObject2D_to_Visual2D(triang[1], v2d1);
	
	triang[2] = new Polygon2D(Color(0,1,0), true);
	triang[2]->addPoint(Point2D(750, 50));
	triang[2]->addPoint(Point2D(800, 50));
	triang[2]->addPoint(Point2D(775, 90));
	triangles.push_back(triang[2]);
	objects.push_back(triang[2]);
	addObject2D_to_Visual2D(triang[2], v2d1);

	rectg[0] = new Rectangle2D(Point2D(1150,50),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[0], v2d1);
	objects.push_back(rectg[0]);
	rectangles.push_back(rectg[0]);

	rectg[1] = new Rectangle2D(Point2D(1400,100),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[1], v2d1);
	objects.push_back(rectg[1]);
	rectangles.push_back(rectg[1]);

	rectg[2] = new Rectangle2D(Point2D(1650,150),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[2], v2d1);
	objects.push_back(rectg[2]);
	rectangles.push_back(rectg[2]);

	for(i = 0; i < 10; i++) {
		triang[i+3] = new Polygon2D(Color(0,0,0), true);
		triang[i+3]->addPoint(Point2D(1200+(float)i*50, 50));
		triang[i+3]->addPoint(Point2D(1250+(float)i*50, 50));
		triang[i+3]->addPoint(Point2D(1225+(float)i*50, 90));
		triangles.push_back(triang[i+3]);
		objects.push_back(triang[i+3]);
		addObject2D_to_Visual2D(triang[i+3], v2d1);
	}

	/* Portiunea 2/5 */
	rectg[3] = new Rectangle2D(Point2D(2350,50),200,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[3], v2d1);
	objects.push_back(rectg[3]);
	rectangles.push_back(rectg[3]);

	rectg[4] = new Rectangle2D(Point2D(2550,100),200,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[4], v2d1);
	objects.push_back(rectg[4]);
	rectangles.push_back(rectg[4]);

	rectg[5] = new Rectangle2D(Point2D(2900,150),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[5], v2d1);
	objects.push_back(rectg[5]);
	rectangles.push_back(rectg[5]);

	triang[13] = new Polygon2D(Color(0,1,0), true);
	triang[13]->addPoint(Point2D(2900, 150));
	triang[13]->addPoint(Point2D(2950, 150));
	triang[13]->addPoint(Point2D(2925, 110));
	triangles.push_back(triang[13]);
	objects.push_back(triang[13]);
	addObject2D_to_Visual2D(triang[13], v2d1);

	rectg[6] = new Rectangle2D(Point2D(3050,150),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[6], v2d1);
	objects.push_back(rectg[6]);
	rectangles.push_back(rectg[6]);

	rectg[7] = new Rectangle2D(Point2D(3350,50),50,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[7], v2d1);
	objects.push_back(rectg[7]);
	rectangles.push_back(rectg[7]);

	triang[14] = new Polygon2D(Color(0,1,0), true);
	triang[14]->addPoint(Point2D(3540, 75));
	triang[14]->addPoint(Point2D(3580, 50));
	triang[14]->addPoint(Point2D(3580, 100));
	triangles.push_back(triang[14]);
	objects.push_back(triang[14]);
	addObject2D_to_Visual2D(triang[14], v2d1);

	prop = new Circle2D(Point2D(3375, 120), 10, Color(1,1,0), true);
	objects.push_back(prop);
	addObject2D_to_Visual2D(prop, v2d1);

	triang[16] = new Polygon2D(Color(0,1,0), true);
	triang[16]->addPoint(Point2D(3540, 175));
	triang[16]->addPoint(Point2D(3580, 150));
	triang[16]->addPoint(Point2D(3580, 200));
	triangles.push_back(triang[16]);
	objects.push_back(triang[16]);
	addObject2D_to_Visual2D(triang[16], v2d1);

	triang[17] = new Polygon2D(Color(0,1,0), true);
	triang[17]->addPoint(Point2D(3540, 125));
	triang[17]->addPoint(Point2D(3580, 100));
	triang[17]->addPoint(Point2D(3580, 150));
	triangles.push_back(triang[17]);
	objects.push_back(triang[17]);
	addObject2D_to_Visual2D(triang[17], v2d1);

	rectg[9] = new Rectangle2D(Point2D(3650,50),200,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[9], v2d1);
	objects.push_back(rectg[9]);
	rectangles.push_back(rectg[9]);

	/* Portiunea 3/5 */
	rectg[10] = new Rectangle2D(Point2D(4350,50),200,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[10], v2d1);
	objects.push_back(rectg[10]);
	rectangles.push_back(rectg[10]);

	rectg[10] = new Rectangle2D(Point2D(4550,100),300,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[10], v2d1);
	objects.push_back(rectg[10]);
	rectangles.push_back(rectg[10]);

	triang[15] = new Polygon2D(Color(0,1,0), true);
	triang[15]->addPoint(Point2D(4800, 150));
	triang[15]->addPoint(Point2D(4850, 150));
	triang[15]->addPoint(Point2D(4825, 190));
	triangles.push_back(triang[15]);
	objects.push_back(triang[15]);
	addObject2D_to_Visual2D(triang[15], v2d1);

	rectg[11] = new Rectangle2D(Point2D(4850,50),300,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[11], v2d1);
	objects.push_back(rectg[11]);
	rectangles.push_back(rectg[11]);

	rectg[12] = new Rectangle2D(Point2D(5150,100),250,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[12], v2d1);
	objects.push_back(rectg[12]);
	rectangles.push_back(rectg[12]);

	rectg[13] = new Rectangle2D(Point2D(5550,100),200,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[13], v2d1);
	objects.push_back(rectg[13]);
	rectangles.push_back(rectg[13]);


	triang[18] = new Polygon2D(Color(0,0,0), true);
	triang[18]->addPoint(Point2D(5400, 50));
	triang[18]->addPoint(Point2D(5450, 50));
	triang[18]->addPoint(Point2D(5425, 90));
	triangles.push_back(triang[18]);
	objects.push_back(triang[18]);
	addObject2D_to_Visual2D(triang[18], v2d1);

	triang[19] = new Polygon2D(Color(0,0,0), true);
	triang[19]->addPoint(Point2D(5450, 50));
	triang[19]->addPoint(Point2D(5500, 50));
	triang[19]->addPoint(Point2D(5475, 90));
	triangles.push_back(triang[19]);
	objects.push_back(triang[19]);
	addObject2D_to_Visual2D(triang[19], v2d1);

	triang[20] = new Polygon2D(Color(0,0,0), true);
	triang[20]->addPoint(Point2D(5500, 50));
	triang[20]->addPoint(Point2D(5550, 50));
	triang[20]->addPoint(Point2D(5525, 90));
	triangles.push_back(triang[20]);
	objects.push_back(triang[20]);
	addObject2D_to_Visual2D(triang[20], v2d1);

	/* Portiunea 4/5 */
	triang[21] = new Polygon2D(Color(0,0,0), true);
	triang[21]->addPoint(Point2D(6300, 50));
	triang[21]->addPoint(Point2D(6350, 50));
	triang[21]->addPoint(Point2D(6325, 90));
	triangles.push_back(triang[21]);
	objects.push_back(triang[21]);
	addObject2D_to_Visual2D(triang[21], v2d1);

	rectg[14] = new Rectangle2D(Point2D(6700,50),100,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[14], v2d1);
	objects.push_back(rectg[14]);
	rectangles.push_back(rectg[14]);

	rectg[15] = new Rectangle2D(Point2D(7000,100),100,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[15], v2d1);
	objects.push_back(rectg[15]);
	rectangles.push_back(rectg[15]);

	rectg[16] = new Rectangle2D(Point2D(7400,150),150,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[16], v2d1);
	objects.push_back(rectg[16]);
	rectangles.push_back(rectg[16]);

	for(i = 0; i < 3; i++) {
		triang[i+22] = new Polygon2D(Color(0,0,0), true);
		triang[i+22]->addPoint(Point2D(7400+(float)i*50, 150));
		triang[i+22]->addPoint(Point2D(7450+(float)i*50, 150));
		triang[i+22]->addPoint(Point2D(7425+(float)i*50, 110));
		triangles.push_back(triang[i+22]);
		objects.push_back(triang[i+22]);
		addObject2D_to_Visual2D(triang[i+22], v2d1);
	}

	for(i = 0; i < 3; i++) {
		triang[i+25] = new Polygon2D(Color(0,0,0), true);
		triang[i+25]->addPoint(Point2D(6800+(float)i*50, 50));
		triang[i+25]->addPoint(Point2D(6850+(float)i*50, 50));
		triang[i+25]->addPoint(Point2D(6825+(float)i*50, 90));
		triangles.push_back(triang[i+25]);
		objects.push_back(triang[i+25]);
		addObject2D_to_Visual2D(triang[i+25], v2d1);
	}

	triang[28] = new Polygon2D(Color(0,0,0), true);
	triang[28]->addPoint(Point2D(7750, 50));
	triang[28]->addPoint(Point2D(7800, 50));
	triang[28]->addPoint(Point2D(7775, 90));
	triangles.push_back(triang[28]);
	objects.push_back(triang[28]);
	addObject2D_to_Visual2D(triang[28], v2d1);

	/* Portiunea 5/5 */
	rectg[17] = new Rectangle2D(Point2D(8300,50),700,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[17], v2d1);
	objects.push_back(rectg[17]);
	rectangles.push_back(rectg[17]);

	rectg[18] = new Rectangle2D(Point2D(9200,50),700,50, Color(0.1f,0.7f,0.1f), true);
	addObject2D_to_Visual2D(rectg[18], v2d1);
	objects.push_back(rectg[18]);
	rectangles.push_back(rectg[18]);

	for(i = 0; i < 4; i++) {
		triang[i+29] = new Polygon2D(Color(0,0,0), true);
		triang[i+29]->addPoint(Point2D(9000+(float)i*50, 50));
		triang[i+29]->addPoint(Point2D(9050+(float)i*50, 50));
		triang[i+29]->addPoint(Point2D(9025+(float)i*50, 90));
		triangles.push_back(triang[i+29]);
		objects.push_back(triang[i+29]);
		addObject2D_to_Visual2D(triang[i+29], v2d1);
	}

	srand(time(NULL));
	r = (float)(rand() % 500);
	srand(time(NULL));

	triang[33] = new Polygon2D(Color(0,0,0), true);
	triang[33]->addPoint(Point2D(8300 + r, 100));
	triang[33]->addPoint(Point2D(8350 + r, 100));
	triang[33]->addPoint(Point2D(8325 + r, 140));
	triangles.push_back(triang[33]);
	objects.push_back(triang[33]);
	addObject2D_to_Visual2D(triang[33], v2d1);

	r = (float)(rand() % 300);
	srand(time(NULL));

	triang[35] = new Polygon2D(Color(0,0,0), true);
	triang[35]->addPoint(Point2D(9400 + r, 100));
	triang[35]->addPoint(Point2D(9450 + r, 100));
	triang[35]->addPoint(Point2D(9425 + r, 140));
	triangles.push_back(triang[35]);
	objects.push_back(triang[35]);
	addObject2D_to_Visual2D(triang[35], v2d1);


	/* Checkpoints */
	checkpoint[0] = new Polygon2D(Color(1,1,1), true);
	checkpoint[0]->addPoint(Point2D(2000, 150));
	checkpoint[0]->addPoint(Point2D(2000, 50));
	checkpoint[0]->addPoint(Point2D(2005, 50));
	checkpoint[0]->addPoint(Point2D(2005, 200));
	checkpoint[0]->addPoint(Point2D(1970, 175));
	objects.push_back(checkpoint[0]);
	addObject2D_to_Visual2D(checkpoint[0], v2d1);

	checkpoint[1] = new Polygon2D(Color(1,1,1), true);
	checkpoint[1]->addPoint(Point2D(4000, 150));
	checkpoint[1]->addPoint(Point2D(4000, 50));
	checkpoint[1]->addPoint(Point2D(4005, 50));
	checkpoint[1]->addPoint(Point2D(4005, 200));
	checkpoint[1]->addPoint(Point2D(3970, 175));
	objects.push_back(checkpoint[1]);
	addObject2D_to_Visual2D(checkpoint[1], v2d1);

	checkpoint[2] = new Polygon2D(Color(1,1,1), true);
	checkpoint[2]->addPoint(Point2D(6000, 150));
	checkpoint[2]->addPoint(Point2D(6000, 50));
	checkpoint[2]->addPoint(Point2D(6005, 50));
	checkpoint[2]->addPoint(Point2D(6005, 200));
	checkpoint[2]->addPoint(Point2D(5970, 175));
	objects.push_back(checkpoint[2]);
	addObject2D_to_Visual2D(checkpoint[2], v2d1);

	checkpoint[3] = new Polygon2D(Color(1,1,1), true);
	checkpoint[3]->addPoint(Point2D(8000, 150));
	checkpoint[3]->addPoint(Point2D(8000, 50));
	checkpoint[3]->addPoint(Point2D(8005, 50));
	checkpoint[3]->addPoint(Point2D(8005, 200));
	checkpoint[3]->addPoint(Point2D(7970, 175));
	objects.push_back(checkpoint[3]);
	addObject2D_to_Visual2D(checkpoint[3], v2d1);

	checkpoint[4] = new Polygon2D(Color(1,1,1), true);
	checkpoint[4]->addPoint(Point2D(10000, 150));
	checkpoint[4]->addPoint(Point2D(10000, 50));
	checkpoint[4]->addPoint(Point2D(10005, 50));
	checkpoint[4]->addPoint(Point2D(10005, 200));
	checkpoint[4]->addPoint(Point2D(9970, 175));
	objects.push_back(checkpoint[4]);
	addObject2D_to_Visual2D(checkpoint[4], v2d1);

	/* Background */
	for(i = 0; i < 5; i++) {
		baza[i] = new Rectangle2D(Point2D(0,(float)40-i*10),10000,10, Color(0, 0, 0.1f+0.05f*i), true); 
		addObject2D_to_Visual2D(baza[i], v2d1);
	}

	
	rect3 = new Rectangle2D(Point2D(0,495),1000, 10, Color(0,0,0), true);
	addObject2D_to_Visual2D(rect3, v2d1);

	for(i = 0; i < 20; i++) {
		background[i] = new Rectangle2D(Point2D(0,(float)25*i),(float)DrawingWindow::width*10, (float)(DrawingWindow::height/22), Color(0.3f+0.01f*i, 0.3f-0.01f*i, 0.8f), true);
		addObject2D_to_Visual2D(background[i], v2d1);
	}

	rect4 = new Rectangle2D(Point2D(0,504),1000, 95, Color(1,1,1), true); 
	text = new Text("Dreptunghi",Point2D(10,570),Color(0.5f,0,1),BITMAP_HELVETICA_18);
	text2 = new Text("Flags: 0/5",Point2D(10,545),Color(0.5f,0,1),BITMAP_HELVETICA_18);
	addText_to_Visual2D(text2, v2d2);
	text3 = new Text("Lives: 3",Point2D(10,520),Color(0.5f,0,1),BITMAP_HELVETICA_18);
	addText_to_Visual2D(text3, v2d2);
}


//functia care permite animatia
void DrawingWindow::onIdle()
{   

	isDead();

	if(isPressed > 0) {
		if(dead == false) { 
			pas_joc += abs(inc);
		}
	}

	if(pas_joc > 1950) {
		lastCheckpoint = 1950;
		steag = 1;
		if(pas_joc < 1960) {
			DrawingWindow::onReshape(0, 0);
		}
	}
	if(pas_joc > 3950) {
		lastCheckpoint = 3950;
		steag = 2;
		if(pas_joc < 3960) {
			DrawingWindow::onReshape(0, 0);
		}
	}
	if(pas_joc > 5950) {
		lastCheckpoint = 5950;
		steag = 3;
		if(pas_joc < 5960) {
			DrawingWindow::onReshape(0, 0);
		}
	}
	if(pas_joc > 7950) {
		lastCheckpoint = 7950;
		steag = 4;
		if(pas_joc < 7960) {
			DrawingWindow::onReshape(0, 0);
		}
	}
	if(pas_joc > 10000) {
		lastCheckpoint = 10000;
		steag = 5;
		if(pas_joc < 10010) {
			DrawingWindow::onReshape(0, 0);
		}
	}

	if(vieti == 0 || steag == 5) {
		Sleep(5000);
		exit(0);
	}

	if(dead == true) {
		isPressed = 0;
		for(i = 0; i < (int)objects.size(); i++) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix((float)pas_joc - lastCheckpoint, 0);
			Transform2D::applyTransform(objects[i]);
		}
		pas_joc = (float)lastCheckpoint;
		pas_om = 0;
		height_prev = 0;
		pas_rot = 0;
		height1 = 0;
		Transform2D::loadIdentityMatrix();
		Transform2D::applyTransform(rect);
		Transform2D::applyTransform(rect2);
		Transform2D::applyTransform(eyes[0]);
		Transform2D::applyTransform(eyes[1]);
		Transform2D::applyTransform(gura);
		dead = false;

	}

	for(i = 0; i < (int)objects.size(); i++) {
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-pas_joc, 0);
		Transform2D::applyTransform(objects[i]);
	}


	if((rect->points[0]->y + pas_om == 100 || rect->points[0]->y + pas_om == 150) && rect->points[0]->x + pas_joc < 3400 && rect->points[0]->x + pas_joc > 3350) {
		isPressed = 7;
	}

	if(isPressed == 7) {
		propulsion();
	}

	fall();
	jump();


}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{

	if(isPressed == -1) {
		text->text = "Choose dificulty level: Low: press 'a' | High: press 's', then press space";
		addText_to_Visual2D(text, v2d2);
	}

	if(isPressed == 0) {
		text->text = "Use space to play";
		addText_to_Visual2D(text, v2d2);
	}

	if(isPressed == -2) {
		text->text = "Choose player: Green: default | Red: press 'q' | Grey: press 'w', then press space";
		addText_to_Visual2D(text, v2d2);
	}

	if(vieti == 2) {
		text3->text = "Lives: 2";
		addText_to_Visual2D(text3, v2d2);
	}

	if(vieti == 1) {
		text3->text = "Lives: 1";
		addText_to_Visual2D(text3, v2d2);
	}

	if(vieti == 0) {
		text3->text = "You lost!";
		addText_to_Visual2D(text3, v2d2);
		isPressed = 10;
	}

	if(steag == 1) {
		text2->text = "Flags: 1/5";
		addText_to_Visual2D(text2, v2d2);
	}

	if(steag == 2) {
		text2->text = "Flags: 2/5";
		addText_to_Visual2D(text2, v2d2);
	}

	if(steag == 3) {
		text2->text = "Flags: 3/5";
		addText_to_Visual2D(text2, v2d2);
	}
	
	if(steag == 4) {
		text2->text = "Flags: 4/5";
		addText_to_Visual2D(text2, v2d2);
	}

	if(steag == 5) {
		text2->text = "You won!!!";
		addText_to_Visual2D(text2, v2d2);
	}

}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		if(isPressed == -2) {

			case 'q': { rect->color = Color(1,0,0);
						addObject2D_to_Visual2D(rect, v2d1);
					 } break;
			case 'w': { rect->color = Color(0.5f, 0.5f, 0.5f);
						addObject2D_to_Visual2D(rect, v2d1);
					  }	break;
		}
		case 32 : if(isPressed < 2) {
					isPressed++;
					if(isPressed <= 0) {
						onReshape(DrawingWindow::width,DrawingWindow::height);
					}
				  }
				  break;
		case 'a': if(isPressed == -1) inc = 2.5; break;
		case 's': if(isPressed == -1) inc = 5; break;
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{

}


/* Functia care verifica daca omulteul a s-a ciocnit cu un triunghi sau un patrat/dreptunghi */
void isDead() {

	for(j = 0; j < (int)triangles.size(); j++) {
		if (sqrt( (125 - triangles[j]->points[0]->x + pas_joc + (triangles[j]->points[0]->x - triangles[j]->points[1]->x)/2)
			*(125 - triangles[j]->points[0]->x + pas_joc + (triangles[j]->points[0]->x - triangles[j]->points[1]->x)/2) + 
			(75 + pas_om - triangles[j]->points[0]->y - 15)*(75 + pas_om - triangles[j]->points[0]->y - 15) ) < (23*sqrt(2) + 25)) {
			dead = true;
			vieti--;
			DrawingWindow::onReshape(0,0);
		}
	}

	for(j = 0; j < (int)rectangles.size(); j++) {
		if ((rect->points[0]->y + pas_om) < rectangles[j]->points[2]->y && (rect->points[2]->y + pas_om) > rectangles[j]->points[0]->y
		&& (rectangles[j]->points[0]->x - pas_joc < 150) && (rectangles[j]->points[2]->x - pas_joc > 100)) {
			dead = true;
			vieti--;
			DrawingWindow::onReshape(0,0);
		}
	}
}

/* Functie care verifica daca omuletul va cadea de pe o platforma sau nu */
void fall() {
	int p = 0;
	for(i = 0; i < (int)rectangles.size(); i++) {
		if((rectangles[i]->points[2]->x - pas_joc < 100 || rectangles[i]->points[0]->x - pas_joc > 150) && isPressed == 1 && pas_om > 0) {
			p++;
		}
	}

	if(p == (int)rectangles.size()) {
		falling = true;
	}

}


/* Functie care realizeaza saritura atunci cand este atins un element de propulsie */
void propulsion() {
	if(isPressed == 7) {
		for(i = 0; i < (int)rectangles.size(); i++) {
			if(rectangles[i]->points[2]->x - pas_joc > 100 + 400 + height_prev - rectangles[i]->points[0]->y 
				&& rectangles[i]->points[0]->x - pas_joc < 150 + 400 + height_prev - rectangles[i]->points[0]->y) {
				height1 = rectangles[i]->points[2]->y - 50;
			}
		}
		isPressed = 6;
	}

	if(isPressed == 6) {
		pas_om += inc;
		if (inc > 0) {
			pas_rot += inc * 3 / 4;
		} else {
			pas_rot -= inc * 3 / 4;
		}

		if(pas_om < 200 + height_prev && inc > 0) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-125, -75);
			Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
			Transform2D::translateMatrix(125,75);
			Transform2D::translateMatrix(0,pas_om);
			Transform2D::applyTransform(rect);
			Transform2D::applyTransform(rect2);
			Transform2D::applyTransform(eyes[0]);
			Transform2D::applyTransform(eyes[1]);
			Transform2D::applyTransform(gura);
		}

		if(pas_om == (200 + height_prev)) {
			inc = -inc;
		}

		if(pas_om >= height1 && inc < 0) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-125,-75);
			Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
			Transform2D::translateMatrix(125,75);
			Transform2D::translateMatrix(0,pas_om);
			Transform2D::applyTransform(rect);
			Transform2D::applyTransform(rect2);
			Transform2D::applyTransform(eyes[0]);
			Transform2D::applyTransform(eyes[1]);
			Transform2D::applyTransform(gura);
		}

		isPressed = 7;

		if(pas_om < height1 && inc < 0) {
			inc = -inc;
			pas_om = height1;
			if(pas_rot < 320) {
				pas_rot = 300;
			} else {
				pas_rot = 0;
			}
			isPressed = 1;
			height_prev = height1;
			height1 = 0;
		}
	}
}


/* Functie care realizeaza saritura */
void jump() {
	
	if(falling == true) {
		isPressed = 4;
		pas_om -= inc;
		pas_rot -= -inc * 300/height_prev;

		if(pas_om >= 0) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-125,-75);
			Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
			Transform2D::translateMatrix(125,75);
			Transform2D::translateMatrix(0,pas_om);
			Transform2D::applyTransform(rect);
			Transform2D::applyTransform(rect2);
			Transform2D::applyTransform(eyes[0]);
			Transform2D::applyTransform(eyes[1]);
			Transform2D::applyTransform(gura);
		}

		if(pas_om < 0) {
			pas_om = 0;
			if(pas_rot < 350) {
				pas_rot = 300;
			} else {
				pas_rot = 0;
			}
			isPressed = 1;
			height_prev = 0;
			height1 = 0;
			falling = false;
		}

	}
	
	if(isPressed == 2) {
		for(i = 0; i < (int)rectangles.size(); i++) {
			if(rectangles[i]->points[2]->x - pas_joc > 100 + 300 + height_prev - rectangles[i]->points[0]->y 
				&& rectangles[i]->points[0]->x - pas_joc < 150 + 300 + height_prev - rectangles[i]->points[0]->y) {
				height1 = rectangles[i]->points[2]->y - 50;
			}
		}
		isPressed = 3;
	}


	if (isPressed == 3) {
		
		if(height1 == 0) {
			pas_om += inc;
			if (inc > 0) {
				pas_rot += inc;
			} else {
				pas_rot -= inc * 150/(150 +height_prev - height1);
			}

			if(pas_om < 150 + height_prev && inc > 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125, -75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om == (150 + height_prev)) {
				inc = -inc;
			}

			if(pas_om >= height1 && inc < 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125,-75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/(300 - height_prev)));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om < height1) {
				inc = -inc;
				pas_om = height1;
				if(pas_rot < 350) {
					pas_rot = 300;
				} else {
					pas_rot = 0;
				}
				isPressed = 1;
				height_prev = height1;
				height1 = 0;
			}
		}



		if(height1 == 50) {
			pas_om += inc;
			if (inc > 0) {
				pas_rot += inc;
			} else {
				pas_rot -= inc * 150/(150 + height_prev - height1);
			}

			if(pas_om < 150 + height_prev && inc > 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125, -75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om == (150 + height_prev)) {
				inc = -inc;
			}

			if(pas_om >= height1 && inc < 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125,-75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om < height1 && inc < 0) {
				inc = -inc;
				pas_om = height1;
				if(pas_rot < 320) {
					pas_rot = 300;
				} else {
					pas_rot = 0;
				}
				isPressed = 1;
				height_prev = height1;
				height1 = 0;
			}
		}


		if(height1 == 100) {
			pas_om += inc;
			if (inc > 0) {
				pas_rot += inc;
			} else {
				pas_rot -= inc * 150/(150 +height_prev - height1);
			}

			if(pas_om < 150 + height_prev && inc > 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125, -75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om == (150 + height_prev)) {
				inc = -inc;
			}

			if(pas_om >= height1 && inc < 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125,-75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om < height1 && inc < 0) {
				inc = -inc;
				pas_om = height1;
				if(pas_rot < 320) {
					pas_rot = 300;
				} else {
					pas_rot = 0;
				}
				isPressed = 1;
				height_prev = height1;
				height1 = 0;
			}
		}

		if(height1 == 150) {
			pas_om += inc;
			if (inc > 0) {
				pas_rot += inc;
			} else {
				pas_rot -= inc * 150/(150 +height_prev - height1);
			}

			if(pas_om < 150 + height_prev && inc > 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125, -75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om == (150 + height_prev)) {
				inc = -inc;
			}

			if(pas_om >= height1 && inc < 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-125,-75);
				Transform2D::rotateMatrix((float)(-pas_rot*PI/300));
				Transform2D::translateMatrix(125,75);
				Transform2D::translateMatrix(0,pas_om);
				Transform2D::applyTransform(rect);
				Transform2D::applyTransform(rect2);
				Transform2D::applyTransform(eyes[0]);
				Transform2D::applyTransform(eyes[1]);
				Transform2D::applyTransform(gura);
			}

			if(pas_om < height1 && inc < 0) {
				inc = -inc;
				pas_om = height1;
				if(pas_rot < 320) {
					pas_rot = 300;
				} else {
					pas_rot = 0;
				}
				isPressed = 1;
				height_prev = height1;
				height1 = 0;
			}
		}
	}
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1000, 600, 0, 0, "Tema 1");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}
#include "Background.h"

void Background::defaultBehavior(Entity* e)
{
	static_cast<Background*>(e)->draw();
}

void Background::draw() {

	glMatrixMode(GL_TEXTURE); //the texture matrix will be the matrix we will perform our operations on
	glLoadIdentity(); //load the identity matrix

	//adjust the matrix to the size of our image
	glScaled(1.0 / this->storedSource->w, 1.0 / this->storedSource->h, 1.0); //the scale will be derived from the image dimensions

	//now use modelview for drawing the image
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up the parameters for drawing the image so it uses the pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//bind this texture to our image
	glBindTexture(GL_TEXTURE_2D, this->image);

	//enable texture drawing
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
		glTexCoord2i(0, 0);				//top left of texture
		glVertex2i(this->x, this->y);	//top left of background

		glTexCoord2i(this->w, 0);				//top right of texture
		glVertex2i(this->x + this->w, this->y);	//top right of background

		glTexCoord2i(this->w, this->h);				//bottom right of texture
		glVertex2i(this->x + this->w, this->y + this->h);	//bottom right of background

		glTexCoord2i(0, this->h);				//bottom left of texture
		glVertex2i(this->x, this->y + this->h);	//bottom left of background
	glEnd();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	//must disable textures to prevent OpenGL mixing up the textures as we go
	glDisable(GL_TEXTURE_2D);
}

void Background::flipX() {

}

void Background::flipY() {

}

void Background::rotate(int angle) {
	//translate so center is at (0,0,0)
	glTranslatef(-this->x, -this->y, 0);

	//rotate the background a specified angle around the z-axis (2-D rotation)
	glRotatef(angle, 0.0, 0.0, 1.0);

	//translate back to original position
	glTranslatef(this->x, this->y, 0);

}

void Background::setPosition(int x, int y) {
	//set the x and y position of the background
	this->x = x;
	this->y = y;
}

void Background::setSize(unsigned int w, unsigned int h) {
	//set the width and height of background
	this->w = w;
	this->h = h;
}

void Background::execute() {
	this->storedBehavior(this);
}

Background::Background() {
	this->x = 0;
	this->y = 0;
	this->w = 1;
	this->h = 1;

	this->visible = true;

	this->setBehavior(Background::defaultBehavior);
}

Background::~Background() {

}
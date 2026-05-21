#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "Viewport.h"

class Camera
{
public:
	explicit Camera(Viewport* vp);
	~Camera() = default;

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix
	glm::mat4 const& viewMat() const { return mViewMat; };

	void set2D();
	void set3D();

	void pitch(GLfloat a);	// rotates a degrees on the X axis
	void yaw(GLfloat a);	// rotates a degrees on the Y axis
	void roll(GLfloat a);	// rotates a degrees on the Z axis
	void changePrj();		// changes the camera projection

	void moveLR(GLfloat cs); // right / left
	void moveFB(GLfloat cs); // forward / back
	void moveUD(GLfloat cs); // up / down

	void pitchReal(GLfloat cs);	// pitch up / pitch down
	void yawReal(GLfloat cs);	// yaw right / yaw left
	void rollReal(GLfloat cs);	// roll right / roll left

	void orbit(GLdouble incAng, GLdouble incY);	// moves the camera +incAng degrees and +incY height
	void setCenital();

	// projection matrix
	glm::mat4 const& projMat() const { return mProjMat; };

	// sets scene visible area size
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const;

protected:
	glm::vec3 mEye = {0.0, 0.0, 500.0}; // camera's position
	glm::vec3 mLook = {0.0, 0.0, 0.0};  // target's position
	glm::vec3 mUp = {0.0, 1.0, 0.0};    // the up vector
	glm::vec3 mRight;
	glm::vec3 mUpward;
	glm::vec3 mFront;

	glm::mat4 mViewMat;   // view matrix = inverse of modeling matrix
	void uploadVM() const; // transfers viewMat to the GPU

	glm::mat4 mProjMat;   // projection matrix
	void uploadPM() const; // transfers projMat to the GPU

	glm::vec4 mLightDir = glm::vec4(-1.0f, -1.5f, -1.25f, 0.0f);	// cosas de la luz
	void uploadLight() const;

	GLfloat xRight, xLeft, yTop, yBot;     // size of scene visible area
	GLfloat mNearVal = 1, mFarVal = 10000; // view volume
	GLfloat mScaleFact = 1;                // scale factor
	bool bOrto = true;                      // orthogonal or perspective projection

	Viewport* mViewPort; // the viewport

	GLdouble mRadio; 
	GLdouble mAng;

	void setVM();
	void setPM();
	void setAxes();	
};

#endif //_H_Camera_H_

#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>

using namespace glm;

Camera::Camera(Viewport* vp)
  : mViewMat(1.0)
  , mProjMat(1.0)
  , xRight(vp->width() / 2.0)
  , xLeft(-xRight)
  , yTop(vp->height() / 2.0)
  , yBot(-yTop)
  , mViewPort(vp)
{
	setPM();
}

void
Camera::uploadVM() const
{
	Shader::setUniform4All("modelView", mViewMat);
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
	setAxes();
}

void
Camera::set2D()
{
	mEye = {0, 0, 500};
	mLook = {0, 0, 0};
	mUp = {0, 1, 0};
	mAng = 0;
	mRadio = 500;
	setVM();
}

void
Camera::set3D()
{
	mEye = {500, 500, 500};
	mLook = {0, 10, 0};
	mUp = {0, 1, 0};
	mAng = -45;
	mRadio = 1000.0;
	setVM();
}

void
Camera::pitch(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}

void
Camera::yaw(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}

void
Camera::roll(GLfloat a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::vec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
		                 xRight * mScaleFact,
		                 yBot * mScaleFact,
		                 yTop * mScaleFact,
		                 mNearVal,
		                 mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}

	else {
		float ratio = mNearVal / distance(mLook, mEye);
		mProjMat = frustum(xLeft * mScaleFact * ratio,
						   xRight * mScaleFact * ratio,
						   yBot * mScaleFact * ratio,
						   yTop * mScaleFact * ratio,	
						   mNearVal,
						   mFarVal);
	}
}

void
Camera::uploadPM() const
{
	Shader::setUniform4All("projection", mProjMat);
}

void
Camera::uploadLight() const
{
	glm::vec4 lightDir = normalize(mViewMat * vec4(-1.0f, -1.5f, -1.25f, 0.0f));
	Shader::get("simple_light")->use();
	Shader::get("simple_light")->Shader::setUniform("lightDir", lightDir);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
	uploadLight();
}

void 
Camera::setAxes() 
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void
Camera::changePrj() 
{
	bOrto = !bOrto;

	setPM();
}

void
Camera::moveLR(GLfloat cs) 
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

void
Camera::moveFB(GLfloat cs) 
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

void
Camera::moveUD(GLfloat cs) 
{
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}

void
Camera::pitchReal(GLfloat cs)
{
	mLook += mUpward * cs;
	setVM();
}

void
Camera::yawReal(GLfloat cs)
{
	mLook += mRight * cs;
	setVM();
}

void
Camera::rollReal(GLfloat cs)
{
	mUp = glm::mat3(rotate(mat4(1.0f), glm::radians(cs), mFront)) * mUp;
	setVM();
}

void 
Camera::orbit(GLdouble incAng, GLdouble incY) {
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	setVM();
}

void
Camera::setCenital() {
	mLook = glm::vec3(0.0);
	mEye.x = 0.0;
	mEye.z = 0.1;	// si es 0.0 el renderizado se rompe
	mEye.y += 500.0;
	setVM();
}
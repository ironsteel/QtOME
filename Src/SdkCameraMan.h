/*
 -----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/
 
 Copyright (c) 2000-2009 Torus Knot Software Ltd
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 This is modified version of the original file.
 The main change is the use of Qt's mouse events in place of OIS's.

 -----------------------------------------------------------------------------
 */
#ifndef __SdkCameraMan_H__
#define __SdkCameraMan_H__

#include <QMouseEvent>
#include "OGRE/Ogre.h"
#include <limits>

struct mousePos
{
    double X;
    double Y;
};


	/*=============================================================================
	| Utility class for controlling the camera in samples.
	=============================================================================*/
	class SdkCameraMan
    {
    public:
		SdkCameraMan(Ogre::Camera* cam)
		: mCamera(0)
		, mTarget(0)

		{

                        setCamera(cam);
                        startPos.X=0;startPos.Y=0;
                        relPos.X=0;relPos.Y=0;
		}

		virtual ~SdkCameraMan() {}

		/*-----------------------------------------------------------------------------
		| Swaps the camera on our camera man for another camera.
		-----------------------------------------------------------------------------*/
		virtual void setCamera(Ogre::Camera* cam)
		{
			mCamera = cam;
		}

		virtual Ogre::Camera* getCamera()
		{
			return mCamera;
		}

		/*-----------------------------------------------------------------------------
		| Sets the target we will revolve around. Only applies for orbit style.
		-----------------------------------------------------------------------------*/
		virtual void setTarget(Ogre::SceneNode* target)
		{
			if (target != mTarget)
			{
				mTarget = target;
				if(target)
				{
					setYawPitchDist(Ogre::Degree(0), Ogre::Degree(15), 150);
					mCamera->setAutoTracking(true, mTarget);
				}
				else
				{
					mCamera->setAutoTracking(false);
				}

			}


		}

		virtual Ogre::SceneNode* getTarget()
		{
			return mTarget;
		}

		/*-----------------------------------------------------------------------------
		| Sets the spatial offset from the target. Only applies for orbit style.
		-----------------------------------------------------------------------------*/
		virtual void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist)
		{
                        mCamera->setPosition(mTarget->_getDerivedPosition());
                        mCamera->setOrientation(mTarget->_getDerivedOrientation());
			mCamera->yaw(yaw);
			mCamera->pitch(-pitch);
			mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
		}


                void Rotate()
		{

				Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

                                mCamera->setPosition(mTarget->_getDerivedPosition());

                                mCamera->yaw(Ogre::Degree(-relPos.X * 0.25f));
                                mCamera->pitch(Ogre::Degree(-relPos.Y * 0.25f));

                                mCamera->moveRelative(Ogre::Vector3(0, 0, dist));

                                resetRel();
		}
                /*
                void Zoom()
                {
                    if (mStyle == CS_ORBIT)
                    {
                        else if (mZooming)  // move the camera toward or away from the target
                        {
                                // the further the camera is, the faster it moves
                                mCamera->moveRelative(Ogre::Vector3(0, 0, evt.state.Y.rel * 0.004f * dist));
                        }
                        else if (evt.state.Z.rel != 0)  // move the camera toward or away from the target
                        {
                                // the further the camera is, the faster it moves
                                mCamera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));
                        }
                    }
                }
                */
                void setStartPos(int x, int y)/// Used to set where the cursor was when rotation began
                {
                    startPos.X=x;
                    startPos.Y=y;
                }

                void setRelPos(int x, int y) /// Use to set where the cursor is at the time of the event
                {
                    relPos.X =  x - startPos.X;
                    relPos.Y =  y - startPos.Y;
                    startPos.X=x;
                    startPos.Y=y;
                }

                void resetRel() /// When camera has already been moved the values are reset to zero
                {
                    relPos.X=0;relPos.Y=0;
                }



    protected:

                mousePos startPos;
                mousePos relPos;
		Ogre::Camera* mCamera;
		Ogre::SceneNode* mTarget;

    };


#endif

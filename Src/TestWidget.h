#ifndef TestWidget_H
#define TestWidget_H
//
// --- Includes ---
//
#include "QOgreWidget.h"
#include "SdkCameraMan.h"
#include <QtGui/QSplashScreen>
//
// --- Class Definition ---
//
class TestWidget : public QOgreWidget {
	Q_OBJECT
public:
	//
	// ########## Public functions ##########
	//
	//
	// --- Constructors ---
	//
///
/// Default constructor
///
        TestWidget(QWidget *parent) : QOgreWidget(parent)
        {
	  m_sceneMgr = NULL;
	  m_vp = NULL;
	  m_mousePressed = false;

          //sdkCam->setTarget(m_mainNode);
	}
        ~TestWidget(void);
        void setSplash(QSplashScreen * splash);
protected:
	//
	// ########## Protected functions ##########
	//
	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void createScene(void);
	void setupResources(void);
	void setupScene(void);

	//
	// ########## Private variables ##########
	//
	bool m_mousePressed;
        QSplashScreen* splash;
	QPoint m_mousePressPos;
	Ogre::Quaternion m_orientationPressed;
	Ogre::SceneNode *m_mainNode;
	Ogre::SceneManager *m_sceneMgr;
	Ogre::Camera *m_camera;
        SdkCameraMan *sdkCam;
	Ogre::Viewport *m_vp;
	//
	// ########## Private constants ##########
	//
	static const float m_RADIUS;
};
//
//
//
#endif

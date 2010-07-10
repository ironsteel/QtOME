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
          meshName = "mesh1";
	}
        ~TestWidget(void);
        void setSplash(QSplashScreen * splash);
        QString changeMesh(QString fullname);
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
        void wheelEvent(QWheelEvent* w);
	void createScene(void);
	void setupResources(void);
        void setupScene(void);
	//
	// ########## Private variables ##########
	//
	bool m_mousePressed;
        QSplashScreen*         splash;
        QPoint                 m_mousePressPos;
        Ogre::SceneNode       *m_mainNode;
        Ogre::SceneManager    *m_sceneMgr;
        Ogre::Camera          *m_camera;
        SdkCameraMan          *sdkCam;
        Ogre::Viewport        *m_vp;
        Ogre::Entity          *mesh;
        Ogre::SceneNode       *camTarget;
        Ogre::SceneNode       *sceneCenter;
        Ogre::String           meshName;
            //keeps track of mesh names for mesh replacing in changeMesh()
	//
	// ########## Private constants ##########
	//
        static const float m_RADIUS;
private slots:

};
//
//
//
#endif

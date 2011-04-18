#ifndef TestWidget_H
#define TestWidget_H
//
// --- Includes ---
//
#include "QOgreWidget.h"
#include "MaterialManager.hpp"
#include "SdkCameraMan.h"
#include <QtGui/QSplashScreen>
#include <QPlainTextEdit>
#include "MyLogListener.h"
//
// --- Class Definition ---
//
class TestWidget : public QOgreWidget {
	Q_OBJECT
public:
    SdkCameraMan        *sdkCam;
    MyLogListener *mLogListener;


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
          manager = new MaterialManager();
          mLogListener = new MyLogListener(this);
        }
        ~TestWidget(void);
        void setSplash(QSplashScreen * splash);
        void setMaterial(const Ogre::String &script,const Ogre::String& matName, const Ogre::String &VP = "", const Ogre::String &FP = "");
        void clearMaterial();
        QString changeMesh(QString fullname);



        MaterialManager       *manager;
protected:
	//
	// ########## Protected functions ##########
	//
        void setVertexProgram(const Ogre::String& VpSource);
        void setFragmentProgram(const Ogre::String& FpSource);
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

        Ogre::Viewport        *m_vp;
        Ogre::Entity          *mesh;
        Ogre::SceneNode       *camTarget;
        Ogre::SceneNode       *sceneCenter;
        Ogre::String           meshName;
        Ogre::MaterialPtr      tempMat;
        Ogre::MaterialPtr      currentMaterial;
        Ogre::Log *mLog;
        Ogre::HighLevelGpuProgramPtr vp;
        Ogre::HighLevelGpuProgramPtr fp;



            //keeps track of mesh names for mesh replacing in changeMesh()
	//
	// ########## Private constants ##########
	//
        static const float m_RADIUS;


};
//
//
//
#endif

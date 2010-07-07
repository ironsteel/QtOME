//
// --- Includes ---
//
#include "TestWidget.h"
#include <QMouseEvent>
//
// --- Functions ---
//
#include <QtGui/QSplashScreen>
Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

///
/// Destructor
///
TestWidget::~TestWidget(void) {
}
///
///
/// \name Protected functions
/// Protected helper functions
///

//@{
///
/// Handle a resize event (pass q-it along to the render window)
/// \param e The event data
///
void TestWidget::resizeEvent(QResizeEvent *e) {
	QOgreWidget::resizeEvent(e);
	
	if (m_renderWindow) {
		// Alter the camera aspect ratio to match the viewport
		m_camera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));
		m_vp->update();
	}
}
///
/// Handle a paint event (just render again, if needed create render window)
/// \param e The event data
///
void TestWidget::paintEvent(QPaintEvent *) {
	if(!m_renderWindow) {
		createRenderWindow();
		setupResources();
		setupScene();
	}

	update();
}
///
/// Handle a timer event
/// \param e The event data
///
void TestWidget::timerEvent(QTimerEvent *) {
    update();
}
///
/// The user pressed a mouse button, start tracking
/// \param e The event data
///
void TestWidget::mousePressEvent(QMouseEvent *e) {
    m_mousePressPos = e->pos();
	if (m_mainNode)
		m_orientationPressed = m_mainNode->getOrientation();
    m_mousePressed = true;
}
///
/// The user released a mouse button, stop tracking
/// \param e The event data
///
void TestWidget::mouseReleaseEvent(QMouseEvent *) {
    m_mousePressed = false;
}
///
/// The user moved the mouse, if tracking process it
/// \param e The event data
///
void TestWidget::mouseMoveEvent(QMouseEvent *e) {
    if (m_mousePressed) {
        QPoint curPos = e->pos();
		
        double w = width();
        double h = height();
		
        double curX = (curPos.x() * 2. - w) / w;
        double curY = (h - curPos.y() * 2.) / h;
        double x0 = (m_mousePressPos.x() * 2. - w) / w;
        double y0 = (h - m_mousePressPos.y() * 2.) / h;
		
        Ogre::Vector3 v1(x0, y0, 0);
        Ogre::Vector3 v2(curX, curY, 0);
		
        double radiusSqr = m_RADIUS * m_RADIUS;
        double cutoff = radiusSqr * 0.5;
        double Rho = v1[0] * v1[0] + v1[1] * v1[1];
        v1[2] = (Rho < cutoff) ? sqrt(radiusSqr - Rho) : (cutoff / sqrt(Rho));
		
        Rho = v2[0] * v2[0] + v2[1] * v2[1];
        v2[2] = (Rho < cutoff) ? sqrt(radiusSqr - Rho) : (cutoff / sqrt(Rho));
		
        // v_cross is the normal of rotating plane
        Ogre::Vector3 cross = v2.crossProduct(v1);
        cross.normalise();

        // compute the angle
        v1.normalise();
        v2.normalise();
        double cosAngle = v1.dotProduct(v2);
        if (cosAngle < -1.0)
            cosAngle = -1.0;
        else if(cosAngle > 1.0)
            cosAngle = 1.0;
        double angle = acos(cosAngle);
		
        m_mainNode->rotate(cross, Ogre::Radian(angle));
		
        m_mousePressPos = curPos;
        m_orientationPressed = m_mainNode->getOrientation();

        update();
    }
}
///
/// Create the Ogre scene
///
void TestWidget::createScene(void) {

    splash->showMessage(QObject::tr("Creating Scene..."), topRight, Qt::black);
        m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.6, 0.6, 0.6));
	
	// Setup the actual scene
	Ogre::Light* l = m_sceneMgr->createLight("MainLight");
	l->setPosition(0, 100, 500);
	
	Ogre::Entity* mesh = m_sceneMgr->createEntity("mesh", "dwarf.mesh");
	m_mainNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
	m_mainNode->attachObject(mesh);
	
	m_camera->setAutoTracking(true, m_mainNode);

        splash->finish(this);
        delete splash;
}
///
/// Configure the resources in Ogre
/// \todo This should be moved somewhere else
///
void TestWidget::setupResources(void) {
	// Load resource paths from config file
    splash->raise();
    splash->showMessage(QObject::tr("Setting Up Resources..."),topRight, Qt::black);
	Ogre::ConfigFile config;
        config.load("Data/resources.cfg");
	
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator it = config.getSectionIterator();
	
	Ogre::String secName, typeName, archName;
	while (it.hasMoreElements()) {
		secName = it.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = it.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
    }
}
//@}
///
/// \name Private functions
/// Private helper functions
///
//@{
///
/// Setup the scene
///
void TestWidget::setupScene(void) {

    splash->showMessage(QObject::tr("Setting Up Scene..."), topRight, Qt::black);

	m_sceneMgr = m_ogreRoot->createSceneManager(Ogre::ST_GENERIC);
	
	// Create the camera
	m_camera = m_sceneMgr->createCamera("PlayerCam");
	m_camera->setPosition(Ogre::Vector3(0, 0, 200));
	
	// Look back along -Z
	m_camera->lookAt(Ogre::Vector3(0, 0, -300));
	m_camera->setNearClipDistance(5);
	
	// Create one viewport, entire window
	m_vp = m_renderWindow->addViewport(m_camera);
	m_vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	m_vp->setClearEveryFrame(true);
	
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	createScene();
	
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_BILINEAR);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(1);
	
	// Alter the camera aspect ratio to match the viewport
	m_camera->setAspectRatio(Ogre::Real(m_vp->getActualWidth()) / Ogre::Real(m_vp->getActualHeight()));
	
	startTimer(20);
}

void TestWidget::setSplash(QSplashScreen * splash)
{
    this->splash = splash;
}

//@}
///
/// \name Private constants
/// Private constants this class uses
///
//@{
///
/// The radius used for rotating
///
const float TestWidget::m_RADIUS = 0.8;
//@}
//
//

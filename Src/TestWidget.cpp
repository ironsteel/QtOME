//
// --- Includes ---
//
#include "TestWidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QChar>
#include <QKeyEvent>

//
// --- Functions ---
//
#include <QtGui/QSplashScreen>

Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

///
/// Destructor
///
TestWidget::~TestWidget(void)
{
    m_sceneMgr->destroyAllManualObjects();
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

void TestWidget::mousePressEvent(QMouseEvent *e)
{
    m_mousePressPos = e->pos();
    m_mousePressed = true;
    sdkCam->setStartPos(e->x(),e->y());
}
///
/// The user released a mouse button, stop tracking
/// \param e The event data
///
void TestWidget::mouseReleaseEvent(QMouseEvent *) {
    m_mousePressed = false;
    sdkCam->resetRel();
}
///
/// The user moved the mouse, if tracking process it
/// \param e The event data
///
void TestWidget::mouseMoveEvent(QMouseEvent *e) {
    if (m_mousePressed) {

        sdkCam->setRelPos(e->x(),e->y());
        sdkCam->Rotate();
        update();
    }
}

void TestWidget::wheelEvent(QWheelEvent* w)
{
    sdkCam->Zoom(w->delta());
}


///
/// Create the Ogre scene
///
void TestWidget::createScene(void)
{
        splash->showMessage(QObject::tr("Creating Scene..."), topRight, Qt::black);
        m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.6, 0.6, 0.6));

	// Setup the actual scene
	Ogre::Light* l = m_sceneMgr->createLight("MainLight");
        l->setPosition(100, 100, 200);

        // Init camera target ================================>
        Ogre::ManualObject* target = m_sceneMgr->createManualObject("target");
        target->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

        target->position(  1.0,  0.0,  1.0);
        target->position(  1.0,  0.0, -1.0);
        target->position(  1.0,  0.0, -1.0);
        target->position( -1.0,  0.0, -1.0);
        target->position( -1.0,  0.0, -1.0);
        target->position( -1.0,  0.0,  1.0);
        target->position( -1.0,  0.0,  1.0);
        target->position(  1.0,  0.0,  1.0);
        target->end();

        camTarget = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
        camTarget->attachObject(target);
        sdkCam->setTarget(camTarget);

        // Create center with arrows ================================>
        Ogre::ManualObject* center = m_sceneMgr->createManualObject("center");
        center->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

        center->position(  5.0,  0.0,  0.0);
        center->position( -5.0,  0.0,  0.0);
        center->position(  0.0,  0.0,  5.0);
        center->position(  0.0,  0.0, -5.0);
        center->position(  0.0,  0.0,  0.0);
        center->position(  0.0,  5.0,  0.0);
        center->position(  5.0,  0.0,  0.0);
        center->position(  4.0,  0.0, -0.5);
        center->position(  5.0,  0.0,  0.0);
        center->position(  4.0,  0.0,  0.5);
        center->position(  4.0,  0.0,  0.5);
        center->position(  4.0,  0.0, -0.5);
        center->position(  0.0,  0.0,  5.0);
        center->position( -0.5,  0.0,  4.0);
        center->position(  0.0,  0.0,  5.0);
        center->position(  0.5,  0.0,  4.0);
        center->position(  0.5,  0.0,  4.0);
        center->position( -0.5,  0.0,  4.0);
        center->end();

        sceneCenter = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
        sceneCenter->attachObject(center);

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
        sdkCam = new SdkCameraMan(m_camera);
	
	// Look back along -Z
        //m_camera->lookAt(Ogre::Vector3(0, 0, -300));
        m_camera->setNearClipDistance(0.1);
	
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

QString TestWidget::changeMesh(QString fullname)
{
    QString Qname;
    Ogre::String name;
    QString Qpath;
    Ogre::String path;
    QString::iterator It = fullname.end();
    // We will iterate through the fullname backwards until we find '/' because the filename starts there
    while ( *It != '/' )
    {
        Qname.push_front(*It);
        It--;
    }
    // The rest of the fullname is the path
    while ( It != fullname.begin() - 1)
    {
        Qpath.push_front(*It);
        It--;
    }
    It = Qpath.begin();
    // Here we convert the QString (Qpath) to Ogre::String (path)
    while ( It != Qpath.end())
    {
        path.push_back(It->toAscii());
        It++;
    }
    It = Qname.begin();
    // Here we convert the QString (Qname) to Ogre::String (name)
    while ( It != Qname.end()+1)
    {
        name.push_back(It->toAscii());
        It++;
    }

    //Ogre::ResourceGroupManager::initialiseResourceGroup("ImportedMeshes")
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation( path ,"FileSystem","ImportedMeshes");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("ImportedMeshes");

    if(meshName == "mesh1")
    {
        mesh = m_sceneMgr->createEntity( name, name);
        m_mainNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
        m_mainNode->attachObject(mesh);
        meshName=name;
    }
    else
    {
        m_mainNode->detachObject(meshName);
        mesh = m_sceneMgr->createEntity( name, name);
        m_sceneMgr->destroyEntity(meshName);
        mesh->setMaterialName("Material1");
        m_mainNode->attachObject(mesh);
        meshName=name;
    }

    return Qname;
}

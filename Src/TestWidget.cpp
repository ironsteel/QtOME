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

        currentMaterial = Ogre::MaterialManager::getSingleton().getByName("DefaultSettings", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        tempMat         = Ogre::MaterialManager::getSingleton().getByName("Material1",       Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        vp = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram(
                "CustomShadowCasterVp", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,"cg", Ogre::GPT_VERTEX_PROGRAM);
        fp = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram(
                "CustomShadowCasterFp", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,"cg", Ogre::GPT_FRAGMENT_PROGRAM);

        // Get the default log
        mLog = Ogre::LogManager::getSingletonPtr()->getDefaultLog();

        // Add the listener to the current log
        mLog->addListener(mLogListener);



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

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation( path ,"FileSystem","ImportedMeshes");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("ImportedMeshes");

    if(meshName == "mesh1")
    {
        mesh = m_sceneMgr->createEntity( name, name);
        m_mainNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
        m_mainNode->attachObject(mesh);
        meshName=name;
        mesh->setMaterial(currentMaterial);
    }
    else
    {
        m_mainNode->detachObject(meshName);
        mesh = m_sceneMgr->createEntity( name, name);
        m_sceneMgr->destroyEntity(meshName);
        m_mainNode->attachObject(mesh);
        mesh->setMaterial(currentMaterial);
        meshName=name;
    }

    return Qname;
}

void TestWidget::setMaterial(const Ogre::String &script,const Ogre::String& matName, const Ogre::String &VP, const Ogre::String &FP )
{
    Ogre::LogManager::getSingleton().logMessage("Starting compilation of material script ...");

    this->clearMaterial();

    Ogre::MemoryDataStream *memoryStream = new Ogre::MemoryDataStream((void*)script.c_str(), script.length() * sizeof(char));
    Ogre::DataStreamPtr dataStream(memoryStream);
    Ogre::MaterialManager::getSingleton().parseScript(dataStream, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::StringVector lines = Ogre::StringUtil::split(script, "\n");

    for(Ogre::StringVector::iterator line = lines.begin(); line != lines.end(); line++)
    {
        Ogre::StringVector params = Ogre::StringUtil::split(*line, " \t:");
        if (params[0] == "material")
        {
            Ogre::String materialName = params[1];
            //currentMaterial = Ogre::MaterialManager::getSingleton().getByName(materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            currentMaterial = Ogre::MaterialManager::getSingleton().getByName(matName);
            currentMaterial->compile();
        }
    }

    if(!(VP==""))this->setVertexProgram(VP);
    if(!(FP==""))this->setFragmentProgram(FP);

    mesh->setMaterial(currentMaterial);
    Ogre::LogManager::getSingleton().logMessage("Finished compilation of material script ...");
}

void TestWidget::setVertexProgram(const Ogre::String &VpSource)
{
    vp->setSource(VpSource);
    vp->setParameter("profiles", "vs_1_1 arbvp1");
    vp->setParameter("entry_point", "customCasterVp");
    vp->load();


    Ogre::Pass* p = currentMaterial->getTechnique(0)->getPass(0);
    p->setVertexProgram("CustomShadowCasterVp");
    p->getVertexProgramParameters()->setNamedAutoConstant("worldViewProj", Ogre::GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX);
}

void TestWidget::setFragmentProgram(const Ogre::String &FpSource)
{
    fp->setSource(FpSource);
    fp->setParameter("profiles", "ps_1_1 arbfp1");
    fp->setParameter("entry_point", "customCasterFp");
    fp->load();

    Ogre::Pass* p = currentMaterial->getTechnique(0)->getPass(0);
    p->setFragmentProgram("CustomShadowCasterFp");
}

void TestWidget::clearMaterial()
{
    mesh->setMaterial(tempMat);
    // Sets the mesh material to the temp one then deletes the current
    // We need to do this because only materials that are not being used will be deleted
    Ogre::MaterialManager::getSingletonPtr()->remove(currentMaterial->getHandle());
}


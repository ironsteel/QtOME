//
// --- Includes ---
//
#include "QOgreWidget.h"
#if defined(Q_WS_MAC)
#include <Carbon/Carbon.h>
#include <Ogre/OgreOSXContext.h>
#include <AGL/agl.h>
#elif !defined(Q_WS_WIN)
#include <QX11Info>
#endif
//
// --- Functions ---
//
///
/// Default constructor
///
QOgreWidget::QOgreWidget(QWidget *parent) : QWidget(parent) {
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoBackground);
	
	m_renderWindow = NULL;
	m_ogreRoot = NULL;
}
///
/// Destructor
///
QOgreWidget::~QOgreWidget(void) {
    delete m_ogreRoot;
}
///
/// \name Misc
/// Miscellaneous functions of this class
///
//@{
///
/// Render a frame
///
void QOgreWidget::update(void) {
	if (m_renderWindow) {
		m_ogreRoot->_fireFrameStarted();
		m_renderWindow->update();
		m_ogreRoot->_fireFrameEnded();
	}
}
///
/// Give the minimum size for this widget
/// \return Returns a size
/// \warning Needs to be big enough so that ogre doesn't crash (50 50 looks big enough)
///
QSize QOgreWidget::minimumSizeHint(void) const {
	return QSize(50, 50);
}
//@}
///
/// \name Protected functions
/// Protected helper functions
///
//@{
///
/// Handle a resize event (pass it along to the render window)
/// \param e The event data
///
void QOgreWidget::resizeEvent(QResizeEvent *) {
	if (m_renderWindow)
		resizeRenderWindow();
}
///
/// Handle a paint event (just render again, if needed create render window)
/// \param e The event data
///
void QOgreWidget::paintEvent(QPaintEvent *) {
	if (!m_renderWindow)
		createRenderWindow();
	
	update();
}
//@}
///
/// \name Private functions
/// Private helper functions
///
//@{
///
/// Create the Ogre render window
///
void QOgreWidget::createRenderWindow(void) {
	Ogre::NameValuePairList params;
	
	if (m_renderWindow)
		return;
	if (!m_ogreRoot)
		configure();
	
#if defined(Q_WS_MAC) || defined(Q_WS_WIN)
	params["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)winId());
#else
    QX11Info info = x11Info();
	Ogre::String winHandle;
	winHandle  = Ogre::StringConverter::toString(reinterpret_cast<unsigned long>(info.display()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString(static_cast<unsigned int>(info.screen()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(parentWidget()->winId()));
	params["parentWindowHandle"] = winHandle;
#endif
	
	m_renderWindow = m_ogreRoot->createRenderWindow("View" + Ogre::StringConverter::toString(reinterpret_cast<unsigned long>(this)),
													width(), height(), false, &params);
	
#if defined(Q_WS_MAC)
	// store context for hack
	Ogre::OSXContext *context;
	m_renderWindow->getCustomAttribute("GLCONTEXT", &context);
	context->setCurrent();
	m_aglContext = aglGetCurrentContext();
	resizeRenderWindow();
#endif
	
	// take over ogre window
#if !defined(Q_WS_MAC) && !defined(Q_WS_WIN)
	WId ogreWinId = 0x0;
	m_renderWindow->getCustomAttribute("WINDOW", &ogreWinId);
	assert(ogreWinId);
	create(ogreWinId);
#endif
}
///
/// Configure Ogre
/// \todo This really needs to be moved somewhere else (singleton?)
///
void QOgreWidget::configure(void) {
	if (m_ogreRoot)
		return;
	
#if defined(Q_WS_X11)
        m_ogreRoot = new Ogre::Root("Data/plugins.cfg", "Data/ogre.cfg", "Data/ogre.log");
#else
        m_ogreRoot = new Ogre::Root("Data/plugins.cfg", "Data/ogre.cfg", "Data/ogre.log");
#endif
	if (!m_ogreRoot->restoreConfig()) {
		// setup a renderer
		Ogre::RenderSystemList renderers = m_ogreRoot->getAvailableRenderers();
		assert(!renderers.empty()); // we need at least one renderer to do anything useful
		
		//Ogre::RenderSystem *renderSystem = chooseRenderer(renderers);
		Ogre::RenderSystem *renderSystem = *(renderers.begin());
		assert(renderSystem); // user might pass back a null renderer, which would be bad!
		
		m_ogreRoot->setRenderSystem(renderSystem);
		QString dimensions = QString("%1x%2").arg(width()).arg(height());
		renderSystem->setConfigOption("Video Mode", dimensions.toStdString());
		
		// initialize without creating window
		m_ogreRoot->getRenderSystem()->setConfigOption("Full Screen", "No");
		m_ogreRoot->saveConfig();
	}
	m_ogreRoot->initialise(false);
}
///
/// Resize the render window (when the widget was resized)
///
void QOgreWidget::resizeRenderWindow(void) {
	if (!m_renderWindow)
		return;
	
#if !defined(Q_WS_MAC)
	m_renderWindow->resize(width(), height());
	m_renderWindow->windowMovedOrResized();
#else
	GLint bufferRect[4];
	HIViewRef mView = HIViewRef(winId());
	
	m_renderWindow->windowMovedOrResized();
	
	// reposition our drawing region
	HIRect viewBounds, winBounds;
	HIViewGetBounds(mView, &viewBounds);
	HIViewRef root = HIViewGetRoot(HIViewGetWindow(mView));
	HIViewRef content_root;
	HIViewFindByID(root, kHIViewWindowContentID, &content_root);
	
	HIViewGetBounds(content_root, &winBounds);
	HIViewConvertRect(&viewBounds, mView, content_root);
	
	bufferRect[0] = x();
	bufferRect[1] = GLint((winBounds.size.height) - (viewBounds.origin.y + viewBounds.size.height));
	bufferRect[2] = width();
	bufferRect[3] = height();
	
	aglSetInteger(m_aglContext, AGL_BUFFER_RECT, bufferRect);
	aglEnable(m_aglContext, AGL_BUFFER_RECT);
#endif
}
//@}
///
/// \name Protected variables
/// Protected variables this class uses
///
//@{
///
/// The Ogre root
///
Ogre::Root * QOgreWidget::m_ogreRoot = NULL;
//@}
//
//

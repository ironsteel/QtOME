#ifndef QOgreWidget_H
#define QOgreWidget_H
///
/// \class QOgreWidget
/// \brief A Qt and Ogre widget
///
/// This widget connects the Qt library with the Ogre library. Derive from this
///	class to implement the createScene and other functions to init the ogre
/// part. Note: when reimplementing the resize event, do not forget to call the 
/// resizeRenderWindow function (or call the parent resize function).
///
//
// --- Includes ---
//
#include <QWidget>
#if defined(Q_WS_WIN)
#include <Ogre.h>
#else
#include <OGRE/Ogre.h>
#endif
//
// --- Used classes ---
//
#if defined(Q_WS_MAC)
typedef struct __AGLContextRec  *AGLContext;
#endif
//
// --- Class Definition ---
//
class QOgreWidget : public QWidget {
	Q_OBJECT
public:
	//
	// ########## Public functions ##########
	//
	//
	// --- Constructors ---
	//
	QOgreWidget(QWidget* parent);
	~QOgreWidget(void);
	//
	// --- Misc ---
	//
	virtual void update(void);
	QSize minimumSizeHint(void) const;
protected:
	//
	// ########## Protected functions ##########
	//
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	virtual void createScene(void) = 0;
	virtual void setupResources(void) = 0;
	virtual void configure(void);
	void createRenderWindow(void);
	void resizeRenderWindow(void);
	//
	// ########## Protected variables ##########
	//
	Ogre::RenderWindow *m_renderWindow;
	static Ogre::Root *m_ogreRoot;
#if defined(Q_WS_MAC)
	AGLContext m_aglContext;
#endif
};
//
//
//
#endif

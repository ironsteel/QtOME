#include <Qsci/qscilexercpp.h>
#include <qobject.h>
#include <Qsci/qscistyle.h>
class GLSLLexer : public QsciLexerCPP
{

	public:
                GLSLLexer(QObject *parent = 0);
                ~GLSLLexer();

                virtual const char *language() const;
                virtual QString description(int style) const;
                const char *keywords(int set) const;

};

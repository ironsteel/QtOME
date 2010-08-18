#include <Qsci/qscilexercpp.h>
#include <qobject.h>
#include <Qsci/qscistyle.h>
class CgLexer : public QsciLexerCPP
{

	public:
		CgLexer(QObject *parent = 0);
		~CgLexer();

                virtual const char *language() const;
                virtual QString description(int style) const;
                const char *keywords(int set) const;

};

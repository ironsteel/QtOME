#ifndef OGREMATERIALLEXER_H
#define OGREMATERIALLEXER_H

#include <Qsci/qscilexercpp.h>
#include <qobject.h>
#include <Qsci/qscistyle.h>
class OgreMaterialLexer : public QsciLexerCPP
{
public:
    OgreMaterialLexer(QObject *parent = 0);
    ~OgreMaterialLexer();

    // Overriding virtual methods of QsciLexerCPP for our new Lexer
    virtual const char* language() const;
    virtual QString description(int style) const;
    virtual const char* keywords(int set) const;
    virtual QStringList autoCompletionWordSeparators() const;

};

#endif

/***************************************************************************
 *   Copyright (C) 2009 by Gancov Kostya                                   *
 *   kossne@mail.ru                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "TextEdit.h"
#include "Highlighter.h"
TextEdit::TextEdit(QWidget *pard)
        : QsciScintilla(pard)
{
    initSettings();
    setSyntaxHighlighter("cpp");
    this->setTabWidth(4);

}

TextEdit::~TextEdit() {

}

void TextEdit::initSettings() {

    this->setCaretLineBackgroundColor(QColor("#e4e4e4"));
    this->setCaretLineVisible(true);
    //lexer = new QsciLexerCPP(this);
    //this->setLexer(cpp);
    //this->markerAdd(0, 0);

    this->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    //this->setMarginType(1, QsciScintilla::NumberMargin);
    //this->setMarginMarkerMask(10, 10);
    //this->setMarginsBackgroundColor(QColor("#e4e4e4"));

    //this->setMarginLineNumbers(0, true);
    //this->setMarginWidth(0, QString("---------"));
    this->setMarginWidth(0, 42);
    this->setMarginSensitivity(1, true);
    
    //this->setProperty("marker","2");
    //this->setMarginMarkerMask(1, 1);
    this->markerDefine(QsciScintilla::RightTriangle);
    this->setMarkerBackgroundColor(QColor("#00ff00"));

    this->setIndentationGuides(true);
    this->setTabIndents(true);
    this->setBackspaceUnindents(false);
    this->setAutoIndent(true);
    this->setIndentationsUseTabs(true);
    this->zoomTo(0);
    this->setUtf8(true);
    this->selectAll(true);

    this->setAutoCompletionSource(QsciScintilla::AcsAPIs);

    //this->setAutoCompletionThreshold(3);
    this->setAutoCompletionCaseSensitivity(true);
    this->setAutoCompletionShowSingle(true);
    this->setAutoCompletionFillupsEnabled(true);

    #ifdef Q_WS_WIN
    defaultFont.setFamily("Courier New");
    defaultFont.setPointSize(10);
    defaultFont.setWeight(0);
    #endif

    #ifdef Q_WS_X11
    defaultFont.setFamily("Monospace");
    defaultFont.setPointSize(10);
    #endif
    this->setMarginsFont(defaultFont);
    this->setFont(defaultFont);
}

void TextEdit::setSyntaxHighlighter(QString style) {
    styleSyntax = style;

    if (styleSyntax == "none")
        lexer = 0;

    if (styleSyntax == "bash") {
        lexer = new QsciLexerBash(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "batch") {
        lexer = new QsciLexerBatch(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "cmake") {
        lexer = new QsciLexerCMake(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "cpp") {
        lexer = new QsciLexerCPP(this);


        //lexer->setColor(QColor(255,0,0), 5);

        QFont fontBold;
        fontBold.setFamily("Courier New");
        fontBold.setPointSize(10);
        fontBold.setWeight(100);

        QFont fontNormal;
        fontNormal.setFamily("Courier New");
        fontNormal.setPointSize(10);

        QFont fontItalic;
        fontItalic.setFamily("Courier New");
        fontItalic.setPointSize(10);
        fontItalic.setItalic(true);

        lexer->setFont(fontBold, 5);
        //lexer->setFont(fontBold, 6);

        lexer->setFont(fontBold, 10);
        lexer->setColor(QColor("#008080"), 3);
        lexer->setColor(QColor("#804000"), 9);
        lexer->setColor(QColor("#0000ff"), 5);
        lexer->setColor(QColor("#ff8000"), 4);
        lexer->setColor(QColor("#000080"), 10);
        lexer->setColor(QColor("#000080"), 8);
        lexer->setColor(QColor("#008000"), 6);//808080
        lexer->setColor(QColor("#008000"), 7);//008000

        lexer->setFont(fontBold, 4);

        //lexer->setFont(fontKeywords, 5);
    }

    if (styleSyntax == "csharp") {
        lexer = new QsciLexerCSharp(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "css") {
        lexer = new QsciLexerCSS(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "d") {
        lexer = new QsciLexerBatch(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "diff") {
        lexer = new QsciLexerDiff(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "fortran77") {
        lexer = new QsciLexerFortran77(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "html") {
        lexer = new QsciLexerHTML(this);
//        lexer->setFont(defaultFont);

        QFont fontBold;
        fontBold.setFamily("Courier New");
        fontBold.setPointSize(10);
        fontBold.setWeight(100);

        QFont fontNormal;
        fontNormal.setFamily("Courier New");
        fontNormal.setPointSize(10);

        QFont fontItalic;
        fontItalic.setFamily("Courier New");
        fontItalic.setPointSize(10);
        fontItalic.setItalic(true);


        //lexer->setFont(fontBold, 5);
        //lexer->setFont(fontBold, 10);
        lexer->setColor(QColor("#000080"), 123);
        lexer->setFont(fontBold, 123);
        lexer->setFont(fontBold, 121);
        lexer->setColor(QColor("#0000ff"), 121);
        //lexer->setFont(fontBold, 18);
        lexer->setColor(QColor("#ff0000"), 18);
        lexer->setColor(QColor("#000080"), 127);
        lexer->setColor(QColor("#ff8000"), 122);
        lexer->setColor(QColor("#808080"), 119);
        lexer->setColor(QColor("#808080"), 120);
        lexer->setColor(QColor("#008000"), 124);
        lexer->setColor(QColor("#008000"), 125);
        lexer->setColor(QColor("#8000ff"), 1);//#8000ff
        lexer->setColor(QColor("#ff0000"), 3);//#8000ff
        lexer->setColor(QColor("#8000ff"), 6);//#8000ff
        lexer->setFont(fontBold, 6);
        lexer->setColor(QColor("#8000ff"), 7);//#8000ff
        lexer->setFont(fontBold, 7);
        //lexer->setFont(fontBold, 0);


    }

    if (styleSyntax == "java") {
        lexer = new QsciLexerJava(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "javascript") {
        lexer = new QsciLexerJavaScript(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "lua") {
        lexer = new QsciLexerLua(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "pascal") {
        lexer = new QsciLexerPascal(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "perl") {
        lexer = new QsciLexerPerl(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "php") {
        lexer = new QsciLexerHTML(this);
//        lexer->setFont(defaultFont);

        QFont fontBold;
        fontBold.setFamily("Courier New");
        fontBold.setPointSize(10);
        fontBold.setWeight(100);

        QFont fontNormal;
        fontNormal.setFamily("Courier New");
        fontNormal.setPointSize(10);

        QFont fontItalic;
        fontItalic.setFamily("Courier New");
        fontItalic.setPointSize(10);
        fontItalic.setItalic(true);

        //lexer->setFont(fontBold, 5);
        //lexer->setFont(fontBold, 10);
        lexer->setColor(QColor("#000080"), 123);
        lexer->setFont(fontNormal, 123);
        lexer->setFont(fontBold, 121);
        lexer->setColor(QColor("#0000ff"), 121);
        //lexer->setFont(fontBold, 18);
        lexer->setColor(QColor("#ff0000"), 18);
        lexer->setColor(QColor("#000080"), 127);
        lexer->setFont(fontNormal, 127);
        lexer->setEolFill(true, 127);

        lexer->setColor(QColor("#ff8000"), 122);
        lexer->setColor(QColor("#808080"), 119);
        lexer->setColor(QColor("#808080"), 120);
        lexer->setColor(QColor("#008000"), 124);
        lexer->setFont(fontNormal, 124);
        lexer->setColor(QColor("#008000"), 125);
        lexer->setFont(fontNormal, 125);
        lexer->setColor(QColor("#8000ff"), 1);//#8000ff
        lexer->setColor(QColor("#ff0000"), 3);//#8000ff
        lexer->setColor(QColor("#8000ff"), 6);//#8000ff
        lexer->setFont(fontBold, 6);
        lexer->setColor(QColor("#8000ff"), 7);//#8000ff
        lexer->setFont(fontBold, 7);
        //lexer->setFont(fontBold, 0);


    }

    if (styleSyntax == "postscript") {
        lexer = new QsciLexerPostScript(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "pov") {
        lexer = new QsciLexerPOV(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "properties") {
        lexer = new QsciLexerProperties(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "python") {
        lexer = new QsciLexerPython(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "ruby") {
        lexer = new QsciLexerRuby(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "spice") {
        lexer = new QsciLexerSpice(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "sql") {
        lexer = new QsciLexerSQL(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "tcl") {
        lexer = new QsciLexerTCL(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "tex") {
        lexer = new QsciLexerTeX(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "verilog") {
        lexer = new QsciLexerVerilog(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "vhdl") {
        lexer = new QsciLexerVHDL(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "xml") {
        lexer = new QsciLexerXML(this);
//        lexer->setFont(defaultFont);
    }

    if (styleSyntax == "yaml") {
        lexer = new QsciLexerYAML(this);
//        lexer->setFont(defaultFont);
    }

    this->setLexer(lexer);

    if (styleSyntax != "none") {
        apis = new QsciAPIs(lexer);
        apis->load(QApplication::applicationDirPath() + "/apis/" + styleSyntax + ".api");
        //qDebug() << QApplication::applicationDirPath() + "/apis/" + styleSyntax + ".api";
        apis->prepare();
        lexer->setAPIs(apis);
        this->setMarginsFont(defaultFont);
        lexer->setFont(defaultFont);
    }

    this->setMatchedBraceForegroundColor(QColor("#0000ff"));
    this->setMatchedBraceBackgroundColor(QColor("#ffff55"));
    this->setUnmatchedBraceForegroundColor(QColor("#ff0000"));
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    this->setFont(defaultFont);
}

QString TextEdit::syntaxHighlighter() {
    return styleSyntax;
}

void TextEdit::keyPressEvent(QKeyEvent *event) {
    QMessageBox ms;
    ms.setText(tr("%1").arg(event->key()));
    //ms.exec(); //47 d68
    //qDebug() << event->key() << Qt::Key_Enter;
    switch (event->key()) {
        case Qt::Key_Space:
            if (event->modifiers() & Qt::ControlModifier) {
                this->autoCompleteFromAPIs();
            } else {
                QsciScintilla::keyPressEvent(event);
            }
        break;
        case Qt::Key_Return:
            if (event->modifiers() & Qt::ControlModifier) {
                this->autoCompleteFromDocument();
            } else {
                QsciScintilla::keyPressEvent(event);
            }
        break;
        default:
            QsciScintilla::keyPressEvent(event);
    }
}

void TextEdit::openFile(const QString &filename)
{
    matScriptFilename = filename;

    QFile fileForEdit(matScriptFilename);
    if (!fileForEdit.open(QFile::ReadOnly)){
        QMessageBox::warning(this, tr("QtOME"), tr("Cannot open file!"));
        return ;
    }
    this->setText(fileForEdit.readAll());
    fileForEdit.close();
}

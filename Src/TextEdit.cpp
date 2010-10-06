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
#include "Lexers/OgreMaterialLexer.h"
TextEdit::TextEdit(QWidget *pard)
    : QsciScintilla(pard)
{
    initSettings();
    setSyntaxHighlighter();
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
    this->setMarginWidth(0, 30);
    this->setMarginSensitivity(1, true);
    
    //this->setProperty("marker","2");
    //this->setMarginMarkerMask(1, 1);
    this->markerDefine(QsciScintilla::RightTriangle);
    this->setMarkerBackgroundColor(QColor("#00ff00"));

    //[0] AutoIndent Settings
    this->setIndentationGuides(true);
    this->setTabIndents(true);
    this->setBackspaceUnindents(false);
    this->setAutoIndent(true);
    this->setIndentationsUseTabs(true);
    this->zoomTo(0);
    this->setUtf8(true);
    this->selectAll(true);


    this->setAutoCompletionThreshold(2);
    setAutoCompletionSource(QsciScintilla::AcsAPIs);
    //this->setAutoCompletionShowSingle(true);
    //this->setAutoCompletionFillupsEnabled(true);




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

void TextEdit::setSyntaxHighlighter() {


    styleSyntax = "material script";

    lexer = new OgreMaterialLexer(this);



   apis = new QsciAPIs(lexer);


   apis->load("./mat.api");
// apis->add("pass");
// apis->add("\\sblah");
// apis->add("env_map.spherical");


   apis->prepare();
   lexer->setAPIs(apis);
   this->setMarginsFont(defaultFont);
   lexer->setFont(defaultFont);


    this->setLexer(lexer);
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


void TextEdit::openFile(const QString &filename, const QString &materialName)
{

    if (matScriptFilename != filename) {
        this->saveModified();
    } else if (matScriptFilename == filename) {
        this->findFirst(materialName, false, true, true, false, true, 0, 0);
        return ;
    }


    matScriptFilename = filename;

    QFile fileForEdit(matScriptFilename);
    if (!fileForEdit.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("QtOME"), tr("Cannot open file!"));
        return ;
    }
    this->setText(fileForEdit.readAll());
    this->setModified(false);
    this->findFirst(materialName, false, true, true, false, true, 0, 0);
    fileForEdit.close();

}

void TextEdit::saveFile()
{
    if(matScriptFilename.isEmpty() == true) {
        return ;
    }

    QString text = this->text();

    QFile file(matScriptFilename);

    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("QtOME"), tr("Cannot write to file!"));
        return ;
    }

    QTextStream textStream(&file);

    textStream << text;

    file.close();

}

void TextEdit::saveModified()
{
    QString fileNameShort = this->matScriptFilename.section(QRegExp("/"), -1);

    QMessageBox::StandardButton userChoice;
    if (this->isModified()) {
        userChoice = QMessageBox::warning(this, tr("QtOME"),
                                          tr("Script file '%1' has been modified.\n"
                                             "Do you want to save your changes ?").arg(fileNameShort),
                                          QMessageBox::Save | QMessageBox::Discard  );

        if (userChoice == QMessageBox::Save) {
            this->saveFile();
            return ;
        }
    }

    return ;

}

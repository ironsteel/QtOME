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
#include "GLSLEdit.h"
#include "OGRE/OgreGpuProgramManager.h"
GLSLEdit::GLSLEdit(QWidget *pard)
    : QsciScintilla(pard)
{
    initSettings();
}

GLSLEdit::~GLSLEdit() {

}

void GLSLEdit::initSettings() {

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

    this->setTabWidth(4);
    this->setIndentationGuides(true);
    this->setTabIndents(true);
    this->setBackspaceUnindents(false);
    this->setAutoIndent(true);
    this->setIndentationsUseTabs(true);
    this->zoomTo(0);
    this->setUtf8(true);
    this->selectAll(true);
    this->setSyntaxHighlighter();
    //this->setAutoCompletionSource(QsciScintilla::AcsAPIs);
    this->setAutoCompletionThreshold(4);
    //this->setAutoCompletionCaseSensitivity(true);
    //this->setAutoCompletionShowSingle(true);
    //this->setAutoCompletionFillupsEnabled(true);
    this->setAutoCompletionSource(QsciScintilla::AcsAPIs);
    //this->autoCompleteFromAll();

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

void GLSLEdit::setSyntaxHighlighter() {

    styleSyntax = "glsl";
    lexer = new GLSLLexer(this);

    QFont fontBold;
    fontBold.setFamily("Courier New");
    fontBold.setPointSize(10);
    fontBold.setWeight(500);
    QFont fontNormal;
    fontNormal.setFamily("Courier New");
    fontNormal.setPointSize(10);
    QFont fontItalic;
    fontItalic.setFamily("Courier New");
    fontItalic.setPointSize(10);
    fontItalic.setItalic(true);
    lexer->setFont(fontBold, 5);
    lexer->setFont(fontBold, 10);
    lexer->setFont(fontBold, 6);
    lexer->setColor(QColor("#008000"), 16);
    lexer->setColor(QColor("#008080"), 3);
    lexer->setColor(QColor("#804000"), 9);
    lexer->setColor(QColor(Qt::blue).darker(200),  5);
    lexer->setColor(QColor("#ff8000"), 4);
    lexer->setColor(QColor("#000080"),10);
    lexer->setColor(QColor("#000080"), 8);
    lexer->setColor(QColor("#008000"), 6);//808080
    lexer->setColor(QColor(Qt::red).dark(), 7);//008000
    lexer->setFont(fontBold, 4);

    apis = new QsciAPIs(lexer);

    QStringList b = QString(lexer->keywords(1)).split(' ');
    QStringList::Iterator It = b.begin();
    while(It != b.end())
    {
        apis->add(*It);
        It++;
    }
    TYPES = b;
    b = QString(lexer->keywords(2)).split(' ');
    It = b.begin();
    while(It != b.end())
    {
        apis->add(*It);
        It++;
    }
    b = QString(lexer->keywords(3)).split(' ');
    It = b.begin();
    while(It != b.end())
    {
        apis->add(*It);
        It++;
    }
    b = QString(lexer->keywords(4)).split(' ');
    It = b.begin();
    while(It != b.end())
    {
        apis->add(*It);
        It++;
    }
    b = QString(lexer->keywords(5)).split(' ');
    It = b.begin();
    while(It != b.end())
    {
        apis->add(*It);
        It++;
    }

    apis->prepare();
    lexer->setAPIs(apis);
    this->setMarginsFont(defaultFont);
    lexer->setFont(defaultFont);
    //}
    this->setLexer(lexer);

    this->setMatchedBraceForegroundColor(QColor("#0000ff"));
    this->setMatchedBraceBackgroundColor(QColor("#ffff55"));
    this->setUnmatchedBraceForegroundColor(QColor("#ff0000"));
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    this->setFont(defaultFont);
}

QString GLSLEdit::syntaxHighlighter() {
    return styleSyntax;
}

void GLSLEdit::keyPressEvent(QKeyEvent *event) {
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

void GLSLEdit::openFile(const QString &filename)
{
    matScriptFilename = filename;

    QFile fileForEdit(matScriptFilename);
    if (!fileForEdit.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("QtOME"), tr("Cannot open file!"));
        return ;
    }
    this->setText(fileForEdit.readAll());
    fileForEdit.close();
}

void GLSLEdit::saveFile()
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

void GLSLEdit::saveModified()
{
    QString shaderSrcFilename = this->getShaderSource();
    QMessageBox::StandardButton userChoice;
    userChoice = QMessageBox::warning(this, tr("QtOME"),
                                      tr("Shader program file '%1' has been modified.\n"
                                         "Do you want to save your changes ?").arg(shaderSrcFilename),
                                          QMessageBox::Save | QMessageBox::Discard  );

    if (userChoice == QMessageBox::Save) {
       this->saveFile();
       return;
    }

    return;
}

QStringList GLSLEdit::scan()
{
    QStringList List;
    QStringList Text = QString(this->text()).split(' ', QString::SkipEmptyParts);

    QStringList::Iterator It = Text.begin();
    while(It != Text.end() )
    {
        if(this->listHasString(TYPES,*It))List.append(*It);
        It++;
    }

    return List;
}

bool GLSLEdit::listHasString(QStringList list, QString string)
{
    QStringList::Iterator It = list.begin();
    while(It != list.end())
    {
        if(*It == string)return true;
        It++;
    }

    return false;
}

void GLSLEdit::setShaderName(const QString &name)
{
    this->shaderName = name;
}

const QString GLSLEdit::getShaderName() const
{
    return this->shaderName;
}

const QString GLSLEdit::getShaderSource()
{
    return  this->matScriptFilename.section("/", -1);
}

void GLSLEdit::clearData()
{

    Ogre::GpuProgramPtr program;
    if (!this->shaderName.isEmpty()) {
        if(this->isModified()) {
            this->saveModified();
        }
        program = Ogre::GpuProgramManager::getSingletonPtr()->getByName(shaderName.toStdString());
        program->setSourceFile(getShaderSource().toStdString());
        program->reload();
    }
    this->clear();
    this->shaderName = "";
}

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

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtCore>
#include <QKeyEvent>
#include <QMessageBox>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerproperties.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qsciapis.h>
#include <QDir>
#include <QApplication>


#include <Qsci/qscilexer.h>
class TextEdit : public QsciScintilla
{
Q_OBJECT
public:
    TextEdit(QWidget *pard = 0);
    virtual ~TextEdit();
    void setSyntaxHighlighter();
    QString syntaxHighlighter();
    void openFile(const QString& filename);
    void saveFile();
    QString matScriptFilename;

private:
    void initSettings();
    QsciLexer *lexer;
    QString styleSyntax;
    QFont defaultFont;
    QsciAPIs *apis;
protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // TEXTEDIT_H

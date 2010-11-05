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

#ifndef CgEdit_H
#define CgEdit_H

#include <QtCore>
#include <QKeyEvent>
#include <QMessageBox>
#include <Qsci/qsciscintilla.h>

#include <Qsci/qscilexer.h>
#include <Qsci/qsciapis.h>
#include <QDir>
#include <QApplication>
#include <vector>

#include "Lexers/CgLexer.h"

class CgEdit : public QsciScintilla
{
Q_OBJECT
public:QStringList scan();
    CgEdit(QWidget *pard = 0);
    virtual ~CgEdit();
    void setSyntaxHighlighter();
    QString syntaxHighlighter();
    void openFile(const QString& filename);
    QString matScriptFilename;
    const QString getShaderName() const;
    void setShaderName(const QString &name);
    const QString getShaderSource();
    void clearData();
private:
    void initSettings();
    bool listHasString(QStringList list, QString string);
    QsciLexer *lexer;
    QString styleSyntax;
    QFont defaultFont;
    QsciAPIs *apis;
    QString shaderName;

    QStringList TYPES;
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:

};

// structures for holding the cg programs
/*struct Structure
{
    QString name;
    struct Parameters
    {
        QString type;
        QString name;
        QString passtype;
    };

    vector<Parameters> parameters;
};*/

#endif // CgEdit_H

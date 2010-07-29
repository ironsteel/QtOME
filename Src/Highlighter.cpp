/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "Highlighter.h"

//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkGreen);
    keywordFormat.setFontWeight(QFont::Bold);
    QRegExp ogreMaterialKeywords("\\b(abstract|material|pass|technique|texture_unit|vertex_program|fragment_program|vertex_program_ref|fragment_program_ref)\\b");
    rule.pattern = ogreMaterialKeywords;
    rule.format = keywordFormat;
    highlightingRules.append(rule);



    ogreMaterialVariablesFormat.setForeground(Qt::darkYellow);
    ogreMaterialVariablesFormat.setFontWeight(QFont::Normal);
    QRegExp ogreMaterialVariables("\\b(ambient|diffuse|specular|emissive|scene_blend|depth_write|depth_check|depth_writedepth_func|depth_bias|cull_hardware|cull_software|lighting|shading|fog_override|colour_write|max_lights|iteration)\\b");
    rule.pattern = ogreMaterialVariables;
    rule.format = ogreMaterialVariablesFormat;
    highlightingRules.append(rule);

    ogreMaterialVariables = QRegExp("\\b(texture|source|anim_texture|cubic_texture|tex_coord_set|tex_address_mode|filtering|max_anisotropy|colour_op|alpha_rejection|colour_op_ex|colour_op_multipass_fallback|alpha_op_ex|env_map|scroll|scroll_anim|rotate|rotate_anim|scale|wave_xform)\\b");
    rule.pattern = ogreMaterialVariables;
    rule.format = ogreMaterialVariablesFormat;
    highlightingRules.append(rule);

    ogreMaterialVariables = QRegExp("\\b(syntax|entry_point|profiles|target|param_named|param_named_auto)\\b");
    rule.pattern = ogreMaterialVariables;
    rule.format = ogreMaterialVariablesFormat;
    highlightingRules.append(rule);

    ogreMaterialValuesFormat.setForeground(Qt::red);
    ogreMaterialValuesFormat.setFontWeight(QFont::Normal);
    QRegExp ogreMaterialValues("\\b(on|off|true|false)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(add|modulate|alpha_blend|clamp|one|zero|dest_colour|src_colour|one_minus_dest_colour|one_minus_src_colour|dest_alpha)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(sc_alpha|one_minus_dest_alpha|one_minus_src_alpha|always_fail|always_pass|less|less_equal|equal|not_equal|greater_equal|greater|clockwise|anticlockwise|none)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(back|front|flat|gouraud|phong|linear|exp|exp2|once|once_per_light|point directional|spot)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(1d|2d|cubic|combinedUVW|separateUV|wrap|clamValues|mirrorTexture|bilinear|trilinear|anisotropic|replace)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(source1|source2|modulate|modulate_x2|modulate_x4|add_signed|add_smooth|subtract|blend_diffuse_alpha|blend_texture_alpha|blend_current_alpha)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(blend_manual|src_current|src_texture|src_diffuse|src_specular|src_manual|spherical|planar|cubic_reflection|cubic_normal|scroll_x|scroll_y)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(scale_x|scale_y|sine|triangle|square|sawtooth|inverse_sawtooth|shininess)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);

    ogreMaterialValues = QRegExp("\\b(asm|cg|hlsl|vs_1_1|vs_2_0|vs_2_x|vs_3_0|arbvp1|arbfp1|fp20|ps_1_1|ps_1_2|ps_1_3|ps_1_4|ps_3_0|ps_3_x)\\b");
    rule.pattern = ogreMaterialValues;
    rule.format = ogreMaterialValuesFormat;
    highlightingRules.append(rule);







    digitFormat.setFontWeight(QFont::Bold);
    digitFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = digitFormat;
    highlightingRules.append(rule);


    singleLineCommentFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
/*
    multiLineCommentFormat.setForeground(Qt::red);
//! [3]

//! [4]
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//! [4]

//! [5]
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
//! [5]

//! [6]*/
    //commentStartExpression = QRegExp("/\\*");
    //commentEndExpression = QRegExp("\\*/");
}



void Highlighter::highlightBlock(const QString &text)
{


    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }



//setCurrentBlockState(0);



    /*int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);



        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);*/
}


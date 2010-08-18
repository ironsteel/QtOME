#include "CgLexer.h"

CgLexer::CgLexer(QObject *parent)
        :QsciLexerCPP(parent)
{
    this->setColor(Qt::green, 16);

}
CgLexer::~CgLexer()
{
}

const char *CgLexer::language() const
{
    return "cg";
}

QString CgLexer::description(int ) const
{
    return QString("no Style");
}

const char *CgLexer::keywords(int set) const
{
    if (set == 1)
            return "in out inout struct";
    if (set == 2)
        return "float float1x1 float2x2 float3x3 float4x4 int float2 float3 float4 TEXCOORD0 TEXCOORD1 TEXCOORD2 COLOR0";
    return 0;
}

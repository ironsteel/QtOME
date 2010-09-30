#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

#include <OGRE/Ogre.h>
#include <QStringList>
#include <QString>
#include <QMap>

class MaterialManager
{
public:
    MaterialManager();
    QStringList getMaterialList(const QString & Path);
    QString     getFileName(const QString& Material);

private:
    std::vector<Ogre::Material*>   mats;
    Ogre::MaterialPtr              currentMaterial;
    int                            count;
    QMap<QString,QString>          fileNames;

};

#endif // MATERIALMANAGER_HPP

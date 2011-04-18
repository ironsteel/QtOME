#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

#include <OGRE/Ogre.h>
#include <QStringList>
#include <QString>
#include <QMap>
#include <OGRE/OgreSingleton.h>

class MaterialManager : public Ogre::Singleton<MaterialManager>
{
public:
    MaterialManager();
    QStringList getMaterialList(const QString & Path);
    QString     getFileName(const QString& Material);
    QString     getWorkDir();

private:
    std::vector<Ogre::Material*>   mats;
    Ogre::MaterialPtr              currentMaterial;
    int                            count;
    QMap<QString,QString>          fileNames;
    QString                        workDir;

};

#endif // MATERIALMANAGER_HPP

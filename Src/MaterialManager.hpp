#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

#include <OGRE/Ogre.h>
#include <QStringList>
#include <QString>

class MaterialManager
{
public:
    MaterialManager();
    QStringList getMaterialList();
private:
    std::vector<Ogre::Material*>   mats;
    Ogre::MaterialPtr              currentMaterial;
    int                            count;
};

#endif // MATERIALMANAGER_HPP

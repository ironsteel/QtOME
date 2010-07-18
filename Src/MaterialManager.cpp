#include "MaterialManager.hpp"

MaterialManager::MaterialManager()
{
    count = 0;
}

QStringList MaterialManager::getMaterialList()
{
    QStringList       list;
    QString           name;
    Ogre::MaterialPtr ptr;

    Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingletonPtr()->getResourceIterator();
    while (materialIterator.hasMoreElements())
    {
        count++;
        ptr = (static_cast<Ogre::MaterialPtr>(materialIterator.peekNextValue()));
        mats.push_back(ptr.getPointer());
        list.push_back(name.fromStdString(mats[mats.size()-1]->getName()));
        materialIterator.moveNext();
    }

    return list;
}


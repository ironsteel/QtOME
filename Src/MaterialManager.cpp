#include "MaterialManager.hpp"

MaterialManager::MaterialManager()
{
    count = 0;
}

QStringList MaterialManager::getMaterialList(const QString & Path)
{
    QStringList       list;
    QString           name;
    Ogre::MaterialPtr ptr;


    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Path.toStdString() ,"FileSystem","Mats");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Mats");

    Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingletonPtr()->getResourceIterator();
    while (materialIterator.hasMoreElements())
    {
        count++;
        ptr = (static_cast<Ogre::MaterialPtr>(materialIterator.peekNextValue()));
        mats.push_back(ptr.getPointer());
        if(!ptr.getPointer()->getOrigin().empty())
        {

            list.push_back(name.fromStdString(mats[mats.size()-1]->getName()));
            fileNames.insert(name.fromStdString(mats[mats.size()-1]->getName()), Path + '/' + ptr.getPointer()->getOrigin().c_str());
        }
        materialIterator.moveNext();

    }

    return list;
}

QString MaterialManager::getFileName(const QString &Material)
{
    return fileNames[Material];
    //return QString(fileNames.size());
}

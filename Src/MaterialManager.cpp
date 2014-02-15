#include "MaterialManager.hpp"

template<> MaterialManager* Ogre::Singleton<MaterialManager>::msSingleton = 0;

MaterialManager::MaterialManager()
{
    count = 0;
}

QStringList MaterialManager::getMaterialList(const QString & Path)
{
    QStringList       list;
    QString           name;
    Ogre::MaterialPtr ptr;
    workDir = Path + '/';

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Path.toStdString() ,"FileSystem","Mats");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Mats");
    Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingletonPtr()->getResourceIterator();
    while (materialIterator.hasMoreElements())
    {
        count++;
        ptr = materialIterator.peekNextValue().staticCast<Ogre::Material>();
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
}

QString MaterialManager::getWorkDir()
{
    return workDir;
}

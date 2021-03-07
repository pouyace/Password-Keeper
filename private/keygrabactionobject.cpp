#include "keygrabactionobject.h"
#include "keygrabaction.h"
#include <QAction>

KeyGrabActionObject::KeyGrabActionObject(QAction *parentAction, KeyGrabAction *parentGrabber, const QString &name, const Qt::CaseSensitivity &caseSensivity,ActionMethod method)
    :QObject(parentAction)
    ,action(parentAction)
    ,parentGrabber(parentGrabber)
    ,name(name)
    ,caseSensivity(caseSensivity)
    ,actionMethod(method)
{

}

KeyGrabActionObject::~KeyGrabActionObject()
{
    if(parentGrabber){
        parentGrabber->removeGrabAction(name);
    }
}

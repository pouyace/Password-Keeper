#ifndef KEYGRABACTIONOBJECT_H
#define KEYGRABACTIONOBJECT_H

#include <QObject>
class QAction;
class KeyGrabAction;

class KeyGrabActionObject:public QObject
{
    Q_OBJECT
    friend class KeyGrabAction;
    friend class KeyGrabActionPrivate;
    typedef void(QAction::* ActionMethod)(void);
public:
    KeyGrabActionObject(QAction *parentAction,KeyGrabAction *parentGrabber,const QString &name,const Qt::CaseSensitivity &caseSensivity,ActionMethod method);
    virtual ~KeyGrabActionObject() override;
private:
    QAction *action = nullptr;
    KeyGrabAction *parentGrabber = nullptr;
    QString name;
    Qt::CaseSensitivity caseSensivity;
    ActionMethod actionMethod;
};

#endif // KEYGRABACTIONOBJECT_H

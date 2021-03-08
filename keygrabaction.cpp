#include "keygrabaction.h"
#include <QTimer>
#include <QString>
#include <QKeyEvent>
#include <QDebug>
#include <QMap>
#include <QMapIterator>
#include <QElapsedTimer>
#include "private/keygrabactionobject.h"

class KeyGrabActionPrivate{
    friend class KeyGrabAction;

    QElapsedTimer timer;
    int maxLength = 50;
    int waitTime = 1000;
    QString buffer;
    QMap<QString,KeyGrabActionObject*> actionNames;
    KeyGrabAction *parent;

public:
    KeyGrabActionPrivate(KeyGrabAction *parent):parent(parent){}
    ~KeyGrabActionPrivate(){
        QMapIterator<QString,KeyGrabActionObject*> mItr(actionNames);
        while(mItr.hasNext()){
            mItr.next();
            KeyGrabActionObject *gValue = mItr.value();
            if(gValue->parentGrabber == parent){
                gValue->parentGrabber = nullptr;
                gValue->deleteLater();
            }
        }
    }
    void updateMaxLength(const QString &newActionName, bool removedItem){
        if(removedItem){
            if(newActionName.length() < maxLength)
                return;
            QMapIterator<QString,KeyGrabActionObject*> mItr(actionNames);
            int mMaxLength = -1;
            while(mItr.hasNext()){
                mItr.next();
                if(mItr.key().length() > mMaxLength){
                    mMaxLength = mItr.key().length();
                }
            }
            maxLength = mMaxLength;
        }else{
            if(newActionName.length() > maxLength){
                maxLength = newActionName.length();
            }
        }
    }
};

KeyGrabAction::KeyGrabAction()
    :d(new KeyGrabActionPrivate(this))
{
    d->timer.start();
}

KeyGrabAction::~KeyGrabAction()
{
    delete d;
}

void KeyGrabAction::addGrabAction(const QString &name, Qt::CaseSensitivity caseSensivity, QAction *action, ActionMethod actionMethod)
{
    QString lowerName = name.toLower();
    if(!d->actionNames.contains(lowerName)){
        KeyGrabActionObject *tempObject = new KeyGrabActionObject(action,this,name,caseSensivity,actionMethod);
        d->actionNames.insert(lowerName,tempObject);
        d->updateMaxLength(lowerName,false);
    }else{
        qDebug() << Q_FUNC_INFO << name << "already exists";
    }
}

void KeyGrabAction::removeGrabAction(const QString &actionName)
{
    QString lowerName = actionName.toLower();
    if(d->actionNames.contains(lowerName)){
        KeyGrabActionObject *tempObject = d->actionNames.value(lowerName);
        d->updateMaxLength(lowerName,true);
        d->actionNames.remove(lowerName);
        tempObject->deleteLater();
    }
}

void KeyGrabAction::setMaximumWaitTime(const int &waitTime)
{
    d->waitTime = waitTime;
}

int KeyGrabAction::maximumWaitTime() const
{
    return d->waitTime;
}

void KeyGrabAction::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<event->text();
    if(d->timer.elapsed() > d->waitTime){
        d->buffer = "";
    }
    d->timer.restart();
    if(d->buffer.length() == d->maxLength){
        d->buffer = d->buffer.left(d->maxLength - 1);
    }
    d->buffer.append(event->text());
    QString lowerBuffer = d->buffer.toLower();
    if(d->actionNames.contains(lowerBuffer)){
        KeyGrabActionObject *actionObject = d->actionNames.value(lowerBuffer);
        if(!actionObject->name.compare(d->buffer,actionObject->caseSensivity)){
            QAction *tempAction = actionObject->action;
            ActionMethod aMethod = actionObject->actionMethod;
            d->buffer = "";
            (tempAction->*aMethod)();
        }
    }
}



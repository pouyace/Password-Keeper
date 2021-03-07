#ifndef KEYGRABACTION_H
#define KEYGRABACTION_H
#include <QAction>

class QKeyEvent;
class KeyGrabActionPrivate;

#define KEYGRABACTION \
    protected: \
    virtual void keyReleaseEvent(QKeyEvent *event) override{KeyGrabAction::keyReleaseEvent(event);} \
    private:
/**
 * @brief The KeyGrabAction class
 *  The class is used to trigger an action using words input by keyboard without showing any widget.
 *  Action, action name and the pointer of the function we want to call will be added to module.
 *  action name can be both case sensitive and case insensitive.
 *  buffer size will be updated automatically
 *  letters should be entered sequentially.If the interval exceeds maximum wait time the buffer will be emptied out
 *  Maximum wait time can be set
 */
class KeyGrabAction
{
public:
    typedef void(QAction::* ActionMethod)(void);
    KeyGrabAction();
    ~KeyGrabAction();
    void addGrabAction(const QString &name,Qt::CaseSensitivity caseSensivity,QAction* action,ActionMethod actionMethod = &QAction::toggle);
    void removeGrabAction(const QString &actionName);
    void setMaximumWaitTime(const int &waitTime = 1000);
    int maximumWaitTime() const;

protected:
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    KeyGrabActionPrivate *d = nullptr;
};

#endif // KEYGRABACTION_H

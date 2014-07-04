#ifndef QJOYSTICK_H
#define QJOYSTICK_H

//Original by Dante Sanchez (dante.a.sanchez@gmail.com)
//Modifications (hat, toggle, re-enumeration) by Chris Konstad (chriskon149@gmail.com)

#include <QObject>
#include <QString>
#include <QList>
#include "qjoystickinterface.h"

#include <SDL/SDL.h>

class QJoystick: public QJoystickInterface
{
    Q_OBJECT
    public:
        QJoystick();
        virtual ~QJoystick();

        public slots:
        virtual int reenumerateDevices(); 

        virtual QString name() const;

        virtual int numJoysticks() const;

        virtual int numAxes() const;

        virtual int numHats() const;

        virtual int numButtons() const;

    signals:

    protected:
        virtual void init();

    private slots:
        virtual void getData();
        HatDirection mapHatDirection(int sdldir);

    private:
        SDL_Joystick *mJoystick;
};

#endif // QJOYSTICK_H

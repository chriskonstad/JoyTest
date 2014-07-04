#ifndef QJOYSTICKINTERFACE_H
#define QJOYSTICKINTERFACE_H

//Original by Dante Sanchez (dante.a.sanchez@gmail.com)
//Modifications (hat, toggle, re-enumeration) by Chris Konstad (chriskon149@gmail.com)

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QTimer>

#define POLL_INTERVAL 40

class QJoystickInterface : public QObject
{
    Q_OBJECT
    public:
        QJoystickInterface();
        virtual ~QJoystickInterface();

        enum HatDirection { Center, Up, RightUp, Right, RightDown, Down, LeftDown, Left, LeftUp };

        public slots:
        /*!
         * Set the current joystick.
         * This will select the joystick with ID
         * jsNumber as the current joystick.
        */
        bool currentJoystick(int id);

        int currentJoystick() const;

        /*!
         * Reenumerates the connected joysticks.
         * This restarts SDL's joystick subsystem
         * which can cause significant lag on some
         * systems.  It is the only way (at this time)
         * to rescan the system for newly attached
         * or detatched devices. It returns the number
         * of detected joysticks.
         */
        virtual int reenumerateDevices() = 0; 

        virtual QString name() const = 0;

        virtual int numJoysticks() const = 0;

        virtual int numAxes() const = 0;

        virtual int numHats() const = 0;

        virtual int numButtons() const = 0;

        void bilinearEnable(bool enable);

        bool bilinearEnabled() const;

        void bilinearConstant(double k);

        double bilinearConstant() const;

        bool deadzone(int axisId, int size);

        int deadzone(int axisId) const;

        //TODO: Add bilinear code


signals:
        /*!
         * Signal emitted when button is pressed.
         * Pressed is defined as off->on
         */
        void buttonPressed(int button);

        /*!
         * Signal emitted when button is released.
         * Released is defined as on->off
         */
        void buttonReleased(int button);

        /*!
         * Signal emitted when button is toggled.
         * Toggled is defined as going from off->on->off
         */
        void buttonToggled(int button, bool state);

        /*!
         * Signal emitted when hat is pressed.
         * Pressed is defined as off->on
         */
        void hatPressed(int hat, int dir);

        /*!
         * Signal emitted when hat is released.
         * Released is defined as on->off
         */
        void hatReleased(int hat, int dir);

        /*!
         * Signal emitted when hat is toggled.
         * Toggled is defined as going from off->on->off
         */
        void hatToggled(int hat, int dir, bool state);

        /*!
         * Signal emitted on a timer.
         * A timer is used because the axes are analog,
         * and this API shouldn't flood the event processing
         * loop with axesUpdated signals
         */
        void axesUpdated(QList<int> values);

    protected:
        virtual void init();
        QList<bool> mButtonsCurrent;
        QList<QMap<int, bool> > mHatsCurrent;
        QList<int> mAxesCurrent;

        QList<bool> mButtonsPrevious;
        QList<QMap<int, bool> > mHatsPrevious;

        QList<bool> mButtonsToggled;
        QList<QMap<int, bool> > mHatsToggled;

    private slots:
        virtual void getData() = 0;

    private:
        int mCurrentId;

        bool mBilinearEnabled;
        double mBilinearConstant;

        QList<int> mDeadzones;

        QTimer mTimer;
};

#endif // QJOYSTICK_H

#include "qjoystickinterface.h"
#include <QtGlobal>
#include <QtDebug>

QJoystickInterface::QJoystickInterface()
{
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(getData()));
    mTimer.start(POLL_INTERVAL);
}

QJoystickInterface::~QJoystickInterface()
{

}

bool QJoystickInterface::currentJoystick(const int id)
{
    bool ret = false;
    if(0 <= id && id < numJoysticks())
    {
        mCurrentId = id;
        init(); //update js model
        ret = true;
    }

    return ret;
}

int QJoystickInterface::currentJoystick() const
{
    return mCurrentId;
}

void QJoystickInterface::bilinearEnable(bool enable)
{
    mBilinearEnabled = enable;
}

bool QJoystickInterface::bilinearEnabled() const
{
    return mBilinearEnabled;
}

void QJoystickInterface::bilinearConstant(double k)
{
    mBilinearConstant = k;
}

double QJoystickInterface::bilinearConstant() const
{
    return mBilinearConstant;
}

bool QJoystickInterface::deadzone(int axisId, int size)
{
    bool ret = false;
    if(0 <= axisId && axisId < mDeadzones.count() &&
            0 <= size && size <= 32767)
    {
        mDeadzones[axisId] = size;
        ret = true;
    }

    return ret;
}

int QJoystickInterface::deadzone(int axisId) const
{
    int ret = -1;
    if(0 <= axisId && axisId < mDeadzones.count())
    {
        ret = mDeadzones[axisId];
    }

    return ret;
}

void QJoystickInterface::init()
{
    //Reset axes information
    mDeadzones.clear();
    mAxesCurrent.clear();
    for(int i=0; i<numAxes(); i++)
    {
        mDeadzones.append(0);
        mAxesCurrent.append(0);
    }

    //Reset button information
    mButtonsCurrent.clear();
    mButtonsPrevious.clear();
    mButtonsToggled.clear();
    for(int i=0; i<numButtons(); i++)
    {
        mButtonsCurrent.append(false);
        mButtonsPrevious.append(false);
        mButtonsToggled.append(false);
    }

    //Reset hat information
    mHatsCurrent.clear();
    mHatsPrevious.clear();
    mHatsToggled.clear();
    for(int i=0; i<numHats(); i++)
    {
        QMap<int, bool> temp;
        mHatsCurrent.append(temp);
        mHatsPrevious.append(temp);
        mHatsToggled.append(temp);
    }

    mBilinearEnabled = false;
    mBilinearConstant = 1;  //TODO MIGHT BE 0
}

void QJoystickInterface::processDeadzones()
{
    for(int i=0; i<mAxesCurrent.count(); i++)
    {
        int dz = mDeadzones[i];
        if(qAbs(mAxesCurrent[i]) <= dz)
        {
            mAxesCurrent[i] = 0;
        }
        else
        {
            const int posMax = 32767;
            const int negMax = -32768;
            double slope;
            int b;
            if(mAxesCurrent[i] > 0)
            {
                slope = (double)posMax/(posMax-dz);
                b = -1 * slope * dz;
            }
            else
            {
                slope = (double)negMax/(negMax+dz);
                b = slope * dz;
            }

            //Calculate the new value
            mAxesCurrent[i] = (int)(mAxesCurrent[i] * slope) + b;
        }
    }
}

void QJoystickInterface::processBilinear()
{
    //TODO: Implement
}

#include "pxt.h"
#include "AccelerometerLogger.h"

// MICROBIT_OK
// https://github.com/lancaster-university/microbit-dal/blob/master/inc/core/ErrorNo.h

// accelerometer
// https://lancaster-university.github.io/microbit-docs/ubit/accelerometer/

/**
 * Constructor.
 * Create a representation of the AccelerometerLogger
 * @param _accelerometer An instance of MicroBitAccelerometer.
 */
AccelerometerLogger::AccelerometerLogger(
#if MICROBIT_CODAL
    codal::Accelerometer &_accelerometer
#else  // MICROBIT_CODAL
    MicroBitAccelerometer &_accelerometer
#endif // MICROBIT_CODAL
    ) : accelerometer(_accelerometer)
{
    logging = false;
}

/**
 * Accelerometer update callback
 */
void AccelerometerLogger::accelerometerUpdate(MicroBitEvent e)
{
    if (logging)
    {
        // logging
        accelerometer.getX();
        accelerometer.getY();
        accelerometer.getZ();
    }
}

/**
 * Clear logging data, and set the sample rate of the accelerometer to the specified value (in ms).
 * @param period the requested time between samples, in milliseconds.
 */
int AccelerometerLogger::reset(int period)
{

#if MICROBIT_CODAL

    stop();

    // clear logging

    // set the sample rate
    return accelerometer.setPeriod(period);

#else // MICROBIT_CODAL

    // v1 - not supported
    return MICROBIT_NOT_SUPPORTED;

#endif // MICROBIT_CODAL
}

/**
 * Start logging.
 */
int AccelerometerLogger::start()
{

#if MICROBIT_CODAL

    if (logging)
    {
        return MICROBIT_OK;
    }
    // start
    logging = true;
    EventModel::defaultEventBus->listen(MICROBIT_ID_ACCELEROMETER, MICROBIT_ACCELEROMETER_EVT_DATA_UPDATE, this, &AccelerometerLogger::accelerometerUpdate, MESSAGE_BUS_LISTENER_IMMEDIATE);

#else // MICROBIT_CODAL

    // v1 - not supported
    return MICROBIT_NOT_SUPPORTED;

#endif // MICROBIT_CODAL
}

/**
 * Stop logging.
 */
int AccelerometerLogger::stop()
{

#if MICROBIT_CODAL
    if (!logging)
    {
        return MICROBIT_OK;
    }

    // stop
    logging = false;
    EventModel::defaultEventBus->ignore(MICROBIT_ID_ACCELEROMETER, MICROBIT_ACCELEROMETER_EVT_DATA_UPDATE, this, &AccelerometerLogger::accelerometerUpdate);

#else // MICROBIT_CODAL

    // v1 - not supported
    return MICROBIT_NOT_SUPPORTED;

#endif // MICROBIT_CODAL
}

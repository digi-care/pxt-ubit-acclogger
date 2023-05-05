#ifndef ACCELEROMETER_LOGGER_H
#define ACCELEROMETER_LOGGER_H

#include "pxt.h"

class AccelerometerLogger
{
public:
#if MICROBIT_CODAL
    /**
     * Constructor.
     * Create a representation of the AccelerometerLogger
     * @param _accelerometer An instance of MicroBitAccelerometer.
     */
    AccelerometerLogger(codal::Accelerometer &_accelerometer);

#else // MICROBIT_CODAL
    /**
     * Constructor.
     * Create a representation of the AccelerometerLogger
     * @param _accelerometer An instance of MicroBitAccelerometer.
     */
    AccelerometerLogger(MicroBitAccelerometer &_accelerometer);

#endif // MICROBIT_CODAL

private:
    /**
     * Accelerometer update callback
     */
    void accelerometerUpdate(MicroBitEvent e);

#if MICROBIT_CODAL
    codal::Accelerometer &accelerometer;
#else  // MICROBIT_CODAL
    MicroBitAccelerometer &accelerometer;
#endif // MICROBIT_CODAL

    bool logging;

public:
    /**
     * Clear logging data, and set the sample rate of the accelerometer to the specified value (in ms).
     * @param period the requested time between samples, in milliseconds.
     */
    int reset(int period);

    /**
     * Start logging.
     */
    int start();

    /**
     * Stop logging.
     */
    int stop();
};

#endif // #ifndef ACCELEROMETER_LOGGER_H
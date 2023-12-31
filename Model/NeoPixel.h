#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <ws2811/ws2811.h>
#include <cmath>

class NeoPixel : public QObject {
Q_OBJECT

private:
    static const int GPIO_PIN = 18;
    static const int LED_COUNT = 16;
    static const int BASE_BRIGHTNESS = 255;
    static const int TARGET_FREQ = WS2811_TARGET_FREQ;
    static const int STRIP_TYPE = WS2811_STRIP_GRB;
    static const int DMA = 10;

    ws2811_t ledstring;

    int min;
    int max;
    float rpm = 0;
    float battery = 0;
    float coolant = 0;

    bool startup = true;
    bool spark = false;

    size_t n = LED_COUNT-1;

    void fill(int color);
    void startup_animation();

public:
    NeoPixel() = delete;
    NeoPixel(int min, int max) : min(min), max(max) {
        ledstring = {
            .freq = TARGET_FREQ,
            .dmanum = DMA,
            .channel = {
                {
                    .gpionum = GPIO_PIN,
                    .invert = 0,
                    .count = LED_COUNT,
                    .strip_type = STRIP_TYPE,
                    .brightness = BASE_BRIGHTNESS,
                }
            }
        };

        ws2811_return_t ret;
        if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
            qWarning() << "NeoPixel: failed to start " << ws2811_get_return_t_str(ret) << '\n';
            exit(1);
        }
    }

public slots:
    void start();
    void rpmReceived(int value);
    void batteryReceived(float value);
    void coolantReceived(float value);
    void sparkCutReceived();
};

#endif // NEOPIXEL_H

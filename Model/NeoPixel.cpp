#include "NeoPixel.h"

using namespace std;

void NeoPixel::fill(int color) {
    for(size_t i=0; i<LED_COUNT; i++) {
        ledstring.channel[0].leds[i] = color;
    }
    ws2811_render(&ledstring);
}

void NeoPixel::startup_animation() {
    for(size_t i=0; i<LED_COUNT / 2; i++) {
        ledstring.channel[0].leds[i] = 0xFFFFFF;
        ledstring.channel[0].leds[n-i] = 0xFFFFFF;
        ws2811_render(&ledstring);
        QThread::msleep(80);
    }

    QThread::msleep(500);

    auto &currentBrightness = ledstring.channel[0].brightness;
    while(0 < currentBrightness) {
        currentBrightness -= 1;
        ws2811_render(&ledstring);
        QThread::msleep(4);
    }

    fill(0);
    currentBrightness = 255;
    startup = false;
}


void NeoPixel::start() {
    startup_animation();

    while(true) {
        QCoreApplication::processEvents();
        QThread::msleep(17);
        if(startup) continue;

        ledstring.channel[0].brightness = 255;

        if(rpm == 0 && spark) {
            fill(0x008080);
            QThread::msleep(100);
            auto &currentBrightness = ledstring.channel[0].brightness;
            while(0 < currentBrightness) {
                currentBrightness -= 1;
                ws2811_render(&ledstring);
                QThread::msleep(1);
            }
            currentBrightness = 255;
            spark = false;
        }

        if(230 <= coolant) { fill(0xFF0000); continue; }
        if(220 <= coolant) { fill(0xFFA500); continue; }
        if(rpm == 0 && battery <= 12.2) { fill(0xFFA500); continue; }

        float percentage = (rpm - min) / (max - min);
        int active_pixels = ceil(percentage * 6);

        if (active_pixels <= 0) { fill(0); continue; }

        for (int i = 0; i < active_pixels; ++i) {
            if (i < 3) {
                ledstring.channel[0].leds[i] = 0xFF0000;
                ledstring.channel[0].leds[n-i] = 0xFF0000;
            } else if (i < 6) {
                ledstring.channel[0].leds[i] = 0x0000FF;
                ledstring.channel[0].leds[n-i] = 0x0000FF;
            } else if (i < 8) {
                ledstring.channel[0].leds[i] = 0x00FF00;
                ledstring.channel[0].leds[n-i] = 0x00FF00;
            }
        }

        ws2811_render(&ledstring);
    }
}

void NeoPixel::rpmReceived(int value) {
    rpm = value;
}

void NeoPixel::batteryReceived(float value) {
    battery = value;
}

void NeoPixel::coolantReceived(float value) {
    coolant = value;
}

void NeoPixel::sparkCutReceived() {
    spark = true;
}

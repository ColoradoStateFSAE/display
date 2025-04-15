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
	const int RED = 0xFF0000;
	const int GREEN = 0x00FF00;
	const int BLUE = 0x0000FF;
	const int YELLOW = 0xFFA500;
	const int BLACK = 0x000000;
	const int WHITE = 0xFFFFFF;
	
	static const int GPIO_PIN = 18;
	static const int LED_COUNT = 16;
	static const int ERROR_LED_COUNT = 4;
	static const int SHIFT_LED_COUNT = 12;
	static const int BASE_BRIGHTNESS = 255;
	static const int TARGET_FREQ = WS2811_TARGET_FREQ;
	static const int STRIP_TYPE = WS2811_STRIP_GRB;
	static const int DMA = 10;

	ws2811_t ledString;

	float min;
	float max;
	float rpm = 0;
	int gear = 0;
	float battery = 0;
	float coolant = 0;
	int estop = 0;
	bool ecuOffline = false;
	bool shiftingSystemOffline = false;
	bool steeringWheelOffline = false;
	int brightness = BASE_BRIGHTNESS;
	int targetBrightness = 255;

	size_t n = LED_COUNT-1;

	void fill(int color);
	void fillError(int color);
	void fillShift(int active_pixels);
	void startup_animation();

public:
	enum State {
		SHIFT_LIGHTS,
		CRITICAL
	};
	
	State state = SHIFT_LIGHTS;
	
	NeoPixel() = delete;
	NeoPixel(int min, int max);

public slots:
	void start();
	bool warning();
	bool critical();
	void rpmReceived(int value);
	void gearReceived(int value);
	void batteryReceived(float value);
	void coolantReceived(float value);
	void brightnessReceived(int value);
	void estopReceived(int value);
	void shiftingReceived(bool state);
	void shiftControllerReceived(bool state);
	void ecuReceived(bool state);
};

#endif // NEOPIXEL_H

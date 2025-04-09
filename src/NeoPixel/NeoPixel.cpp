#include "NeoPixel.h"

using namespace std;

NeoPixel::NeoPixel(int min, int max) : min(min), max(max) {
	ledString = {
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
	if ((ret = ws2811_init(&ledString)) != WS2811_SUCCESS) {
		qWarning() << "NeoPixel: failed to start " << ws2811_get_return_t_str(ret) << '\n';
		exit(1);
	}
}

void NeoPixel::fill(int color) {
	for(size_t i=0; i<LED_COUNT; i++) {
		ledString.channel[0].leds[i] = color;
	}
	ws2811_render(&ledString);
}

void NeoPixel::fillError(int color) {
	for (size_t i=0; i<ERROR_LED_COUNT; i++){
		ledString.channel[0].leds[i] = color;
	}
}

void NeoPixel::fillShift(int active_pixels){
	for (int i = ERROR_LED_COUNT; i < active_pixels + ERROR_LED_COUNT; ++i){
		if (i > 0) {
			ledString.channel[0].leds[i] = RED;
		}
		if (i > 9) {
			for (int i = ERROR_LED_COUNT + SHIFT_LED_COUNT / 2; i < LED_COUNT; ++i){
				ledString.channel[0].leds[i] = BLUE;
			}
		}
	}
}

void NeoPixel::startup_animation() {
	for(size_t i=0; i<LED_COUNT / 2; i++) {
		ledString.channel[0].leds[i] = WHITE;
		ledString.channel[0].leds[n-i] = WHITE;
		ws2811_render(&ledString);
		QThread::msleep(80);
	}

	QThread::msleep(500);

	auto &currentBrightness = ledString.channel[0].brightness;
	while(0 < currentBrightness) {
		currentBrightness -= 1;
		ws2811_render(&ledString);
		QThread::msleep(4);
	}

	fill(0);
	currentBrightness = targetBrightness;
}

bool NeoPixel::warning() {
	return coolant >= 220 || (battery <= 11.2 && battery > 0);
}

bool NeoPixel::critical() {
	return coolant >= 230;
}

void NeoPixel::start() {
	startup_animation();

	int seed = 0;
	
	while(true) {
		QCoreApplication::processEvents();
		QThread::msleep(32);

		float percentage = (rpm - min) / (max - min);
		int active_pixels = ceil(percentage * 12);

		if(critical()) state = CRITICAL;
		fill(0);

		switch(state) {
			case SHIFT_LIGHTS: {
				if (warning()) {
					fillError(0xFFA500);
				}
				if (active_pixels > 0 && gear != 6) {
					fillShift(active_pixels);
				}
				ws2811_render(&ledString);
				break;
			}

			case CRITICAL: {
				seed ^= 1;
			
				for (int i = seed; i < LED_COUNT; i += 2) {
					if (i >=0) {
						ledString.channel[0].leds[i] = YELLOW;
					}
					if (i > 3) {
						ledString.channel[0].leds[i] = RED;
					}
					if (i > 9) {
						ledString.channel[0].leds[i] = BLUE;
					}
				}
			
				ws2811_render(&ledString);
				if (!critical()) state = SHIFT_LIGHTS;
				QThread::msleep(212);
				break;
			}
		}
	}
}

void NeoPixel::rpmReceived(int value) {
	rpm = value;
}

void NeoPixel::gearReceived(int value) {
	gear = value;
}

void NeoPixel::batteryReceived(float value) {
	battery = value;
}

void NeoPixel::coolantReceived(float value) {	
	coolant = value;
}

void NeoPixel::brightnessReceived(int value) {
	targetBrightness = std::clamp(value, 0, 255);
	ledString.channel[0].brightness = targetBrightness;
	ws2811_render(&ledString);
}
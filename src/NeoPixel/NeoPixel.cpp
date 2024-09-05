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
	currentBrightness = 255;
}

bool NeoPixel::warning() {
	return coolant >= 220 || battery <= 12.2;
	
}

bool NeoPixel::critical() {
	return coolant >= 230;
}


void NeoPixel::start() {
	startup_animation();
	
	while(true) {
		QCoreApplication::processEvents();
		QThread::msleep(32);
		
		fill(0);
		
		if(warning()) state = WARNING;
		if(critical()) state = CRITICAL;
		
		switch(state) {				
			case SHIFT_LIGHTS: {
				float percentage = (rpm - min) / (max - min);
				int active_pixels = ceil(percentage * 6);
				
				if (active_pixels <= 0) break;
				
				for (int i = 0; i < active_pixels; ++i) {
					if (i < 3) {
						ledString.channel[0].leds[i] = RED;
						ledString.channel[0].leds[n-i] = RED;
					} else if (i < 6) {
						ledString.channel[0].leds[i] = BLUE;
						ledString.channel[0].leds[n-i] = BLUE;
					} else if (i < 8) {
						ledString.channel[0].leds[i] = GREEN;
						ledString.channel[0].leds[n-i] = GREEN;
					}
				}
				
				ws2811_render(&ledString);
				break;
			}
				
			case SHIFT_RECEIVED: {
				fill(0x008080);
				QThread::msleep(100);
				auto &currentBrightness = ledString.channel[0].brightness;
				while(0 < currentBrightness) {
					currentBrightness -= 1;
					ws2811_render(&ledString);
					QThread::msleep(1);
				}
				fill(0x000000);
				ws2811_render(&ledString);
				currentBrightness = 255;
				
				state = SHIFT_LIGHTS;
				break;
			}
				
			case WARNING: {
				fill(0xFFA500);
				ws2811_render(&ledString);
				if(!warning()) state = SHIFT_LIGHTS;
				break;
			}
				
			case CRITICAL: {
				fill(0xFF0000);
				ws2811_render(&ledString);
				if(!critical()) state = SHIFT_LIGHTS;
				break;
			}
		}
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

void NeoPixel::shiftReceived() {
	state = SHIFT_RECEIVED;
}

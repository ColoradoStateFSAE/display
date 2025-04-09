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
	
	while(true) {
		QCoreApplication::processEvents();
		QThread::msleep(32);
		
		fill(0);
		
		if(warning()) state = WARNING;
		if(critical()) state = CRITICAL;
		
		switch(state) {	
			int active_pixels;			
			case SHIFT_LIGHTS: {

				if (rpm >= min) {
					active_pixels = 6;
				}
				else if(rpm >= max - (max - min)) {
					active_pixels = 12;
				}
				else {
					active_pixels = 0;
				} 
				
				if (active_pixels <= 0) break;
				
				for (int i = 4; i < active_pixels + 4; ++i) {
					if (i > 0) {
						ledString.channel[0].leds[i] = BLUE;
					} 
					if (i > 9) {
						ledString.channel[0].leds[i] = RED;
					}
				}
				
				ws2811_render(&ledString);
				break;
			
				
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
			default:
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

void NeoPixel::brightnessReceived(int value) {
	targetBrightness = std::clamp(value, 0, 255);
	ledString.channel[0].brightness = targetBrightness;
	ws2811_render(&ledString);
}

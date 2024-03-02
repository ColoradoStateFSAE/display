#include "canutil.h"

namespace canutil {
	unsigned int read_data(QByteArray data, int offset, int size) {
		unsigned value = 0;
		for (int i = offset; i < offset + size; i++) {
			value = value << 8;
			value += data[i];
		}
		return value;
	}

	void construct_data(QByteArray &data, int value, int offset, int size) {
		for (int i = offset + size - 1; i >= offset; i -= 1) {
			data[i] = value % 256;
			value >>= 8;
		}
	}

	int twos_complement(unsigned int value, int size) {
		if (value & (1 << (size - 1))) {
			return -((1 << size) - (value & ((1 << size) - 1)));
		} else {
			return value;
		}
	}
}

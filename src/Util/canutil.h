#ifndef CANUTIL_H
#define CANUTIL_H

#include <QByteArray>

namespace canutil {
	unsigned int read_data(QByteArray data, int offset, int size);
	void construct_data(QByteArray &data, int value, int offset, int size);
	int twos_complement(unsigned int value, int size);
}

#endif // CANUTIL_H

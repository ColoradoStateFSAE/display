#include "ViewModel.h"

using namespace std;

string ViewModel::get_filename() {
    const filesystem::path dir = "/root/log";

    if (!filesystem::exists(dir)) filesystem::create_directory(dir);

    int maxNumber = 0;

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            auto current = stoi(entry.path().filename().string().substr(0, 4));

            if (current > maxNumber) {
                maxNumber = current;
            }
        }
    }

    stringstream fileNumber;
    maxNumber += 1;
    if (maxNumber != 0) {
        fileNumber << setfill('0') << setw(4) << maxNumber;
    } else {
        fileNumber << "0000";
    }

    return fileNumber.str();
}

void ViewModel::frameReceived() {
    while(device->framesAvailable()) {
        const QCanBusFrame frame = device->readFrame();
        int id = frame.frameId();
        QByteArray data = frame.payload();

        const int base_id = 1520;

        if(id == 522) {
            parseSpark(data);
        } else if(id == 1620) {
            parseGear(data);
            lastShiftingSystemReceived = time.elapsed();
        } else if(id == 1520) {
            parseGroup0(data);
            lastEcuReceived = time.elapsed();
        } else if(id == base_id + 1) {
            parseGroup1(data);
        } else if(id == base_id + 2) {
            parseGroup2(data);
        } else if(id == base_id + 3) {
            parseGroup3(data);
        } else if(id == base_id + 31) {
            parseGroup31(data);
        } else if(id == base_id + 43) {
            parseGroup43(data);
        }

        string canFilename = "/root/log/" + filename + "can.txt";
        canFile = ofstream(canFilename, ios::app);

        QString hexString;

        for (const char byte : frame.payload()) {
            hexString.append(QString::number(static_cast<quint8>(byte), 16).rightJustified(2, '0').toUpper() + " ");
        }

        static auto startTime = QDateTime::currentMSecsSinceEpoch();
        double time = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;

        QString formattedTime = QString::number(time, 'f', 3);

        canFile << formattedTime.toStdString() << " " << frame.frameId() << " " << hexString.trimmed().toStdString() << endl;
    }
}

void ViewModel::parseSpark(QByteArray data) {
    if(canutil::read_data(data, 0, 1) == 1 && rpm == 0) {
        emit sparkCutReceived();
    }
}

void ViewModel::parseGear(QByteArray data) {
    int gearValue = data[0];
    gear = gearValue;
}


void ViewModel::parseGroup0(QByteArray data) {
    float rpmValue = canutil::read_data(data, 6, 2);
    rpm = rpmValue;
}

void ViewModel::parseGroup1(QByteArray data) {
    float advanceValue = canutil::read_data(data, 0, 2);
    advanceValue = canutil::twos_complement(advanceValue, 16);
    advanceValue /= 10;
    advance = advanceValue;
}

void ViewModel::parseGroup2(QByteArray data) {
    float coolantValue = canutil::read_data(data, 6, 2);
    coolantValue = canutil::twos_complement(coolantValue, 16);
    coolantValue = coolantValue / 10;
    coolant = coolantValue;
}

void ViewModel::parseGroup3(QByteArray data) {
    float tpsValue = canutil::read_data(data, 0, 2);
    tpsValue = canutil::twos_complement(tpsValue, 16);
    tpsValue /= 10;
    tps = tpsValue;

    float batteryValue = canutil::read_data(data, 2, 2);
    batteryValue = canutil::twos_complement(batteryValue, 16);
    batteryValue /= 10;
    battery = batteryValue;
}

void ViewModel::parseGroup31(QByteArray data) {
    float afrValue = canutil::read_data(data, 0, 1);
    afrValue /= 10;
    afr = afrValue;
}

void ViewModel::parseGroup43(QByteArray data) {
    float syncValue = canutil::read_data(data, 0, 1);
    sync = syncValue;
}

#include "Navigation.h"

using namespace std;

void Navigation::encoderReceived(int value) {
    if(!taskSwitcher) return;

    auto current = tasks[heading][task];
    auto currentId = current->id;
    auto &currentSelected = current->selected;
    auto &currentValue = current->value;

    // If a MenuItem is has been clicked its value will be changed
    if(currentSelected) {
        // Increment the fast amount if the encoder moves more than 2
        if(abs(value) > 2) {
            if (value < 0) {
                value = -current->fast;
            } else {
                value = current->fast;
            }
        }

        // Subtract the the encoder value from the selected MenuItem's value
        currentValue -= value;
        if(currentValue < 0) currentValue = 0;

        bool shiftSelected = currentId == upDelay.id || currentId == downDelay.id || currentId == output.id || currentId == timeout.id;
        bool clutchSelected = currentId == start.id || currentId == end.id || currentId == friction.id;

        bool clutchPositionSelected = currentId == position.id;
        bool autoLaunchSelected = currentId == autoLaunch.id;

        if(shiftSelected) {
            emit sendShiftValues(upDelay.value, downDelay.value, output.value, timeout.value);
        } else if(clutchSelected) {
            emit sendClutchValues(start.value, end.value, friction.value);
        } else if(clutchPositionSelected) {
            emit sendClutchPosition(position.value);
        } else if(autoLaunchSelected) {
            if(1 < currentValue) currentValue = 1;
            emit sendAutoLaunch(autoLaunch.value);
        }
    } else {
        // Do not move the cursor more than 1 position at a time
        if(value > 1) value = 1;
        if(value < 1) value = -1;

        if(task > 0) {
            // Move the cursor between tasks
            size_t difference = static_cast<size_t>(task - value);
            if(difference > tasks[heading].size()-1) return;
            if(task - value < 0) return;
            task -= value;
            emit changeCursor(tasks[heading][task]->id);
        } else {
            // Move the cursor between headings
            size_t difference = static_cast<size_t>(heading - value);
            if(difference > tasks.size()-1) return;
            if(heading - value < 0) return;
            heading -= value;
            emit changeCursor(heading);
        }
    }

    updateMenu();
}

void Navigation::buttonPressReceived() {
    auto current = tasks[heading][task];
    auto currentId = current->id;
    auto &currentSelected = current->selected;

    // Open the task switcher and move the cursor to the exit button
    if(taskSwitcher == false) {
        taskSwitcher = true;
        heading = exitHeading.id;
        emit changeTaskSwitcher(true);

    // Close the task switcher if the exit button is pressed
    } else if(currentId == exitHeading.id) {
        taskSwitcher = false;
        emit changeTaskSwitcher(false);

    // Select the first task from the heading if the button is pressed
    } else if(current->is_heading()) {
        // Special case for the about page
        if(tasks[heading].size() == 1) {
            return;
        }

        // Move to the first task
        task = 1;
        emit changeCursor(tasks[heading][task]->id);

    // Select a task so it's value can be changed
    } else if(!current->is_heading()) {
        // Special case for the servo position.
        // Ignore input from the hall effect sensors until the position is deselected
        if(currentId == position.id && currentSelected) {
            sendDisableClutchOverride();
        }

        currentSelected = !currentSelected;
    }

    emit updateMenu();
}

void Navigation::shiftValuesReceived(int upDelayValue, int downDelayValue, int outputValue, int timeoutValue) {
    if(!taskSwitcher) {
        upDelay.value = upDelayValue;
        downDelay.value = downDelayValue;
        output.value = outputValue;
        timeout.value = timeoutValue;
    }
}

void Navigation::clutchValuesReceived(int startValue, int endValue, int frictionValue, int positionValue) {
    if(!taskSwitcher) {
        start.value = startValue;
        end.value = endValue;
        friction.value = frictionValue;
        position.value = positionValue;
   }
}

void Navigation::autoLaunchReceived(int state) {
   if(state == 1) {
        autoLaunch.value = 1;
   } else if(state == 0) {
        autoLaunch.value = 0;
   }
}

void Navigation::sendShiftValues(int upDelayValue, int downDelayValue, int outputValue, int timeoutValue) {
    QCanBusFrame frame;
    frame.setFrameId(1621);
    QByteArray data(8, 0);
    canutil::construct_data(data, upDelayValue, 0, 2);
    canutil::construct_data(data, downDelayValue, 2, 2);
    canutil::construct_data(data, outputValue, 4, 2);
    canutil::construct_data(data, timeoutValue, 6, 2);
    frame.setPayload(data);

    if (!device->writeFrame(frame)) {
        qDebug() << "CAN: Failed to write shift values";
    }
}

void Navigation::sendClutchValues(int startValue, int endValue, int frictionValue) {
    QCanBusFrame frame;
    frame.setFrameId(1622);
    QByteArray data(8, 0);
    canutil::construct_data(data, startValue, 0, 2);
    canutil::construct_data(data, endValue, 2, 2);
    canutil::construct_data(data, frictionValue, 4, 2);
    frame.setPayload(data);

    if (!device->writeFrame(frame)) {
        qDebug() << "CAN: Failed to write clutch values";
    }
}

void Navigation::sendClutchPosition(int positionValue) {
    QCanBusFrame frame;
    frame.setFrameId(1623);
    QByteArray data(8, 0);
    canutil::construct_data(data, positionValue, 0, 2);
    frame.setPayload(data);

    if (!device->writeFrame(frame)) {
        qDebug() << "CAN: Failed to set clutch position";
    }
}

void Navigation::sendDisableClutchOverride() {
    QCanBusFrame frame;
    frame.setFrameId(1624);
    if (!device->writeFrame(frame)) {
        qDebug() << "CAN: Failed to disable clutch override";
    }
}

void Navigation::sendAutoLaunch(int state) {
    QCanBusFrame frame;

    frame.setFrameId(1625);
    QByteArray data(8, 0);
    data[0] = state;
    frame.setPayload(data);

    if (!device->writeFrame(frame)) {
        qDebug() << "CAN: Failed to write auto launch";
    }
}

void Navigation::frameReceived() {
    while (device->framesAvailable()) {
        const QCanBusFrame frame = device->readFrame();
        int id = frame.frameId();
        QByteArray data = frame.payload();

        if(id == 1621) {
            int upDelay = canutil::read_data(data, 0, 2);
            int downDelay = canutil::read_data(data, 2, 2);
            int output = canutil::read_data(data, 4, 2);
            int timeout = canutil::read_data(data, 6, 2);

            emit shiftValuesReceived(upDelay, downDelay, output, timeout);

        } else if(id == 1622) {
            int start = canutil::read_data(data, 0, 2);
            int end = canutil::read_data(data, 2, 2);
            int friction = canutil::read_data(data, 4, 2);
            int position = canutil::read_data(data, 6, 2);

            emit clutchValuesReceived(start, end, friction, position);
        } else if(id == 1625) {
            int state = data[0];
            emit autoLaunchReceived(state);
        }
    }
}

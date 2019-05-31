#include <Arduino.h>
#include "IRserial.h"

IRpitCommand irPitCmd = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
IRpitSvFlags irPitFlags = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };

const char* const irTelegramNames[] = { "PFU", "PFL", "PCM" };

IRtelegram::IRtelegram(const char* type, const char* value) {
	_type = type;
	_value = value;
}

IRtelegram::IRtelegram() {
	_type = NULL;
	_value = NULL;
}

bool IRtelegram::isValid() {
	return _type != NULL;
}

int IRtelegram::toIntValue() {
	if( _value != NULL ) {
		return atoi(_value);
	}
}

float IRtelegram::toFloatValue() {
	if( _value != NULL ) {
		return atof(_value);
	}
}

bool IRtelegram::isOfType(const char* type) {
	return strcmp(_type, type);
}

IRserial::IRserial(Stream* serial) {
	_port = serial;
}

void IRserial::sendPitCommand(int pitCommand) {
	char buff[3];
	this->sendTelegram("PCM", itoa(pitCommand, buff, 10));
}

void IRserial::sendRefuelAmount(int amount) {
	char buff[5];
	this->sendTelegram("PFU", itoa(amount, buff, 10));
}

void IRserial::sendTelegram(IRtelegram telegram) {
	this->sendTelegram(telegram._type, telegram._value);
}

void IRserial::sendTelegram(const char* code, const char* value) {
	if (_port != NULL) {
		_port->print('#');
		_port->print(code);
		_port->print('=');
		_port->print(value);
		_port->print('*');
		_port->print('\n');
	}
}

IRtelegram* IRserial::receiveTelegram() {
	const char* telegram = this->readTelegram();
	if (telegram != NULL) {
		_telegram._type = strtok((char*)&_buff, "=");
		_telegram._value = strtok(NULL, "=");
	} else {
		_telegram._type = NULL;
	}

	return &_telegram;
}

const char* IRserial::readTelegram() {
	int datacount = 0;
	boolean startdata = false;
	while (_port->available()) {
		char c = _port->read();
		if (c == '#') {
			startdata = true;
		} else if (startdata && datacount < 10) {
			if (c != '*') {
				_buff[datacount++] = c;
			} else {
				break;
			}
		} else if (datacount >= 10) {
			return NULL;
		}
	}
	for( int i = datacount; i < 10; i++) {
		_buff[i] = 0;
	}
	if (startdata || datacount > 0) {
		return (const char*) &_buff;
	}
	return NULL;
}

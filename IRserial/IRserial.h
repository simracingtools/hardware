#ifndef IRserial_h
#define IRserial_h

#include <Arduino.h>

#include "Stream.h"

struct IRpitCommand {
    int clear;       // Clear all pit checkboxes
    int ws;          // Clean the winshield, using one tear off
    int fuel;        // Add fuel, optionally specify the amount to add in liters or pass '0' to use existing amount
    int lf;          // Change the left front tire, optionally specifying the pressure in KPa or pass '0' to use existing pressure
    int rf;          // right front
    int lr;          // left rear
    int rr;          // right rear
    int clear_tires; // Clear tire pit checkboxes
    int fr;          // Request a fast repair
    int clear_ws;    // Uncheck Clean the winshield checkbox
    int clear_fr;    // Uncheck request a fast repair
    int clear_fuel;  // Uncheck add fuel
};

extern IRpitCommand irPitCmd;

struct IRpitSvFlags {
    byte lf_tire_change;
    byte rf_tire_change;
    byte lr_tire_change;
    byte rr_tire_change;
    byte fuel_fill;
    byte windshield_tearoff;
    byte fast_repair;
};

extern IRpitSvFlags irPitFlags;

extern const char* const irTelegramNames[];

class IRtelegram {
	public:
		IRtelegram();
		IRtelegram(const char* type, const char* value);
		bool isValid();
		bool isOfType(const char* type);

		int toIntValue();
		float toFloatValue();

		const char* _type;
		const char* _value;
};


class IRserial {
	public:
		IRserial(Stream* serial);
		void sendPitCommand(int pitCommand);
		void sendRefuelAmount(int amount);
		IRtelegram* receiveTelegram();

	protected:
		void sendTelegram(IRtelegram telegram);

	private:
		Stream* _port;
  		char _buff[10];
  		IRtelegram _telegram;
		void sendTelegram(const char* tCode, const char* tValue);
		const char* readTelegram();
};

#endif

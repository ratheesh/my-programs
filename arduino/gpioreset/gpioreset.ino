/*
 * Copyright (C) 2014  Ratheesh S<ratheeshreddy@gmail.com>
 *
 * Based on ReadASCIIString demo in default Arduino Suite
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#define RESET_ACTIVE      0
#define RESET_INACTIVE    1

const int resetPin = 13;/* pins for the LEDs: */
const int max_cnt = 3;	/* max length for input string */
int current_cnt, i;
char buf[50];         /* string to hold incoming data */

void setup() {
	current_cnt = 0;
        /* initialize serial port: */
	Serial.begin(115200);

        /* make the pins outputs: */
	pinMode(resetPin, OUTPUT); 
}

void loop() {
	/* if there's any serial available, read it: */
	while (Serial.available() > 0) {
		Serial.readBytesUntil('\n', buf, max_cnt);

		/* Serial.println(buf); */
		if (!strcmp(buf, "on") || !strcmp(buf, "ON")) {
			Serial.print("Switch ON...");
			digitalWrite(resetPin, RESET_INACTIVE);
			Serial.print("OK!\n");
		} else if (!strcmp(buf, "off") || !strcmp(buf, "OFF")) {
			Serial.print("Switch OFF...");
			digitalWrite(resetPin, RESET_ACTIVE);
			Serial.print("OK!\n");
		} else if (!strcmp(buf, "rst") || !strcmp(buf, \
							  "RST")) {
			Serial.print("Resetting...");			
			digitalWrite(resetPin, RESET_INACTIVE);
			delay(500);
			digitalWrite(resetPin, RESET_ACTIVE);
			delay(2000);
			digitalWrite(resetPin, RESET_INACTIVE);
			Serial.print("OK!\n");
		} else {

			Serial.print("ERROR\n");
		}
		for (i = 0; i < 10; i++)
			buf[i] = '\0';
		current_cnt = 0;
	}
}
/* End of File */
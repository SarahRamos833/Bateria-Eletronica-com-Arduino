
 void debugCode()
 {
// 	 MIDI_TX(noteOn, 38, 90);
// 	 delay(300);
 }
 
 void debugScantimeArray(int values[])
 {
	 
	 Serial.print("Scantime = {");
	 for (int m = 0; m < 10; m++)
	 {
	 	Serial.print(values[m]);
		Serial.print(", ");
	 }
	 Serial.println("}");

 }
 
 void debugScantimeValues(int pin, int time, int value)
 {
	 
	Serial.print(pin);
	Serial.print(" > ");
	Serial.print(time);
	Serial.print(" > ");
	Serial.println(value);

 }
 
 void debugMIDI(int channel, int note, int vel)
 {
	 
	 Serial.print(channel);
	 Serial.print(" > ");
	 Serial.print(note);
	 Serial.print(" > ");
	 Serial.println(vel);
	 
 }

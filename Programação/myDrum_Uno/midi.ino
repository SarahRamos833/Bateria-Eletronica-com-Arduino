void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY)
{
	//status = MESSAGE + midichannel;
	Serial.write((MESSAGE | midichannel));
	Serial.write(PITCH);
	Serial.write(VELOCITY);
}

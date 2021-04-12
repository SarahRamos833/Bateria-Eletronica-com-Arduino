//Retorna a maior leitura dentro do Scantime
// int maxValue(int read[], int length)
// {
// 	int max = 0;
// 		
// 	for (int n=0; n < length; n++)
// 	{	
// 		if (max < read[n]) {
// 			max = read[n];
// 		}
// 	}
// 	return max;
// }

//Normalizar o valor do velocity, de acordo com a sensibilidade do pad. Fun��o de Gain
int normalizeSensor(int sensor, int pin)
{
	
	if (sensor < thresholdMin[pin])
	{
		sensor = thresholdMin[pin];
	} else if (sensor > thresholdMax[pin])
	{
		sensor = thresholdMax[pin];
	}
	
	if (SensorType[pin] == 176) {
		sensor = map(sensor, thresholdMax[pin], thresholdMin[pin], 1, 127);
	}
	else
	{
		sensor = map(sensor, 0, thresholdMax[pin], 0, 127);
	}
	
	return sensor;
}

// int scanTimeBool(int pin)
// {
// 	boolean scan;
// 	unsigned long currentMillis = millis();
// // 	if ((unsigned long)(currentMillis - previousMillis) < sensorScantime[pin])
// 	{
// 		scan = true;
// 	} else {
// 		scan = false;
// 		previousMillis = currentMillis;
// 	}
// 	
// 	return scan;
// 	
	
//}

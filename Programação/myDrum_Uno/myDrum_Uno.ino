//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Código Escrito por: Christian D'Aquino																                                                        //
// Versão: 20150109																											                                                      	//
// Editado por Rodrigo Amaral 
// Modificado por Sarah Ramos para usar um botão no hihat
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// NÃO ESQUEÇA DE COLOCAR O BAUDRATE DO HAIRLESS COM O VALOR 115200

//******	Configurações do Usuário		************************************************************************************/

// EXPLICAÇÃO CONFIGURACAO DOS PADS 
// TODOS OS PARAMETROS ABAIXO ESTÃO POR ORDEM DOS PINOS ANALOGICOS, DESSA FORMA: ={A0,A1,A2,A3,A4,A5};
// SensorType[6] = TIPO DE CADA PAD; || 144 = PIEZO || 176 = CONTROLADOR DE HIHAAT || 128 = DESABILITADO ||													
// PadNote[6] = NOTA DE CADA UM DOS PINOS														
// thresholdMin[6]= VALOR MINIMO DOS PIEZOS PARA DISPARAR A NOTA													
// thresholdMax[6]= VALOR MAXIMO DOS PIEZOS														
// sensorScantime[6]= TEMPO DE LEITURA DE CADA UM DOS PIEZOS														
// sensorMasktime[6]= TEMPO DE LEITURA DO PIEZO QUE SERÁ IGNORADO

//CONFIGURACAO DEFAULT DAS NOTAS DOS PINOS (NOTAS UTILIZADAS NO ADDICTIVE DRUMS, PODE VARIAR COM OUTROS VST'S)

//NOTA (CC) 4 - CONTROLADOR DE HIHAT
//NOTA 38 - SNARE (CAIXA)
//NOTA 42 - SNARE SIDESTICK (ARO)
//NOTA 36 - KICK (BUMBO)
//NOTA 71 - TOM 1
//NOTA 69 - TOM 2
//NOTA 67 - TOM 3
//NOTA 65 - TOM 3 
//NOTA 47 - XTRA 1 (PAD EXTRA)
//NOTA 73 - XTRA 2 (PAD EXTRA)
//NOTA 8 - HIHAT (CHIMBAL)
//NOTA 77 - CYMBAL 1 (PRATO 1)
//NOTA 79 - CYMBAL 2 (PRATO 2)
//NOTA 81 - CYMBAL 3 (PRATO 3)
//NOTA 60 - RIDE TIP (CONDUÇÃO CORPO)
//NOTA 61 - RIDE BELL (CONDUÇÃO CÚPULA)

byte SensorType[6] ={144,144,144,144,144,144};			//aqui voce faz suas modificações 										
byte PadNote[6] ={55,71,67,36,38,77};								//chimbal  tom1  surdo  bumbo  caixa ataque 							
int thresholdMin[6]={50,50,50,50,50,50};															
int thresholdMax[6]={1000,800,500,800,1000,500};															
int sensorScantime[6]={0,0,2,0,0,2};															
int sensorMasktime[6]={90,90,90,90,90,90};	

const int chimbal = 6;


#define READPIN 6 // DEFINE QUANTOS PINOS ANALÓGICOS DO ARDUINO SERÃO LIDOS, EM ORDEM (Ex: 1 = A0 || 2= A0, A1 e assim por diante. //														
													

//****** Configurações de Choke e dos Pinos Digitais Auxiliares*********************************//	

// Define as notas do chocke //

#define choke1 78
#define choke2 80   
#define choke3 82
#define chokeRide 63

// Define as Notas dos Plugs Digitais Auxiliares //

#define Aux1 4
#define Aux2 47
#define Aux3 47
#define Aux4 47
#define Aux5 47
#define Aux6 47
#define Aux7 47																	
																														
//******  NAO ALTERAR //	Configuração do programa //NAO ALTERAR SE NAO SOUBER O QUE ESTÁ FAZENDO!*********************************//

//Define os Pinos Digitais dos Chokes

#define Choke1_Pin 2 
#define Choke2_Pin 3
#define Choke3_Pin 4
#define ChokeRide_Pin 5 

//Define os Pinos Digitais Auxiliares

#define Aux1_Pin 6
#define Aux2_Pin 7
#define Aux3_Pin 8
#define Aux4_Pin 9
#define Aux5_Pin 10
#define Aux6_Pin 11
#define Aux7_Pin 12

//Define o estado dos pinos digitais

int Choke1_State = LOW;
int Choke2_State = LOW;
int Choke3_State = LOW;
int ChokeRide_State = LOW;
int Aux1_State = LOW;
int Aux2_State = LOW;
int Aux3_State = LOW;
int Aux4_State = LOW;
int Aux5_State = LOW;
int Aux6_State = LOW;
int Aux7_State = LOW;

int currentSwitchState = LOW;

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define midichannel 0


int readSensor = 0;
int led = 13;
unsigned long previousMillis[6];
unsigned long currentMillis[6];
unsigned int sensorReads[10];
int readNumber[6] = {0,0,0,0,0,0};
boolean playNote[6] ={true, true, true,true,true,true};

int pin = 0;

void setup()
{
  pinMode(chimbal, INPUT); 
  
  Serial.begin(115200);
  pinMode(Choke1_Pin, INPUT_PULLUP);
  pinMode(Choke2_Pin, INPUT_PULLUP);
  pinMode(Choke3_Pin, INPUT_PULLUP);
  pinMode(ChokeRide_Pin, INPUT_PULLUP);
  pinMode(Aux1_Pin, INPUT_PULLUP);
  pinMode(Aux2_Pin, INPUT_PULLUP);
  pinMode(Aux3_Pin, INPUT_PULLUP);
  pinMode(Aux4_Pin, INPUT_PULLUP);
  pinMode(Aux5_Pin, INPUT_PULLUP);
  pinMode(Aux6_Pin, INPUT_PULLUP);
  pinMode(Aux7_Pin, INPUT_PULLUP);

  

  pinMode(led, OUTPUT);
	
	while (!Serial) {
	; // wait for serial port to connect. Needed for Arduino Leonardo only
	}
  
	// set prescale to 8
	cbi(ADCSRA,ADPS2);
	sbi(ADCSRA,ADPS1);
	sbi(ADCSRA,ADPS0);
	
	Serial.flush();
  
}

void loop()
{
           int estado = digitalRead(chimbal);
           if(estado==HIGH)
          {
            PadNote[0] = 50;
          }
          else
          {
            PadNote[0] = 55;
          }

// ==================================== LEITURA DOS PINOS DIGITAIS ==================================== //

// CHOKE PRATO 01
{
digitalRead(Choke1_Pin);
currentSwitchState = digitalRead(Choke1_Pin);
if( currentSwitchState == LOW && Choke1_State == HIGH ) // push
MIDI_TX(144,  choke1, 127);
if( currentSwitchState == HIGH && Choke1_State == LOW ) // release
MIDI_TX(128, choke1, 127);
Choke1_State = currentSwitchState;
  
// CHOKE PRATO 02
{
currentSwitchState = digitalRead(Choke2_Pin);
if( currentSwitchState == LOW && Choke2_State == HIGH ) // push
MIDI_TX(144,  choke2, 127);
if( currentSwitchState == HIGH && Choke2_State == LOW ) // release
MIDI_TX(128, choke2, 127);
Choke2_State = currentSwitchState;
  
// CHOKE PRATO 03
{
currentSwitchState = digitalRead(Choke3_Pin);
if( currentSwitchState == LOW && Choke3_State == HIGH ) // push
MIDI_TX(144,  choke3, 127);
if( currentSwitchState == HIGH && Choke3_State == LOW ) // release
MIDI_TX(128, choke3, 127);
Choke3_State = currentSwitchState;
  
// CHOKE RIDE
{
currentSwitchState = digitalRead(ChokeRide_Pin);
if( currentSwitchState == LOW && ChokeRide_State == HIGH ) // push
MIDI_TX(144,  chokeRide, 127);
if( currentSwitchState == HIGH && ChokeRide_State == LOW ) // release
MIDI_TX(128, chokeRide, 127);
ChokeRide_State = currentSwitchState;
  
// AUX 1
{    
currentSwitchState = digitalRead(Aux1_Pin);
if( currentSwitchState == LOW && Aux1_State == HIGH ) // push
MIDI_TX( 0xB0 | 176,  Aux1, 127);
if( currentSwitchState == HIGH && Aux1_State == LOW ) // release
MIDI_TX( 0xB0 | 176, Aux1, 0);
Aux1_State = currentSwitchState;
  
// AUX 2
{    
currentSwitchState = digitalRead(Aux2_Pin);
if( currentSwitchState == LOW && Aux2_State == HIGH ) // push
MIDI_TX(144,  Aux2, 127);
if( currentSwitchState == HIGH && Aux2_State == LOW ) // release
MIDI_TX(128, Aux2, 127);
Aux2_State = currentSwitchState;

// AUX 3
{    
currentSwitchState = digitalRead(Aux3_Pin);
if( currentSwitchState == LOW && Aux3_State == HIGH ) // push
MIDI_TX(144,  Aux3, 127);
if( currentSwitchState == HIGH && Aux3_State == LOW ) // release
MIDI_TX(128, Aux3, 127);
Aux3_State = currentSwitchState;

// AUX 4
{    
currentSwitchState = digitalRead(Aux4_Pin);
if( currentSwitchState == LOW && Aux4_State == HIGH ) // push
MIDI_TX(144,  Aux4, 127);
if( currentSwitchState == HIGH && Aux4_State == LOW ) // release
MIDI_TX(128, Aux4, 127);
Aux4_State = currentSwitchState;

// AUX 5
{    
currentSwitchState = digitalRead(Aux5_Pin);
if( currentSwitchState == LOW && Aux5_State == HIGH ) // push
MIDI_TX(144,  Aux5, 127);
if( currentSwitchState == HIGH && Aux5_State == LOW ) // release
MIDI_TX(128, Aux5, 127);
Aux5_State = currentSwitchState;
  
// AUX 6
{    
currentSwitchState = digitalRead(Aux6_Pin);
if( currentSwitchState == LOW && Aux6_State == HIGH ) // push
MIDI_TX(144,  Aux6, 127);
if( currentSwitchState == HIGH && Aux6_State == LOW ) // release
MIDI_TX(128, Aux6, 127);
Aux6_State = currentSwitchState;
  
// AUX 7
{    
currentSwitchState = digitalRead(Aux7_Pin);
if( currentSwitchState == LOW && Aux7_State == HIGH ) // push
MIDI_TX(144,  Aux7, 127);
if( currentSwitchState == HIGH && Aux7_State == LOW ) // release
MIDI_TX(128, Aux7, 127);
Aux7_State = currentSwitchState;

//============================= LEITURA DOS PINOS ANALOGICOS =========================================================================//

	for(pin = 0; pin < READPIN; pin++)
	{
    analogRead(pin);  
		readSensor = analogRead(pin);

                if((SensorType[pin] != 128) && (readSensor > thresholdMin[pin]) && ((currentMillis[pin] - previousMillis[pin]) <= sensorMasktime[pin]))
		{
			currentMillis[pin] = millis();
			
			if (readNumber[pin] < sensorScantime[pin])
			{
				if (readSensor > sensorReads[pin])
				{
					sensorReads[pin] = readSensor;
					
				}
				readNumber[pin]++;
			} else if (playNote[pin] == true)
			{
				
				playNote[pin] = false;
				
				int velocity = normalizeSensor(sensorReads[pin], pin);
				MIDI_TX(SensorType[pin], PadNote[pin], velocity);
                                digitalWrite(led, HIGH);
                                digitalWrite(led, LOW);
			}
			
			
			
		} else if ((currentMillis[pin] - previousMillis[pin]) > sensorMasktime[pin])
		{
			playNote[pin] = true;
			readNumber[pin] = 0;
			sensorReads[pin] = 0;
			previousMillis[pin] = currentMillis[pin];
		}
	}

// =======================================================================================================================================================//
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

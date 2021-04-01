#define BUTTON 52

// UART Start frame
#define FRAME_START_LOW        0x5A
#define FRAME_START_HIGH      0xA5

// DWIN Command set
#define CMD_REGISTER_WRITE      0x80
#define CMD_REGISTER_READ     0x81
#define CMD_VARIABLE_WRITE      0x82
#define CMD_VARIABLE_READ     0x83
#define CMD_TREND_CURVE_BUFFER    0x84

#define WRITE_REGISTER_NO_BYTES 7
#define WRITE_VARIABLE_NO_BYTES 8

#define CIRCLE_REG 0x0102

void display_write_variable(uint16_t variable_id, int16_t value)
{
  const uint8_t no_bytes = 5;

  uint8_t bytes[WRITE_VARIABLE_NO_BYTES];
  bytes[0] = FRAME_START_LOW;
  bytes[1] = FRAME_START_HIGH;
  bytes[2] = no_bytes;
  bytes[3] = CMD_VARIABLE_WRITE;
  bytes[4] = (variable_id >> 8) & 0xFF;
  bytes[5] = variable_id & 0xFF;
  bytes[6] = (value >> 8) & 0xFF;
  bytes[7] = value & 0xFF;

  Serial1.write(bytes, WRITE_VARIABLE_NO_BYTES);
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, INPUT);

  // Open serial communications and wait for port to open:
  //Serial.begin(115200);
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }


  Serial.println("Goodnight moon!");

  */
  // set the data rate for the SoftwareSerial port
  Serial1.begin(19200);
}

void loop() // run over and over
{
  if(digitalRead(BUTTON)){
    digitalWrite(LED_BUILTIN, HIGH);
    display_write_variable(CIRCLE_REG, 0);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    display_write_variable(CIRCLE_REG, 1);
  }
  
  /*if (mySerial.available()){
    Serial.write(mySerial.read());
       // turn the LED on (HIGH is the voltage level)

  }
  if (Serial.available())
    mySerial.write(Serial.read());*/
}

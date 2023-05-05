

#define LIGHT_SENSOR 2
#define LIGHT_SENSOR_POWER 7
#define SOUND_SENSOR 3

byte FirstLight; // To store who is first
byte FirstMic;

const unsigned long TimeOutAmount = 5000000;
long Latency;

volatile unsigned long Micros_For_Light_Sensor;
volatile unsigned long Micros_For_Mic;

volatile bool sound_has_changed = false;
volatile bool light_has_changed = false;

void on_sound_change()
{
    sound_has_changed = true;
}
void on_light_change()
{
    light_has_changed = true;
}

Difference = Micros_For_Mic - Micros_For_Light_Sensor;
Latency = Difference / 1000;

void setup()
{
    Serial.begin(115200);
    pinMode(LIGHT_SENSOR_POWER, OUTPUT);
    pinMode(SOUND_SENSOR, INPUT);

    pinMode(LIGHT_SENSOR, INPUT);
    digitalWrite(LIGHT_SENSOR_POWER, HIGH);

    attachInterrupt(digitalPinToInterrupt(SOUND_SENSOR), on_sound_change, RISING);
    attachInterrupt(digitalPinToInterrupt(LIGHT_SENSOR), on_light_change, FALLING);
    Micros_For_Light_Sensor = 0 - TimeOutAmount;
    Micros_For_Mic = 0 - TimeOutAmount;
}

void loop()
{

    if (sound_has_changed)
    {
        // Handle
        sound_has_changed = false;
    }

    Serial.println(Latency);

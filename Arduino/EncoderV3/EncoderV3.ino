
#define LEFT_ENCODER_A 2
#define LEFT_ENCODER_B 3

long leftEncoderCount = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(LEFT_ENCODER_A, INPUT_PULLUP);
    pinMode(LEFT_ENCODER_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_A), readLeftEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_B), readLeftEncoder, CHANGE);
}

void loop()
{
    Serial.println(leftEncoderCount / 9600.0);
    delay(100);
}

void readLeftEncoder()
{
    leftEncoderCount++;
    // if (digitalRead(LEFT_ENCODER_A) == HIGH)
    // {
    //     if (digitalRead(LEFT_ENCODER_B) == LOW)
    //     {
    //         leftEncoderCount++;
    //     }
    //     else
    //     {
    //         leftEncoderCount--;
    //     }
    // }
    // else
    // {
    //     if (digitalRead(LEFT_ENCODER_B) == LOW)
    //     {
    //         leftEncoderCount--;
    //     }
    //     else
    //     {
    //         leftEncoderCount++;
    //     }
    // }
}
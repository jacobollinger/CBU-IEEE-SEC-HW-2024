void setup()
{
    Serial.begin(115200);
    pinMode(A13, INPUT);
}

void loop()
{
    double value = analogRead(A0);
    Serial.println(value);
    delay(100);
}
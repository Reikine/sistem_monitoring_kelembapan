#include "secrets.h"
#define BLYNK_PRINT Serial
#include <reikine-project-1_inferencing.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>
#define PIN_DHT 4
#define DHTTYPE DHT22
DHT dht(PIN_DHT, DHTTYPE);

const int pinTanahA = 34;
const int pinTanahB = 35;
const int pinRelayPompa = 26;
const int pinRelaySelector = 27;

BlynkTimer timer;
float features[4];

void runAI();

void setup()
{
  Serial.begin(115200);
  dht.begin();

  pinMode(pinRelayPompa, OUTPUT);
  pinMode(pinRelaySelector, OUTPUT);
  digitalWrite(pinRelayPompa, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  timer.setInterval(2000L, runAI);
}

void loop()
{
  Blynk.run();
  timer.run();
}

void runAI()
{

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int tanahA = analogRead(pinTanahA);
  int tanahB = analogRead(pinTanahB);

  if (isnan(t) || isnan(h))
  {
    Serial.println("Gagal baca DHT!");
    return;
  }

  features[0] = t;
  features[1] = h;
  features[2] = tanahA;
  features[3] = tanahB;

  Serial.print("Sensor: ");
  Serial.print(t);
  Serial.print("C, ");
  Serial.print(h);
  Serial.print("%, TA:");
  Serial.print(tanahA);
  Serial.print(", TB:");
  Serial.println(tanahB);

  ei_impulse_result_t result = {0};
  signal_t signal;
  int err = numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  if (err != 0)
  {
    Serial.print("ERR Sinyal: ");
    Serial.println(err);
    return;
  }

  err = run_classifier(&signal, &result, false);
  if (err != 0)
  {
    Serial.print("ERR Classifier: ");
    Serial.println(err);
    return;
  }

  float peluangKering = result.classification[1].value;
  Serial.print("Skor Kering: ");
  Serial.println(peluangKering);

  if (peluangKering > 0.8)
  {
    Serial.println(">>> Robotku: MENYIRAM! <<<");
    Blynk.virtualWrite(V4, "Robotku: MENYIRAM");
    digitalWrite(pinRelayPompa, LOW);
  }
  else
  {
    Serial.println(">>> Robotku: AMAN. <<<");
    Blynk.virtualWrite(V4, "Robotku: AMAN");
    digitalWrite(pinRelayPompa, HIGH);
  }

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, tanahA);
  Blynk.virtualWrite(V3, tanahB);
}
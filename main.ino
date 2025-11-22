// Smart Goggle - Eye drowsiness/dizziness detection
// For ESP32-S (Dev board) or other microcontrollers with analogRead.
// IR sensor analog -> GPIO34. Active buzzer -> GPIO26 (driven by digitalWrite).

const int IR_PIN = 34;        // ADC input
const int BUZZER_PIN = 26;    // digital output for active buzzer

// Detection parameters
float T_CLOSED = 2.0;         // seconds eye must be closed
int SAMPLE_INTERVAL_MS = 50;
int CAL_SAMPLES = 200;

int threshold = 1500;
int openVal = 0;
int closedVal = 0;

unsigned long closedStart = 0;
bool alarmOn = false;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== Smart Goggle: Eye drowsiness detection ===");
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // ensure buzzer off

  // Calibrate sensor
  calibrateSensor();

  Serial.print("Calibration done. Threshold = ");
  Serial.println(threshold);
  Serial.println("Monitoring started...");
}

void calibrateSensor() {
  Serial.println("\nCalibration will start in 3 seconds. Get ready (eyes open).");
  delay(3000);
  Serial.println("KEEP EYES OPEN for calibration now...");
  openVal = averageReadings(CAL_SAMPLES);
  Serial.print("Open average = ");
  Serial.println(openVal);

  Serial.println("Now CLOSE EYES for calibration in 3 seconds...");
  delay(3000);
  Serial.println("KEEP EYES CLOSED for calibration now...");
  closedVal = averageReadings(CAL_SAMPLES);
  Serial.print("Closed average = ");
  Serial.println(closedVal);

  threshold = (openVal + closedVal) / 2;
}

int averageReadings(int n) {
  long sum = 0;
  for (int i = 0; i < n; ++i) {
    int v = analogRead(IR_PIN);
    sum += v;
    delay(5);
  }
  return (int)(sum / n);
}

void loop() {
  int val = analogRead(IR_PIN);
  Serial.print("ADC: ");
  Serial.println(val);

  bool isClosed;
  if (openVal < closedVal) {
    isClosed = (val >= threshold); // closed gives higher reading
  } else {
    isClosed = (val <= threshold); // closed gives lower reading
  }

  unsigned long now = millis();
  if (isClosed) {
    if (closedStart == 0) closedStart = now;
    unsigned long closedDurationMs = now - closedStart;
    if (!alarmOn && closedDurationMs >= (unsigned long)(T_CLOSED * 1000.0)) {
      triggerAlarm();
      alarmOn = true;
    }
  } else {
    closedStart = 0;
    if (alarmOn) {
      stopAlarm();
      alarmOn = false;
    }
  }

  delay(SAMPLE_INTERVAL_MS);
}

void triggerAlarm() {
  Serial.println("ALARM: Eye closed too long!");
  digitalWrite(BUZZER_PIN, HIGH); // turn active buzzer ON
}

void stopAlarm() {
  Serial.println("Alarm cleared.");
  digitalWrite(BUZZER_PIN, LOW); // turn buzzer OFF
}
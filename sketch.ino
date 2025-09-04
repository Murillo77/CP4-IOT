// Guilherme Paes Camargo | RM555166
// Icaro Albuquerque | RM555131
// Murillo Santanna | RM557183
// Cicero Serafim | RM556996
// Eduardo Miguel | RM555871

#include <Arduino.h>

// ===== Pinos e amostragem =====
constexpr int ADC_PIN       = 34; // somente entrada (ADC)
constexpr int LED_XOR_TRUE  = 2;
constexpr int LED_XOR_FALSE = 4;

constexpr int FS_HZ  = 1000; // 1 kHz
constexpr int WIN_MS = 200;  // 200 ms
constexpr int N      = FS_HZ * WIN_MS / 1000; // 200 amostras
static float buf[N];

static inline float adc_to_unit(int raw) {
  return (float)raw / 4095.0f; // 12 bits -> 0..1
}

static inline void calc_feats(const float *x, int n, float &rms, float &ptp) {
  float xmin = x[0], xmax = x[0];
  double sumsq = 0.0;
  for (int i = 0; i < n; ++i) {
    float v = x[i];
    sumsq += (double)v * (double)v;
    if (v < xmin) xmin = v;
    if (v > xmax) xmax = v;
  }
  rms = sqrt(sumsq / (double)n);
  ptp = xmax - xmin;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_XOR_TRUE,  OUTPUT);
  pinMode(LED_XOR_FALSE, OUTPUT);

  analogReadResolution(12);                 // 0..4095
  analogSetPinAttenuation(ADC_PIN, ADC_11db); // ~0..3.3V

  // Inicial: Y=0 -> LED_FALSE ON
  digitalWrite(LED_XOR_TRUE,  LOW);
  digitalWrite(LED_XOR_FALSE, HIGH);

  Serial.println("# seq,rms,ptp,A,B,Y");
}

// Limiar fixo (ajuste se quiser)
float TH_RMS = 0.50f;
float TH_PTP = 0.20f;

void loop() {
  const uint32_t Ts = 1000000UL / FS_HZ; // 1 ms
  static uint32_t seq = 0;

  // 1) Captura janela
  for (int i = 0; i < N; ++i) {
    buf[i] = adc_to_unit(analogRead(ADC_PIN));
    delayMicroseconds(Ts);
  }

  // 2) Features
  float rms, ptp;
  calc_feats(buf, N, rms, ptp);

  // 3) Booleans
  bool A = (rms >= TH_RMS);
  bool B = (ptp >= TH_PTP);

  // 4) XOR e LEDs
  bool Y = (A ^ B);
  digitalWrite(LED_XOR_TRUE,  Y ? HIGH : LOW);
  digitalWrite(LED_XOR_FALSE, Y ? LOW  : HIGH);

  // 5) Log
  Serial.print(seq++); Serial.print(',');
  Serial.print(rms, 3); Serial.print(',');
  Serial.print(ptp, 3); Serial.print(',');
  Serial.print(A);      Serial.print(',');
  Serial.print(B);      Serial.print(',');
  Serial.println(Y);
}

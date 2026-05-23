/*
 * ============================================================
 *  Medidor de Tensão com Alerta Sonoro — Arduino UNO
 * ============================================================
 *  Autor:    Instituto Técnico Educacional Mirian Menchini
 *  Data:     Abril / 2026
 *  Versão:   1.0
 * ============================================================
 *  Descrição:
 *    Lê a tensão no pino A0, exibe o valor em um display
 *    LCD 16x2 e aciona um buzzer sempre que a tensão
 *    ultrapassar o limiar de 1,0 V.
 *
 *  Conexões:
 *    LCD RS  -> D12
 *    LCD E   -> D11
 *    LCD D4  -> D5
 *    LCD D5  -> D4
 *    LCD D6  -> D3
 *    LCD D7  -> D2
 *    LCD VO  -> Potenciômetro 250 kΩ (contraste)
 *    LCD LED+-> Resistor 220 Ω -> 5V
 *    Buzzer  -> D8
 *    Sensor  -> A0  (tensão a medir, max 5V)
 * ============================================================
 */

#include <LiquidCrystal.h>

// ---------- Pinos ----------
int pinoA0 = A0;   // Entrada analógica
int buzzer  = 8;   // Buzzer ativo

// Inicialização do LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ---------- Limiar de alerta ----------
const float LIMIAR_V = 1.0;  // Volts

// ============================================================
void setup() {
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Medidor Tensao");
  delay(1500);
  lcd.clear();
}

// ============================================================
void loop() {
  int leitura = analogRead(pinoA0);

  // Converte leitura do ADC (0-1023) para volts (0-5 V)
  float tensao = leitura * (5.0 / 1023.0);

  // Exibe a tensão no LCD com 2 casas decimais
  lcd.setCursor(0, 0);
  lcd.print(" Tensao:        ");
  lcd.setCursor(0, 1);
  lcd.print("  ");
  lcd.print(tensao, 2);
  lcd.print(" V          ");

  // Dispara buzzer se a tensão ultrapassar o limiar
  if (tensao > LIMIAR_V) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(100);  // Atualiza a cada 100 ms
}

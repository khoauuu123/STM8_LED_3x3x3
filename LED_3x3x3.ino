uint8_t columns[] = { PD3, PD2, PD1, PC7, PC6, PC5, PC4, PC3, PA1 };
uint8_t layers[] = { PD4, PD5, PD6 };

// Bật 1 LED tại vị trí (cột, hàng)
void lightLed(int8_t colPin, int8_t layerPin) {
  clearAll();                    // Tắt tất cả trước
  digitalWrite(colPin, HIGH);    // Cột ON (GND)
  digitalWrite(layerPin, HIGH);  // Hàng ON (VCC)
}


// Tắt toàn bộ LED
void clearAll() {
  for (int8_t i = 0; i < 9; i++) digitalWrite(columns[i], 0);
  for (int8_t i = 0; i < 3; i++) digitalWrite(layers[i], 0);
}

// Bật LED theo index với thời gian delay truyền vào
void lightLedByIndex(int8_t index, uint16_t delayTime) {
  if (index >= 27) return;
  int8_t row = index / 9;
  int8_t col = index % 9;

  int8_t colPin = columns[col];
  int8_t layerPin = layers[row];

  lightLed(colPin, layerPin);
  delay(delayTime);
}


// ========== HIỆU ỨNG ==========

// 1. Chạy từng LED từ 0 → 26
void effect_line() {
  for (int j = 0; j < 3; j++) {
    for (int8_t i = 0; i < 27; i++) {
      lightLedByIndex(i, 40);
    }
    for (int8_t i = 26; i >= 0; i--) {
      lightLedByIndex(i, 40);
    }
  }
}

// 2. Chạy từng hàng từ trái sang phải
void effect_rowByRow() {
  clearAll();
  for (int8_t i = 0; i < 9; i++) {
    digitalWrite(columns[i], 1);
  }
  for (int8_t layer = 0; layer < 3; layer++) {
    for (int8_t j = 0; j < 3; j++) {
      if (j == layer) digitalWrite(layers[j], 1);
      else digitalWrite(layers[j], 0);
    }
    delay(200);
  }

  clearAll();
  for (int8_t i = 0; i < 3; i++) {
    digitalWrite(layers[i], 1);
  }
  for (int8_t i = 0; i < 3; i++) {
    for (int8_t j = 0; j < 3; j++) {
      digitalWrite(columns[(j * 3) + i], 1);
      if (i != 0) digitalWrite(columns[(j * 3) + (i - 1)], 0);
    }
    delay(200);
  }

  clearAll();
  for (int8_t i = 0; i < 9; i++) {
    digitalWrite(columns[i], 1);
  }
  for (int8_t layer = 2; layer >= 0; layer--) {
    for (int8_t j = 0; j < 3; j++) {
      if (j == layer) digitalWrite(layers[j], 1);
      else digitalWrite(layers[j], 0);
    }
    delay(200);
  }

  clearAll();
  for (int8_t i = 0; i < 3; i++) {
    digitalWrite(layers[i], 1);
  }
  for (int8_t i = 2; i >= 0; i--) {
    for (int8_t j = 0; j < 3; j++) {
      digitalWrite(columns[(j * 3) + i], 1);
      if (i != 2) digitalWrite(columns[(j * 3) + (i + 1)], 0);
    }
    delay(200);
  }
}

// 3. Chạy từng cột từ trên xuống
void effect_colByCol() {
  clearAll();

  for (int8_t row = 0; row < 3; row++) {
    digitalWrite(layers[row], 1);
  }

  for (int8_t col = 0; col < 9; col++) {
    int8_t col_chay[9] = { 0, 1, 2, 5, 8, 7, 6, 3, 4 };
    digitalWrite(columns[col_chay[col]], 1);
    delay(200);
  }
}

// 4. Nhấp nháy toàn bộ
void effect_blinkAll(int8_t times) {
  for (int8_t t = 0; t < times; t++) {
    for (int8_t row = 0; row < 3; row++) {
      for (int8_t col = 0; col < 9; col++) {
        digitalWrite(columns[col], HIGH);
        digitalWrite(layers[row], HIGH);
      }
    }
    delay(100);
    clearAll();
    delay(200);
  }
}

// 5. xoay vòng led
void effect_quayvong() {
  for (int8_t solan = 0; solan < 8; solan++) {
    for (int8_t i = 0; i < 4; i++) {
      int8_t j = 4 - i;
      clearAll();
      for (int8_t i = 0; i < 3; i++) {
        digitalWrite(layers[i], 1);
      }

      for (int8_t f = 0; f < 3; f++) {
        digitalWrite(columns[i + (j * f)], 1);
      }

      if (solan < 4) delay(300);
      else delay(100);
    }
  }

  for (int8_t solan = 0; solan < 8; solan++) {
    for (int8_t i = 3; i >= 0; i--) {
      int8_t j = 4 - i;
      clearAll();
      for (int8_t i = 0; i < 3; i++) {
        digitalWrite(layers[i], 1);
      }

      for (int8_t f = 0; f < 3; f++) {
        digitalWrite(columns[i + (j * f)], 1);
      }

      if (solan < 4) delay(300);
      else delay(100);
    }
  }
}




void setup() {
  // Columns as output
  pinMode(columns[0], OUTPUT);
  pinMode(columns[1], OUTPUT);
  pinMode(columns[2], OUTPUT);
  pinMode(columns[3], OUTPUT);
  pinMode(columns[4], OUTPUT);
  pinMode(columns[5], OUTPUT);
  pinMode(columns[6], OUTPUT);
  pinMode(columns[7], OUTPUT);
  pinMode(columns[8], OUTPUT);

  // Layers as output
  pinMode(layers[0], OUTPUT);
  pinMode(layers[1], OUTPUT);
  pinMode(layers[2], OUTPUT);

  clearAll();
}

void loop() {
  effect_line();
  effect_rowByRow();
  effect_quayvong();
  effect_colByCol();
  effect_blinkAll(7);
}

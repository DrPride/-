    char line[500] = "";   // 传入的串行数据
    int ret = 0;

    void setup() {
      Serial.begin(9600);     // 打开串口，设置数据传输速率9600
    }

    void loop() {

      // 纯口可用时操作
      if (Serial.available() > 0) {
        // 读取传入的数据:  读到 \n 为止，或者最多 500 个字符
        ret = Serial.readBytesUntil('\n', line, 500);

        //打印你得到的：
        Serial.print("I received: ");
        Serial.println(line);
      }
      // 每1秒做一个输出
      delay(1000);
      Serial.println("I am waiting! ");
    }

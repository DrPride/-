//这是网上直接复制粘贴的一个写法，发上来作为参考

/**
 * 桌面工作伴侣
 * 功能： 1、反馈桌面的温度和湿度
 *        2、判断人是否坐下
 *        3、警告自己不要保持一个姿势太长时间
 * 版本号：1.0
 * 作  者：田辛
 * 日  期：2015年12月18日
 */

/* 针脚定义 */
#define DHT_PIN 2     /* IO 温湿度传感器数据       */
//其实主要还是温湿度的测试
#define TRG_PIN 3     /*  O 距离传感器启动         */
#define ECH_PIN 12    /* I  距离传感器数据输入     */
#define ALM_PIN 4     /*  O 蜂鸣器输出             */
#define HMC_PIN 8     /* I  人体感应传感器数据输入 */

/* 全局变量声明  */
#define ALARM_COUNTER 180; /* 监视不到人体的报警周期，15分钟 */
//这个我觉得意思不是很大
void setup() {
  Serial.begin(9600);
  Serial.println("===SETUPED===");
}

void loop() {

  /* 每5秒执行一次 */
  delay(5000);

  /* 获得温度和湿度信息 */
  int *DHT = getTemperatureAndHumidity();
  //主要是看下这个指针之后要怎么用
  
  /* 获得距离信息 */
  int distance = getDistance();
  /* 监视人体并报警 */
  int humanCheck = getHumanInfo();

  /* 人体传感器感受太久没有活动的话，开始报警 */
  if(humanCheck <= 0){
      digitalWrite(ALM_PIN, HIGH);
  }else{
      digitalWrite(ALM_PIN, LOW);
  }

  /* 参数输出 */
  /* 距离 */
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm.");
  /* 湿度 */
  Serial.print("Humidity:");
  Serial.print(*DHT);
  Serial.println("%.");
  /* 温度 */
  Serial.print("Temperature:");
  Serial.print(*(DHT+1));
  Serial.println("C.");
  /* 运动倒计时 */
  Serial.print("Nobody Check Counter:");
  Serial.println(humanCheck);

  /* 清理内存 */
  delete[] DHT;
}

/**
 * 取得人体感应传感器的状态
 * 参数： 无
 * 返回值：人体当前是否在运动
 *         返回值=预定义常数ALARM_COUNTER则是在运动
 *         返回值<预定义常数则没有在运动
 * 版本号：1.0
 */
int getHumanInfo(){
  static int alarmCounter = ALARM_COUNTER;   // 设置静态参数

  /* 针脚定义 */
  pinMode(ALM_PIN, OUTPUT);
  pinMode(HMC_PIN, INPUT);

  /* 如果检测到人体的话，认为人体在动。报警计数器重新开始 */
  if(digitalRead(HMC_PIN) == HIGH){
    alarmCounter = ALARM_COUNTER;
  }else{
    /* 未检测到人体的话，报警计数器开始倒数计数 */
    alarmCounter--;
    /* 报警计数器下限设定 */
    if(alarmCounter <= 0){
      alarmCounter = 0;
    }
  }

  /* 返回报警计数器的值 */
  return alarmCounter;
}

/**
 * 取得DHT11的湿度和问题信息
 * 参数：无
 * 返回值：数组[0]湿度，[1]温度
 * 版本：1.0
 * 说明：学习用，所以没有调用库
 */
int* getTemperatureAndHumidity(){
  //这个是我想看到的具体实现
  
  int temperature;            /* 温度               */
  int humidity;               /* 湿度               */
  int tokenCheck;             /* 校验位             */
  int chr[40] = {0};          /* 传感器返回值数组   */
  unsigned long time;         /* 采样时间记录       */
  //也就是说返回一个数组呗，看下能不能传给后端
  int *DHT = new int[2];      /* 返回数组对象       */

  /* 持续向传感器发送时序序列，直到收到正确反馈为止 */
  while(pushSingle4DHT11()){};

  /* 开始接收传感器反馈(40字节)*/
  for(int i = 0; i < 40; i++){
    /* 监视低电平，直到其结束 */
    while(digitalRead(DHT_PIN) == LOW){}
    /* 记录高电平的初始时间   */
    time = micros();
    /* 监视高电平，直到其结束 */
    while(digitalRead(DHT_PIN) == HIGH){}
    /* 如果高电平的持续时间大于50um，则认为是1，否则是0 */
    if(micros() - time > 50){
      chr[i] = 1;
    }else{
      chr[i] = 0;
    }
  }

  /* 获得湿度的具体值 */
  humidity    = chr[0] * 128 + chr[1] * 64 + chr[2] * 32 + chr[3] * 16 + chr[4] * 8 + chr[5] * 4 + chr[6] * 2 + chr[7];
  /* 获得温度的具体值 */
  temperature = chr[16] * 128 + chr[17] * 64 + chr[18] * 32 + chr[19] * 16 + chr[20] * 8 + chr[21] * 4 + chr[22] * 2 + chr[23];
  /* 获得校验位的值   */
  tokenCheck  = chr[32] * 128 + chr[33] * 64 + chr[34] * 32 + chr[35] * 16 + chr[36] * 8 + chr[37] * 4 + chr[38] * 2 + chr[39];

  /* 校验检查通过，将温湿度的值放入返回数组 */
  if( humidity + temperature == tokenCheck){
    DHT[0] = humidity;
    DHT[1] = temperature;
  }

  /* 返回值 */
  return DHT;
}

/**
 * 发送测量请求信号
 * 参数:无
 * 返回值：true -- 请求失败重新请求
 */
boolean pushSingle4DHT11(){
  int waitingCounter;       /* 等待计数器 */

  /* 与上次发送测量信号间隔40毫秒 */
  delay(40);
  /* 设置向传感器发送请求信号的IO模式 */
  pinMode(DHT_PIN, OUTPUT);
  /* 1、一个持续20毫秒的低电平 */
  digitalWrite(DHT_PIN, LOW);
  delay(20);
  /* 2、一个持续40微秒的高电平 */
  digitalWrite(DHT_PIN, HIGH);
  delayMicroseconds(40);
  /* 3、恢复低电平，并等待传感器反馈 */
  digitalWrite(DHT_PIN, LOW);
  pinMode(DHT_PIN, INPUT);

  /* 等待传感器返回一高一低两个信号 */
  /* 当高低电平信号任意一个找不到的时候，返回真，则会重新开始此函数 */
  /* 等待高电平信号 */
  waitingCounter = 10000;
  while(digitalRead(DHT_PIN) != HIGH){
    if(waitingCounter-- == 0){
      return true;
    }
  }

  /* 等待低电平信号 */
  waitingCounter = 30000;
  while(digitalRead(DHT_PIN) != LOW){
    if(waitingCounter-- == 0){
      return true;
    }
  }
}

/**
 * 从距离传感器取得距离
 * 参数：无
 * 返回值：距离的数值，单位厘米，精确到两位小数
 */
float getDistance(){
  /* 设置针脚 */
  pinMode(TRG_PIN, OUTPUT);
  pinMode(ECH_PIN, INPUT);

  /* 设置两微秒的低电平 */
  digitalWrite(TRG_PIN, LOW);
  delayMicroseconds(2);
  /* 发送10微秒的高电平 */
  digitalWrite(TRG_PIN, HIGH);
  delayMicroseconds(10);
  /* 返回高电平 */
  digitalWrite(TRG_PIN, LOW);

  /* 取得传感器的值并计算距离 */
  return pulseIn(ECH_PIN, HIGH) / 58.00;
}

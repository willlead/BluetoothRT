//앱과 아두이노 블루투스 통신 코드

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
byte buffer[1024];
int bufferPosition; //버퍼에 기록할 위치

//아두이노 시리얼 모니터 명령어
//연결 확인: AT
//이름 설정: AT+NAME이름 => AT+NAMEYOON
//핀 설정: AT+PIN4자리 => AT+NAME1008

void setup() {
  Serial.begin(9600); //시리얼 모니터 초기화
  BTSerial.begin(9600); // 블루투스 모듈 초기화
  bufferPosition = 0;
}

void loop() {
  
  // 블루투스, 데이터 수신 가능 
  if(BTSerial.available()){ 
//    Serial.write(BTSerial.read());
    
    byte data = BTSerial.read();     

    //앱에서 받은 문자 시리얼 모니터에 출력 //한글은 출력이 불가능
    Serial.write(data);
    Serial.print("/");
    
    //버퍼에 받은 데이터를 저장 후 bufPos를 증가시킨다.
    buffer[bufferPosition++] = data;    
    
    // 데이터 끝을 만나면
    if(data == '\n'){ 
      buffer[bufferPosition] = '\0';

      //스마트폰으로 전송할 문자를 시리얼 모니터에 출력
      Serial.print("보내는 문자: ");      
      Serial.write(buffer, bufferPosition);

      //블루투스에서 앱으로 문자를 전송
      BTSerial.write("아두이노가 말한다: ");
      BTSerial.write(buffer, bufferPosition);
      bufferPosition = 0;
      
    }
  }
}

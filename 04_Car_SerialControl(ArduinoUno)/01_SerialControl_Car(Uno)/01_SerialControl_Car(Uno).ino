#include <AFMotor.h>          // L293D 모터 라이브러리
AF_DCMotor Left_Front(1);   // 모터 1 객체         
AF_DCMotor Left_Back(2);    // 모터 2 객체 
AF_DCMotor Right_Front(4);  // 모터 4 객체
AF_DCMotor Right_Back(3);   // 모터 3 객체

void setup() {
  Serial.begin(9600);         // 통신 속도
  Left_Front.setSpeed(100);   // 모터 1 속도 설정          
  Left_Back.setSpeed(100);    // 모터 2 속도 설정          
  Right_Front.setSpeed(100);  // 모터 4 속도 설정          
  Right_Back.setSpeed(100);   // 모터 3 속도 설정          
}
void Release();             // 모터 회전정지
void Forward();             // 전진
void Backward();            // 후진
void Sideway_Right();       // 우측 옆으로
void Sideway_Left();        // 좌측 옆으로
void Rotate_Right();        // 우측 회전
void Rotate_Left();         // 좌측 회전
void Diagonal_RF();         // 우측 대각선 앞으로
void Diagonal_RB();         // 우측 대각선 뒤로
void Diagonal_LF();         // 좌측 대각선 앞으로
void Diagonal_LB();         // 좌측 대각선 뒤로
void Parking_Front_Left();  // 앞바퀴 중심으로 시계반대방향 회전
void Parking_Front_Right(); // 앞바퀴 중심으로 시계방향 회전
void Parking_Back_Right();  // 뒷바퀴 중심으로 시계반대방향 회전
void Parking_Back_Left();   // 뒷바퀴 중심으로 시계반대방향 회전
//void Parking();

void loop() {
  char rx_data;
  if(Serial.available())
  {
    rx_data = Serial.read();
    switch(rx_data){
      case '1':
        Serial.println("Diagonal_LB");
        Diagonal_LB();
        break;  
        
      case '2':
        Serial.println("Backward");   
        Backward();
        break;
        
      case '3':
        Serial.println("Diagonal_RB");
        Diagonal_RB();
        break;
        
      case '4':
        Serial.println("Sideway_Left");
        Sideway_Left();   
        break;
      
      case '5':
        Serial.println("LED1 ON");
        Sideway_Right();
        
        break;  
      case '6':
        Serial.println("Sideway_Right");   
        Sideway_Right();
        
        break;
      case '7':
        Serial.println("Diagonal_LF");
        Diagonal_LF(); 
        break;
        
      case '8':
        Serial.println("Forward");  
        Forward();    
        break;
        
      case '9':
        Serial.println("Diagonal_RF");  
        Diagonal_RF();   
        break;
        
      case 'm':
        Serial.println("Parking_Front_Left");  
        Parking_Front_Left();
        break; 
      
      case ',':
        Serial.println("Parking_Front_Right");  
        Parking_Front_Right();
        break; 
      
      case '.':
        Serial.println("Parking_Back_Left");  
        Parking_Back_Left();
        break; 
      
      case '/':
        Serial.println("Parking_Back_Right");  
        Parking_Back_Right();
        break;     
        
      default : break;
    }   // End of Switch
  }     // End of if(Serial.available())
}       // End of loop

void Release(){
  Left_Front.run(RELEASE);
  Left_Back.run(RELEASE);
  Right_Back.run(RELEASE);
  Right_Front.run(RELEASE);
}
void Forward(){
  Left_Front.run(FORWARD);
  Left_Back.run(FORWARD);
  Right_Front.run(FORWARD);
  Right_Back.run(FORWARD);
  delay(100);
  Release();  
}

void Backward(){
  Left_Front.run(BACKWARD); 
  Left_Back.run(BACKWARD);
  Right_Back.run(BACKWARD);
  Right_Front.run(BACKWARD);
  delay(100);
  Release();
}

void Sideway_Right(){     // 우측 옆으로
  Left_Front.run(FORWARD);
  Left_Back.run(BACKWARD);
  Right_Front.run(BACKWARD);
  Right_Back.run(FORWARD);  
  delay(100);
  Release();
}
void Sideway_Left(){       // 좌측 옆으로
  Left_Front.run(BACKWARD);
  Left_Back.run(FORWARD);
  Right_Front.run(FORWARD);
  Right_Back.run(BACKWARD);  
  delay(100);
  Release();
  }      
void Rotate_Right(){       // 우측 회전
  Left_Front.run(FORWARD);
  Left_Back.run(FORWARD);
  Right_Front.run(BACKWARD);
  Right_Back.run(BACKWARD);      
  delay(100);
  Release();
}      
void Rotate_Left(){        // 좌측 회전
  Left_Front.run(BACKWARD);
  Left_Back.run(BACKWARD);
  Right_Front.run(FORWARD);
  Right_Back.run(FORWARD);   
  delay(100);
  Release();
}       
void Diagonal_RF(){        // 우측 대각선 앞으로
  Left_Front.run(FORWARD);
  Left_Back.run(BRAKE);
  Right_Front.run(BRAKE);
  Right_Back.run(FORWARD);  
  delay(100);
  Release();
}       
void Diagonal_RB(){         // 우측 대각선 뒤로
  Left_Front.run(BRAKE);
  Left_Back.run(BACKWARD);
  Right_Front.run(BACKWARD);
  Right_Back.run(BRAKE);    
  delay(100);
  Release();
}       
void Diagonal_LF(){        // 좌측 대각선 앞으로
  Left_Front.run(BRAKE);
  Left_Back.run(FORWARD);
  Right_Front.run(FORWARD);
  Right_Back.run(BRAKE);     
  delay(100);
  Release();
}       
void Diagonal_LB(){        // 좌측 대각선 뒤로
  Left_Front.run(BACKWARD);
  Left_Back.run(BRAKE);
  Right_Front.run(BRAKE);
  Right_Back.run(BACKWARD);    
  delay(100);
  Release();
}
void Parking_Front_Right(){    // 주차시 앞바퀴중심 시계방향 회전
  Left_Front.run(FORWARD);
  Right_Front.run(BACKWARD); 
  delay(100);
  Release();
}
void Parking_Front_Left(){     // 주차시 앞바퀴중심 시계반대방향 회전
  Left_Front.run(BACKWARD);
  Right_Front.run(FORWARD); 
  delay(100);
  Release();
}

void Parking_Back_Right(){    // 주차시 뒷바퀴중심 시계방향 회전
  Left_Back.run(FORWARD);
  Right_Back.run(BACKWARD); 
  delay(100);
  Release();
}
void Parking_Back_Left(){     // 주차시 뒷바퀴중심 시계반대방향 회전
  Left_Back.run(BACKWARD);
  Right_Back.run(FORWARD); 
  delay(100);
  Release();
}

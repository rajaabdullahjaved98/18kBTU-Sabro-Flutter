

void LCd_Setup()

{
  pinMode(PIN_HT1621_BL, OUTPUT);
  pinMode(PIN_HT1621_CS, OUTPUT);
  pinMode(PIN_HT1621_RW, OUTPUT);
  pinMode(PIN_HT1621_DATA, OUTPUT);

  digitalWrite(PIN_HT1621_BL, LOW);

  ht.begin();

  ht.sendCommand(HT1621::RC256K);
  ht.sendCommand(HT1621::BIAS_THIRD_4_COM);
  ht.sendCommand(HT1621::SYS_EN);
  ht.sendCommand(HT1621::LCD_ON);



  digitalWrite(PIN_HT1621_BL, HIGH);
  ALL_OF();
  Fan_OFF();
  Tsig_25();
  delay(500);
  ht.write(4, 0b00001000);  // for c display
  delay(100);
 digitalWrite(PIN_HT1621_BL, LOW);
  ht.sendCommand(HT1621::LCD_OFF);
}


void LCD_Temp(uint8_t L_Temp)

{
  //Serial.printf("In LCD_Temp*********************************************************************************************************\n");

  if(Saving_Mode == 1)

  {

     Tsig_27();
     return;
  }

  if (L_Temp == 16) {

    Tsig_16();
  }

  if (L_Temp == 17) {

    Tsig_17();
  }

  if (L_Temp == 18) {

    Tsig_18();
  }

  if (L_Temp == 19) {

    Tsig_19();
  }
  if (L_Temp == 20) {

    Tsig_20();
  }

  if (L_Temp == 21) {
    Tsig_21();
  }

  if (L_Temp == 22) {
    Tsig_22();
  }

  if (L_Temp == 23) {
    Tsig_23();
  }

  if (L_Temp == 24) {
    Tsig_24();
  }

  if (L_Temp == 25) {
    Tsig_25();
  }

  if (L_Temp == 26) {
    Tsig_26();
  }

  if (L_Temp == 27) {
    Tsig_27();
  }

  if (L_Temp == 28) {
    Tsig_28();
  }

  if (L_Temp == 29) {
    Tsig_29();
  }
  if (L_Temp == 30) {
    Tsig_30();
  }
}




void Sig1_C()

{

  ht.write(0, 0b00000010);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00001110);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000000);  // for 8 segment 1 temp
}



void Sig1_H()

{

  ht.write(0, 0b00001100);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00001100);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000010);  // for 8 segment 1 temp
}

void Sig1_A()

{

  ht.write(0, 0b00001110);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00001100);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000010);  // for 8 segment 1 temp
}


void Sig1_D()

{

  ht.write(0, 0b00001110);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00001110);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000000);  // for 8 segment 1 temp
}


void Sig1_F()

{

  ht.write(0, 0b00000010);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00001100);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000010);  // for 8 segment 1 temp
}


void Sig1_E()

{

  ht.write(0, 0b00000010);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00001110);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000010);  // for 8 segment 1 temp
}





void Sig1_1()

{

  ht.write(0, 0b00001100);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  ht.write(1, 0b00000000);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000000);  // for 8 segment 1 temp
}


void Sig1_2()

{
  ht.write(0, 0b00000110);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00000110);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000010);  // for 8 segment 1 temp
}

void Sig1_3()

{
  ht.write(0, 0b00001110);  // for 1  segment 1 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(1, 0b00000010);  // for 3  segment 1 temp
  delay(10);
  ht.write(2, 0b00000010);  // for 8 segment 1 temp
}

void Sig2_1()

{


  ht.write(3, 0b00001100);  // for 1  segment 2 make 7 temp// only bit5.b6.b7 with every address
  delay(10);
  ht.write(8, 0b00000000);
  delay(10);
  ht.write(9, 0b00000000);
}

void Sig2_2()

{

  ht.write(3, 0b00000110);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00000110);
}

void Sig2_3()

{
  ht.write(3, 0b00001110);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00000010);
}


void Sig2_4()

{
  ht.write(3, 0b00001100);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00001000);
}

void Sig2_5()

{
  ht.write(3, 0b00001010);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00001010);
}

void Sig2_6()

{




  ht.write(3, 0b00001010);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00001110);
}

void Sig2_7()

{


  ht.write(3, 0b00001110);
  delay(10);
  ht.write(8, 0b00000000);
  delay(10);
  ht.write(9, 0b00000000);
}

void Sig2_8()

{


  ht.write(3, 0b00001110);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00001110);
}

void Sig2_9()

{



  ht.write(3, 0b00001110);
  delay(10);
  ht.write(8, 0b00000010);
  delay(10);
  ht.write(9, 0b00001000);
}

void Sig2_0()

{



  ht.write(3, 0b00001110);
  delay(10);
  ht.write(8, 0b00000000);
  delay(10);
  ht.write(9, 0b00001110);
  // delay(10);
}

void Tsig_16()

{

  Sig1_1();
  Sig2_6();
}

void Tsig_17()

{

  Sig1_1();
  Sig2_7();
}

void Tsig_18()

{

  Sig1_1();
  Sig2_8();
}

void Tsig_19()

{

  Sig1_1();
  Sig2_9();
}

void Tsig_20()

{
  Sig1_2();
  Sig2_0();
}

void Tsig_21()

{

  Sig1_2();
  Sig2_1();
}



void Tsig_22()

{

  Sig1_2();
  Sig2_2();
}

void Tsig_23()

{

  Sig1_2();
  Sig2_3();
}

void Tsig_24()

{

  Sig1_2();
  Sig2_4();
}

void Tsig_25()

{

  Sig1_2();
  Sig2_5();
}

void Tsig_26()

{

  Sig1_2();
  Sig2_6();
}

void Tsig_27()

{

  Sig1_2();
  Sig2_7();
}

void Tsig_28()

{

  Sig1_2();
  Sig2_8();
}

void Tsig_29()

{

  Sig1_2();
  Sig2_9();
}

void Tsig_30()

{

  Sig1_3();
  Sig2_0();
}


void Error_0()

{

  Sig1_E();
  Sig2_0();
}

void Error_1()

{

  Sig1_E();
  Sig2_1();
}


void Error_2()

{

  Sig1_E();
  Sig2_2();
}



void Error_3()

{

  Sig1_E();
  Sig2_3();
}


void Error_4()

{

  Sig1_E();
  Sig2_4();
}


void Error_5()

{

  Sig1_E();
  Sig2_5();
}


void Error_6()

{

  Sig1_E();
  Sig2_6();
}

void Error_7()

{

  Sig1_E();
  Sig2_7();
}

void Error_8()

{

  Sig1_E();
  Sig2_8();
}

void Error_9()

{

  Sig1_E();
  Sig2_9();
}


void Error_10()

{

  Sig1_F();
  Sig2_0();
}

void Error_11()

{

  Sig1_F();
  Sig2_1();
}

void Error_12()

{

  Sig1_F();
  Sig2_2();
}

void Error_13()

{

  Sig1_F();
  Sig2_3();
}
void Error_14()

{

  Sig1_F();
  Sig2_4();
}

void Error_15()

{

  Sig1_F();
  Sig2_5();
}

void Error_16()

{

  Sig1_F();
  Sig2_6();
}

void Error_17()

{

  Sig1_F();
  Sig2_7();
}

void Error_18()

{

  Sig1_F();
  Sig2_8();
}
void Error_19()

{

  Sig1_F();
  Sig2_9();
}

void Error_20()

{

  Sig1_H();
  Sig2_0();
}


void Error_21()

{

  Sig1_H();
  Sig2_1();
}

void Error_22()

{

  Sig1_H();
  Sig2_2();
}

void Error_23()

{

  Sig1_H();
  Sig2_3();
}


void Error_24()

{

  Sig1_H();
  Sig2_4();
}


void Error_25()

{

  Sig1_H();
  Sig2_5();
}

void Error_26()

{

  Sig1_H();
  Sig2_6();
}

void Error_27()

{

  Sig1_H();
  Sig2_7();
}

void Error_28()

{

  Sig1_H();
  Sig2_8();
}
void Error_29()

{

  Sig1_H();
  Sig2_9();
}








void Fault_disp()

{

  ALL_OF();
  delay(1000);
  Sig1_C();
  delay(1000);
  Sig1_H();
  delay(1000);
  Sig1_A();
  delay(1000);
  Sig1_D();
  delay(1000);
  Sig1_F();
  delay(1000);
  Sig1_E();
  delay(1000);
  Error_1();
  delay(1000);
  Error_2();
  delay(1000);
  Error_3();
  delay(1000);
  Error_4();
  delay(1000);
  Error_5();
  delay(1000);
  Error_6();
  delay(1000);
  Error_7();
  delay(1000);
  Error_8();
  delay(1000);
  Error_9();
  delay(1000);
  Error_10();
  delay(1000);
  Error_11();
  delay(1000);
  Error_12();
  delay(1000);
  Error_13();
  delay(1000);
  Error_14();
  delay(1000);
  Error_15();
  delay(1000);
  Error_16();
  delay(1000);
  Error_17();
  delay(1000);
  Error_18();
  delay(1000);
  Error_19();
  delay(1000);
  Error_20();
  delay(1000);
  Error_21();
  delay(1000);
  Error_22();
  delay(1000);
  Error_23();
  delay(1000);
  Error_24();
  delay(1000);
  Error_25();
  delay(1000);
  Error_26();
  delay(1000);
  Error_27();
  delay(1000);
  Error_28();
  delay(1000);
  Error_29();
  delay(1000);




  ALL_OF();
}


void ALL_OF()

{

  //Clear display
  for (int i = 0; i < 10; i++) {
    //displayMemory[i] = 0;
    ht.write(i, 0);
  }
  delay(200);
}


void LCD_DATA_Update()

{

  if (Stop_Stop == "Yes" || Esp_32!="RUN")

  {

    return;
  }
  // Serial.printf("In LCD_DATA_Update****************************************************\n");

  LCD_Temp(Set_Temp);  // Send Lcd Temp
  delay(100);
  ht.write(4, 0b00001000);  // for c display
  delay(100);
  Fan_OFF();


}

void Fan_OFF()

{

  ht.write(5, 0b00000000);  // forLine display rs 2 more
  delay(50);
  ht.write(6, 0b00000000);  // forLine display rs 2 more
  delay(50);
  ht.write(7, 0b00000000);  // forLine display rs 2 more
  delay(50);
  ht.write(4, 0b00001000);  // for c display
  delay(50);
}


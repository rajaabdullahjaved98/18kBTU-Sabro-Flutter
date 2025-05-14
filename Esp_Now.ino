#define Sabro_remote 1184005015
#define Sabro_remote_small 1184005014


#define Sabro_remote_pair_broadcast 2 
#define Sabro_remote_pair_request 3 
#define Sabro_remote_pair_request_done 5
#define Sabro_ac_name_request 12
#define Sabro_ac_unpair_request 13
#define Sabro_paired_screen_response_back 7
#define Sabro_new_name_request 15
#define Sabro_new_remote_pair_confirm 11
#define Sabro_SPM_request 17
#define Sabro_TPM_request 18
#define Sabro_Set_Temp_Mode 23
#define Sabro_Set_PKR_mode 24
#define Sabro_turn_on_AP 25
#define Sabro_Reset_PMonitor 26

#define ESP_NOW_TYPE_1 0

esp_now_peer_info_t peerInfo, peerInfo2, peerInfo3;
uint8_t broadcastAddress_1[6];



unsigned long timeout;

String success;
uint32_t success_number;
uint8_t message_sabro_ac;
bool send_name = false;
bool response_message = false;
bool pair_accepted = false;
bool pair_added = false;
bool unpair_request = true;
bool pair_on_pair = false;
bool timed_out = false;
bool timer_start = false;
bool deny_pair = false;
bool new_pair_confirm = false;


void peer_Broad(){

  memcpy(peerInfo.peer_addr, peerMAC_broad_Mac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}



void peer_storedBroad(){

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}


void peer_small(){
  memcpy(peerInfo3.peer_addr, small_screen_mac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo3) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }


}

void Espnow_setup()

{
  // Set device as a Wi-Fi Statio
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

//add small screen

//peer_small();

if (!connect.isPaired){
//peer_Broad();
  
}
else{
peer_storedBroad();
}
  // Register for a callback function that will be called when data is received
  
}

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
 // Serial.print("\r\nLast Packet Send Status:\t");
 // Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == ESP_NOW_SEND_SUCCESS) {
    success_number=0;
    success = "Delivery Success :)";
    //Serial.println("SUCCESS");
  } else {
    success_number++;
    success = "Delivery Fail :(";
  }
}


bool broadcast_check(const uint8_t * addr, int size){

        for (int i =0;i<size;i++){
                      if (broadcastAddress[i]!=addr[i])
                        return true;
                  }
                  return false;
}


void OnDataRecv(const esp_now_recv_info* info, const uint8_t* incomingData, int len)
  //const uint8_t *mac, const uint8_t *incomingData, int len)
 {
  // uint8_t check;
 // Serial.println(*incomingData);//********************************************************************************************
  // memcpy(&check,incomingData,sizeof(uint8_t));
  if (connect.isPaired){

    if (len==sizeof(uint8_t)){
      uint8_t message = 0;
      memcpy(&message,incomingData,sizeof(uint8_t));
      if (message==Sabro_ac_name_request)
      send_name = true;
      else if (message == Sabro_ac_unpair_request){
        uint8_t dummy[6];
        memcpy(&dummy,info->src_addr,6);
      unpair_request = broadcast_check(dummy, 6);   
      }
      else if (message==Sabro_paired_screen_response_back){
        if (!timed_out){
        timer_start = false;
        timeout = 0;
        deny_pair = true;
        }

    }
    
    else if (message == Sabro_Set_Temp_Mode)
    {
      operation_mode = false;
      Buzzer();

    }

    else if (message == Sabro_Reset_PMonitor) // Pom Reset*****************************************************************************
    {
      POM_RESET = 786786373;
    }
    

    // else if (message == Sabro_Set_PKR_mode){
    //   operation_mode = true;
    // }
    else if (message == Sabro_turn_on_AP){
    //  ap_mode = true;
    }

    }
    else if (len==sizeof(four_byte_data_t)){
    memcpy(&Control_Screen, incomingData,sizeof(four_byte_data_t));
    four_byte_bool_f = true;
    Serial.printf("\*************************one**********************nincomingData : 0x%04x\n\n",Control_Screen.control_screen);
    Buzzer();
    }

    else if (len == sizeof(three_phase_meter_data_t)){
      uint8_t data_kind = 0;
      memcpy(&data_kind,incomingData,sizeof(uint8_t));
      if (data_kind == Sabro_TPM_request){
      memcpy(&three_PM_data,incomingData,sizeof(three_phase_meter_data_t));//******************************************************************************* 3phase
     Serial.println(*incomingData);
      TPM = true;
      SPM = false;
      once = 1;
      Buzzer_Tone();
      }
    }

    else if (len==sizeof(remote_side_pair_t)){
    uint8_t data_kind = 0;
    memcpy(&data_kind,incomingData,sizeof(uint8_t));
    if (data_kind==1){
    memcpy(&dateTime, incomingData, sizeof(DateTimeStruct_t));
    CTime = 1;
    time_beep();
    //Serial.printf("\n Got 8 byte********************************************************************************************************\n");
    }
    else if (data_kind == Sabro_SPM_request) {
      memcpy(&single_PM_data,incomingData,sizeof(remote_side_pair_t));
      SPM = true;
      TPM = false;
      once = 1;
     Buzzer_Tone();


    }
    else{ 
    memcpy(&incoming_remote,incomingData,sizeof(remote_side_pair_t));
    Serial.printf("\n Request Authent %d ::: Request TYPE %d \n ",incoming_remote.authenticator,incoming_remote.request);
    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_remote_pair_broadcast){
    response_message = true;
    for (int i =0;i<6;i++){
        broadcastAddress_1[i]=info->src_addr[i];
      }
    //peer_storedBroad();
  memcpy(peerInfo2.peer_addr, broadcastAddress_1, 6);
  peerInfo2.channel = 0;
  peerInfo2.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo2) != ESP_OK) {
    Serial.println("Failed to add peer");
  }

    pair_on_pair = true;
    }
    }


    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_remote_pair_request){
    pair_accepted = true;
    pair_on_pair = true;

    }
    }

    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_paired_screen_response_back){
        if (!timed_out){
        timer_start = false;
        timeout = 0;
        deny_pair = true;
        }
        else {
          
        }
    }
    }

    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_new_remote_pair_confirm){
        new_pair_confirm = true;


    }
    }

    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_remote_pair_request_done){
        for (int i = 0 ; i < 6 ; i++ ){
          broadcastAddress[i]=broadcastAddress_1[i];
          broadcastAddress_1[i] = 0;
        }
    peer_storedBroad();
    store=true;
    EEP="YES";
    connect.isPaired = 1;
    selfMAC.pair_status = connect.isPaired;
    pair_added = true;
    Buzzer_pair();
    }
    }


    }

    }
    else if (len == 21){
      uint8_t message = 0;

      memcpy(&message,incomingData,sizeof(uint8_t));
      if(message==Sabro_new_name_request){
        memcpy(&selfMAC.name,(incomingData+1),20);
        send_name = true;
        nameString = String(selfMAC.name); // Convert to Arduino String
         Buzzer();
        Name_Save=true;
      }
    }
    else if (len == (2*sizeof(uint8_t))){
     uint8_t message = 0;
     memcpy(&message,incomingData,sizeof(uint8_t));
     if (message == Sabro_Set_PKR_mode){                 //PKRS Mode
      operation_mode = true;
      memcpy(&message,incomingData+1,sizeof(uint8_t));
      CT = (float) message;
      Set_Temp = CT;
       Saving_Mode = 0;
  bitWrite(Ble_8Bit2,4,0);  //saving mode off
 // Serial.printf("*********************Making operation Mode true select in Lcd**************************************************************\n\n\n");
      Buzzer();
      
      }

    }

  }
  else{
    if (len==sizeof(remote_side_pair_t)){
    memcpy(&incoming_remote,incomingData,sizeof(remote_side_pair_t));
    Serial.printf("\n Request Authent %d ::: Request TYPE %d \n ",incoming_remote.authenticator,incoming_remote.request);

    if (incoming_remote.authenticator==Sabro_remote_small){
      if (incoming_remote.request==Sabro_remote_pair_broadcast){
    response_message = true;
    small_screen_request = true;
    for (int i =0;i<6;i++){
        small_screen_mac[i]=info->src_addr[i];
      }
    peer_small();
    }
    }

    if (incoming_remote.authenticator==Sabro_remote_small){
    if (incoming_remote.request==Sabro_remote_pair_request){
    pair_accepted = true;
    small_screen_request = true;
    }
    }
    if (incoming_remote.authenticator==Sabro_remote_small){
      if (incoming_remote.request==Sabro_remote_pair_request_done){
    store=true;
    EEP="YES";
    small_screen_request = true;
    connect.isPaired = 1;
    selfMAC.pair_status = connect.isPaired;
    pair_added = true;
    Buzzer_pair();
    }
    }

    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_remote_pair_broadcast){
    response_message = true;
    for (int i =0;i<6;i++){
        broadcastAddress[i]=info->src_addr[i];
      }
    peer_storedBroad();
    }
    }


    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_remote_pair_request){
    pair_accepted = true;

    }
    }

    if (incoming_remote.authenticator==Sabro_remote){
      if (incoming_remote.request==Sabro_remote_pair_request_done){
    store=true;
    EEP="YES";
    connect.isPaired = 1;
    selfMAC.pair_status = connect.isPaired;
    pair_added = true;
    Buzzer_pair();
    }
    }

    }
  }

  #if ESP_NOW_TYPE_1

  if (connect.isPaired){
    bool not_your_partner_1 = true;
        for (int i =0;i<6;i++){
                      if (broadcastAddress[i]==info->src_addr[i]){
                        not_your_partner_1 = false;
                      }
                      else{
                        not_your_partner_1 = true;
                        break;
                      }
                  }
if (not_your_partner_1)
    return;
  }

// bool not_your_partner = true;
//         for (int i =0;i<6;i++){
//                       if (broadcastAddress[i]==info->src_addr[i]){
//                         not_your_partner = false;
//                       }
//                       else{
//                         not_your_partner = true;
//                         break;
//                       }
//                   }

  if (len == 8) {
    uint8_t check;
    memcpy(&check,incomingData,sizeof(uint8_t));
    if (check==2)
    { 
//      uint8_t previous_connection = connect.isPaired;

      memcpy(&connect,incomingData,sizeof(connection_t));
      if(connect.authenticatoR==(selfMAC.authenticator-1)){
        // if (previous_connection){
        //   bool not_your_partner = true;
        //   for (int i =0;i<6;i++){
        //       if (broadcastAddress[i]==info->src_addr[i]){
        //         not_your_partner = false;
        //       }
        //       else{
        //         not_your_partner = true;
        //         break;
        //       }
        //   }
        //   if (not_your_partner){
        //     connect.isPaired=previous_connection;
        //     return;
        //   }
        // }
      store=true;
      EEP="YES";
      for (int i =0;i<6;i++){
        broadcastAddress[i]=info->src_addr[i];
      }
      if (connect.isPaired){
        Buzzer_pair();
        peer_storedBroad();
      }
      else{
        Buzzer_unpair();
        peer_Broad();
      }


      }
      
    }

    else if (check==1){
    memcpy(&dateTime, incomingData, sizeof(DateTimeStruct_t));
    CTime = 1;
    Serial.printf("\n Got 8 byte********************************************************************************************************\n");
    }
  }
 if (len == 4)
 {

  memcpy(&Control_Screen, incomingData,sizeof(four_byte_data_t));
  four_byte_bool_f = true;
  Serial.printf("\*********************************two**************nincomingData : 0x%04x\n\n",Control_Screen.control_screen);
  Buzzer();
  
  }

  if (len==2){
    memcpy(&protocol_msg, incomingData,sizeof(protocol_esp_t));

    if (protocol_msg.request_type==0)
    return;

    else if (protocol_msg.request_type==1)
         if (protocol_msg.request_id==1){
          send_name = true;
         }
  }
#endif
}

void Espnow_ALL_Data()

{
  if (connect.isPaired){
    esp_err_t N_result,P_result,K_result,P_result_1,K_result_1;
    
  N_result = esp_now_send(broadcastAddress, (uint8_t *) &EE_Hour[1], 96);
  delay(50);
  P_result = esp_now_send(broadcastAddress, (uint8_t *) &EE_Day, (sizeof(float)*32));
  delay(50);
  K_result = esp_now_send(broadcastAddress, (uint8_t *) &EE_Month, (sizeof(float)*13));
  delay(50);
  P_result_1 = esp_now_send(broadcastAddress, (uint8_t *) &EE_Day_Peak, (sizeof(float)*32));
  delay(50);
  K_result_1 = esp_now_send(broadcastAddress, (uint8_t *) &EE_Month_Peak, (sizeof(float)*13));
  delay(50);


}


 
//}


// //Serial.printf("esp Now is Running\n");
//  if (N_result == ESP_OK || P_result == ESP_OK || K_result == ESP_OK) 
//   {
//    // Serial.println("Sent with success");
//   } else 
//   {
//     Serial.println("Error sending the data");
    
//    }

//xSemaphoreGive(xSemaphore);


}



void Espnow_Run_Data()

{
  
if (connect.isPaired){
 esp_err_t N_result = esp_now_send(broadcastAddress, (uint8_t *) &R_Data, sizeof(Running_Data_t));
 delay(50); 
 esp_err_t New_result = esp_now_send(small_screen_mac, (uint8_t *) &R_Data, sizeof(Running_Data_t));
 delay(50); 
 esp_err_t New_result_1 = esp_now_send(broadcastAddress, (uint8_t *) &pkr_send_data, sizeof(pkr_mode_data_t));
 delay(50);
 }
 if (timer_start &&  (millis()> (timeout + 10000))){
 timed_out = true;
 }
  // if (N_result == ESP_OK) 
  // {
  //  // Serial.println("Sent with success");
  // } else 
  // {
  //   Serial.println("Error sending the ruuning data");
    
  // } 

  
 
#if ESP_NOW_TYPE_1
if (success_number>30)
{
  connect.isPaired=0;
  store=true;
  EEP="YES";
  peer_Broad();
}  

if (!connect.isPaired)
esp_err_t B_result = esp_now_send(peerMAC_broad_Mac,(uint8_t *)&selfMAC, sizeof(mac_data_t));

#endif

if (timed_out){
  outgoing_remote.request = 10;
  outgoing_remote.authenticator = Sabro_remote + 1;
  esp_err_t N_result_1 = esp_now_send(broadcastAddress_1,(uint8_t *)&outgoing_remote, sizeof(remote_side_pair_t));
  delay(50);
  timed_out = false;
  timer_start = false;
  timeout = 0;
}

if (response_message){
  if (!pair_on_pair){
  if (small_screen_request)
  esp_err_t N_result_2 = esp_now_send(small_screen_mac,(uint8_t *)&selfMAC, sizeof(mac_data_t));
  else
  esp_err_t N_result_2 = esp_now_send(broadcastAddress,(uint8_t *)&selfMAC, sizeof(mac_data_t));
  }
  else
  esp_err_t N_result_2 = esp_now_send(broadcastAddress_1,(uint8_t *)&selfMAC, sizeof(mac_data_t));

  delay(50);
  pair_on_pair = false;
  response_message = false;
  small_screen_request = false;

}

if (new_pair_confirm){
outgoing_remote.request = 4;
outgoing_remote.authenticator = Sabro_remote + 1;
esp_err_t N_result_1 = esp_now_send(broadcastAddress_1,(uint8_t *)&outgoing_remote, sizeof(remote_side_pair_t));
delay(50);
new_pair_confirm = false;
}

if (pair_accepted){
  if (!pair_on_pair){
  outgoing_remote.request = 4;
  outgoing_remote.authenticator = Sabro_remote + 1;
  if (small_screen_request)
 esp_err_t N_result_1 = esp_now_send(small_screen_mac,(uint8_t *)&outgoing_remote, sizeof(remote_side_pair_t));
  else
  esp_err_t N_result_1 = esp_now_send(broadcastAddress,(uint8_t *)&outgoing_remote, sizeof(remote_side_pair_t));
  }
  else{
  
  outgoing_remote.request = 6;
  outgoing_remote.authenticator = Sabro_remote + 1;
  esp_err_t N_result_1 = esp_now_send(broadcastAddress,(uint8_t *)&outgoing_remote, sizeof(remote_side_pair_t));
  timer_start = true;
  timeout = millis();
  }

  delay(50);
  small_screen_request = false;
  pair_on_pair = false;
  pair_accepted = false;
}

if (!unpair_request)
{
  message_sabro_ac = 14;
  esp_err_t N_result = esp_now_send(broadcastAddress, (uint8_t *) &message_sabro_ac, sizeof(uint8_t));
  delay(50);
  unpair_request = true;
  Buzzer_unpair();
  connect.isPaired = 0;
  selfMAC.pair_status = connect.isPaired;
  store=true;
  EEP="YES";
  message_sabro_ac = 0;
}

if (deny_pair){
  outgoing_remote.request = 9;
  outgoing_remote.authenticator = Sabro_remote + 1;
  esp_err_t N_result_1 = esp_now_send(broadcastAddress_1,(uint8_t *)&outgoing_remote, sizeof(remote_side_pair_t));
  delay(50);
  deny_pair = false;
}

  if (send_name){

    esp_err_t N_result = esp_now_send(broadcastAddress, (uint8_t *) &selfMAC.name, 20);
    delay(50);
    send_name = false;
  }

}

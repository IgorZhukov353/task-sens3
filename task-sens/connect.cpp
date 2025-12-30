/*
  Igor Zhukov (c)
  Created:       01-09-2025
  Last changed:  29-12-2025
*/
#include<Arduino.h>
#include "util.h"
#include "main.h"

extern HardwareSerial Serial1;
#define ESP_Serial Serial1 // для МЕГИ

//---------------------------------------------------------------------------
void APP::setup()
{
  startTime = RTC.now().secondstime();  
  strcpy_P(WSSID,PSTR("Keenetic-7832"));
  strcpy_P(WPASS,PSTR("tgbvgy789"));
  strcpy_P(HOST_STR,PSTR("igorzhukov353.h1n.ru"));
  strcpy_P(HOST_IP_STR,PSTR("81.90.182.128"));
  check_tcp_last_byte[0] = 9;
  check_tcp_last_byte[1] = 22;
  check_tcp_last_byte[2] = 29;
  check_tcp_last_byte[3] = 31;

  //trace(WSSID + String(":") + WPASS);
}

//------------------------------------------------------------------------
bool APP::espSerialSetup() {
  bool r;
  //esp_power_switch(true);
  //delay(200);
  
  ESP_Serial.begin(115200); // default baud rate for ESP8266
  delay(100);
  r = espSendCommand(F("AT"), _STATE::OK , 5000 );
  r = espSendCommand(F("ATE0"), _STATE::OK , 5000 );
  r = espSendCommand( F("AT+GMR"), _STATE::OK, 10000 );
  r = espSendCommand( F("AT+CWMODE=1"), _STATE::OK, 5000 );
  {
    String str = F("AT+CWJAP=\""); 
    str += WSSID;
    str += F("\",\"");
    str += WPASS;
    str += F("\"");
    r = espSendCommand(str, _STATE::OK, 20000);  
  }
  // if(!r){
  //   routerConnectErrorCounter++; 
  //   } else {
  //   routerConnectErrorCounter = 0;
  //   r = espSendCommand( F("AT+CIFSR"), STATE::OK, 5000 );
  // }
  return r;
  }
  
// //---------------------------------------------------------------------------
// bool APP::espSendCommand(const String& cmd, const _STATE goodResponse, const unsigned long timeout, const char *postBuf=NULL, const String &cmd2=""){
//   String str = F("espSendCommand:");
//   str += cmd;
//   trace(str);
//   return 1;
// }
//------------------------------------------------------------------------
#define BUF_SIZE 10
#define STATE_STR_MAX 5
#define RESPONSE_LEN_MAX 512
//static const char *state_str[STATE_STR_MAX] = {"OK", "ERROR", "HTTP/1.1", "200 OK", "CLOSED"};
//static const byte state_str_len[STATE_STR_MAX] = {2, 5, 8, 6, 6};

bool APP::espSendCommand(const String &cmd, const _STATE goodResponse, const unsigned long timeout, const char *postBuf, const String &cmd2) 
{
  {
    trace_begin(F("espSendCommand(\""));
    trace_s(cmd);
    if(postBuf){
      trace_c(postBuf);
      trace_s(cmd2);
    }
    trace_s(F("\","));
    trace_i((byte)goodResponse);
    trace_s(F(","));
    trace_l(timeout);
    trace_s(F(")"));
    trace_end();  
  }
  return;
  // short msglen = cmd.length();
  // if(postBuf){
  //   msglen += strlen(postBuf);  
  //   msglen += cmd2.length();
  //   ESP_Serial.print(cmd);
  //   ESP_Serial.print(postBuf);
  //   ESP_Serial.println(cmd2);
  // } else
  //   ESP_Serial.println(cmd);
    
  // if(maxSendedMSG < msglen)
  //   maxSendedMSG = msglen;
    
  // unsigned long tnow, tstart;
  // bool result;
  // String response;
  // short responseLenMax = (goodResponse == _STATE::CLOSED)? RESPONSE_LEN_MAX: 200;
  // char c;
  // char cbuffer[BUF_SIZE]; //= {'*','*','*','*','*','*','*','*','*','*'};
  // bool state_str_on[STATE_STR_MAX] = {0, 0, 0, 0, 0};
  // bool recived = false;
  // bool bufOverFlag = false;
  // short currResponseLen = 0;
  // tnow = tstart = millis();
  // response.reserve(responseLenMax);
  
  // while ( tnow <= tstart + timeout ) {
  //   c = ESP_Serial.read();
  //   if(c > 0) {
  //     currResponseLen++;
  //     if(currResponseLen < responseLenMax){
  //       response += c; //String(c);
  //       if (!state_str_on[(byte)_STATE::ERR] && !state_str_on[(byte)_STATE::CLOSED]) {
  //         memmove(cbuffer, cbuffer + 1, sizeof(cbuffer) - 1);
  //         cbuffer[sizeof(cbuffer) - 1] = c;
  //         for (byte i = 0; i < STATE_STR_MAX; i++) {
  //           if ((i == (byte)_STATE::HTTP_OK || i == (byte)_STATE::CLOSED) && !state_str_on[(byte)_STATE::HTTP])
  //             continue;
  //           if (!memcmp(cbuffer + sizeof(cbuffer) - 1 - state_str_len[i], state_str[i], state_str_len[i])) {
  //             state_str_on[i] = true;
  //             if(i == (byte)goodResponse || i == (byte)_STATE::ERR)
  //               recived = true;
  //           }
  //         }
  //       }
  //     }
  //     else{
  //       bufOverFlag = true;
  //     }
  //   }
  //   if(recived)
  //     break;
  //   tnow = millis();
  // }
  
  // while (ESP_Serial.available()) {
  //   c = ESP_Serial.read();
  //   currResponseLen++;
  //   if(currResponseLen < responseLenMax)
  //     response += c;
  //   else{
  //     bufOverFlag = true;
  //    }
  // }
  // {
  //   if(bufOverFlag)
  //     buffOverCounter++;  
      
  //   trace_begin(F("espSendCommand:"));
	//   if ( recived) {
	// 	  if(state_str_on[(byte)_STATE::HTTP] && !state_str_on[(byte)_STATE::HTTP_OK]){
	// 	    httpFailCounter++;
  //       lastErrorTypeId = _ErrorType::HTTP_FAIL;
  //       result = false;
  //       } 
  //     else{
  //       result = (state_str_on[(byte)_STATE::ERR] || bufOverFlag) ? false : true;
  //       lastErrorTypeId = (result) ? _ErrorType::NONE : (bufOverFlag)? _ErrorType::BUFFOVER : _ErrorType::OTHER;
  //       }
  //     trace_s((result) ? F("SUCCESS") : F("ERROR"));
      
  //     } 
  //   else {
	// 	  result = false;
  //     trace_s(F("ERROR - Timeout"));
  //     timeoutCounter++;
  //     lastErrorTypeId = _ErrorType::TIMEOUT;
	//   }
  //   trace_s(F(" - Response time: " ));
  //   trace_l(millis() - tstart);
  //   trace_s(F("ms. Len: "));
  //   trace_i(currResponseLen);
	//   trace_s(F("\n\rRESPONSE:"));
	//   trace_s(response);
	//   trace_s(F("\n\r---END RESPONSE---"));
	//   trace_end();
  // }
  // if(result)
  //   responseProcessing(response);
    
  // checkMemoryFree();
  // return result;
}

//---------------------------------------------------------------------------
bool  APP::ping(const String &host, short timeout = 5000) {
    String str = F("AT+PING=\"");
    str += host;
    str += F("\"");
    return espSendCommand(str, _STATE::OK , timeout);
}




/*
  YubiOTP.cpp - Library for validating Yubi One-Time-Passwords (OTP)
  Created by Cyber Ninjas Inc, March 4, 2016
  Released under GPL v3
*/

#include "Arduino.h"
#include "YubiOTP.h"
#include "Client.h"
#include "OTPResponse.h"
#include "Sha1.h"
#include "libb64\cdecode.h"
#include "libb64\cencode.h"

  YubiOTP::YubiOTP(Client& client) : _client(client){
    _servers[0] =   "api.yubico.com";
    _servers[1] =   "api2.yubico.com";
    _servers[2] =   "api3.yubico.com";
    _servers[3] =   "api4.yubico.com";  
    _servers[4] =   "api5.yubico.com";
    _id = 1;
    _port = 80;
    _shouldSign=true;
    _maxTimeMilliSecs=3000;
  }
  
  void YubiOTP::setb64HmacKey(String key){
    _b64hmackey = key;
  }
  
  void YubiOTP::setOTP(String otp){
    _otp = otp;
  }
  
  void YubiOTP::setId(int id){
    _id = id;
  }
  
  void YubiOTP::setSigned(boolean shouldSign){
    _shouldSign = shouldSign;
  }
  
  void YubiOTP::setServers(String servers[], int serverCount){
    Serial.println("Not Implemented");
  }
  
  boolean YubiOTP::validateOTP(){
    this->getOTPResult();
  }
  
  String YubiOTP::getNonce(){
    String nonce = "asdlkjasdfweWErewrsdfsdfs";
    return nonce;
  }
  
  String YubiOTP::getOTPResult(){
    String url = "/wsapi/2.0/verify?";
    String params = "id=" + String(_id) + "&otp=" + _otp + "&nonce=" + this->getNonce() + "&timestamp=1"; 
    if(_shouldSign){
      String h = this->getHMACSha1(params);
      url += "&h=" + h;
    }
    for(const String &server : _servers) {
        String response = this->getRequest(server, _port, url + params);
        if(response.length() != 0){
          Serial.println(url);
          Serial.println(response);
          OTPResponse resp(response);
        } 
    }
    return "Hi";
  }
  
  String YubiOTP::getHMACSha1(String input){
    //Convert String _hmackey to char[] hmackey
    String hmackey = this->base64DecodeString(_b64hmackey);
    int hmacKeySize = hmackey.length() + 1;
    char cHmacKey[hmackeySize]; 
    hmackey.toCharArray(cHmacKey, hmacKeySize);
        
    Sha1.initHmac((uint8_t *)cHmacKey,hmacKeySize);
    Sha1.print(input);
    String hash = String(Sha1.resultHmac());
    return base64EncodeString(hash);
  }
  
  String YubiOTP::base64DecodeString(String input) {
    int inputSize = input.length() + 1;
    char cInput[inputSize];
    input.toCharArray(cInput, inputSize);

    int outputSize = base64_decode_expected_len(inputSize);
    char cOutput[outputSize];
    base64_decode_chars(cInput, inputSize, cOutput);
    return String(cOutput);
  }

  String YubiOTP::base64EncodeString(String input) {
    int inputSize = input.length() + 1;
    char cInput[inputSize];
    input.toCharArray(cInput, inputSize);
    
    int outputSize = base64_encode_expected_len(inputSize);
    char cOutput[outputSize];
    base64_encode_chars(cInput, inputSize, cOutput);
    
    return String(cOutput);
  }
  
  String YubiOTP::getRequest(String server, int port, String url){
      String response = "";
      char cServer[server.length() + 1];
      server.toCharArray(cServer, server.length() + 1);
      if(_client.connect(cServer, port)){
        _client.println("GET " + url + " HTTP/1.1");
        _client.println("Host: " + server);
        _client.println();
        delay(5000);
        
        while (_client.available()) {
          char c = _client.read();
          response = response + c;
        }
      }
      return response;
  }
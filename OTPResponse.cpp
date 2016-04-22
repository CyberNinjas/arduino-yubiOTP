/*
  OTPResponse.cpp - Library for handling the response from the Yubi One-Time-Passwords (OTP) Server
  Created by Cyber Ninjas Inc, March 4, 2016
  Released under GPL v3
*/

#include "Arduino.h"
#include "OTPResponse.h"

  OTPResponse::OTPResponse(String rawResponse){
    //Find double-line ending, since that is the request body
    int loc = rawResponse.indexOf("\r\n\r\n");
    if(loc == -1)
      return;
    String body = rawResponse.substring(loc + 4);
    while(body.indexOf("=") && body.indexOf("\r\n")){
      String name = body.substring(0, body.indexOf("="));
      String value = body.substring(body.indexOf("=") + 1, body.indexOf("\r\n"));
      
      //Set values based on name
      _h              = (name == "h") ? value : _h;
      _t              = (name == "t") ? value : _t;
      _otp            = (name == "otp") ? value : _otp;
      _nonce          = (name == "nonce") ? value : _nonce;
      _status         = (name == "status") ? value : _status;
      _timestamp      = (name == "timestamp") ? value : _timestamp;
      _sessioncounter = (name == "sessioncounter") ? value : _sessioncounter;
      _sessionuse = (name == "sessionuse") ? value : _sessionuse;
      
      body = body.substring(body.indexOf("\r\n") + 2);
    }
  }
  
  String OTPResponse::getResponseOTP(){
    return _otp;
  }
  
  String OTPResponse::getResponseNonce(){
    return _nonce;
  }
  
  String OTPResponse::getResponseSignature(){
    return _h;
  }
  
  String OTPResponse::getResponseTimeStamp(){
    return _t;
  }
  
  String OTPResponse::getStatus(){
    return _status;
  }
  
  String OTPResponse::getYubiTimestamp(){
    return _timestamp;
  }
  
  String OTPResponse::getYubiSessionCounter(){
    return _sessioncounter;
  }
  
  int OTPResponse::getSuccessfulReplyCount(){
    return _sl;
  }
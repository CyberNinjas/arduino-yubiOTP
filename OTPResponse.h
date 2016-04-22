/*
  OTPResponse.h - Library for handling the response from the Yubi One-Time-Passwords (OTP) Server
  Created by Cyber Ninjas Inc, March 4, 2016
  Released under GPL v3
*/
#ifndef OTPResponse_h
#define OTPResponse_h

#include "Arduino.h"

class OTPResponse {
  public:
    OTPResponse(String rawResponse);
    String getResponseOTP();
    String getResponseNonce();
    String getResponseSignature();
    String getResponseTimeStamp();
    String getStatus();
    String getYubiTimestamp();
    String getYubiSessionCounter();
    int getSuccessfulReplyCount();
    
  private:
    String _otp;
    String _nonce;
    String _h;
    String _t;
    String _status;
    String _timestamp;
    String _sessioncounter;
    String _sessionuse;
    int _sl;
};

#endif
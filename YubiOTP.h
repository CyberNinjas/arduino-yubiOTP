/*
  YubiOTP.h - Library for validating Yubi One-Time-Passwords (OTP)
  Created by Cyber Ninjas Inc, March 4, 2016
  Released under GPL v3
*/
#ifndef YubiOTP_h
#define YubiOTP_h

#include "Arduino.h"
#include "Client.h"

class YubiOTP {
  public:
    YubiOTP(Client& client);
    void setOTP(String otp);
    void setId(int id);
    void setb64HmacKey(String key);
    void setPort(int port);
    void setSigned(boolean shouldSign);
    void setServers(String servers[], int serverCount);
    boolean validateOTP();
  private:
    String _servers[5];
    String _otp;
    int _port;
    int _id;
    String _b64hmackey;
    boolean _shouldSign;
    Client& _client;
    int _maxTimeMilliSecs;
    String getOTPResult();
    String getNonce();
    String getRequest(String server, int port, String url); 
    String getHMACSha1(String input);
    String base64EncodeString(String input);
    String base64DecodeString(String input);
};

#endif
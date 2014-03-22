#pragma once
#include <xsl.h>
#include <string>
#include <boost/thread.hpp>
#include <memory>
#include "event.hpp"

// using tns = boost;
namespace tns = boost; // tns = thread namespace

namespace Net
{
  class TTVChat;
}

class Net::TTVChat
{
  protected:
    xsl_tcp_socket_t *clientSock;
    
    xsl_ipaddr_t serverIp;
    bool isIpResolved;
    
    std::unique_ptr<tns::thread> receiveThread; // I'm a twat
    bool quitReceiveThread;
    
    bool loginOk;
    
    std::string userName;
    std::string userPass;
    std::string channel;
    
    Event<const std::string&> messageReceiveEvents;
  public:
    TTVChat(void);
    ~TTVChat(void);
    
    bool Connect(const std::string &name, const std::string &auth, const std::string &channel);
    void Send(const std::string &message);
    
    Event<const std::string&> &MessageReceiveEvents(void) { return messageReceiveEvents; }
  private:
    void Receive(void);
    void HandleResponse(const std::string &response);
};
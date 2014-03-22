#include "ttv_chat.hpp"
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <boost/chrono.hpp>
#include "util.hpp"

using namespace Net;
namespace sns = boost; // sns = sleep namespace

static void FooSleep(unsigned int ms)
{
  sns::this_thread::sleep_for(sns::chrono::milliseconds(ms));
}

TTVChat::TTVChat(void)
: clientSock(nullptr),
  serverIp({0}),
  isIpResolved(false),
  receiveThread(nullptr),
  quitReceiveThread(false),
  loginOk(true),
  userName(""),
  userPass(""),
  channel(""),
  messageReceiveEvents()
{}

TTVChat::~TTVChat(void)
{
  if(clientSock)
  {
    std::string quitMsg("QUIT :");
    xsl_tcp_send(clientSock, quitMsg.c_str(), quitMsg.size() + 1);
    xsl_tcp_close(clientSock);
  }
  
  quitReceiveThread = true;
}

bool TTVChat::Connect(const std::string &name, const std::string &auth, const std::string &channel)
{
  if(!isIpResolved)
  {
    int ret = xsl_resolve_host(&serverIp, "irc.twitch.tv", 6667);
    if(ret < 0)
    {
      std::cout << "Could not resolve host! (" << ret << ")\n";
      return false;
    }
  }
  
  std::cout << "Attempting to connect...\n";
  clientSock = xsl_tcp_connect(&serverIp);
  if(!clientSock)
  {
    std::cout << "Couldn't connect to dat host, yo!\n";
    return false;
  }
  
  receiveThread.reset(new boost::thread(boost::bind(&TTVChat::Receive, this)));
  
  /* IRC "handshake" */
  std::string msg1("PASS " + auth + '\n');
  std::string msg2("NICK :" + name + '\n');
  std::string msg3("JOIN :" + channel + '\n');
  
  xsl_tcp_send(clientSock, msg1.c_str(), msg1.size() + 1);
  FooSleep(100);
  xsl_tcp_send(clientSock, msg2.c_str(), msg2.size() + 1);
  
  FooSleep(100);
  if(!loginOk)
  {
    std::cout << "Login failed!\n";
    return false;
  }
  
  userName = name;
  userPass = auth;
  
  FooSleep(100);
  xsl_tcp_send(clientSock, msg3.c_str(), msg3.size() + 1);
  
  this->channel = channel;
  
  return true;
}

void TTVChat::Receive(void)
{
  constexpr size_t bufSize = 1024;
  char *buf = new char[bufSize];
  std::unique_ptr<char> _buf(buf);
  
  while(!quitReceiveThread)
  {
    memset(buf, 0, bufSize);
    int ret = xsl_tcp_recv(clientSock, buf, bufSize - 1);
    
    if(ret < 0)
      break;
    
    if(ret > 0)
    {
      // std::cout << "Received: " << buf;
      HandleResponse(std::string(buf));
    }
  }
  
  std::cout << "Done receiving\n";
}

void TTVChat::HandleResponse(const std::string &response)
{
  const std::string lowResponse = Util::StringToLower(response);
  
  if(lowResponse.find("login unsuccessful"))
  {
    loginOk = false;
  }
  
  /* Parse user message */
  unsigned colon1 = response.find(':');
  unsigned colon2 = response.find(':', colon1 + 1);
  
  
  if(colon2 != std::string::npos && response.find("PRIVMSG") != std::string::npos)
  {
    std::string message = response.substr(colon2 + 1, response.size() - colon2 - 1); // -1 to strip the \n
    
    std::cout << "Calling message receive events with \"" << message << "\"\n";
    messageReceiveEvents(message);
  }
  else
  {
    if(colon2 == std::string::npos) std::cout << "Second colon not found\n";
    if(response.find("PRIVMSG") == std::string::npos) std::cout << "PRIVMSG not found\n";
  }
}

void TTVChat::Send(const std::string &message)
{
  std::cout << "Sending message: " << message << '\n';
  std::string msg("PRIVMSG " + channel + " :" + message + '\n');
  xsl_tcp_send(clientSock, msg.c_str(), msg.size() + 1);
}
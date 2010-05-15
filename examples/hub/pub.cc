#include "pubsub.h"
#include <muduo/base/ProcessInfo.h>
#include <muduo/net/EventLoop.h>

#include <stdio.h>

using namespace muduo;
using namespace muduo::net;
using namespace pubsub;

int main(int argc, char* argv[])
{
  if (argc == 4)
  {
    string hostport = argv[1];
    size_t colon = hostport.find(':');
    if (colon != string::npos)
    {
      string hostip = hostport.substr(0, colon);
      uint16_t port = atoi(hostport.c_str()+colon+1);
      string topic = argv[2];
      string content = argv[3];

      EventLoop loop;
      string name = ProcessInfo::username()+"@"+ProcessInfo::hostname();
      name += ":" + ProcessInfo::pidString();
      PubSubClient client(&loop, InetAddress(hostport, port), name);
      client.start();
      loop.loop();
    }
    else
    {
      printf("Usage: %s hub_ip:port topic content\n", argv[0]);
    }
  }
  else
  {
    printf("Usage: %s hub_ip:port topic content\n", argv[0]);
  }
}
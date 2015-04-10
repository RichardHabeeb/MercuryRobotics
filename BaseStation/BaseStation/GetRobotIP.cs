using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;

namespace BaseStation
{
    class GetRobotIP
    {
        UdpClient Server;
        byte[] ResponseData;

        public GetRobotIP(UdpClient robotServer)
        {
           Server = robotServer;
           IPHostEntry host;
           string localIP = "?";
           host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    localIP = ip.ToString();
                }
            }
           ResponseData = Encoding.ASCII.GetBytes(localIP);
        }
        
        public string GetIP()

        {       IPEndPoint ClientEp = new IPEndPoint(IPAddress.Any, 4444);
                byte[] ClientRequestData = Server.Receive(ref ClientEp);
                string ClientRequest = Encoding.ASCII.GetString(ClientRequestData);
                Server.Send(ResponseData, ResponseData.Length, ClientEp);
                return ClientEp.Address.ToString();
        }
       
    }
}


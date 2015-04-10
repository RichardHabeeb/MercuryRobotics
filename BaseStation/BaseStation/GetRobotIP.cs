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
           ResponseData = Encoding.ASCII.GetBytes("10.131.186.211");
        }
        
        public string GetIP()
        {       IPEndPoint ClientEp = new IPEndPoint(IPAddress.Any, 4444);
                byte[] ClientRequestData = Server.Receive(ref ClientEp);
                string ClientRequest = Encoding.ASCII.GetString(ClientRequestData);
                ClientEp = new IPEndPoint(IPAddress.Parse(ClientRequest), 4444);
                Server.Send(ResponseData, ResponseData.Length, ClientEp);
                return ClientRequest;
        }
       
    }
}


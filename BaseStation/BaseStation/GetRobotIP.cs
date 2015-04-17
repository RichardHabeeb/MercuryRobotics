﻿/*
 * Kansas State University Robotics Team
 * Mecury Robotics Competition
 * 
 * Base Station Get Robot IP class
 * 
 * This class searches for and finds baseStations IP then broadcasts the IP over the subnet for the robot to get, the waits for the robot to send its IP back and establish a handshake.
 *  
 * Author's: Richard Habeeb, Brandon Dunn, Daniel Marts, Daniel Wagner and Doug Anjard.
 */

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

        /// <summary>
        /// Creates a new GetRobotIP object associated with the server.
        /// </summary>
        /// <param name="robotServer">Python server connected to the robot.</param>
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
        
        /// <summary>
        /// Obtains the IP address of the Python server.
        /// </summary>
        /// <returns>The Python server's IP.</returns>
        public string GetIP()
        {
            IPEndPoint SenderEp = new IPEndPoint(IPAddress.Broadcast, 4444);
            Server.Send(ResponseData, ResponseData.Length, SenderEp);
            IPEndPoint ClientEp = new IPEndPoint(IPAddress.Any, 4445); 
            byte[] ClientRequestData = Server.Receive(ref ClientEp);
            string ClientRequest = Encoding.ASCII.GetString(ClientRequestData);
            return ClientEp.Address.ToString();
        }
       
    }
}


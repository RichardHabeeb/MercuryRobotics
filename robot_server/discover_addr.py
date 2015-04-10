import netifaces
from socket import *


def handshake():
    ifaces = netifaces.interfaces()
    assert 'wlan0' in ifaces
    addrs = netifaces.ifaddresses('wlan0')
    addr_info = addrs[2][0]  # IPv4

    mask = map(int, addr_info['netmask'].split('.'))
    addr = map(int, addr_info['addr'].split('.'))

    broadcast = []
    for ae, me in zip(addr, mask):
        broadcast.append(str(ae|(255^me)))

    broadcast = '{}.{}.{}.{}'.format(*broadcast)
    addr = '{}.{}.{}.{}'.format(*addr)

    conn = socket(AF_INET, SOCK_DGRAM)
    conn.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    conn.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)


    incomming = socket(AF_INET, SOCK_DGRAM)
    incomming.bind(('', 4444))
    conn.sendto(addr, (broadcast, 4444))
    assert incomming.recv(1024).strip() == addr, "This is my IP."
    return incomming.recv(1024)

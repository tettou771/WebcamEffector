#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
from pythonosc import osc_message_builder
from pythonosc import udp_client

class OscSender:
    def __init__(self):
        port_num = 8884
        parser = argparse.ArgumentParser()
        parser.add_argument("--ip", default="127.0.0.1", help="The ip of th OSC Server")
        parser.add_argument("--port", type=int, default=port_num, help="The port the OSC server is listening on")
        args = parser.parse_args()
        self.client = udp_client.UDPClient(args.ip, args.port)

        print("ip:127.0.0.1, port:" + str(port_num) + ", address:/filter")

    def send(self, addr, message):
        msg = osc_message_builder.OscMessageBuilder(address=addr)
        msg.add_arg(str(message))
        self.client.send(msg.build())

if __name__ == "__main__":
    oscSender = OscSender()
    oscSender.send('/test', 'teststring')
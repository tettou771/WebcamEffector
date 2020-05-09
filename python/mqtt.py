#!usr/bin/env python
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt     # MQTTのライブラリをインポート
from time import sleep              # 3秒間のウェイトのために使う

class mqttPublisher:
    def __init__(self):
        self.client = mqtt.Client('GCP_Speech_To_Text_Script')                 # クラスのインスタンス(実体)の作成
        self.client.on_connect = self.on_connect         # 接続時のコールバック関数を登録
        self.client.on_disconnect = self.on_disconnect   # 切断時のコールバックを登録
        self.client.on_publish = self.on_publish         # メッセージ送信時のコールバック

        self.client.connect('localhost', 8883)  # 接続先

        # 通信処理スタート
        self.client.loop_start()    # subはloop_forever()だが，pubはloop_start()で起動だけさせる

    # ブローカーに接続できたときの処理
    def on_connect(self, client, userdata, flag, rc):
        print("MQTT Connected with result code " + str(rc))

    # ブローカーが切断したときの処理
    def on_disconnect(self, client, userdata, flag, rc):
        if rc != 0:
            print("MQTT Unexpected disconnection.")

    # publishが完了したときの処理
    def on_publish(self, client, userdata, mid):
        #print("MQTT publish: {0}".format(mid))
        pass

    def publish(self, topic, msg):
        self.client.publish(topic, msg)    # トピック名とメッセージを決めて送信

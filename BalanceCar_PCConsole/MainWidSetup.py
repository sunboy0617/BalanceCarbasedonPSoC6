from PyQt5 import QtWidgets
from mainwid import Ui_MainWindow

from PyQt5.QtGui import QPixmap,QImage

from PyQt5.QtCore import QTimer
from PyQt5 import QtCore
from PyQt5.QtCore import *
import cv2
import socket
import threading
import sys
from functools import partial
from QRCode_Video.QRCode_Video import detect
from VoiceRecognition import voice_control
from queue import Queue

class MainWidSetup(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainWidSetup, self).__init__()
        # basic setup
        self.setupUi(self)
        self.lock = threading.Lock()
        self.soc_lock = threading.Lock()
        self.cap = cv2.VideoCapture()
        self.event = threading.Event()

        # tcp connect
        self.target = ('192.168.1.150', 9000)
        self.soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.queue = Queue(maxsize = 3)
        self.soc.connect(self.target)

        # slots
        self.Button_W.clicked.connect(partial(self.sendchar_b,'s'))
        self.Button_A.clicked.connect(partial(self.sendchar_b,'d'))
        self.Button_S.clicked.connect(partial(self.sendchar_b,'w'))
        self.Button_D.clicked.connect(partial(self.sendchar_b,'a'))
        self.Button_P.clicked.connect(partial(self.sendchar_b,'p'))
        self.Button_I.clicked.connect(partial(self.sendchar_b,'i'))
        self.Button_voice.clicked.connect(self.button_voice_control_click)

        #camera setting
        self.lock.acquire()
        self.cap.open(1)
        self.lock.release()
        self.event.set()

        # threads
        self.t1 = threading.Thread(target=detect, args=(self.cap, self.Lab_camera, self.lock, self.label_9, self.event))
        self.t2 = threading.Thread(target=self.sendchar, args=())
        self.t3 = threading.Thread(target=self.receive, args=())
        self.t1.start()
        self.t2.start()
        self.t3.start()

        self.label_9.setText("Init successfully!")
    
    def button_voice_control_click(self):
        self.label_9.setText('Start Recording...')
        text = voice_control(self.label_9)
        self.queue.put(text)

    def keyPressEvent(self, event):
        if(event.key() == Qt.Key_A):
            self.queue.put('d')
        elif(event.key() == Qt.Key_W):
            self.queue.put('s')
        elif(event.key() == Qt.Key_S):
            self.queue.put('w')
        elif(event.key() == Qt.Key_D):
            self.queue.put('a')
        elif(event.key() == Qt.Key_I):
            self.queue.put('i')
        elif(event.key() == Qt.Key_P):
            self.queue.put('p')
        else:
            pass

    def closeEvent(self, event):
        self.event.clear()
        self.t1.join()
        self.t2.join()
        self.t3.join()
        self.soc.close()
        self.cap.release()
        
        event.accept()
        exit(0)


    def sendchar(self): 
        while True:
            text = self.queue.get()
            if text == 'x':
                return
            self.soc_lock.acquire()
            if self.Lab_cmd.text() == '':
                if text == 'w':
                    self.Lab_cmd.setText('s')
                elif text == 's':
                    self.Lab_cmd.setText('w')
                elif text == 'a':
                    self.Lab_cmd.setText('d')
                elif text == 'd':
                    self.Lab_cmd.setText('a') 
                else:
                    self.Lab_cmd.setText(text)
                self.soc.send(bytes(text, encoding='utf-8'))
            else:
                if text == 'w':
                    self.Lab_cmd.setText(self.Lab_cmd.text()+'s')
                elif text == 's':
                    self.Lab_cmd.setText(self.Lab_cmd.text()+'w')
                elif text == 'a':
                    self.Lab_cmd.setText(self.Lab_cmd.text()+'d')
                elif text == 'd':
                    self.Lab_cmd.setText(self.Lab_cmd.text()+'a') 
                else:
                    self.Lab_cmd.setText(self.Lab_cmd.text()+text)
                self.soc.send(bytes(text, encoding='utf-8'))
            self.soc_lock.release()

            if self.event.is_set() == False:
                break

    def receive(self):
        while True:
            bytes_str = self.soc.recv(1024)
            
            if self.event.is_set() == False:
                break

    def sendchar_b(self, text):
        self.queue.put(text)

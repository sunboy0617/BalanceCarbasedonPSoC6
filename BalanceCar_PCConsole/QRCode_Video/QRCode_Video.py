import cv2
import pyzbar.pyzbar as pyzbar
import numpy
from PIL import Image, ImageDraw, ImageFont
from PyQt5 import QtGui
from PyQt5.QtGui import QPixmap,QImage
import threading


def decodeDisplay(imagex1, Lab_camera, Lab_info):


# 转为灰度图像
   gray = cv2.cvtColor(imagex1, cv2.COLOR_BGR2GRAY)
   QRcodes = pyzbar.decode(gray)

   for QRcode in QRcodes:

# 提取条形码的边界框的位置并画出图像中条形码的边界框
     (x, y, w, h) = QRcode.rect
     cv2.rectangle(imagex1, (x, y), (x + w, y + h), (0, 255, 0), 2)

# 条形码数据为字节对象，所以如果我们想在输出图像上画出来，就需要先将它转换成字符串
     QRcodeData = QRcode.data.decode("utf-8")
     QRcodeType = QRcode.type

# 解码完成以后，原图转码
     img_PIL = Image.fromarray(cv2.cvtColor(imagex1, cv2.COLOR_BGR2RGB))
# 字体默认大小
     font = ImageFont.load_default().font
# 字体颜色（rgb)
     fillColor = (0, 255, 255)
# 文字输出位置
     position = (x, y - 10)
# 输出内容
     str = QRcodeData
# 需要先把输出的中文字符转换成Unicode编码形式(  str.decode("utf-8)   )
     draw = ImageDraw.Draw(img_PIL)
     draw.text(position, str, font=font, fill=fillColor)

     imagex1 = cv2.cvtColor(numpy.asarray(img_PIL), cv2.COLOR_RGB2BGR)

     Lab_info.setText("<a href=\""+QRcodeData+"\">click to view")

   imagex1 = cv2.cvtColor(imagex1, cv2.COLOR_RGB2BGR)
   show_roi = QImage(imagex1.data, imagex1.shape[1], imagex1.shape[0], QImage.Format_RGB888)
   Lab_camera.setPixmap(QPixmap.fromImage(show_roi))



def detect(camera, Lab_camera, lock, Lab_info, event):
  while True:
# 读取当前帧
      lock.acquire()
      ret, frame = camera.read()
      lock.release()
      decodeDisplay(frame, Lab_camera, Lab_info)

      if event.is_set() == False:
        break

      if (cv2.waitKey(5) == 27):
        break
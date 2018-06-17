# -*- coding: utf8 -*-
#import sys
#sys.path.append('/usr/local/lib/python3.4/site-packages')
import cv2
import face_recognition
import numpy as np
from imutils.video import WebcamVideoStream
import imutils
from time import sleep
import serial
import time
import dlib
from imutils import face_utils
print("[INFO] loading facial detector...")
detector = dlib.get_frontal_face_detector()

print("[INFO] camera sensor warming up...")
vs = cv2.VideoCapture(1)

ser = serial.Serial("/dev/ttyACM0",9600, timeout=1)
time.sleep(1)
ser.flushInput()
ser.flushOutput()
wbt_image1 = face_recognition.load_image_file("1.jpg")
wbt_face_encoding1 = face_recognition.face_encodings(wbt_image1)[0]
face_locations = []
face_encodings = []
face_names = []

print("Connecting to Arduino.....")

print("==================================")



while 1:
    i='0'
    j='0'
    k='0'
    flag='0'
    a= vs.grab()    
    b= vs.grab()
    c= vs.grab()
    ret= vs.grab()
    ret, frame = vs.retrieve()
    #frame = imutils.resize(frame,240)
    frame = cv2.resize(frame, (600, 450))
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 0)
    for rect in rects:
        (x, y, w, h) = face_utils.rect_to_bb(rect)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        face_locations = [(y,  x+w,  y+h,  x)]  ##( top, right, bottom, left )
        face_encodings = face_recognition.face_encodings(frame,face_locations )
        xc = (x + x + w) / 2
        yc = (y + y + h) / 2
        d = 15*858.6/w
        print(d)
        
        face_names = []
        for face_encoding in face_encodings:
    
            match1 = face_recognition.compare_faces([wbt_face_encoding1], face_encoding)
            #match2 = face_recognition.compare_faces([justin_face_encoding], face_encoding)
            name = "QQ"

            if match1[0]:
                name = "Objective"
                
                if xc > 301:
                    if xc > 360:
                        if xc >500:
                            i='Y'
                        else:
                            i='T'
                    else:
                            i='R'
                elif xc < 299:
                    if xc < 240:
                        if xc < 100:
                            i='J'
                        else:
                            i='K'
                    else:
                        i='L'
                else:
                    print("no X dispacement")
                    i='Q'
                if yc > 226:
                    if yc > 270:                 
                        j='Z'
                    else:
                        j='D'
                elif yc < 224:
                    if yc < 180:
                        j='H'
                    else:
                        j='U'
                else:
                        j='Q'
                if d<130:
                        k='S'
                else:
                        k='G'
                flag='a'                
                ser.write(i+j+k+flag.encode("ascii"))
                ser.flush()
            face_names.append(name)
    
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (x , y -20), font, 1, (0, 0, 255), 3)
        
    print ('GG')
    cv2.imshow('img', frame)
    k = cv2.waitKey(1) & 0xff
    if k == 27:
       break

cv2.destroyAllWindows()
vs.stop()

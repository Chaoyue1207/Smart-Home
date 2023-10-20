
import RPi.GPIO as GPIO
import cv2
import time
import numpy as np
import os

GPIO.setmode(GPIO.BCM)
GPIO.setup(18,GPIO.OUT)

ENA = 13
IN1 = 19
IN2 = 26

recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath);

font = cv2.FONT_HERSHEY_SIMPLEX

#iniciate id counter
id = 0

# names related to ids: example ==> Marcelo: id=1,  etc
names = ['None', 'ID=1', 'ID=2', 'ID=3', 'Z', 'W'] 

# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height

# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)

while True:

    ret, img =cam.read()
    img = cv2.flip(img, 1) # Flip vertically

    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )

    for(x,y,w,h) in faces:

        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)

        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])

        # Check if confidence is less them 100 ==> "0" is perfect match 
        if (confidence < 100):
            id = names[id]
            confidence = "  {0}%".format(round(100 - confidence))
            
      	GPIO.setmode (GPIO.bcm) 	# use BCM numbering mode
	GPIO.setup (ENA, GPIO.out) 	# Set the GPIO pins connected to ENA to output mode
	GPIO.setup (IN1, GPIO.out) 	# Set the GPIO pins connected to IN1 to output mode
	GPIO.setup (IN2, GPIO.out) 	# Set the GPIO pins connected to IN2 to output mode
	GPIO. output(IN1, False) 	# set IN1 to 0
	GPIO. output(IN2, True) 	# set IN2 to 1
	GPIO. output(ENA, True) 	# Set ENA to 1 and start the A-channel motor
	Time.sleep (0.5) 		# Wait for the motor to turn
	GPIO. The cleanup ()
            
                               
        else:
            id = "unknown"
            confidence = "  {0}%".format(round(100 - confidence))
            
            
        cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
        cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  
    
    cv2.imshow('camera',img) 

    k = cv2.waitKey(10) & 0xff # Press 'ESC' for exiting video
    if k == 27:
        break

# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()


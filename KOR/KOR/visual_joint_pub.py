import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import serial
import cv2
import mediapipe as mp
import math
import time


def calcular_angulo(p1, p2, p3):

        x1, y1 = p1
        x2, y2 = p2
        x3, y3 = p3

        v2 = (x1 - x2, (480 - y1) - (480 - y2))
        v1 = (x3 - x2, (480 - y3) - (480 - y2))

        angulo_radianos = math.atan2(v2[1], v2[0]) - math.atan2(v1[1], v1[0])

        angulo_radianos = (angulo_radianos + 2 * math.pi) % (2 * math.pi)
        return (angulo_radianos * 180/math.pi) - 180

class JointPublisher(Node):
    def __init__(self):
        super().__init__('joint_publisher')

        self.joint_state_pub = self.create_publisher(JointState, 'joint_states', 0)
        self.timer = self.create_timer(0.01, self.publish_joint_state)
        self.cap = cv2.VideoCapture(0)
        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands()
        self.mpDraw = mp.solutions.drawing_utils

        self.pTime = 0
        self.cTime = 0
        self.vect_pose = [[0, 0] for _ in range(21)]
    

    def publish_joint_state(self):
        ret, frame = self.cap.read()

        # Converter o frame para RGB (MediaPipe usa imagens RGB)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Processar o frame com o modelo de rastreamento de mãos
        results = self.hands.process(frame_rgb)

        success, image = self.cap.read()
        imgRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        results = self.hands.process(imgRGB)
    
        #rint(results.multi_hand_landmarks)
        if results.multi_hand_landmarks:
            for handLms in results.multi_hand_landmarks:
                for id, lm in enumerate (handLms.landmark):
                    #print(id,lm)
                    h, w, c = image.shape
                    cx, cy = int(lm.x*w), int(lm.y*h)
                    ##print(id, cx, cy)
                    self.vect_pose[id] = [cx, 480 - cy]
                    if id == 4:
                        cv2.circle(image,(cx,cy),15, (255,0,255),cv2.FILLED)
    
                self.mpDraw.draw_landmarks(image, handLms, self.mpHands.HAND_CONNECTIONS)
    
        self.cTime = time.time()
        fps = 1/(self.cTime-self.pTime)
        self.pTime = self.cTime
    
        cv2.putText(image, str(int(fps)),(10,60), cv2.FONT_HERSHEY_PLAIN,3, (255,0,255),4)
        cv2.imshow("Results", image)

        ##print("Conector: ",calcular_angulo(hand_points[9], hand_points[5], hand_points[6]))

        joint_state_msg = JointState()
        joint_state_msg.header.stamp = self.get_clock().now().to_msg()

        joint_state_msg.name = ['indicador_joint3', 'indicador_joint2', 'indicador_joint1',"indicador_joint0",
                            'medio_joint3', 'medio_joint2', 'medio_joint1',"medio_joint0",
                            'anelar_joint3', 'anelar_joint2', "anelar_joint1","anelar_joint0",
                            'mindinho_joint3', 'mindinho_joint2', 'mindinho_joint1',"mindinho_joint0",
                            'polegar_joint3', 'polegar_joint2', 'polegar_joint1',"polegar_joint0"]
        
        print((calcular_angulo(self.vect_pose[0], self.vect_pose[5], self.vect_pose[6])))
        
        joint_state_msg.position = [(calcular_angulo(self.vect_pose[6], self.vect_pose[7], self.vect_pose[8]))* math.pi/180,
                                        (calcular_angulo(self.vect_pose[5], self.vect_pose[6], self.vect_pose[7]))* math.pi/180,
                                            (calcular_angulo(self.vect_pose[0], self.vect_pose[5], self.vect_pose[6]))* math.pi/180,
                                                (calcular_angulo(self.vect_pose[6], self.vect_pose[5], self.vect_pose[9]) + 85) * math.pi/180 * 0,

                                    (calcular_angulo(self.vect_pose[10], self.vect_pose[11], self.vect_pose[12]))* math.pi/180,
                                        (calcular_angulo(self.vect_pose[9], self.vect_pose[10], self.vect_pose[11]))* math.pi/180,
                                            (calcular_angulo(self.vect_pose[0], self.vect_pose[9], self.vect_pose[10]))* math.pi/180,
                                                (calcular_angulo(self.vect_pose[6], self.vect_pose[5], self.vect_pose[9]) + 85) * math.pi/180 * 0,

                                    (calcular_angulo(self.vect_pose[14], self.vect_pose[15], self.vect_pose[16]))* math.pi/180,
                                        (calcular_angulo(self.vect_pose[13], self.vect_pose[14], self.vect_pose[15]))* math.pi/180,
                                            (calcular_angulo(self.vect_pose[0], self.vect_pose[13], self.vect_pose[14]))* math.pi/180,
                                                (calcular_angulo(self.vect_pose[6], self.vect_pose[5], self.vect_pose[9]) + 85) * math.pi/180 * 0,

                                    (calcular_angulo(self.vect_pose[18], self.vect_pose[19], self.vect_pose[20]))* math.pi/180,
                                        (calcular_angulo(self.vect_pose[17], self.vect_pose[18], self.vect_pose[19]))* math.pi/180,
                                            (calcular_angulo(self.vect_pose[0], self.vect_pose[17], self.vect_pose[18]))* math.pi/180,
                                                (calcular_angulo(self.vect_pose[6], self.vect_pose[5], self.vect_pose[9]) + 85) * math.pi/180 * 0,

                                    (calcular_angulo(self.vect_pose[2], self.vect_pose[3], self.vect_pose[4]))* math.pi/180,
                                        (calcular_angulo(self.vect_pose[1], self.vect_pose[2], self.vect_pose[3]))* math.pi/180,
                                            ((calcular_angulo(self.vect_pose[5], self.vect_pose[2], self.vect_pose[0])) + 50)* math.pi/180,
                                            0.0]

        self.joint_state_pub.publish(joint_state_msg)
        #self.get_logger().info('Joint state published')
        
    

def main(args=None):
    rclpy.init(args=args)
    joint_publisher = JointPublisher()

    while True:
        rclpy.spin_once(joint_publisher, timeout_sec=0.1)
        if cv2.waitKey(1) == 27:  # Break the loop on 'Esc' key press
            break

    joint_publisher.destroy_node()
    rclpy.shutdown()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
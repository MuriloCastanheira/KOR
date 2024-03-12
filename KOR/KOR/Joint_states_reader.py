import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import serial
from math import pi

porta_serial = "/dev/ttyACM0" 

class JointPublisher(Node):
    def __init__(self):
        super().__init__('joint_publisher')

        self.arduino = serial.Serial(porta_serial, 9600, timeout=0.1)
        self.joint_state_pub = self.create_publisher(JointState, 'joint_states', 0)
        self.timer = self.create_timer(0.01, self.publish_joint_state)

    def publish_joint_state(self):
        

        linha = self.arduino.readline().decode('utf-8').strip()
        valores = linha.split(",")
        
        

        joint_state_msg = JointState()
        joint_state_msg.header.stamp = self.get_clock().now().to_msg()

        if len(valores) > 19:
            
        
            valores = [float(valor) for valor in valores]
            
            joint_state_msg.name = ['indicador_joint3', 'indicador_joint2', 'indicador_joint1',"indicador_joint0",
                                    'medio_joint3', 'medio_joint2', 'medio_joint1',"medio_joint0",
                                    'anelar_joint3', 'anelar_joint2', "anelar_joint1","anelar_joint0",
                                    'mindinho_joint3', 'mindinho_joint2', 'mindinho_joint1',"mindinho_joint0",
                                    'polegar_joint3', 'polegar_joint2', 'polegar_joint1',"polegar_joint0"]
            joint_state_msg.position = [valores[0] * pi/180, valores[1]* pi/180 , valores[2] * pi/180, valores[3] * pi/180,
                                        valores[4] * pi/180, valores[5]* pi/180 , valores[6] * pi/180, valores[7] * pi/180,
                                        valores[8] * pi/180, valores[9]* pi/180 , valores[10] * pi/180, valores[11] * pi/180,
                                        valores[12] * pi/180, valores[13]* pi/180 , valores[14] * pi/180, valores[15] * pi/180,
                                        valores[16] * pi/180, valores[17]* pi/180 , valores[18] * pi/180, valores[19] * pi/180]

            self.joint_state_pub.publish(joint_state_msg)
            self.get_logger().info('Joint state published')

def main(args=None):
    rclpy.init(args=args)
    joint_publisher = JointPublisher()
    rclpy.spin(joint_publisher)
    joint_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

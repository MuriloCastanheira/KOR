from setuptools import setup

package_name = 'KOR'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='trevoso',
    maintainer_email='trevoso@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'Joint_states_reader.py = KOR.Joint_states_reader:main',
            'visual_joint_pub.py = KOR.visual_joint_pub:main'
        ],
    },
)

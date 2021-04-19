from setuptools import setup

package_name = 'my_py_pkg'

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
    maintainer='peter',
    maintainer_email='peterborkuti@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "py_node = my_py_pkg.my_first_node:main",
            "py_publisher = my_py_pkg.my_first_publisher:main",
            "py_subscriber = my_py_pkg.my_first_subscriber:main",
            "number_publisher = my_py_pkg.number_publisher:main",
            "number_counter = my_py_pkg.number_counter:main",
            "add_nums_server = my_py_pkg.add_nums_service_server:main",
            "add_nums_service_client_oop = my_py_pkg.add_nums_service_client_oop:main",
            "add_nums_service_client_noop = my_py_pkg.add_nums_service_client_noop:main",
        ],
    },
)

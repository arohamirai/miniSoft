#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

int main(int argc, char* argv[])
{
        io_service iosev;
        //节点文件
	
        serial_port sp(iosev, "/dev/pts/15");
        // 设置参数
        sp.set_option(serial_port::baud_rate(115200));
        sp.set_option(serial_port::flow_control(serial_port::flow_control::none));
        sp.set_option(serial_port::parity(serial_port::parity::none));
        sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
        sp.set_option(serial_port::character_size(8));
        // 向串口写数据
        write(sp, buffer("Hello world", 12));

        iosev.run();
        return 0;
}

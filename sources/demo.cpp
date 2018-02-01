#include <print.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;

int main(int argc, char** argv) {
try {
	std::string text;

    options_description desc{"General options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("output,o", value<std::string>(), "Output");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    std::string pAddress = getenv("HOME");
    pAddress += "/.config/demo.cfg";
    const char* _pAddress = pAddress.c_str();


    if(exists(pAddress)) {
    	store(parse_config_file<char>( _pAddress, desc ), vm);
    }
    notify(vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
    }

    else if (getenv("DEMO_OUTPUT") != nullptr) {


        std::string _trAddress = getenv("DEMO_OUTPUT");
        std::ofstream out(_trAddress, std::ios_base::app);
        while(std::cin >> text) {
			print(text, out);
			out << std::endl;
		}
        out.close();
  	}

  	else if (vm.count("output")) {

  		std::ofstream out(vm["output"].as<std::string>(), std::ios_base::app);
		while(std::cin >> text) {
			print(text, out);
			out << std::endl;
		}
		out.close();
  	}

  	else {
  		std::cout << "DEFAULT" << std::endl;

		std::ofstream out("default.log", std::ios_base::app);
		while(std::cin >> text) {
			print(text, out);
			out << std::endl;
		}
		out.close();
  	}

  } catch (const error &ex) {
    std::cerr << ex.what() << '\n';
  }
}
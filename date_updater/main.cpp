#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main( int argc, char* argv[] )
{
	if(argc < 2)
	{
		std::cerr << "Usage: date_updater <file_path|folder_path>" << std::endl;

		return -1;
	}

	if((fs::is_directory( argv[1] ) && !fs::is_empty( argv[1] )))
	{
		for(auto& entry : fs::recursive_directory_iterator( argv[1] ))
		{
			std::error_code error;
			fs::last_write_time( entry, fs::file_time_type::clock::now(), error );

			if(error)
				std::cerr << "[ERROR] An error has occured while setting the date for" << ' ' <<
				entry.path().string() << std::endl;
		}
	}

	if(fs::is_regular_file( argv[1] ))
	{
		std::error_code error;
		fs::last_write_time( argv[1], fs::file_time_type::clock::now(), error );

		if(error)
			std::cerr << "[ERROR] An error has occured while setting the date for" << ' ' <<
			argv[1] << std::endl;
	}

	return 0;
}
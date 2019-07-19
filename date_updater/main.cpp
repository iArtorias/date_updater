#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main( int argc, char* argv[] )
{
	fs::path file_directory{ fs::current_path() }; // The current path by default

	if(argc >= 2) // No argument provided
		file_directory = fs::path( argv[1] );

	if(fs::is_regular_file( file_directory ))
	{
		std::error_code error;
		fs::last_write_time( file_directory, fs::file_time_type::clock::now(), error );

		if(error)
			std::cerr << "[ERROR] An error has occured while setting the date for" << ' ' <<
			file_directory << std::endl;
	}

	if((fs::is_directory( file_directory ) && !fs::is_empty( file_directory )))
	{
		for(auto& entry : fs::recursive_directory_iterator( file_directory ))
		{
			if(entry.path().filename().compare( fs::path( argv[0] ).filename() ) != 0x0) // Skip the tool
			{
				std::error_code error;
				fs::last_write_time( entry, fs::file_time_type::clock::now(), error );

				if(error)
					std::cerr << "[ERROR] An error has occured while setting the date for" << ' ' <<
					entry.path().string() << std::endl;
			}
		}
	}

	return 0;
}
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int wmain( int argc, wchar_t* argv[] )
{
	fs::path file_directory{ fs::current_path() }; // The current path by default

	if (argc >= 2) // No argument provided
		file_directory = fs::path( argv[1] );

	if (fs::is_regular_file( file_directory ))
	{
		std::error_code error;
		fs::last_write_time( file_directory, fs::file_time_type::clock::now(), error );

		if (error)
			std::wcerr << L"[ERROR] An error has occured while setting the date for" << ' ' <<
			file_directory << std::endl;
	}

	if ((fs::is_directory( file_directory ) && !fs::is_empty( file_directory )))
	{
		// Get the current time only once
		auto time_now = fs::file_time_type::clock::now();

		// The current executable file name
		auto exe_name = fs::path( argv[0] ).filename();

		for (auto& entry : fs::recursive_directory_iterator( file_directory ))
		{
			if (entry.path().filename().compare( exe_name ) != 0x0) // Skip the tool
			{
				std::error_code error;
				fs::last_write_time( entry, time_now, error );

				if (error)
					std::wcerr << L"[ERROR] An error has occured while setting the date for" << ' ' <<
					entry.path().wstring() << std::endl;
			}
		}
	}

	return 0;
}
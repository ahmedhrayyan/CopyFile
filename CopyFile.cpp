//

#include <iostream>
#include <Windows.h>

std::string GetLastErrorAsString();

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Source & destination files are required!";
        exit(1);
    }

	char* sourceFile = argv[1];
	char* destinationFile = argv[2];
	if (!CopyFileA(sourceFile, destinationFile, true))
	{
        std::cout << GetLastErrorAsString();
	}
	return 0;
}

// Returns the last Win32 error, in string format. Returns an empty string if there is no error.
// credit: https://stackoverflow.com/a/17387176/10272966 
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}

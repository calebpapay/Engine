
//2024. Caleb Papay


#include "File.h"
#define BUFFERSIZE 5

namespace Azul
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{

        if (SetFilePointer(fh, 0, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) // Test for failure
        {
            return false;
        }

        return true;
	}


	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
        if (fileName == nullptr) //test file provided
        {
            return Error::OPEN_FAIL;
        }

        DWORD desiredAccess = NULL;

        switch (mode) 
        {
            case Mode::READ:
                desiredAccess = GENERIC_READ;
                break;
            case Mode::WRITE:
                desiredAccess = GENERIC_WRITE;
                break;
            case Mode::READ_WRITE:
                desiredAccess = GENERIC_READ | GENERIC_WRITE;
                break;
            default:
                //mode not supported
                return Error::OPEN_FAIL;
        }

        fh = CreateFileA(fileName,  // file to open
            desiredAccess,          // open for selected access
            0,                      // don't share, synchronous
            NULL,                   // default security
            OPEN_EXISTING,          // USE EXISTING FILE
            FILE_ATTRIBUTE_NORMAL,  // normal file
            NULL);                  // no attr. template

        DWORD errorCode = GetLastError();
        if (errorCode == 2)  //test file did not exist
        {
            fh = CreateFile(fileName,   // name of the write
                desiredAccess,          // open for selected access
                0,                      // don't share, synchronous
                NULL,                   // default security
                CREATE_NEW,             // CREATE NEW FILW
                FILE_ATTRIBUTE_NORMAL,  // normal file
                NULL);                  // no attr. template
        }

        if (fh == INVALID_HANDLE_VALUE) //test for open/create failure
        {
            return Error::OPEN_FAIL;
        }

        return Error::SUCCESS;
	}


	File::Error File::Close(File::Handle &fh) noexcept
	{
        if (SetFilePointer(fh, 0, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) // Test for failure
        {
            return Error::CLOSE_FAIL;
        }

        if (!CloseHandle(fh)) //test file closed
        {
            return Error::CLOSE_FAIL;
        }

        fh = INVALID_HANDLE_VALUE;

        return Error::SUCCESS;
	}


	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{

        BOOL bErrorFlag = FALSE;
        DWORD dwBytesWritten = 0;

        bErrorFlag = WriteFile(
            fh,                 // open file handle
            buffer,             // start of data to write
            inSize,             // number of bytes to write
            &dwBytesWritten,    // number of bytes that were written
            NULL);              // no overlapped structure

        if (FALSE == bErrorFlag) //test file was not written to
        {
            return Error::WRITE_FAIL;
        }
        else if (dwBytesWritten != inSize) //test write was incomplete
        {
            // This is an error because a synchronous write that results in
            // success (WriteFile returns TRUE) should write all data as
            // requested. This would not necessarily be the case for
            // asynchronous writes.
            return Error::WRITE_FAIL;
        }

        return Error::SUCCESS;
	}


	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{

        DWORD  dwBytesRead = 0;

        if (FALSE == ReadFile(fh, buffer, inSize, &dwBytesRead, 0)) //test file not read
        {
            return Error::READ_FAIL;
        }

        if (dwBytesRead == 0 || dwBytesRead < inSize) //test read was incomplete
        {
            return Error::READ_FAIL;
        }

        return Error::SUCCESS;
	}


	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
        DWORD moveMethod = NULL;
      
        switch (location) 
        {
            case Position::BEGIN:
                moveMethod = FILE_BEGIN;
                break;
            case Position::CURRENT:
                moveMethod = FILE_CURRENT;
                break;
            case Position::END:
                moveMethod = FILE_END;
                break;
            default:
                return Error::SEEK_FAIL;
        }

        DWORD dwPtr;
        dwPtr = SetFilePointer(fh, (LONG)offset, NULL, moveMethod);

        if (dwPtr == INVALID_SET_FILE_POINTER) // Test for failure
        {
            return Error::SEEK_FAIL;
        } 

        return Error::SUCCESS;
	}


	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
        offset = SetFilePointer(fh, 0, NULL, FILE_CURRENT);

        if (offset == INVALID_SET_FILE_POINTER) // Test for failure
        {
            return Error::TELL_FAIL;
        }

		return  Error::SUCCESS;
	}


	File::Error File::Flush(File::Handle fh) noexcept
	{
        if (SetFilePointer(fh, 0, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) // Test for failure
        {
            return Error::FLUSH_FAIL;
        }

        if (FlushFileBuffers(fh) == 0)
        {
            return Error::FLUSH_FAIL;
        }
        
        return  Error::SUCCESS;
	}

}

// --- End of File ---

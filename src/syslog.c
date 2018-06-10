#include <windows.h>

void openlog(char *service, ...)
{
}

void syslog(char *fmt,...)
{
    char date[1024];
    char time[1024];
	char temp[4096];

	SYSTEMTIME st;
	GetLocalTime(&st);

	GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, date, sizeof(date));
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, time, sizeof(time));

	wsprintf(temp, "%s %s %u: ", date, time, GetCurrentProcessId());
	DWORD dwBytesRead = lstrlen(temp);
	
	va_list argptr;
	va_start(argptr, fmt);

	wvsprintf(temp+dwBytesRead, fmt, argptr);

	va_end(argptr);

	lstrcat(temp, "\n");

	HANDLE f = CreateFile("debug.log", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( f != INVALID_HANDLE_VALUE ) {
		DWORD dwBytesWritten = 0;
		DWORD dwPos = SetFilePointer(f, 0, NULL, FILE_END);
		dwBytesRead = lstrlen(temp);
		LockFile(f, dwPos, 0, dwPos+dwBytesRead, 0);
		WriteFile(f, temp, dwBytesRead, &dwBytesWritten, NULL);
		UnlockFile(f, dwPos, 0, dwPos+dwBytesRead, 0);
	}
	CloseHandle(f);
}

void closelog(void)
{
}

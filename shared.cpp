#include "shared.h"
#include "defines.h"

namespace Gspeak 
{
	const TCHAR Shared::clientName[] = TEXT("Local\\GMapO");
	const TCHAR Shared::statusName[] = TEXT("Local\\GMapV");

	HANDLE Shared::hMapFileClients = NULL;
	HANDLE Shared::hMapFileStatus = NULL;

	LPVOID Shared::clientView = NULL;
	LPVOID Shared::statusView = NULL;

	Client* Shared::clients()
	{
		return (Client*)clientView;
	}

	Status* Shared::status()
	{
		return (Status*)statusView;
	}

	int Shared::findClientIndex(int clientID)
	{
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			if (clients()[i].clientID == clientID)
				return i;
		}
		return -1;
	}

	//Not realy save to say though
	bool Shared::gmodOnline(Status* status) {
		return status->tslibV > 0;
	}

	bool Shared::tsOnline(Status* status) {
		return status->gspeakV > 0;
	}

	HMAP_RESULT Shared::openStatus()
	{
		return openOrCreateMap(statusName, &hMapFileStatus, &statusView, sizeof(Status));
	}

	HMAP_RESULT Shared::openClients()
	{
		return openOrCreateMap(clientName, &hMapFileClients, &clientView, sizeof(Client) * PLAYER_MAX);
	}

	HMAP_RESULT Shared::openOrCreateMap(const TCHAR* name, HANDLE* hMapFile, LPVOID* view, unsigned int buf_size)
	{
		//open
		*hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, name);
		if (*hMapFile == NULL)
		{
			int code = GetLastError();
			SetLastError(code);

			//not found => create
			if (code == 2)
			{
				*hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, buf_size, name);
				if (*hMapFile == NULL)
					return HMAP_RESULT::CREATION_FAILED;
			}
			else if (code == 5)
				return HMAP_RESULT::ACCESS_DENIED;
			else
				return HMAP_RESULT::UNEXPECTED_ERROR;
		}

		//view
		*view = MapViewOfFile(*hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
		if (*view == NULL)
		{
			closeMap(hMapFile, view);
			return HMAP_RESULT::VIEW_FAILED;
		}

		return HMAP_RESULT::SUCCESS;
	}

	void Shared::closeStatus()
	{
		closeMap(&hMapFileStatus, &statusView);
	}

	void Shared::closeClients()
	{
		closeMap(&hMapFileClients, &clientView);
	}

	void Shared::closeMap(HANDLE* hMapFile, LPVOID* view)
	{
		if (*view != NULL)
		{
			UnmapViewOfFile(*view);
			*view = NULL;
		}
		if (*hMapFile != NULL)
		{
			CloseHandle(*hMapFile);
			*hMapFile = NULL;
		}
	}
}
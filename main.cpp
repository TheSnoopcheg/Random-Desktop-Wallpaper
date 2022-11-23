#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::string GetPathWallpaper();

int main() {
	std::vector<fs::path> files;
	std::string path;
	std::ifstream in("path.txt");
	if (in.is_open())
	{
		getline(in, path);
	}
	in.close();
	try {
		for (const auto& entry : fs::directory_iterator(path))
			files.push_back(entry.path());
	}
	catch(...) {
		MessageBoxA(GetForegroundWindow(), "Incorrect path", "RDI", MB_OK);
	}
	srand(time(NULL));
	int a = rand() % files.size();
	std::string desktopPath = files[a].string();
	std::string currentWallPath = GetPathWallpaper();
	while(true) {
		if (desktopPath == currentWallPath) {
			a = rand() % files.size();
			desktopPath = files[a].string();
			continue;
		}
		else {
			SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)desktopPath.c_str(), SPIF_UPDATEINIFILE);
			break;
		}
	}
	return 0;
}

std::string GetPathWallpaper() {
	char path[1024];
	DWORD sz = 1024;
	RegGetValueA(
		HKEY_CURRENT_USER,
		"Control Panel\\Desktop",
		"WallPaper",
		RRF_RT_ANY | RRF_SUBKEY_WOW6464KEY,
		NULL,
		(LPDWORD)path,
		&sz
	);
	return path;
}
#include<Windows.h>
#include <mscoree.h>
#include <stdio.h>
#include <metahost.h>
#include <comdef.h>
#pragma comment(lib, "mscoree.lib")

extern "C" __declspec(dllexport) void bootstrapper_load_assembly(
	const wchar_t* assembly_path,
	const wchar_t* type_name,
	const wchar_t* method_name
) {
	ICLRMetaHost* metaHost = NULL;
	IEnumUnknown* runtime = NULL;
	ICLRRuntimeInfo* runtimeInfo = NULL;
	ICLRRuntimeHost* runtimeHost = NULL;
	IUnknown* enumRuntime = NULL;
	LPWSTR frameworkName = NULL;
	DWORD bytes = 2048, result = 0;
	HRESULT hr;

	printf("Bootlaoder: CLR via native code....\n\n");

	if (CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&metaHost) != S_OK) {
		printf("Bootloader: [x] Error: CLRCreateInstance(..)\n");
		return;
	}

	if (metaHost->EnumerateInstalledRuntimes(&runtime) != S_OK) {
		printf("Bootloader: [x] Error: EnumerateInstalledRuntimes(..)\n");
		return;
	}

	frameworkName = (LPWSTR)LocalAlloc(LPTR, 2048);
	if (frameworkName == NULL) {
		printf("Bootloader: [x] Error: malloc could not allocate\n");
		return;
	}

	// Enumerate through runtimes and show supported frameworks
	while (runtime->Next(1, &enumRuntime, 0) == S_OK) {
		if (enumRuntime->QueryInterface<ICLRRuntimeInfo>(&runtimeInfo) == S_OK) {
			if (runtimeInfo != NULL) {
				runtimeInfo->GetVersionString(frameworkName, &bytes);
				wprintf(L"Bootloader: [*] Supported Framework: %s\n", frameworkName);
			}
		}
	}

	// For demo, we just use the last supported runtime
	if (runtimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&runtimeHost) != S_OK) {
		printf("Bootloader: [x] ..GetInterface(CLSID_CLRRuntimeHost...) failed\n");
		return;
	}

	if (runtimeHost == NULL || bytes == 0) {
		wprintf(L"Bootloader: [*] Using runtime: %s\n", frameworkName);
	}

	// Start runtime, and load our assembly
	runtimeHost->Start();

	printf("Bootloader: [*] ======= Calling .NET Code =======\n\n");
	HRESULT response = runtimeHost->ExecuteInDefaultAppDomain(
		assembly_path,
		type_name,
		method_name,
		L"",
		&result
	);
	if (response != S_OK) {
		printf("Bootloader: [x] Error: ExecuteInDefaultAppDomain(..) failed with: %X\n", response);
		_com_error err(response);
		wprintf(L"Error Message: %ls\n", err.ErrorMessage());
		return;
	}
	printf("Bootloader: [*] ======= Done =======\n");
	return;
}

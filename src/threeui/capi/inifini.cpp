#include <threeui/threeui.h>

extern "C" {
bool threeuiInit(uint32_t abiVersion) {
	if(abiVersion != THREEUI_ABI_VERSION)
		return false;

	// do something useful here? if we have to?
	// or funnel to the c++ way of doing so
	return true;
}

void threeuiFini() {
	return;
}
}
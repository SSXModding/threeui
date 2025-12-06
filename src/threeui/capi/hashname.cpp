#include <threeui/threeui.h>

#include <threeui/utils/hashname.hpp>

extern "C" {
uint32_t threeuiGetHashValue32(const char* pszStr) {
	return threeui::utils::getHashValue32(pszStr);
}
}
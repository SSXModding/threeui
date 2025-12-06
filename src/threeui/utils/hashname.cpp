#include <threeui/utils/hashname.hpp>

namespace threeui::utils {

	class tHashName32 {
		u32 hash;

	   public:
		void hashValue(const char* pszIn) {
			u32 h = 0;
			u32 high = 0;
			while(*pszIn) {
				h = (h << 4) + *pszIn++;
				high = h & 0xf0'00'00'00;

				if(high) {
					h ^= high >> 23;
				}

				h &= ~high;
			}

			hash = h;
		}

		u32 getHashValue() const {
			return hash;
		}
	};

	u32 getHashValue32(const char* pszString) {
		tHashName32 hashname;
		hashname.hashValue(pszString);
		return hashname.getHashValue();
	}
} // namespace threeui::utils
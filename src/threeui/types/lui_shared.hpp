#pragma once
#include <threeui/types.hpp>
#include "mco/base_types.hpp"

namespace threeui::types::lui {
	/// A simple block array.
	template <class T>
	struct BlockArray {
		u32 elemCount;

		T* GetBlockPtr() {
			return reinterpret_cast<T*>(this + 1);
		}
	};

    struct tARGB {
        u8 a;
        u8 r;
        u8 g;
        u8 b;
    };

    mcoAssertSize(tARGB, 0x4);
} // namespace threeui::types::lui
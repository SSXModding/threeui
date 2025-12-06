#pragma once
#include <mco/base_types.hpp>
#include <threeui/types.hpp>
#include "../utils/offset_ptr.hpp"
#include "lui_shared.hpp"

namespace threeui::types::lui {

	struct AnimationBlockEntry;
	struct ScreenBlockEntry;
	struct TextureBlockEntry;
	struct FontBlockEntry;

	struct Header {
		u32 magic;
		f32 cookie; // 3.9

		utils::OffsetPtr<BlockArray<AnimationBlockEntry>> animationBlockOffset;
		utils::OffsetPtr<BlockArray<ScreenBlockEntry>> screenBlockOffset;
		utils::OffsetPtr<BlockArray<TextureBlockEntry>> textureBlockOffset;
		utils::OffsetPtr<BlockArray<FontBlockEntry>> fontBlockOffset;

		constexpr bool valid() {
			if(magic != 0x00465949)
				return false;

			// Cranky but this makes it not float math which could fall apart.
			return std::bit_cast<u32>(cookie) == 0x4079999a;
		}

		auto animationBlock() {
			return animationBlockOffset(this);
		}

		auto screenBlock() {
			return screenBlockOffset(this);
		}

		auto textureBlock() {
			return textureBlockOffset(this);
		}

		auto fontBlock() {
			return fontBlockOffset(this);
		}
	};

	struct AnimationBlockEntry {
		u32 unk;
		u32 unk2;
		u32 hashName;
		u32 animDataSize;

		std::span<u8> getAnimationData() {
			auto* pAnimDataStart = reinterpret_cast<u8*>(this + 1);
			return { pAnimDataStart, animDataSize - sizeof(*this) };
		}

		AnimationBlockEntry* next() {
			return reinterpret_cast<AnimationBlockEntry*>(reinterpret_cast<u8*>(this + 1) + animDataSize - sizeof(*this));
		}
	};

	struct ScreenBlockEntry {
		u32 hashName;
		u32 screenDataRelativeOffset;

		u8* getRefpackData(Header* pHeader) {
			return reinterpret_cast<u8*>(pHeader->screenBlock()) + screenDataRelativeOffset;
		}
	};

	struct TextureBlockEntry {
		u32 hashName;

		u8 pad; // seems to be unused
		u8 textureId;
		u8 pad2; // same here
		u8 pad3; // same here

		// rect of where in textures[textureId] (the texture sheet)
		// the specicific "texture object" is.
		f32 x;
		f32 y;
		f32 w;
		f32 h;
	};

	struct FontBlockEntry {
		u32 fontNameHash;
		u32 fontNameLength;

		const std::string_view getFontName() {
			return { reinterpret_cast<const char*>(this + 1), fontNameLength };
		}

		FontBlockEntry* next() {
			return reinterpret_cast<FontBlockEntry*>(reinterpret_cast<u8*>(this + 1) + fontNameLength);
		}
	};

	mcoAssertSize(Header, 0x18);
	mcoAssertSize(AnimationBlockEntry, 0x10);
	mcoAssertSize(ScreenBlockEntry, 0x8);
	mcoAssertSize(TextureBlockEntry, 0x18);
	mcoAssertSize(FontBlockEntry, 0x8);
} // namespace threeui::types::lui
// SPDX-License-Identifier: MIT

#pragma once
#include <bit>
#include <span>
#include <threeui/types.hpp>
#include <type_traits>

namespace threeui::utils {

	namespace detail {

		template <class NativeT, class OffsetType>
		constexpr NativeT* createPtrFromAddend(void* pBase, OffsetType offsetAddend) noexcept {
			return std::bit_cast<NativeT*>(static_cast<u8*>(pBase) + offsetAddend);
		}

	} // namespace detail

	/// An "auto-resolving" offset pointer type.
	/// This is designed to allow resolving offsets in data for
	/// games written before 64-bit pointers were common/used at all.
	/// This allows looking up data a lot easier :)
	///
	/// [NativeT] is the type of data this would point to
	/// [OffsetType] is the type of data the "pointer" is repressented as
	template <class NativeT, class OffsetType = u32>
	struct OffsetPtr final {
		using Type = std::remove_cvref_t<NativeT>;
		using Pointer = Type*;
		using ConstPointer = const Type*;

		/// Set the offset. Duh!
		constexpr void set(OffsetType newOffset) noexcept {
			rawOffset = newOffset;
		}

		[[nodiscard]] constexpr OffsetType raw() const noexcept {
			return rawOffset;
		}

		[[nodiscard]] constexpr Pointer operator()(void* baseAddr) const noexcept {
			// While yucky, it should show problem areas which aren't checking things
			// immediately rather than read invalid data that might do much worse.
			if(rawOffset == 0)
				return nullptr;

			return detail::createPtrFromAddend<Type>(baseAddr, rawOffset);
		}

        /// Returns a offset pointer casted to the new type
		template <class NativeU>
		constexpr OffsetPtr<NativeU, OffsetType> cast() {
			OffsetPtr<NativeU, OffsetType> newPtr;
            newPtr.set(rawOffset);
            return newPtr;
		}

	   private:
		OffsetType rawOffset;
	};

	/// Like OffsetPtr<T> but for arrays of data.
	template <class NativeT, class OffsetType = u32>
	struct OffsetArrayPtr final {
		using Type = std::remove_cvref_t<NativeT>;
		using Pointer = Type*;
		using ConstPointer = const Type*;

		using Span = std::span<NativeT>;

		/// Set the offset. Duh!
		constexpr void Set(OffsetType newOffset) noexcept {
			rawOffset = newOffset;
		}

		[[nodiscard]] constexpr OffsetType Raw() const noexcept {
			return rawOffset;
		}

		[[nodiscard]] constexpr Span operator()(void* baseAddr, OffsetType length) const noexcept {
			// While yucky, it should show problem areas which aren't checking things
			// immediately rather than read invalid data that might do much worse.
			if(rawOffset == 0 || length == 0)
				return {};

			return { detail::createPtrFromAddend<Type>(baseAddr, rawOffset), length };
		}

	   private:
		OffsetType rawOffset;
	};

    // MAke 
    static_assert(sizeof(OffsetPtr<void*, u32>) == sizeof(u32), "OffsetPtr<_, u32> doesn't match size. Fix it");
    static_assert(sizeof(OffsetArrayPtr<void*, u32>) == sizeof(u32), "OffsetArrayPtr<_, u32> doesn't match size. Fix it");

} // namespace threeui::utils
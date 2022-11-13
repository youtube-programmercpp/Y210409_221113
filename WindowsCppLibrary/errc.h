// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include <system_error>
namespace WindowsCppLibrary {
	const std::error_category& LSTATUS_category() noexcept;
	namespace errc {
		enum class LSTATUS;
		std::error_code make_error_code(LSTATUS e) noexcept;
	}
}
template<>struct std::is_error_code_enum<WindowsCppLibrary::errc::LSTATUS> : public true_type {};

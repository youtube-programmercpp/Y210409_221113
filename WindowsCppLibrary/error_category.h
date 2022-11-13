// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include <system_error>
namespace WindowsCppLibrary {
	namespace error_category {
		class LSTATUS : public std::error_category {
		public:
			const char* name() const noexcept override;
			std::string message(int _Errval) const override;
		};
	}
}

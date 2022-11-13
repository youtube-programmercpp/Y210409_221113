// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "pch.h"
#include "errc.h"
#include "error_category.h"

const std::error_category& WindowsCppLibrary::LSTATUS_category() noexcept
{
	static const WindowsCppLibrary::error_category::LSTATUS singleton;
	return singleton;
}
std::error_code WindowsCppLibrary::errc::make_error_code(LSTATUS e) noexcept
{
	return std::error_code(static_cast<int>(e), LSTATUS_category());
}
